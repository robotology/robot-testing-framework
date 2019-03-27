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


set(RTF_dll_HDRS include/robottestingframework/dll/DllFixturePluginLoader.h
                 include/robottestingframework/dll/DllPluginLoader.h
                 include/robottestingframework/dll/Plugin.h
                 include/robottestingframework/dll/SharedLibrary.h
                 include/robottestingframework/dll/SharedLibraryClass.h
                 include/robottestingframework/dll/SharedLibraryClassApi.h
                 include/robottestingframework/dll/SharedLibraryClassFactory.h
                 include/robottestingframework/dll/SharedLibraryFactory.h
                 include/robottestingframework/dll/Vocab.h
                 include/robottestingframework/dll/robottestingframework_dll_config.h)

set(RTF_dll_IMPL_HDRS include/robottestingframework/dll/impl/DllPluginLoader_impl.h)

set(RTF_dll_SRCS src/DllFixturePluginLoader.cpp
                 src/DllPluginLoader.cpp
                 src/SharedLibrary.cpp
                 src/SharedLibraryFactory.cpp)

add_library(RTF_dll ${RTF_dll_SRCS}
                    ${RTF_dll_HDRS}
                    ${RTF_dll_IMPL_HDRS})
add_library(RobotTestingFramework::RTF_dll ALIAS RTF_dll)

target_include_directories(RTF_dll PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(RTF_dll PUBLIC RobotTestingFramework::RTF)

if(NOT WIN32)
  target_link_libraries(RTF_dll PRIVATE dl)
endif()

target_compile_features(RTF_dll PUBLIC cxx_nullptr)

set_property(TARGET RTF_dll PROPERTY PUBLIC_HEADER ${RTF_dll_HDRS})

set_property(TARGET RTF_dll PROPERTY OUTPUT_NAME robottestingframework-dll)
set_property(TARGET RTF_dll PROPERTY SOVERSION 2)

install(TARGETS RTF_dll
        EXPORT RobotTestingFramework
        COMPONENT librobottestingframework-dll
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/robottestingframework/dll)
