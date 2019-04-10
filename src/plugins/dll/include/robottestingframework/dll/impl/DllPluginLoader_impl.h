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


#ifndef ROBOTTESTINGFRAMEWORK_DLLPLUGINLOADERIMPL_H
#define ROBOTTESTINGFRAMEWORK_DLLPLUGINLOADERIMPL_H

#include <robottestingframework/dll/Plugin.h>
#include <robottestingframework/dll/SharedLibrary.h>
#include <robottestingframework/dll/SharedLibraryClass.h>

#include <string>

/**
 * class DllPluginLoaderImpl
 */
template <class T>
class DllPluginLoaderImpl
{

    class Plugin
    {
    public:
        shlibpp::SharedLibraryClassFactory<T> factory;
        shlibpp::SharedLibraryClass<T> test;
    };

public:
    /**
     * DllPluginLoaderImpl constructor
     */
    DllPluginLoaderImpl() :
            plugin(nullptr)
    {
    }

    /**
     *  DllPluginLoaderImpl destructor
     */
    virtual ~DllPluginLoaderImpl()
    {
        close();
    }


    /**
     * @brief open Loads a generic plugin
     * @param filename the plugin filename
     * @return A pointer to the class loaded from the
     * plugin or a null pointer in case of failure.
     */
    T* open(const std::string filename,
            const std::string factory_name)
    {

        // close any previous loaded plugin
        close();

        // create an instance of plugin class and factory
        plugin = new DllPluginLoaderImpl::Plugin;

        // load the test case plugin
        open_internal(filename, factory_name);

        if (!plugin->factory.isValid()) {
            if (plugin->factory.getStatus() == shlibpp::VOCAB('f', 'a', 'c', 't')) {
                std::string plug_type = (factory_name == ROBOTTESTINGFRAMEWORK_PLUGIN_FACTORY_NAME) ? "test case" : "fixture manager";
                error = "cannot load plugin " + filename + "; (it is not a Robot Testing Framework " + plug_type + " plugin!)";
            } else {
                error = "cannot load plugin " + filename + "; error (" + shlibpp::Vocab::decode(plugin->factory.getStatus()) + ") : " + plugin->factory.getError();
            }
            delete plugin;
            plugin = nullptr;
            return nullptr;
        }

        // TODO: check if this is neccessary!!!
        //plugin->factory.addRef();

        // create an instance of the test case from the plugin
        plugin->test.open(plugin->factory);
        if (!plugin->test.isValid()) {
            //error = Asserter::format("cannot create an instance of TestCase from %s", filename.c_str());
            delete plugin;
            plugin = nullptr;
            return nullptr;
        }

        return &plugin->test.getContent();
    }


    /**
     * @brief close Unloads the plugin and deletes any
     * allocated memory.
     */
    void close()
    {
        if (plugin)
            delete plugin;
        plugin = nullptr;
        error.clear();
    }

    /**
     * @brief getLastError gets the last error if any.
     * @return returns the last error string.
     */
    const std::string& getLastError()
    {
        return error;
    }

private:
    std::string error;
    Plugin* plugin;

    void open_internal(const std::string filename,
                       const std::string factory_name)
    {

        std::string fullpath;
#if defined(_WIN32)
        std::string ext = ".dll";
#else
        std::string ext = ".so";
#endif
        std::string basename;
        bool has_ext;
        if (filename.find(ext) != std::string::npos) {
            basename = filename.substr(0, filename.size() - ext.size());
            has_ext = true;
        } else {
            basename = filename;
            has_ext = false;
        }

#if defined(_MSC_VER) && !defined(NDEBUG)
        // MSVC DEBUG build: try debug name before basic name
        if (!has_ext) {
            fullpath = basename + "d" + ext;
            if (plugin->factory.open(fullpath.c_str(), factory_name.c_str()))
                return;
        }
#endif

        // Basic name
        fullpath = basename + ext;
        if (plugin->factory.open(fullpath.c_str(), factory_name.c_str()))
            return;

#if defined(_MSC_VER) && defined(NDEBUG)
        // MSVC RELEASE build: try debug name after basic name
        if (!has_ext) {
            fullpath = basename + "d" + ext;
            if (plugin->factory.open(fullpath.c_str(), factory_name.c_str()))
                return;
        }
#endif


#ifdef CMAKE_INTDIR
        // On multi-config system, try to find the plugin in the
        // current config subdirectory

#    if defined(_MSC_VER) && !defined(NDEBUG)
        // MSVC DEBUG build: try debug name before basic name
        if (!has_ext) {
            fullpath = std::string(CMAKE_INTDIR) + "/" + basename + "d" + ext;
            if (plugin->factory.open(fullpath.c_str(), factory_name.c_str()))
                return;
        }
#    endif

        // Basic name
        fullpath = std::string(CMAKE_INTDIR) + "/" + basename + ext;
        if (plugin->factory.open(fullpath.c_str(), factory_name.c_str()))
            return;

#    if defined(_MSC_VER) && defined(NDEBUG)
        // MSVC RELEASE build: try debug name after basic name
        if (!has_ext) {
            fullpath = std::string(CMAKE_INTDIR) + "/" + basename + "d" + ext;
            if (plugin->factory.open(fullpath.c_str(), factory_name.c_str()))
                return;
        }
#    endif

#endif
    }
};

#endif // ROBOTTESTINGFRAMEWORK_DLLPLUGINLOADERIMPL_H
