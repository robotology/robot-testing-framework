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


#ifndef ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYCLASSFACTORY_H
#define ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYCLASSFACTORY_H

#include <robottestingframework/dll/SharedLibraryFactory.h>

namespace shlibpp {
template <class T>
class SharedLibraryClassFactory;
}


/**
 *
 * A type-safe wrapper for SharedLibraryFactory, committing to
 * creation/destruction of instances of a particular super-class.
 * Note that we take on faith that the named factory method in the
 * named shared library does in fact create the named type.
 *
 */
template <class T>
class shlibpp::SharedLibraryClassFactory : public SharedLibraryFactory
{
public:
    SharedLibraryClassFactory()
    {
    }

    SharedLibraryClassFactory(const char* dll_name, const char* fn_name = 0 /*nullptr*/) :
            SharedLibraryFactory(dll_name, fn_name)
    {
    }

    T* create()
    {
        if (!isValid())
            return nullptr;
        return (T*)getApi().create();
    }

    void destroy(T* obj)
    {
        if (!isValid())
            return;
        getApi().destroy(obj);
    }
};

#endif // ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYCLASSFACTORY_H
