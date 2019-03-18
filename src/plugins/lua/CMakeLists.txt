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


find_package(Lua)
if(NOT LUA_FOUND)
    find_package(Lua53)
elseif(NOT LUA_FOUND)
    find_package(Lua52)
elseif(NOT LUA_FOUND)
    find_package(Lua51 REQUIRED)
endif()

set(RTF_lua_HDRS include/robottestingframework/lua/LuaPluginLoader.h)

set(RTF_lua_IMPL_HDRS include/robottestingframework/lua/impl/LuaPluginLoader_impl.h)

set(RTF_lua_SRCS src/LuaPluginLoader.cpp)

add_library(RTF_lua ${RTF_lua_SRCS}
                    ${RTF_lua_HDRS}
                    ${RTF_lua_IMPL_HDRS})
add_library(RobotTestingFramework::RTF_lua ALIAS RTF_lua)

target_include_directories(RTF_lua PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
                                   PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(RTF_lua PUBLIC RobotTestingFramework::RTF
                                     RobotTestingFramework::RTF_dll
                              PRIVATE ${LUA_LIBRARY})

target_compile_features(RTF_lua PUBLIC cxx_nullptr)

set_property(TARGET RTF_lua PROPERTY PUBLIC_HEADER ${RTF_lua_HDRS})

set_property(TARGET RTF_lua PROPERTY OUTPUT_NAME robottestingframework-lua)
set_property(TARGET RTF_lua PROPERTY SOVERSION 2)

install(TARGETS RTF_lua
        EXPORT RobotTestingFramework
        COMPONENT librobottestingframework-lua
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/robottestingframework/lua)
