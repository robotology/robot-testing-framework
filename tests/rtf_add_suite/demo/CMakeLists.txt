# Copyright (C) 2017 Istituto Italiano di Tecnologia (IIT)
# Authors: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT


set(RTF_ADD_SUITE_DEBUG TRUE)
cmake_minimum_required(VERSION 3.5)
project(rtf_add_suite_demo)
enable_testing()

find_package(RTF REQUIRED)

rtf_add_plugin(demo_fixturemanager SOURCES demo_fixturemanager.cpp)
target_link_libraries(demo_fixturemanager RTF::RTF
                                          RTF::RTF_dll)

rtf_add_plugin(demo_testcase SOURCES demo_testcase.cpp)
target_link_libraries(demo_testcase RTF::RTF
                                    RTF::RTF_dll)

rtf_add_suite(NAME demo
              RTF_FIXTURE demo_fixturemanager
              RTF_TEST demo_testcase TYPE dll
              WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
              WEB_REPORTER
              WEB_PORT 2020)
