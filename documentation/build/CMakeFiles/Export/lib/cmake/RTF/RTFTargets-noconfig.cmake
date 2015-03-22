#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "RTF::RTF" for configuration ""
set_property(TARGET RTF::RTF APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(RTF::RTF PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libRTF.so"
  IMPORTED_SONAME_NOCONFIG "libRTF.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS RTF::RTF )
list(APPEND _IMPORT_CHECK_FILES_FOR_RTF::RTF "${_IMPORT_PREFIX}/lib/libRTF.so" )

# Import target "RTF::RTF_dll" for configuration ""
set_property(TARGET RTF::RTF_dll APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(RTF::RTF_dll PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "dl"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libRTF_dll.so"
  IMPORTED_SONAME_NOCONFIG "libRTF_dll.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS RTF::RTF_dll )
list(APPEND _IMPORT_CHECK_FILES_FOR_RTF::RTF_dll "${_IMPORT_PREFIX}/lib/libRTF_dll.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
