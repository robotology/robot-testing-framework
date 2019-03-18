/*
 * Robot Testing Framework
 *
 * Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef ROBOTTESTINGFRAMEWORK_PLUGIN_H
#define ROBOTTESTINGFRAMEWORK_PLUGIN_H

#include "SharedLibraryClass.h"

#define ROBOTTESTINGFRAMEWORK_PLUGIN_FACTORY_NAME "robottestingframework_dll_factory"
#define ROBOTTESTINGFRAMEWORK_FIXTURE_FACTORY_NAME "robottestingframework_fixture_factory"

#define ROBOTTESTINGFRAMEWORK_PREPARE_PLUGIN(classname) SHLIBPP_DEFINE_SHARED_SUBCLASS(robottestingframework_dll_factory, classname, classname)
#define ROBOTTESTINGFRAMEWORK_PREPARE_FIXTURE_PLUGIN(classname) SHLIBPP_DEFINE_SHARED_SUBCLASS(robottestingframework_fixture_factory, classname, classname)

#endif // ROBOTTESTINGFRAMEWORK_PLUGIN_H
