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


#ifndef ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYFACTORY_H
#define ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYFACTORY_H

#include <robottestingframework/dll/SharedLibrary.h>
#include <robottestingframework/dll/SharedLibraryClassApi.h>
#include <robottestingframework/dll/Vocab.h>

#include <string>


namespace shlibpp {
class SharedLibraryFactory;
}

/**
 * A wrapper for a named factory method in a named shared library.
 * This wrapper will do some basic checks that the named method does
 * indeed behave like a YARP plugin hook before offering access to it.
 * This is to avoid accidents, it is not a security mechanism.
 */
class shlibpp::SharedLibraryFactory
{
public:
    /**
     * The status of a factory can be:
     *  - STATUS_NONE: Not configured yet
     *  - STATUS_OK: Present and sane
     *  - STATUS_LIBRARY_NOT_FOUND: Named shared library was not found
     *  - STATUS_LIBRARY_NOT_LOADED: Named shared library failed to load
     *  - STATUS_FACTORY_NOT_FOUND: Named method wasn't present in library
     *  - STATUS_FACTORY_NOT_FUNCTIONAL: Named method is not working right
     */
    enum
    {
        STATUS_NONE, //!< Not configured yet.
        STATUS_OK = VOCAB('o', 'k'), //!< Present and sane.
        STATUS_LIBRARY_NOT_FOUND = VOCAB('f', 'o', 'u', 'n'), //!< Named shared library was not found.
        STATUS_LIBRARY_NOT_LOADED = VOCAB('l', 'o', 'a', 'd'), //!< Named shared library failed to load.
        STATUS_FACTORY_NOT_FOUND = VOCAB('f', 'a', 'c', 't'), //!< Named method wasn't present in library.
        STATUS_FACTORY_NOT_FUNCTIONAL = VOCAB('r', 'u', 'n') //!< Named method is not working right.
    };

    /**
     * Constructor for unconfigured factory.
     */
    explicit SharedLibraryFactory();

    /**
     * Constructor.
     *
     * @param dll_name name/path of shared library.
     * @param fn_name name of factory method, a symbol within the shared library.
     */
    SharedLibraryFactory(const char* dll_name,
                         const char* fn_name = nullptr);

    /**
     * Destructor
     */
    virtual ~SharedLibraryFactory();

    /**
     * Configure the factory.
     *
     * @param dll_name name/path of shared library.
     * @param fn_name name of factory method, a symbol within the shared library.
     * @return true on success.
     */
    bool open(const char* dll_name, const char* fn_name = nullptr);

    /**
     * Check if factory is configured and present.
     *
     * @return true iff factory is good to go.
     */
    bool isValid() const;

    /**
     * Get the status of the factory.
     *
     * @return one of the SharedLibraryFactory::STATUS_* codes.
     */
    int getStatus() const;

    /**
     * Get the latest error of the factory.
     *
     * @return the latest error.
     */
    std::string getError() const;

    /**

     * Get the factory API, which has creation/deletion methods.
     *
     * @return the factory API
     */
    const SharedLibraryClassApi& getApi() const;

    /**
     * Get the current reference count of this factory.
     *
     * @return the current reference count of this factory.
     */
    int getReferenceCount() const;

    /**
     * Increment the reference count of this factory.
     *
     * @return the current reference count of this factory, after increment.
     */
    int addRef();

    /**
     * Decrement the reference count of this factory.
     *
     * @return the current reference count of this factory, after decrement.
     */
    int removeRef();

    /**
     * Get the name associated with this factory.
     *
     * @return the name associated with this factory.
     */
    std::string getName() const;

    /**
     * Get the type associated with this factory.
     *
     * @return the type associated with this factory.
     */
    std::string getClassName() const;

    /**
     * Get the base type associated with this factory.
     *
     * @return the base type associated with this factory.
     */
    std::string getBaseClassName() const;

    /**
     *
     * Specify function to use as factory.
     *
     * @param factory function to use as factory.
     *
     * @result true on success.
     *
     */
    bool useFactoryFunction(void* factory);

private:
    SharedLibrary lib;
    int status;
    SharedLibraryClassApi api;
    int returnValue;
    int rct;
    std::string name;
    std::string className;
    std::string baseClassName;
    std::string error;
};


#endif // ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYFACTORY_H
