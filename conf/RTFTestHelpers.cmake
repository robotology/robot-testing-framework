# RTFTestHelpers
# -------------------------
#
# Helpers functions for creating tests

#=============================================================================
# Copyright 2017 Ali Paikan <ali.paikan@gmail.com>
#

include(CTest)
include(CMakeParseArguments)

macro(ENABLE_RTF_TESTS)
    get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)
    #get_property(RTF_LIBS GLOBAL PROPERTY RTF_LIBS)
    include_directories(${CMAKE_SOURCE_DIR}
                        ${RTF_TREE_INCLUDE_DIRS})
    set(TESTRUNNER_PATH ${CMAKE_BINARY_DIR}/bin/testrunner)
    # set the output plugin directory to collect all tests
    set(TEST_TARGET_PATH ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TEST_TARGET_PATH})
    set(CMAKE_SHARED_MODULE_PREFIX "")
    # running test units
    #add_test(NAME tests
    #     COMMAND ${TESTRUNNER_PATH} -v --tests ${TEST_TARGET_PATH}
    #     WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endmacro()

function(ADD_CPPTEST)
    # set(options )
    set(oneValueArgs NAME PARAM)
    set(multiValueArgs SRCS LIBS)
    cmake_parse_arguments(ADD_CPPTEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(TEST_LIBS RTF)
    if(ENABLE_PLUGIN)
        set(TEST_LIBS ${TEST_LIBS} RTF_dll)
    endif()
    if(ENABLE_LUA_PLUGIN)
        set(TEST_LIBS ${TEST_LIBS} RTF_lua)
    endif()
    if(ENABLE_PYTHON_PLUGIN)
        set(TEST_LIBS ${TEST_LIBS} RTF_python)
    endif()

    if(ENABLE_RUBY_PLUGIN)
        set(TEST_LIBS ${TEST_LIBS} RTF_ruby)
    endif()

    set(TEST_LIBS ${TEST_LIBS} ${ADD_CPPTEST_LIBS})

    add_executable(${ADD_CPPTEST_NAME} ${ADD_CPPTEST_SRCS})
    target_link_libraries(${ADD_CPPTEST_NAME} ${TEST_LIBS})
    set_target_properties(${ADD_CPPTEST_NAME}
                          PROPERTIES
                            RUNTIME_OUTPUT_DIRECTORY "${TEST_TARGET_PATH}")
    # adding test unit
     add_test(NAME ${ADD_CPPTEST_NAME}
              WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
              COMMAND ${ADD_CPPTEST_NAME} ${ADD_CPPTEST_PARAM})
 endfunction()


function(ADD_RTF_CPPTEST)
    # set(options )
    set(oneValueArgs NAME PARAM ENV)
    set(multiValueArgs SRCS LIBS)
    cmake_parse_arguments(ADD_RTF_CPPTEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(TEST_LIBS RTF RTF_dll)
    if(ENABLE_LUA_PLUGIN)
        set(TEST_LIBS ${TEST_LIBS} RTF_lua)
    endif()
    if(ENABLE_PYTHON_PLUGIN)
        set(TEST_LIBS ${TEST_LIBS} RTF_python)
    endif()

    if(ENABLE_RUBY_PLUGIN)
        set(TEST_LIBS ${TEST_LIBS} RTF_ruby)
    endif()

    set(TEST_LIBS ${TEST_LIBS} ${ADD_RTF_CPPTEST_LIBS})

    add_library(${ADD_RTF_CPPTEST_NAME} MODULE ${ADD_RTF_CPPTEST_SRCS})
    target_link_libraries(${ADD_RTF_CPPTEST_NAME} ${TEST_LIBS})

    # adding test unit
     add_test(NAME ${ADD_RTF_CPPTEST_NAME}
         COMMAND ${TESTRUNNER_PATH} -v --no-output --no-summary -p ${ADD_RTF_CPPTEST_PARAM} -e "${ADD_RTF_CPPTEST_ENV}" --test $<TARGET_FILE:${ADD_RTF_CPPTEST_NAME}>
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()

macro(ADD_RTF_TEST_SCRIPT SOURCE)
    configure_file(${SOURCE} ${TEST_TARGET_PATH}/${SOURCE} COPYONLY)
    # adding test unit
    add_test(NAME ${SOURCE}
         COMMAND ${TESTRUNNER_PATH} -v --no-output --no-summary --test ${TEST_TARGET_PATH}/${SOURCE}
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endmacro()

macro(ADD_RTF_LUATEST SOURCE)
    ADD_RTF_TEST_SCRIPT(${SOURCE})
endmacro()

macro(ADD_RTF_PYTHONTEST SOURCE)
    ADD_RTF_TEST_SCRIPT(${SOURCE})
endmacro()

macro(ADD_RTF_RUBYTEST SOURCE)
    ADD_RTF_TEST_SCRIPT(${SOURCE})
endmacro()
