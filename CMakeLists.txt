cmake_minimum_required(VERSION 3.6)
project(contra)

# general configurations
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c99 -Wall -pedantic")
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(bin_dir ${CMAKE_CURRENT_BINARY_DIR})

# library: libcontra, libcontra_static
set(src_lib
    src/http.c
    src/path.c
    src/string.c
)
include_directories(${root_dir}/include)
link_libraries(curl)
add_library(contra SHARED ${src_lib})
add_library(contra_static STATIC ${src_lib})
install(TARGETS contra contra_static LIBRARY DESTINATION lib)
install(FILES include/contra.h DESTINATION include)
install(DIRECTORY include/contra DESTINATION include)

if(NOT (${CMAKE_BUILD_TYPE} MATCHES Release))
    link_libraries(cmocka contra)

    # cmocka
    include_directories(deps/cmocka/include)
    link_directories(deps/cmocka/build/src)
    add_custom_target(cmocka
        COMMAND mkdir -p build && cd build && cmake .. && make
        WORKING_DIRECTORY ${root_dir}/deps/cmocka
    )

    # task: tests.assert
    add_custom_target(tests.assert COMMAND ${root_dir}/test/assert/assert.test.sh)

    # task: tests.http
    add_executable(http.test EXCLUDE_FROM_ALL test/http.test.c)
    add_dependencies(http.test cmocka)
    add_custom_target(tests.http COMMAND ${bin_dir}/http.test)
    add_dependencies(tests.http http.test)

    # task: tests.is
    add_executable(is.test EXCLUDE_FROM_ALL test/is.test.c)
    add_dependencies(is.test cmocka)
    add_custom_target(tests.is COMMAND ${bin_dir}/is.test)
    add_dependencies(tests.is is.test)

    # task: tests.math
    add_executable(math.test EXCLUDE_FROM_ALL test/math.test.c)
    add_dependencies(math.test cmocka)
    add_custom_target(tests.math COMMAND ${bin_dir}/math.test)
    add_dependencies(tests.math math.test)

    # task: tests.path
    add_executable(path.test EXCLUDE_FROM_ALL test/path.test.c)
    add_dependencies(path.test cmocka)
    add_custom_target(tests.path COMMAND ${bin_dir}/path.test)
    add_dependencies(tests.path path.test)

    # task: tests.string
    add_executable(string.test EXCLUDE_FROM_ALL test/string.test.c)
    add_dependencies(string.test cmocka)
    add_custom_target(tests.string COMMAND ${bin_dir}/string.test)
    add_dependencies(tests.string string.test)

    # task: tests
    add_custom_target(tests)
    add_dependencies(tests
        tests.assert
        tests.http
        tests.is
        tests.math
        tests.path
        tests.string
    )
endif()
