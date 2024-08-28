#!/usr/bin/env bash

# directory holding the assert tests (not the upper `test/` directory)
testdir="$(dirname "${BASH_SOURCE[0]}")"

# repository's directory
rootdir="$(dirname "${testdir}")"
rootdir="$(dirname "${rootdir}")"

tests=(
    "ok(null)|Expected the expression to be truthy"
    "ok(0)|Expected the expression to be truthy"
    "int_eq(0,1)|Expected: 0 == 1"
    "int_ne(0,0)|Expected: 0 != 0"
    "int_lt(1,0)|Expected: 1 < 0"
    "int_lte(1,0)|Expected: 1 <= 0"
    "int_gt(0,1)|Expected: 0 > 1"
    "int_gte(0,1)|Expected: 0 >= 1"
    "str_eq(abc,123)|Expected: abc == 123"
    "str_ne(abc,abc)|Expected: abc != abc"
    'str_empty(abc)|Expected: abc == \"\"'
    "str_not_empty('')|Expected:  != \"\""
    "null('')|Expected: .+ == NULL"
    "not_null(NULL)|Expected: \(nil\) != NULL"
)

# exit code
exit_code=0

for t in "${tests[@]}"
do
    name="$(echo "${t}"|cut -d '|' -f 1)"
    expected="$(echo "${t}"|cut -d '|' -f 2)"
    report="$("${rootdir}"/deps/crun/crun.sh "${testdir}/assert.test.c" "${name}" 2>&1)"
    grep -q -E 'Assertion failed at' <<< "${report}" && grep -q -E "${expected}" <<< "${report}" || {
        echo "[FAILED] contra_assert_${name}"
        echo
        echo "${report:-"(no-output)"}"
        echo
        exit_code=1
        continue
    }
    echo "[OK] contra_assert_${name}"
done
exit ${exit_code}
