cmake_minimum_required(VERSION 3.6)
project(contra)

# general configurations
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c99 -Wall -pedantic")
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(bin_dir ${CMAKE_CURRENT_BINARY_DIR})
set(deps )
set(test_deps contra ${deps} cmocka)
set(test_headers_dir ${bin_dir}/test-headers)
include_directories(${root_dir}/include ${bin_dir} deps)

# library
set(src_lib
    deps/sds/sds.c
    src/path/index.c)
add_library(contra SHARED ${src_lib})

# test executable
add_custom_target(test-pre
    COMMAND mkdir -p ${bin_dir}/inline-tests
    COMMAND mkdir -p ${bin_dir}/test-headers)
# list inline-tests as by-products of this target
add_custom_target(test-inline
    COMMAND ROOT_DIR=${root_dir} python ${root_dir}/script/gen-inline-tests.py ${root_dir}/src/**/*.c
    WORKING_DIRECTORY ${bin_dir}/inline-tests
    BYPRODUCTS ${bin_dir}/inline-tests/src_path_index.c)
add_custom_target(test-hdrs
    COMMAND python ${root_dir}/script/gen-test-headers.py --input ${root_dir}/test/*.c ${bin_dir}/inline-tests/*.c --main ${root_dir}/test/main.h.in --namespace contra
    WORKING_DIRECTORY ${bin_dir}/test-headers)
set(test_src_exe
    test/is.c
    test/main.c
    ${bin_dir}/inline-tests/src_path_index.c)
add_executable(test-contra EXCLUDE_FROM_ALL ${test_src_exe})
target_link_libraries(test-contra ${test_deps})
add_dependencies(test-contra contra test-hdrs)
add_dependencies(test-inline test-pre)
add_dependencies(test-hdrs test-pre test-inline)

# task: running tests
add_custom_target(run-tests
    COMMAND TEST_DIR=${root_dir}/test ${bin_dir}/test-contra
    COMMAND TEST_DIR=${root_dir}/test ${root_dir}/test/run.sh
    WORKING_DIR ${root_dir})
add_dependencies(run-tests test-contra)
