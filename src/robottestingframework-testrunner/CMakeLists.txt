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


configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/Version.h.in"
               "${CMAKE_CURRENT_BINARY_DIR}/include/Version.h"
               @ONLY)

set(RTF_testrunner_HDRS include/ErrorLogger.h
                        include/JUnitOutputter.h
                        include/PlatformDir.h
                        include/PluginFactory.h
                        include/PluginRunner.h
                        include/SuiteRunner.h
                        include/cmdline.h
                        "${CMAKE_CURRENT_BINARY_DIR}/include/Version.h")

set(RTF_testrunner_SRCS src/ErrorLogger.cpp
                        src/JUnitOutputter.cpp
                        src/PluginRunner.cpp
                        src/SuiteRunner.cpp
                        src/main.cpp)

add_executable(RTF_testrunner ${RTF_testrunner_HDRS}
                              ${RTF_testrunner_SRCS})
add_executable(RobotTestingFramework::RTF_testrunner ALIAS RTF_testrunner)

target_include_directories(RTF_testrunner PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
                                                  "${CMAKE_CURRENT_BINARY_DIR}/include")

target_link_libraries(RTF_testrunner PRIVATE RobotTestingFramework::RTF
                                             RobotTestingFramework::RTF_dll)

target_compile_features(RTF_testrunner PRIVATE cxx_nullptr)

# TinyXML
if(TinyXML_FOUND)
  target_include_directories(RTF_testrunner PRIVATE ${TinyXML_INCLUDE_DIRS})
  target_link_libraries(RTF_testrunner PRIVATE ${TinyXML_LIBRARIES})
else()
  target_sources(RTF_testrunner PRIVATE $<TARGET_OBJECTS:RobotTestingFramework::RTF_tinyxml>)
  target_include_directories(RTF_testrunner PRIVATE $<TARGET_PROPERTY:RobotTestingFramework::RTF_tinyxml,INTERFACE_INCLUDE_DIRECTORIES>)
  get_target_property(RTF_tinyxml_INTERFACE_LINK_LIBRARIES RobotTestingFramework::RTF_tinyxml INTERFACE_LINK_LIBRARIES)
  if(RTF_tinyxml_INTERFACE_LINK_LIBRARIES)
    target_link_libraries(RTF_testrunner PRIVATE ${RTF_tinyxml_INTERFACE_LINK_LIBRARIES})
  endif()
  target_compile_definitions(RTF_testrunner PRIVATE $<TARGET_PROPERTY:RobotTestingFramework::RTF_tinyxml,INTERFACE_COMPILE_DEFINITIONS>)
endif()

if(ENABLE_WEB_LISTENER)
  target_compile_definitions(RTF_testrunner PRIVATE ENABLE_WEB_LISTENER)
endif()

if(ENABLE_LUA_PLUGIN)
  target_link_libraries(RTF_testrunner PRIVATE RobotTestingFramework::RTF_lua)
  target_compile_definitions(RTF_testrunner PRIVATE ENABLE_LUA_PLUGIN)
endif()

if(ENABLE_PYTHON_PLUGIN)
  target_link_libraries(RTF_testrunner PRIVATE RobotTestingFramework::RTF_python)
  target_compile_definitions(RTF_testrunner PRIVATE ENABLE_PYTHON_PLUGIN)
endif()

if(ENABLE_RUBY_PLUGIN)
  target_link_libraries(RTF_testrunner PRIVATE RobotTestingFramework::RTF_ruby)
  target_compile_definitions(RTF_testrunner PRIVATE ENABLE_RUBY_PLUGIN)
endif()

set_property(TARGET RTF_testrunner PROPERTY OUTPUT_NAME robottestingframework-testrunner)

install(TARGETS RTF_testrunner
        EXPORT RobotTestingFramework
        COMPONENT robottestingframework-testrunner
        RUNTIME DESTINATION bin)
