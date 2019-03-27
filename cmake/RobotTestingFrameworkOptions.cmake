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


include(CMakeDependentOption)

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Shared/Dynamic or Static library?
option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" ON)

# enable RPATH
option(ENABLE_RPATH "Enable RPATH for this library" ON)
mark_as_advanced(ENABLE_RPATH)
include(AddInstallRPATHSupport)
add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}"
                          LIB_DIRS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
                          DEPENDS ENABLE_RPATH
                          USE_LINK_PATH)

# setting options
option(ENABLE_PLUGIN "Enable plugins" ON)
option(ENABLE_LUA_PLUGIN "Enable Lua plugins" OFF)
option(ENABLE_PYTHON_PLUGIN "Enable Python plugins" OFF)
option(ENABLE_RUBY_PLUGIN "Enable Ruby plugins" OFF)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTRUNNER "Build robottestingframework-testrunner utility" ON)
#option(BUILD_TESTS "Build tests" ON)
option(ENABLE_WEB_LISTENER "Enable web listener" ON)


#########################################################################
# Control where libraries and executables are placed during the build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

if(BUILD_TESTRUNNER)
  set_property(CACHE ENABLE_PLUGIN PROPERTY VALUE ON)
endif()

# setting default compilation to release/optmized
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, recommanded options are: Debug or Release" FORCE)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  option(ENABLE_CODE_PROFILING "Enable code coverage profiling (only for GNUCXX)" OFF)
  mark_as_advanced(ENABLE_CODE_PROFILING)
  if(ENABLE_CODE_PROFILING)
    set(CMAKE_BUILD_TYPE "Coverage" CACHE STRING "Choose the type of build, recommanded options are: Debug or Release" FORCE)
    include(CodeCoverage)
    setup_target_for_coverage(coverage ctest coverage)
  endif()
endif()
