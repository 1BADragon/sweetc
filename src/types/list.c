#include <assert.h>
#include <stdbool.h>

#include <sc/containers/list.h>
#include <sc/containers/raw/list.h>
#include <sc/hooks.h>
#include <sc/traits/cmp.h>

struct sc_list {
    struct sc_object hdr;
    size_t len;
    list_head_t list;
};

struct sc_list_node {
    list_head_t list;
    struct sc_object *obj;
};

struct sc_list_iter {
    struct sc_object hdr;
    sc_list_t *parent;
    struct sc_list_node *node;
    bool forward;
};

static void sc_list_free(sc_list_t *lst);

static struct sc_trait_object sc_list_object_trait = {
    .free_f = (sc_free_f)sc_list_free,
};

static struct sc_type sc_list_type = {
    .name = "sc::list",
    .triats = {
        [SC_TRAIT_OBJECT] = &sc_list_object_trait,
    },
};

static struct sc_trait_object sc_list_iter_object_trait = {
    .free_f = (sc_free_f)sc_free,
};

static struct sc_type sc_list_iter_type = {
    .name = "sc::list::iter",
    .triats = {
        [SC_TRAIT_OBJECT] = &sc_list_iter_object_trait,
    },
};

sc_list_t *sc_list_init(void)
{
    sc_list_t *new_list = NULL;

    new_list = sc_zalloc(sizeof(sc_list_t));
    if (NULL == new_list) {
        return NULL;
    }

    new_list->hdr.type = &sc_list_type;
    new_list->len = 0;
    INIT_LIST_HEAD(&new_list->list);

    return new_list;
}

int sc_list_push_front(sc_list_t *lst, struct sc_object *obj)
{
    struct sc_list_node *node = NULL;

    assert(lst);
    assert(obj);

    node = sc_zalloc(sizeof(struct sc_list_node));

    if (NULL == node) {
        return -1;
    }

    node->obj = obj;
    list_add(&node->list, &lst->list);

    lst->len++;
    return 0;
}

int sc_list_push_back(sc_list_t *lst, struct sc_object *obj)
{
    struct sc_list_node *node = NULL;

    assert(lst);
    assert(obj);

    node = sc_zalloc(sizeof(struct sc_list_node));

    if (NULL == node) {
        return -1;
    }

    node->obj = obj;
    list_add_tail(&node->list, &lst->list);

    lst->len++;
    return 0;
}

int sc_list_push_sorted(sc_list_t *lst, struct sc_object *obj)
{
    struct sc_list_node *node = NULL;
    struct sc_trait_cmp *cmp = NULL;
    struct sc_list_node *curr = NULL;
    bool inserted = false;

    assert(lst);
    assert(obj);

    cmp = sc_trait_cmp(obj);

    assert(cmp);

    node = sc_zalloc(sizeof(struct sc_list_node));

    if (NULL == node) {
        return -1;
    }

    node->obj = obj;

    list_for_each_entry (curr, &lst->list, list) {
        if (sc_object_cmp(obj, curr->obj) < 0) {
            list_add_tail(&node->list, &curr->list);
            inserted = true;
            break;
        }
    }

    if (!inserted) {
        list_add_tail(&node->list, &lst->list);
    }

    lst->len++;
    return 0;
}

struct sc_object *sc_list_pop_front(sc_list_t *lst)
{
    struct sc_list_node *node = NULL;
    struct sc_object *obj = NULL;

    assert(lst);

    node = list_first_entry_or_null(&lst->list, struct sc_list_node, list);

    if (NULL == node) {
        return NULL;
    }

    obj = node->obj;

    list_del(&node->list);
    sc_free(node);

    lst->len--;
    return obj;
}

struct sc_object *sc_list_pop_back(sc_list_t *lst)
{
    struct sc_list_node *node = NULL;
    struct sc_object *obj = NULL;

    assert(lst);

    if (list_empty(&lst->list)) {
        return NULL;
    }

    node = list_last_entry(&lst->list, struct sc_list_node, list);

    obj = node->obj;

    list_del(&node->list);
    sc_free(node);

    lst->len--;
    return obj;
}

