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


#ifndef ROBOTTESTINGFRAMEWORK_PLUGINFACTORY_H
#define ROBOTTESTINGFRAMEWORK_PLUGINFACTORY_H

#include <robottestingframework/PluginLoader.h>
#include <robottestingframework/dll/DllPluginLoader.h>

#include <algorithm>
#include <string>

#ifdef ENABLE_LUA_PLUGIN
#    include <robottestingframework/lua/LuaPluginLoader.h>
#endif
#ifdef ENABLE_PYTHON_PLUGIN
#    include <robottestingframework/python/PythonPluginLoader.h>
#endif
#ifdef ENABLE_RUBY_PLUGIN
#    include <robottestingframework/ruby/RubyPluginLoader.h>
#endif

/**
 * class PluginFactory
 */
class PluginFactory
{

public:
    static robottestingframework::plugin::PluginLoader* createByType(std::string type)
    {
        if (compare(type.c_str(), "dll"))
            return new robottestingframework::plugin::DllPluginLoader();
#ifdef ENABLE_LUA_PLUGIN
        if (compare(type.c_str(), "lua"))
            return new robottestingframework::plugin::LuaPluginLoader();
#endif
#ifdef ENABLE_PYTHON_PLUGIN
        if (compare(type.c_str(), "python"))
            return new robottestingframework::plugin::PythonPluginLoader();
#endif
#ifdef ENABLE_RUBY_PLUGIN
        if (compare(type.c_str(), "ruby"))
            return new robottestingframework::plugin::RubyPluginLoader();
#endif
        return nullptr;
    }

    static robottestingframework::plugin::PluginLoader* createByName(std::string name)
    {
#ifdef ENABLE_PYTHON_PLUGIN
        // check for .py
        if (name.size() > 2) {
            std::string ext = name.substr(name.size() - 3, 3);
            if (PluginFactory::compare(ext.c_str(), ".py"))
                return new robottestingframework::plugin::PythonPluginLoader();
        }
#endif

#ifdef ENABLE_RUBY_PLUGIN
        // check for .rb
        if (name.size() > 2) {
            std::string ext = name.substr(name.size() - 3, 3);
            if (PluginFactory::compare(ext.c_str(), ".rb"))
                return new robottestingframework::plugin::RubyPluginLoader();
        }
#endif
        if (name.size() > 3) {
            // check for windows .dll
            std::string ext = name.substr(name.size() - 4, 4);
            if (PluginFactory::compare(ext.c_str(), ".dll"))
                return new robottestingframework::plugin::DllPluginLoader();
#ifdef ENABLE_LUA_PLUGIN
            // check for .lua
            if (PluginFactory::compare(ext.c_str(), ".lua"))
                return new robottestingframework::plugin::LuaPluginLoader();
#endif
        }
        if (name.size() > 3) {
            // check for unix .so
            std::string ext = name.substr(name.size() - 3, 3);
            if (PluginFactory::compare(ext.c_str(), ".so"))
                return new robottestingframework::plugin::DllPluginLoader();
        }
        return nullptr;
    }

    static bool compare(const char* first,
                        const char* second)

    {
        if (!first && !second)
            return true;
        if (!first || !second)
            return false;

        std::string strFirst(first);
        std::string strSecond(second);
        std::transform(strFirst.begin(), strFirst.end(), strFirst.begin(), (int (*)(int))toupper);
        std::transform(strSecond.begin(), strSecond.end(), strSecond.begin(), (int (*)(int))toupper);

        return (strFirst == strSecond);
    }
};

#endif // ROBOTTESTINGFRAMEWORK_PLUGINFACTORY_H
