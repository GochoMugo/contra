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

    # build cmocka
    include_directories(deps/cmocka/include)
    link_directories(deps/cmocka/build/src)
    add_custom_target(build-cmocka
        COMMAND mkdir -p build && cd build && cmake .. && make
        WORKING_DIRECTORY ${root_dir}/deps/cmocka
    )

    add_executable(http.test EXCLUDE_FROM_ALL test/http.test.c)
    add_dependencies(http.test build-cmocka)

    add_executable(is.test EXCLUDE_FROM_ALL test/is.test.c)
    add_dependencies(is.test build-cmocka)

    add_executable(math.test EXCLUDE_FROM_ALL test/math.test.c)
    add_dependencies(math.test build-cmocka)

    add_executable(path.test EXCLUDE_FROM_ALL test/path.test.c)
    add_dependencies(path.test build-cmocka)

    add_executable(string.test EXCLUDE_FROM_ALL test/string.test.c)
    add_dependencies(string.test build-cmocka)

    # task: running tests
    add_custom_target(tests
        COMMAND ${root_dir}/test/assert/assert.test.sh
        COMMAND ${bin_dir}/http.test
        COMMAND ${bin_dir}/is.test
        COMMAND ${bin_dir}/math.test
        COMMAND ${bin_dir}/path.test
        COMMAND ${bin_dir}/string.test
        WORKING_DIR ${root_dir})
    add_dependencies(tests http.test is.test math.test path.test string.test)
endif()
