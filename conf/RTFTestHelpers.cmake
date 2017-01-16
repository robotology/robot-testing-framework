# RTFTestHelpers
# -------------------------
#
# Helpers functions for creating tests 

#=============================================================================
# Copyright 2017 Ali Paikan <ali.paikan@gmail.com>
#

include(CTest)

macro(ENABLE_RTF_TESTS)    
    get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)
    get_property(RTF_LIBS GLOBAL PROPERTY RTF_LIBS)

    include_directories(${CMAKE_SOURCE_DIR}
                        ${RTF_TREE_INCLUDE_DIRS})

    set(TESTRUNNER_PATH ${CMAKE_BINARY_DIR}/bin/testrunner)
    # set the output plugin directory to collect all tests
    set(TEST_TARGET_PATH ${CMAKE_BINARY_DIR}/bin/tests)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TEST_TARGET_PATH})
    set(CMAKE_SHARED_MODULE_PREFIX "")

    # running test units
    add_test(NAME tests
         COMMAND ${TESTRUNNER_PATH} -v --tests ${TEST_TARGET_PATH}
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endmacro()


macro(ADD_RTF_CPPTEST TESTNAME SOURCES)
    add_library(${TESTNAME} MODULE ${SOURCES})
    target_link_libraries(${TESTNAME} ${RTF_LIBS})
endmacro()

macro(ADD_RTF_LUATEST SOURCE)
    configure_file(${SOURCE} ${TEST_TARGET_PATH}/${SOURCE} COPYONLY)
endmacro()

