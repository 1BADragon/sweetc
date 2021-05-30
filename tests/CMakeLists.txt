macro(create_test TEST_NAME)
    add_executable(${TEST_NAME} ${ARGN})
    target_link_libraries(${TEST_NAME} sweetc sc_testing)
    add_test(${TEST_NAME} ${TEST_NAME})
endmacro()

create_test(list-test list.c)
create_test(tree-test tree.c)
