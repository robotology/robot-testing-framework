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


# build plugin manager
if (ENABLE_PLUGIN OR BUILD_TESTRUNNER)
  add_subdirectory(dll)
endif()

# build Lua plugin manager
if (ENABLE_LUA_PLUGIN)
  add_subdirectory(lua)
endif()

# build Python plugin manager
if (ENABLE_PYTHON_PLUGIN)
  add_subdirectory(python)
endif()

# build Ruby plugin manager
if (ENABLE_RUBY_PLUGIN)
  add_subdirectory(ruby)
endif()
