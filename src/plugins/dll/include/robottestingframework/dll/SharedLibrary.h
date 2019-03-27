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


#ifndef ROBOTTESTINGFRAMEWORK_SHAREDLIBRARY_H
#define ROBOTTESTINGFRAMEWORK_SHAREDLIBRARY_H

#include <string>

namespace shlibpp {
class SharedLibrary;
}

/**
 * Low-level wrapper for loading shared libraries (DLLs) and accessing
 * symbols within it.
 */
class shlibpp::SharedLibrary
{
public:
    /**
     * Initialize, without opening a shared library yet.
     */
    SharedLibrary();

    /**
     * Load the named shared library / DLL.
     *
     * @param filename name of file (see open method)
     */
    SharedLibrary(const char* filename);

    /**
     * Destructor.  Will close() if needed.
     */
    virtual ~SharedLibrary();

    /**
     * Load the named shared library / DLL.  The library is found
     * using the algoithm of ACE::ldfind.  Operating-system-specific
     * extensions will be tried, and the relevant path for shared
     * libraries.
     *
     * @param filename name of file.
     * @return true on success
     */
    bool open(const char* filename);

    /**
     * Shared library no longer needed, unload if not in use elsewhere.
     * @return true on success
     */
    bool close();

    /**
     * Returns a human-readable string describing the most recent error that
     * occurred from a call to one of its functions.
     *
     * @return the most recent error
     */
    std::string error();

    /**
     * Look up a symbol in the shared library.
     */
    void* getSymbol(const char* symbolName);

    /**
     * Check if the shared library is valid
     *
     * @return true iff a valid library has been loaded.
     */
    bool isValid() const;

private:
    void* implementation;
    std::string err_message;
    SharedLibrary(const SharedLibrary&); // Not implemented
    SharedLibrary& operator=(const SharedLibrary&); // Not implemented
};

#endif // ROBOTTESTINGFRAMEWORK_SHAREDLIBRARY_H
