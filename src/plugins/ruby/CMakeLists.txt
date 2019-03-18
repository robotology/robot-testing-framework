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

find_package(Ruby REQUIRED)

set(RTF_ruby_HDRS include/robottestingframework/ruby/RubyPluginLoader.h)

set(RTF_ruby_IMPL_HDRS include/robottestingframework/ruby/impl/RubyPluginLoader_impl.h)

set(RTF_ruby_SRCS src/RubyPluginLoader.cpp)

add_library(RTF_ruby ${RTF_ruby_SRCS}
                     ${RTF_ruby_HDRS}
                     ${RTF_ruby_IMPL_HDRS})
add_library(RobotTestingFramework::RTF_ruby ALIAS RTF_ruby)

target_include_directories(RTF_ruby PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
                                    PRIVATE ${RUBY_INCLUDE_DIRS})

target_link_libraries(RTF_ruby PUBLIC RobotTestingFramework::RTF
                                      RobotTestingFramework::RTF_dll
                               PRIVATE ${RUBY_LIBRARY})

target_compile_features(RTF_ruby PUBLIC cxx_nullptr)

set_property(TARGET RTF_ruby PROPERTY PUBLIC_HEADER ${RTF_ruby_HDRS})

set_property(TARGET RTF_ruby PROPERTY OUTPUT_NAME robottestingframework-ruby)
set_property(TARGET RTF_ruby PROPERTY SOVERSION 2)

install(TARGETS RTF_ruby
        EXPORT RobotTestingFramework
        COMPONENT librobottestingframework-ruby
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/robottestingframework/ruby)
