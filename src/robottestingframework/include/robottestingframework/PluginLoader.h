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

#ifndef ROBOTTESTINGFRAMEWORK_PLUGINLOADER_H
#define ROBOTTESTINGFRAMEWORK_PLUGINLOADER_H

#include <robottestingframework/TestCase.h>

#include <string>

namespace robottestingframework {
namespace plugin {

/**
 * @brief The PluginLoader is an abstract class for loading a test case plug-in and
 * gives the direct access to the TestCase. The PluginLoader class needs to be implemented
 * by a plugin-specific loader.
 */
class PluginLoader
{
public:
    /**
     * PluginLoader constructor
     */
    PluginLoader() = default;

    /**
     *  PluginLoader destructor
     */
    virtual ~PluginLoader() = default;

    /**
     * @brief open Loads a test case plugin
     * @param filename the plugin filename
     * @return A pointer to the test case loaded from the
     * plugin or a null pointer in case of failure.
     */
    virtual TestCase* open(const std::string filename) = 0;

    /**
     * @brief close Unloads the plugin and deletes any
     * allocated memory.
     */
    virtual void close() = 0;

    /**
     * @brief getLastError gets the last error if any.
     * @return returns the last error string.
     */
    virtual std::string getLastError() = 0;
};

} // namespace plugin
} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_PLUGINLOADER_H
