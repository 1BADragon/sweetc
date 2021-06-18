#ifndef _SC_TYPES_LIST_H
#define _SC_TYPES_LIST_H

#include <sc/object/object.h>

struct sc_list;

struct sc_list_iter;

typedef struct sc_list sc_list_t;

typedef struct sc_list_iter sc_list_iter_t;

typedef int (*sc_walk_f)(sc_list_t *, struct sc_object *, void *);

sc_list_t *sc_list_init(void);

int sc_list_push_front(sc_list_t *lst, struct sc_object *obj);

int sc_list_push_back(sc_list_t *lst, struct sc_object *obj);

int sc_list_push_sorted(sc_list_t *lst, struct sc_object *obj);

struct sc_object *sc_list_pop_front(sc_list_t *lst);

struct sc_object *sc_list_pop_back(sc_list_t *lst);

struct sc_object *sc_list_front(sc_list_t *lst);

struct sc_object *sc_list_back(sc_list_t *lst);

size_t sc_list_len(sc_list_t *lst);

int sc_list_walk(sc_list_t *lst, sc_walk_f cb_func, void *cb_data);

sc_list_iter_t *sc_list_begin(sc_list_t *lst);

sc_list_iter_t *sc_list_rbegin(sc_list_t *lst);

sc_list_iter_t *sc_list_next(sc_list_t *lst, sc_list_iter_t *iter);

struct sc_object *sc_list_iter_data(sc_list_iter_t *iter);

sc_list_iter_t *sc_list_del_iter(sc_list_t *lst, sc_list_iter_t *iter);

struct sc_object *sc_list_pop_iter(sc_list_t *lst, sc_list_iter_t **iter);

#endif //_SC_TYPES_LIST_H
