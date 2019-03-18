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

#include <robottestingframework/dll/SharedLibraryFactory.h>

#include <sys/stat.h>

shlibpp::SharedLibraryFactory::SharedLibraryFactory() :
        status(STATUS_NONE),
        returnValue(0),
        rct(1)
{
}

shlibpp::SharedLibraryFactory::SharedLibraryFactory(const char* dll_name,
                                                    const char* fn_name) :
        status(STATUS_NONE),
        returnValue(0),
        rct(1)
{
    open(dll_name, fn_name);
}

shlibpp::SharedLibraryFactory::~SharedLibraryFactory()
{
}

bool shlibpp::SharedLibraryFactory::open(const char* dll_name, const char* fn_name)
{
    returnValue = 0;
    name = "";
    className = "";
    baseClassName = "";
    status = STATUS_NONE;
    error = "";
    api.startCheck = 0;
    if (!lib.open(dll_name)) {
#if defined(_WIN32)
        struct _stat dummy;
        if (::_stat(dll_name, &dummy) != 0) {
#else
        struct ::stat dummy;
        if (::stat(dll_name, &dummy) != 0) {
#endif
            status = STATUS_LIBRARY_NOT_FOUND;
        } else {
            status = STATUS_LIBRARY_NOT_LOADED;
        }
        error = lib.error();
        return false;
    }
    void* fn = lib.getSymbol((fn_name != nullptr) ? fn_name : SHLIBPP_DEFAULT_FACTORY_NAME);
    if (fn == nullptr) {
        status = STATUS_FACTORY_NOT_FOUND;
        error = lib.error();
        lib.close();
        return false;
    }
    if (!useFactoryFunction(fn)) {
        status = STATUS_FACTORY_NOT_FUNCTIONAL;
        error = "Robot Testing Framework hook in shared library misbehaved";
        return false;
    }
    status = STATUS_OK;
    name = dll_name;

    char buf[256];
    api.getClassName(buf, 256);
    className = buf;
    api.getBaseClassName(buf, 256);
    baseClassName = buf;

    return true;
}

bool shlibpp::SharedLibraryFactory::isValid() const
{
    if (returnValue != VOCAB('S', 'H', 'P', 'P')) {
        return false;
    }
    if (api.startCheck != VOCAB('S', 'H', 'P', 'P')) {
        return false;
    }
    if (api.structureSize != sizeof(SharedLibraryClassApi)) {
        return false;
    }
    if (api.systemVersion != 5) {
        return false;
    }
    if (api.endCheck != VOCAB('P', 'L', 'U', 'G')) {
        return false;
    }
    return true;
}

int shlibpp::SharedLibraryFactory::getStatus() const
{
    return status;
}

std::string shlibpp::SharedLibraryFactory::getError() const
{
    return error;
}

const shlibpp::SharedLibraryClassApi& shlibpp::SharedLibraryFactory::getApi() const
{
    return api;
}


int shlibpp::SharedLibraryFactory::getReferenceCount() const
{
    return rct;
}


int shlibpp::SharedLibraryFactory::addRef()
{
    rct++;
    return rct;
}

int shlibpp::SharedLibraryFactory::removeRef()
{
    rct--;
    return rct;
}

std::string shlibpp::SharedLibraryFactory::getName() const
{
    return name;
}


std::string shlibpp::SharedLibraryFactory::getClassName() const
{
    return className;
}

std::string shlibpp::SharedLibraryFactory::getBaseClassName() const
{
    return baseClassName;
}


bool shlibpp::SharedLibraryFactory::useFactoryFunction(void* factory)
{
    api.startCheck = 0;
    if (factory == nullptr) {
        return false;
    }
    returnValue = ((int (*)(void* ptr, int len))factory)(&api, sizeof(SharedLibraryClassApi));
    return isValid();
}