struct sc_object *sc_list_front(sc_list_t *lst)
{
    struct sc_list_node *node = NULL;

    assert(lst);

    node = list_first_entry_or_null(&lst->list, struct sc_list_node, list);

    if (NULL == node) {
        return NULL;
    }

    return node->obj;
}

struct sc_object *sc_list_back(sc_list_t *lst)
{
    struct sc_list_node *node = NULL;

    assert(lst);

    if (list_empty(&lst->list)) {
        return NULL;
    }

    node = list_last_entry(&lst->list, struct sc_list_node, list);

    return node->obj;
}

size_t sc_list_len(sc_list_t *lst)
{
    assert(lst);

    return lst->len;
}

int sc_list_walk(sc_list_t *lst, sc_walk_f cb_func, void *cb_data)
{
    int rc = 0;
    struct sc_list_node *node = NULL;

    assert(lst);
    assert(cb_func);

    list_for_each_entry (node, &lst->list, list) {
        rc = cb_func(lst, node->obj, cb_data);

        if (rc != 0) {
            break;
        }
    }

    return rc;
}

sc_list_iter_t *sc_list_begin(sc_list_t *lst)
{
    sc_list_iter_t *iter = NULL;

    assert(lst);

    if (list_empty(&lst->list)) {
        return NULL;
    }

    iter = sc_zalloc(sizeof(sc_list_iter_t));

    if (NULL == iter) {
        return NULL;
    }

    iter->hdr.type = &sc_list_iter_type;
    iter->parent = lst;
    iter->node = list_first_entry(&lst->list, struct sc_list_node, list);
    iter->forward = true;

    return iter;
}

sc_list_iter_t *sc_list_rbegin(sc_list_t *lst)
{
    sc_list_iter_t *iter = NULL;

    assert(lst);

    if (list_empty(&lst->list)) {
        return NULL;
    }

    iter = sc_zalloc(sizeof(sc_list_iter_t));

    if (NULL == iter) {
        return NULL;
    }

    iter->hdr.type = &sc_list_iter_type;
    iter->parent = lst;
    iter->node = list_last_entry(&lst->list, struct sc_list_node, list);
    iter->forward = false;

    return iter;
}

sc_list_iter_t *sc_list_next(sc_list_t *lst, sc_list_iter_t *iter)
{
    assert(lst);
    assert(iter);
    assert(iter->parent == lst);

    if (iter->forward) {
        if (list_is_last(&iter->node->list, &lst->list)) {
            goto end_of_list;
        }

        iter->node = list_next_entry(iter->node, list);
    } else {
        if (list_is_first(&iter->node->list, &lst->list)) {
            goto end_of_list;
        }

        iter->node = list_prev_entry(iter->node, list);
    }

    return iter;
end_of_list:
    sc_object_free(iter);
    return NULL;
}

struct sc_object *sc_list_iter_data(sc_list_iter_t *iter)
{
    assert(iter);

    return iter->node->obj;
}

sc_list_iter_t *sc_list_del_iter(sc_list_t *lst, sc_list_iter_t *iter)
{
    struct sc_object *obj = NULL;

    assert(lst);
    assert(iter);
    assert(iter->parent == lst);

    obj = sc_list_pop_iter(lst, &iter);
    sc_object_free(obj);

    return iter;
}

struct sc_object *sc_list_pop_iter(sc_list_t *lst, sc_list_iter_t **iter)
{
    struct sc_list_node *node = NULL;
    struct sc_object *obj = NULL;

    assert(lst);
    assert(iter);
    assert(*iter);
    assert((*iter)->parent == lst);

    node = (*iter)->node;

    *iter = sc_list_next(lst, *iter);

    list_del(&node->list);
    obj = node->obj;
    sc_free(node);

    return obj;
}

static void sc_list_free(sc_list_t *lst)
{
    struct sc_list_node *at;
    struct sc_list_node *_safe;

    list_for_each_entry_safe (at, _safe, &lst->list, list) {
        list_del(&at->list);

        sc_object_free(at->obj);
        sc_free(at);
    }

    sc_free(lst);
}
