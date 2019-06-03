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


set(RobotTestingFramework_USE_PYTHON_VERSION "" CACHE STRING "Specify python version to use (only Python 2 is supported at the moment)" )

if(RobotTestingFramework_USE_PYTHON_VERSION)
  if("${RobotTestingFramework_USE_PYTHON_VERSION}" MATCHES "^3")
    message(SEND_ERROR "Python 3 not supported. Only Python 2 is supported at the moment.")
  endif()
  find_package(PythonInterp ${RobotTestingFramework_USE_PYTHON_VERSION} REQUIRED)
  find_package(PythonLibs ${RobotTestingFramework_USE_PYTHON_VERSION} EXACT REQUIRED)
else()
  find_package(PythonInterp REQUIRED)
  find_package(PythonLibs REQUIRED)
endif()

set(RTF_python_HDRS include/robottestingframework/python/PythonPluginLoader.h)

set(RTF_python_IMPL_HDRS include/robottestingframework/python/impl/PythonPluginLoader_impl.h)

set(RTF_python_SRCS src/PythonPluginLoader.cpp)

add_library(RTF_python ${RTF_python_SRCS}
                       ${RTF_python_HDRS}
                       ${RTF_python_IMPL_HDRS})
add_library(RobotTestingFramework::RTF_python ALIAS RTF_python)

target_include_directories(RTF_python PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                             $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
                                      PRIVATE ${PYTHON_INCLUDE_DIRS})

target_link_libraries(RTF_python PUBLIC RobotTestingFramework::RTF
                                        RobotTestingFramework::RTF_dll
                                 PRIVATE ${PYTHON_LIBRARY})

target_compile_features(RTF_python PUBLIC cxx_nullptr)

set_property(TARGET RTF_python PROPERTY PUBLIC_HEADER ${RTF_python_HDRS})

set_property(TARGET RTF_python PROPERTY OUTPUT_NAME robottestingframework-python)
set_property(TARGET RTF_python PROPERTY SOVERSION 2)

install(TARGETS RTF_python
        EXPORT RobotTestingFramework
        COMPONENT robottestingframework-python
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/robottestingframework/python)


