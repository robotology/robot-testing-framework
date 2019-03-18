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


#ifndef ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYCLASSAPI_H
#define ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYCLASSAPI_H

#include "robottestingframework_dll_config.h"
#include <cstring>

namespace shlibpp {
struct SharedLibraryClassApi;
}

// Be careful loading C++ classes from DLLs.  Generally you
// need an exact or very close match between compilers used
// to compile those DLLs and your own code.

extern "C" {

/**
     *
     * Collection of hooks for creating/destroying a plugin.
     * Be careful to check carefully for compatibility before
     * using create() or destroy().
     *
     */
struct shlibpp::SharedLibraryClassApi
{
public:
    int startCheck; // Constant: this should be 'S' 'H' 'P' 'P'.
        // Don't touch anything further if it isn't.
    int structureSize; // size of the SharedLibraryClassApi.
        // If this doesn't match what you expect,
        // Don't touch anything further if it isn't.
    int systemVersion; // Overall version of plugin system.
        // This does *not* cover compiler version etc.
    void* (*create)(); // Instantiate a plugin object.
    void (*destroy)(void* obj); // Destroy a plugin object.
    int (*getVersion)(char* ver, int len); // Plugin-related version.
    int (*getAbi)(char* abi, int len); // Compiler-related version.
    int (*getClassName)(char* name, int len); // Name of plugin (subclass).
    int (*getBaseClassName)(char* name, int len); // Name superclass.
    int roomToGrow[SHLIBPP_SHAREDLIBRARYCLASSAPI_PADDING]; // Padding.
    int endCheck; // Constant: should be 'P' 'L' 'U' 'G'.
};
}

#define SHLIBPP_SHARED_CLASS_FN extern "C" SHLIBPP_EXPORT

/**
 *
 * Macro to create a bunch of functions with undecorated names that can
 * be found within a plugin library to handle creation/deletion of that
 * plugin.  Use with care.
 *
 * @param factoryname the name of the "hook" function to make.  A collection
 * of other helper functions with names composed of the factoryname with
 * _create/_destroy/... appended.
 *
 * @param classname the class that the hook will be able to instantiate.
 *
 * @param basename the superclass that the user of the plugin should be
 * working with.
 *
 */
#define SHLIBPP_DEFINE_SHARED_SUBCLASS(factoryname, classname, basename)                           \
    SHLIBPP_SHARED_CLASS_FN void* factoryname##_create()                                           \
    {                                                                                              \
        classname* cn = new classname;                                                             \
        basename* bn = dynamic_cast<basename*>(cn);                                                \
        if (!bn)                                                                                   \
            delete cn;                                                                             \
        return static_cast<void*>(bn);                                                             \
    }                                                                                              \
    SHLIBPP_SHARED_CLASS_FN void factoryname##_destroy(void* obj)                                  \
    {                                                                                              \
        classname* cn = dynamic_cast<classname*>(static_cast<basename*>(obj));                     \
        if (cn)                                                                                    \
            delete cn;                                                                             \
    }                                                                                              \
    SHLIBPP_SHARED_CLASS_FN int factoryname##_getVersion(char* ver, int len)                       \
    {                                                                                              \
        return 0;                                                                                  \
    }                                                                                              \
    SHLIBPP_SHARED_CLASS_FN int factoryname##_getAbi(char* abi, int len)                           \
    {                                                                                              \
        return 0;                                                                                  \
    }                                                                                              \
    SHLIBPP_SHARED_CLASS_FN int factoryname##_getClassName(char* name, int len)                    \
    {                                                                                              \
        char cname[] = #classname;                                                                 \
        strncpy(name, cname, len);                                                                 \
        return strlen(cname) + 1;                                                                  \
    }                                                                                              \
    SHLIBPP_SHARED_CLASS_FN int factoryname##_getBaseClassName(char* name, int len)                \
    {                                                                                              \
        char cname[] = #basename;                                                                  \
        strncpy(name, cname, len);                                                                 \
        return strlen(cname) + 1;                                                                  \
    }                                                                                              \
    SHLIBPP_SHARED_CLASS_FN int factoryname(void* api, int len)                                    \
    {                                                                                              \
        struct shlibpp::SharedLibraryClassApi* sapi = (struct shlibpp::SharedLibraryClassApi*)api; \
        if (len < (int)sizeof(shlibpp::SharedLibraryClassApi))                                     \
            return -1;                                                                             \
        sapi->startCheck = shlibpp::VOCAB('S', 'H', 'P', 'P');                                     \
        sapi->structureSize = sizeof(shlibpp::SharedLibraryClassApi);                              \
        sapi->systemVersion = 5;                                                                   \
        sapi->create = factoryname##_create;                                                       \
        sapi->destroy = factoryname##_destroy;                                                     \
        sapi->getVersion = factoryname##_getVersion;                                               \
        sapi->getAbi = factoryname##_getAbi;                                                       \
        sapi->getClassName = factoryname##_getClassName;                                           \
        sapi->getBaseClassName = factoryname##_getBaseClassName;                                   \
        for (int i = 0; i < SHLIBPP_SHAREDLIBRARYCLASSAPI_PADDING; i++) {                          \
            sapi->roomToGrow[i] = 0;                                                               \
        }                                                                                          \
        sapi->endCheck = shlibpp::VOCAB('P', 'L', 'U', 'G');                                       \
        return sapi->startCheck;                                                                   \
    }
// The double cast in the _create() and _destroy() functions are
// required to ensure that everything works when `basename` is not the
// first inherited class:
// _create() will return a valid `basename` or a null pointer if
// `classname` does not inherit from `basename`.
// _destroy() will ensure that we are calling `classname` destructor
// even if `basename` is not the first inherited class. If the
// dynamic_cast fails, it will not delete the object (that is probably
// leaked), but it is less dangerous than executing some other random
// function.

#define SHLIBPP_DEFAULT_FACTORY_NAME "shlibpp_default_factory"
#define SHLIBPP_DEFINE_DEFAULT_SHARED_CLASS(classname) SHLIBPP_DEFINE_SHARED_SUBCLASS(shlibpp_default_factory, classname, classname)
#define SHLIBPP_DEFINE_SHARED_CLASS(factoryname, classname) SHLIBPP_DEFINE_SHARED_SUBCLASS(factoryname, classname, classname)

#endif // ROBOTTESTINGFRAMEWORK_SHAREDLIBRARYCLASSAPI_H
