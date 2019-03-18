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


#ifndef ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYCLASS_H
#define ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYCLASS_H

#include <robottestingframework/dll/SharedLibraryClassFactory.h>

namespace shlibpp {
template <class T>
class SharedLibraryClass;
}


/**
 * Container for an object created using a factory provided by a shared library.
 * Used to ensure the object is destroyed by a method also provided by the
 * shared library.  Mixing creation and destruction methods could be very bad.
 */
template <class T>
class shlibpp::SharedLibraryClass
{
private:
    T* content;
    SharedLibraryClassFactory<T>* pfactory;

public:
    /**
     * Constructor for empty instance.
     */
    SharedLibraryClass() :
            content(nullptr),
            pfactory(nullptr)
    {
    }

    /**
     * Constructor for valid instance of a class from a shared library.
     *
     * @param factory the factory to use to construct (and eventually
     * destroy) the instance.
     */
    SharedLibraryClass(SharedLibraryClassFactory<T>& factory) :
            content(nullptr),
            pfactory(nullptr)
    {
        open(factory);
    }

    /**
     * Construct an instance using the specified factory.  If an
     * instance has already been made, it is destroyed.
     *
     * @param factory the factory to use to construct (and eventually
     * destroy) the instance.
     * @return true on success
     */
    bool open(SharedLibraryClassFactory<T>& factory)
    {
        close();
        content = factory.create();
        pfactory = &factory;
        factory.addRef();

        return content != nullptr;
    }

    /**
     * Destroy an instance if one has been created.
     *
     * @return true on success
     */
    virtual bool close()
    {
        if (content != nullptr) {
            pfactory->destroy(content);
            //NetworkBase::lock();
            if (pfactory->removeRef() == 0) {
                delete pfactory;
            }
            //NetworkBase::unlock();
        }

        content = nullptr;
        pfactory = nullptr;

        return true;
    }

    /**
     * Destructor.
     */
    virtual ~SharedLibraryClass()
    {
        close();
    }

    /**
     * Gives access to the created instance.  No check made to ensure
     * an instance is in fact present.  Call SharedLibraryClass::isValid
     * first if unsure.
     *
     * @return the created instance
     */
    T& getContent()
    {
        return *content;
    }

    /**
     * Check whether a valid instance has been created.
     *
     * @return true iff a valid instance has been created
     */
    bool isValid() const
    {
        return content != nullptr;
    }

    /**
     * Shorthand for SharedLibraryClass::getContent
     *
     * @return the created instance
     */
    T& operator*()
    {
        return (*content);
    }

    /**
     * A pointer version of SharedLibraryClass::getContent
     *
     * @return a pointer to the created instance, or nullptr if there is none
     */
    T* operator->()
    {
        return (content);
    }
};


#endif // ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYCLASS_H
