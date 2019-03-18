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


#ifndef ROBOTTESTINGFRAMEWORK_LUAPLUGINLOADER_IMPL_H
#define ROBOTTESTINGFRAMEWORK_LUAPLUGINLOADER_IMPL_H

#include <robottestingframework/TestCase.h>

#include <lua.hpp>
#include <lualib.h>
#include <string>

namespace robottestingframework {
namespace plugin {

/**
 * @brief The LuaPluginLoaderImpl loads an test case plug-in and
 * gives the direct access to the TestCase.
 */
class LuaPluginLoaderImpl : public robottestingframework::TestCase
{
public:
    /**
     * LuaPluginLoaderImpl constructor
     */
    LuaPluginLoaderImpl();

    /**
     *  LuaPluginLoaderImpl destructor
     */
    ~LuaPluginLoaderImpl() override;

    /**
     * @brief open Loads a test case plugin
     * @param filename the plugin filename
     * @return A pointer to the test case loaded from the
     * plugin or a null pointer in case of failure.
     */
    TestCase* open(const std::string filename);

    /**
     * @brief close Unloads the plugin and deletes any
     * allocated memory.
     */
    void close();

    /**
     * @brief getLastError gets the last error if any.
     * @return returns the last error string.
     */
    const std::string getLastError();

    /**
     * @brief getFileName returns the loaded script file name
     * @return the script file name
     */
    const std::string getFileName();

    /**
     * @brief setTestName set the test case name
     * @param name the test case name
     */
    void setTestName(const std::string name);

    bool setup(int argc, char** argv) override;

    void tearDown() override;

    void run() override;


private:
    bool getLocalFunction(const char* name);
    bool registerExtraFunctions(void);
    std::string extractFileName(const std::string& path);

    // lua accessible functions
    static int setName(lua_State* L);
    static int assertError(lua_State* L);
    static int assertFail(lua_State* L);
    static int testReport(lua_State* L);
    static int testFail(lua_State* L);
    static int testCheck(lua_State* L);
    static int getTestEnvironment(lua_State* L);

private:
    lua_State* L;
    std::string filename;
    std::string error;
#if LUA_VERSION_NUM > 501
    static const struct luaL_Reg luaPluginLib[];
#else
    static const struct luaL_reg luaPluginLib[];
#endif
};

} // namespace robottestingframework
} // namespace plugin

#endif // ROBOTTESTINGFRAMEWORK_LUAPLUGINLOADER_IMPL_H
