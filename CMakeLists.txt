cmake_minimum_required(VERSION 3.6)
project(contra)

# general configurations
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c99 -Wall -pedantic")
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(bin_dir ${CMAKE_CURRENT_BINARY_DIR})
set(test_deps contra cmocka)
set(test_headers_dir ${bin_dir}/test-headers)
include_directories(${root_dir}/include ${bin_dir} deps)

# library
set(src_lib
    src/http.c
    src/path.c
)
add_library(contra SHARED ${src_lib})
install(TARGETS contra LIBRARY DESTINATION lib)
install(FILES include/contra.h DESTINATION include)
install(DIRECTORY include/contra DESTINATION include)

if(NOT (${CMAKE_BUILD_TYPE} MATCHES Release))
    # test executable
    add_custom_target(test-pre
        COMMAND mkdir -p ${bin_dir}/inline-tests
        COMMAND mkdir -p ${bin_dir}/test-headers)
    # list inline-tests as by-products of this target
    add_custom_target(test-inline
        COMMAND ROOT_DIR=${root_dir} python ${root_dir}/script/gen-inline-tests.py ${root_dir}/src/*.c
        WORKING_DIRECTORY ${bin_dir}/inline-tests
        BYPRODUCTS ${bin_dir}/inline-tests/src_path.c)
    add_custom_target(test-hdrs
        COMMAND python ${root_dir}/script/gen-test-headers.py --input ${root_dir}/test/*.c ${bin_dir}/inline-tests/*.c --main ${root_dir}/test/main.h.in --namespace contra
        WORKING_DIRECTORY ${bin_dir}/test-headers)
    set(test_src_exe
        test/is.c
        test/main.c
        ${bin_dir}/inline-tests/src_path.c)
    add_executable(test-contra EXCLUDE_FROM_ALL ${test_src_exe})
    target_include_directories(test-contra PRIVATE /usr/local/include) # TODO: /usr/local/
    target_link_directories(test-contra PRIVATE /usr/local/lib) # TODO: /usr/local/
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
endif()
