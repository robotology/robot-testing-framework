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


#include <robottestingframework/dll/DllPluginLoader.h>
#include <robottestingframework/dll/Plugin.h>
#include <robottestingframework/dll/impl/DllPluginLoader_impl.h>

using namespace std;
using namespace robottestingframework;
using namespace robottestingframework::plugin;
using namespace shlibpp;

/**
 * @brief DllPluginLoader
 */
DllPluginLoader::DllPluginLoader() :
        implementation(nullptr)
{
}

DllPluginLoader::~DllPluginLoader()
{
    close();
}

void DllPluginLoader::close()
{
    if (implementation)
        delete ((DllPluginLoaderImpl<TestCase>*)implementation);
    implementation = nullptr;
}

TestCase* DllPluginLoader::open(const std::string filename)
{
    close();
    implementation = new DllPluginLoaderImpl<TestCase>();
    return ((DllPluginLoaderImpl<TestCase>*)implementation)->open(filename, ROBOTTESTINGFRAMEWORK_PLUGIN_FACTORY_NAME);
}

std::string DllPluginLoader::getLastError()
{
    if (implementation)
        return ((DllPluginLoaderImpl<TestCase>*)implementation)->getLastError();
    return string("");
}
