#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>, Daniele E. Domenichelli <daniele.domenichelli@iit.it>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

cmake_minimum_required(VERSION 3.1)
project(RTF)

# enforce the use of C++11
set(CMAKE_CXX_STANDARD 11)


# Pick up our CMake scripts - they are all in the conf subdirectory.
set(RTF_MODULE_PATH ${PROJECT_SOURCE_DIR}/conf)
set(CMAKE_MODULE_PATH ${RTF_MODULE_PATH})

# include version number
include(RTFVersion)

# Make documentation target, documentation goes in
#doc subdirectory of build.
include(RTFDoc)

# include some helper functions
include(InstallBasicPackageFiles)
include(GNUInstallDirs)
include(GenerateExportHeader)

# include RTF Options
include(RTFOptions)

# adding directories
add_subdirectory(extern)
add_subdirectory(src)


# examples are also used as tests
enable_testing()

add_subdirectory(examples)
add_subdirectory(tests)


# installation
set(BUILD_RTF_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/rtf/include)
set(INSTALL_RTF_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RTF_DLL_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/dll/include)
set(INSTALL_RTF_DLL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RTF_LUA_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/lua/include)
set(INSTALL_RTF_LUA_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RTF_PYTHON_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/python/include)
set(INSTALL_RTF_PYTHON_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RTF_RUBY_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/ruby/include)
set(INSTALL_RTF_RUBY_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)


install_basic_package_files(${PROJECT_NAME}
                            VERSION ${RTF_VERSION}
                            COMPATIBILITY AnyNewerVersion
                            TARGETS_PROPERTIES RTF_LIBS
                                               RTF_TOOLS
                            EXTRA_PATH_VARS_SUFFIX DLL_INCLUDEDIR
                                                   LUA_INCLUDEDIR
                                                   PYTHON_INCLUDEDIR
                                                   RUBY_INCLUDEDIR)

# add uninstall target
include(AddUninstallTarget)

