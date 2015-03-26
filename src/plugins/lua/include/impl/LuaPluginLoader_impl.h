// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_LUAPLUGINLOADER_IMPL_H
#define _RTF_LUAPLUGINLOADER_IMPL_H

#include <string>
#include <TestCase.h>
#include <lua.h>
#include <lualib.h>

namespace RTF {
    namespace plugin {
        class LuaPluginLoaderImpl;
    }
}

/**
 * @brief The LuaPluginLoaderImpl loads an test case plug-in and
 * gives the direct access to the TestCase.
 */
class RTF::plugin::LuaPluginLoaderImpl : public RTF::TestCase{

public:

    /**
     * LuaPluginLoaderImpl constructor
     */
    LuaPluginLoaderImpl();

    /**
     *  LuaPluginLoaderImpl destructor
     */
    virtual ~LuaPluginLoaderImpl();

    /**
     * @brief open Loads a test case plugin
     * @param filename the plugin filename
     * @return A pointer to the test case loaded from the
     * plugin or a null pointer in case of failure.
     */
    RTF::TestCase* open(const std::string filename);

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

    virtual bool setup(int argc, char**argv);

    virtual void tearDown();

    virtual void run();


private:
    bool getLocalFunction(const char *name);
    bool registerExtraFunctions(void);

    // lua accessible fucntions
    static int setName(lua_State* L);
    static int assertError(lua_State* L);
    static int assertFail(lua_State* L);
    static int testReport(lua_State* L);
    static int testFail(lua_State* L);

private:
    lua_State *L;
    std::string filename;
    std::string error;    
#if LUA_VERSION_NUM > 501
    static const struct luaL_Reg luaPluginLib[];
#else
    static const struct luaL_reg luaPluginLib[];
#endif
};

#endif // _RTF_LUAPLUGINLOADER_IMPL_H
