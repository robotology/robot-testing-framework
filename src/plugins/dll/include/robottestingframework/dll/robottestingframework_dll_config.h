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


#ifndef ROBOTTESTINGFRAMEWORK_DLL_CONFIG_H
#define ROBOTTESTINGFRAMEWORK_DLL_CONFIG_H

#if defined _WIN32 || defined __CYGWIN__
#    define SHLIBPP_EXPORT __declspec(dllexport)
#else
#    if defined SHLIBPP_FILTER_API && __GNUC__ >= 4
#        define SHLIBPP_EXPORT __attribute__((visibility("default")))
#    else
#        define SHLIBPP_EXPORT
#    endif
#endif

#define SHLIBPP_POINTER_SIZE 8
#define SHLIBPP_SHAREDLIBRARYCLASSAPI_PADDING (30 - 2 * (SHLIBPP_POINTER_SIZE / 4))

#endif //ROBOTTESTINGFRAMEWORK_DLL_CONFIG_H
