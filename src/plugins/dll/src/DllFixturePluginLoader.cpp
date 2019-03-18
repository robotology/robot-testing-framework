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


#include <robottestingframework/TestCase.h>
#include <robottestingframework/dll/DllFixturePluginLoader.h>
#include <robottestingframework/dll/Plugin.h>
#include <robottestingframework/dll/impl/DllPluginLoader_impl.h>

using namespace std;
using namespace robottestingframework;
using namespace robottestingframework::plugin;
using namespace shlibpp;

/**
 * @brief DllFixturePluginLoader
 */
DllFixturePluginLoader::DllFixturePluginLoader() :
        implementation(nullptr)
{
}

DllFixturePluginLoader::~DllFixturePluginLoader()
{
    close();
}

void DllFixturePluginLoader::close()
{
    if (implementation)
        delete ((DllPluginLoaderImpl<TestCase>*)implementation);
    implementation = nullptr;
}

FixtureManager* DllFixturePluginLoader::open(const std::string filename)
{
    close();
    implementation = new DllPluginLoaderImpl<FixtureManager>();
    return ((DllPluginLoaderImpl<FixtureManager>*)implementation)->open(filename, ROBOTTESTINGFRAMEWORK_FIXTURE_FACTORY_NAME);
}

const std::string DllFixturePluginLoader::getLastError()
{
    if (implementation)
        return ((DllPluginLoaderImpl<FixtureManager>*)implementation)->getLastError();
    return string("");
}
