#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cmocka::cmocka" for configuration ""
set_property(TARGET cmocka::cmocka APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(cmocka::cmocka PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libcmocka.0.7.0.dylib"
  IMPORTED_SONAME_NOCONFIG "@rpath/libcmocka.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS cmocka::cmocka )
list(APPEND _IMPORT_CHECK_FILES_FOR_cmocka::cmocka "${_IMPORT_PREFIX}/lib/libcmocka.0.7.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
