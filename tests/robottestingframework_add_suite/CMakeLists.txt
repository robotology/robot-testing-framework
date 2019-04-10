# Robot Testing Framework
#
# Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA


# Prepare 'build_generator', 'build_options' and 'build_module_path' variables
# for tests in subdirectories
set(build_generator --build-generator "${CMAKE_GENERATOR}")
if(CMAKE_GENERATOR_PLATFORM)
  list(APPEND build_generator --build-generator-platform "${CMAKE_GENERATOR_PLATFORM}")
endif()
if(CMAKE_GENERATOR_TOOLSET)
  list(APPEND build_generator --build-generator-toolset "${CMAKE_GENERATOR_TOOLSET}")
endif()
if(CMAKE_CONFIGURATION_TYPES)
  list(APPEND build_generator --build-config $<CONFIGURATION>)
endif()

unset(build_options)
if(CMAKE_BUILD_TYPE)
  list(APPEND build_options -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
endif()

# Use only if cmake modules not installed by YARP are required by the test
set(build_module_path -DCMAKE_MODULE_PATH="${CMAKE_MODULE_PATH}")
string(REPLACE ";" "\;" build_module_path "${build_module_path}")


add_test(NAME robottestingframework_add_suite_test
         COMMAND ${CMAKE_CTEST_COMMAND} --build-and-test "${CMAKE_CURRENT_SOURCE_DIR}/demo"
                                                         "${CMAKE_CURRENT_BINARY_DIR}/demo"
                                        --build-two-config
                                        ${build_generator}
                                        --build-project robottestingframework_add_suite_demo
                                        --build-options ${build_options}
                                                        ${build_module_path}
                                                        -DRobotTestingFramework_DIR=${CMAKE_BINARY_DIR}
                                        --test-command ${CMAKE_CTEST_COMMAND} ${build_generator}
         WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

# Cleanup
add_test(NAME robottestingframework_add_suite_test::cleanup
         COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/demo")
set_tests_properties(robottestingframework_add_suite_test::cleanup PROPERTIES FIXTURES_CLEANUP robottestingframework_add_suite_test)
