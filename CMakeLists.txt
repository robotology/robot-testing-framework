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


cmake_minimum_required(VERSION 3.5)
project(RobotTestingFramework
        VERSION 1.6.51
        LANGUAGES C CXX)
# FIXME CMake 3.9 these variables are handled by "project"
set(CMAKE_PROJECT_DESCRIPTION "Robot Testing Framework")
set(PROJECT_DESCRIPTION "${CMAKE_PROJECT_DESCRIPTION}")
set(RobotTestingFramework_DESCRIPTION "${CMAKE_PROJECT_DESCRIPTION}")

# enforce the use of C++11
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# use position independent code
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Pick up our CMake scripts - they are all in the cmake subdirectory.
set(RobotTestingFramework_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH ${RobotTestingFramework_MODULE_PATH})

# Make documentation target, documentation goes in
#doc subdirectory of build.
include(RobotTestingFrameworkDoc)

# include some helper functions
include(InstallBasicPackageFiles)
include(GNUInstallDirs)
include(GenerateExportHeader)

# include RobotTestingFramework Options
include(RobotTestingFrameworkOptions)

# adding directories
find_package(TinyXML)
add_subdirectory(extern)

add_subdirectory(src)


# examples are also used as tests
enable_testing()

add_subdirectory(examples)
add_subdirectory(tests)


# installation
set(BUILD_RobotTestingFramework_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/robottestingframework/include)
set(INSTALL_RobotTestingFramework_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RobotTestingFramework_DLL_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/dll/include)
set(INSTALL_RobotTestingFramework_DLL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RobotTestingFramework_LUA_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/lua/include)
set(INSTALL_RobotTestingFramework_LUA_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RobotTestingFramework_PYTHON_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/python/include)
set(INSTALL_RobotTestingFramework_PYTHON_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RobotTestingFramework_RUBY_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/ruby/include)
set(INSTALL_RobotTestingFramework_RUBY_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)


install_basic_package_files(RobotTestingFramework
                            VERSION ${RobotTestingFramework_VERSION}
                            COMPATIBILITY SameMajorVersion
                            EXPORT RobotTestingFramework
                            FIRST_TARGET RTF
                            EXTRA_PATH_VARS_SUFFIX DLL_INCLUDEDIR
                                                   LUA_INCLUDEDIR
                                                   PYTHON_INCLUDEDIR
                                                   RUBY_INCLUDEDIR)

# add uninstall target
include(AddUninstallTarget)
