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


set(RTF_HDRS include/robottestingframework/Arguments.h
             include/robottestingframework/Asserter.h
             include/robottestingframework/ConsoleListener.h
             include/robottestingframework/Exception.h
             include/robottestingframework/FixtureManager.h
             include/robottestingframework/PluginLoader.h
             include/robottestingframework/ResultEvent.h
             include/robottestingframework/TestAssert.h
             include/robottestingframework/TestCase.h
             include/robottestingframework/Test.h
             include/robottestingframework/TestListener.h
             include/robottestingframework/TestMessage.h
             include/robottestingframework/TestResultCollector.h
             include/robottestingframework/TestResult.h
             include/robottestingframework/TestRunner.h
             include/robottestingframework/TestSuite.h
             include/robottestingframework/TextOutputter.h)

set(RTF_IMPL_HDRS )

set(RTF_SRCS src/Arguments.cpp
             src/Asserter.cpp
             src/ConsoleListener.cpp
             src/FixtureManager.cpp
             src/TestCase.cpp
             src/TestMessage.cpp
             src/TestResultCollector.cpp
             src/TestResult.cpp
             src/TestRunner.cpp
             src/TestSuite.cpp
             src/TextOutputter.cpp)

# Create the library
if(ENABLE_WEB_LISTENER)
  list(APPEND RTF_IMPL_HDRS include/robottestingframework/impl/WebProgressListener_impl.h)
  list(APPEND RTF_HDRS include/robottestingframework/WebProgressListener.h)
  list(APPEND RTF_SRCS src/WebProgressListener.cpp)
endif()


add_library(RTF ${RTF_SRCS}
                ${RTF_HDRS}
                ${RTF_IMPL_HDRS})
add_library(RobotTestingFramework::RTF ALIAS RTF)

target_include_directories(RTF PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
                               PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/impl")

if(ENABLE_WEB_LISTENER)
  target_sources(RTF PRIVATE $<TARGET_OBJECTS:RobotTestingFramework::RTF_mongoose>)
  target_include_directories(RTF PRIVATE $<TARGET_PROPERTY:RobotTestingFramework::RTF_mongoose,INTERFACE_INCLUDE_DIRECTORIES>)
  get_target_property(RTF_mongoose_INTERFACE_LINK_LIBRARIES RobotTestingFramework::RTF_mongoose INTERFACE_LINK_LIBRARIES)
  if(RTF_mongoose_INTERFACE_LINK_LIBRARIES)
    target_link_libraries(RTF PRIVATE ${RTF_mongoose_INTERFACE_LINK_LIBRARIES})
  endif()
endif()

target_compile_features(RTF PUBLIC cxx_nullptr)

# choose which header files should be installed
set_property(TARGET RTF PROPERTY PUBLIC_HEADER ${RTF_HDRS})

set_property(TARGET RTF PROPERTY OUTPUT_NAME robottestingframework)
set_property(TARGET RTF PROPERTY SOVERSION 2)

install(TARGETS RTF
        EXPORT RobotTestingFramework
        COMPONENT robottestingframework
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/robottestingframework)
