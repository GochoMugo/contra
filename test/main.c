#include <test-headers/main.h>

int main(void) {
    int failed_tests = 0;

    failed_tests += cmocka_run_group_tests_name("path (inline)", tests_contra_src_path, NULL, NULL);
    failed_tests += cmocka_run_group_tests_name("is", tests_contra_is, NULL, NULL);

    return failed_tests > 0 ? 1 : 0;
}
