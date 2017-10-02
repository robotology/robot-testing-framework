// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_PLUGINFACTORY_H
#define _RTF_PLUGINFACTORY_H

#include <string>
#include <algorithm>
#include <rtf/PluginLoader.h>
#include <rtf/dll/DllPluginLoader.h>

#ifdef ENABLE_LUA_PLUGIN
    #include <rtf/lua/LuaPluginLoader.h>
#endif
#ifdef ENABLE_PYTHON_PLUGIN
    #include <rtf/python/PythonPluginLoader.h>
#endif
#ifdef ENABLE_RUBY_PLUGIN
    #include <rtf/ruby/RubyPluginLoader.h>
#endif

/**
 * class PluginFactory
 */
class PluginFactory {

public:

    static RTF::plugin::PluginLoader* createByType(std::string type) {
        if(compare(type.c_str(), "dll"))
            return new RTF::plugin::DllPluginLoader();
#ifdef ENABLE_LUA_PLUGIN
        if(compare(type.c_str(), "lua"))
            return new RTF::plugin::LuaPluginLoader();
#endif
#ifdef ENABLE_PYTHON_PLUGIN
        if(compare(type.c_str(), "python"))
            return new RTF::plugin::PythonPluginLoader();
#endif
#ifdef ENABLE_RUBY_PLUGIN
        if(compare(type.c_str(), "ruby"))
            return new RTF::plugin::RubyPluginLoader();
#endif
        return nullptr;
    }

    static RTF::plugin::PluginLoader* createByName(std::string name) {
#ifdef ENABLE_PYTHON_PLUGIN
        // check for .py
        if(name.size() > 2) {
            std::string ext = name.substr(name.size()-3,3);
             if(PluginFactory::compare(ext.c_str(), ".py"))
                 return new RTF::plugin::PythonPluginLoader();
        }
#endif

#ifdef ENABLE_RUBY_PLUGIN
        // check for .rb
        if(name.size() > 2) {
            std::string ext = name.substr(name.size()-3,3);
             if(PluginFactory::compare(ext.c_str(), ".rb"))
                 return new RTF::plugin::RubyPluginLoader();
        }
#endif
        if(name.size() > 3) {
            // check for windows .dll
            std::string ext = name.substr(name.size()-4,4);
            if(PluginFactory::compare(ext.c_str(), ".dll"))
                return new RTF::plugin::DllPluginLoader();
#ifdef ENABLE_LUA_PLUGIN
            // check for .lua
             if(PluginFactory::compare(ext.c_str(), ".lua"))
                 return new RTF::plugin::LuaPluginLoader();
#endif
        }
        if(name.size() > 3) {
            // check for unix .so
            std::string ext = name.substr(name.size()-3,3);
            if(PluginFactory::compare(ext.c_str(), ".so"))
                return new RTF::plugin::DllPluginLoader();
        }
        return nullptr;
    }

    static bool compare(const char*first,
                        const char* second)

    {
        if(!first && !second) return true;
        if(!first || !second) return false;

        std::string strFirst(first);
        std::string strSecond(second);
        std::transform(strFirst.begin(), strFirst.end(), strFirst.begin(),
                 (int(*)(int))toupper);
        std::transform(strSecond.begin(), strSecond.end(), strSecond.begin(),
                 (int(*)(int))toupper);

        return (strFirst == strSecond);
    }
};

#endif // _RTF_PLUGINFACTORY_H
