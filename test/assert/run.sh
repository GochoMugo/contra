#!/usr/bin/env bash

# directory holding the assert tests (not the upper `test/` directory)
testdir="$(dirname "${BASH_SOURCE[0]}")"

# repository's directory
rootdir="$(dirname "${testdir}")"
rootdir="$(dirname "${rootdir}")"

tests=(
    "ok(null)"
    "ok(0)"
    "int_eq"
    "int_ne"
    "int_lt"
    "int_gt"
    "int_gte"
    "str_eq"
    "str_ne"
    "str_empty"
    "str_not_empty"
    "null"
    "not_null"
)

# exit code
exit_code=0

for t in "${tests[@]}"
do
    report="$("${rootdir}"/tools/crun/crun.sh "${testdir}/run.c" "${t}" 2>&1)"
    grep -q -E 'Assertion failed at' <<< "${report}" || {
        echo "[FAILED] contra_assert_${t}"
        echo
        echo "${report:-"(no-output)"}"
        echo
        exit_code=1
    }
    echo "[OK] contra_assert_${t}"
done
exit ${exit_code}
