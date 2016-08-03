#!/usr/bin/env bash
#
# Run all the test scripts
#

tests=(
    "assert/run.sh"
)
exit_code=0

for t in "${tests[@]}"
do
    "${TEST_DIR:-$(dirname "${BASH_SOURCE[0]}")}/${t}"
    if [[ $? -ne 0 ]] ; then exit_code=1 ; fi
done
exit ${exit_code}
