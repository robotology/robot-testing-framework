// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <lua.hpp>
#include "rtf/dll/Plugin.h"
#include "rtf/Asserter.h"
#include "rtf/TestAssert.h"
#include "rtf/lua/LuaPluginLoader.h"
#include "rtf/lua/impl/LuaPluginLoader_impl.h"

using namespace std;
using namespace RTF;
using namespace RTF::plugin;


/**
 * @brief LuaPluginLoaderImpl
 */
#define LUA_TEST_CHECK  "function RTF.testCheck(condition, message) \
                           if(not (condition)) then \
                                RTF.testFail(tostring(condition), message) \
                            end \
                        end"

#if LUA_VERSION_NUM > 501
const struct luaL_Reg LuaPluginLoaderImpl::luaPluginLib [] = {
#else
const struct luaL_reg LuaPluginLoaderImpl::luaPluginLib [] = {
#endif
    {"setName", LuaPluginLoaderImpl::setName},
    {"assertError", LuaPluginLoaderImpl::assertError},
    {"assertFail", LuaPluginLoaderImpl::assertFail},
    {"testReport", LuaPluginLoaderImpl::testReport},
    {"testFail", LuaPluginLoaderImpl::testFail},
    {NULL, NULL}
};


LuaPluginLoaderImpl::LuaPluginLoaderImpl()
    : TestCase(""),
      L(NULL) {

}

LuaPluginLoaderImpl::~LuaPluginLoaderImpl() {
    close();
}

void LuaPluginLoaderImpl::close() {
    if(L){
        lua_close(L);
        L = NULL;
    }
}

TestCase* LuaPluginLoaderImpl::open(const std::string filename) {
    close();
    this->filename = filename;

    // initiate lua state
    L = luaL_newstate();
    luaL_openlibs(L);

    //lua_getglobal( L, "package" );
    //lua_getfield( L, -1, "path" ); // get field "path" from table at top of stack (-1)
    //std::string cur_path = lua_tostring( L, -1 ); // grab path string from top of stack

    // register helper functions and assertions
    registerExtraFunctions();
    lua_newtable(L);
    lua_setglobal(L, "TestCase");
    if( luaL_dostring(L, LUA_TEST_CHECK)) {
        error = Asserter::format("Cannot load LUA_TEST_CHECK because %s",
                                 lua_tostring(L, -1));
        close();
        return NULL;
    }

    if(luaL_loadfile(L, filename.c_str())) {
        error = Asserter::format("Cannot load lua script %s because %s",
                                 filename.c_str(), lua_tostring(L, -1));
        close();
        return NULL;
    }

    if(lua_pcall(L, 0, LUA_MULTRET, 0)) {
        error = Asserter::format("Cannot run lua script %s because %s",
                                 filename.c_str(), lua_tostring(L, -1));
        close();
        return NULL;
    }


     // TODO: make TestCase's element read only!
    lua_pushlightuserdata(L, this);
    lua_setglobal(L, "TestCase_Owner");

    lua_getglobal(L, "TestCase");
    if(lua_istable(L, -1) == 0) {
        error = Asserter::format("The script %s  does not contain any valid \'TestCase\' object.",
                                 filename.c_str());
        close();
        return NULL;
    }

    // check for obligatory functions
    // run() must be implemented
    if(!getLocalFunction("run")) {
        error = Asserter::format("The script %s must implement \'TestCase.run()\' function.",
                                 filename.c_str());
        lua_pop(L, 1);
        close();
        return NULL;
    }
    lua_pop(L,1);

    setTestName(extractFileName(filename));

    return this;
}

void LuaPluginLoaderImpl::setTestName(const std::string name) {
    Test::setName(name);
}

const std::string LuaPluginLoaderImpl::getLastError() {

    return error;
}

const std::string LuaPluginLoaderImpl::getFileName() {
    return filename;
}

bool LuaPluginLoaderImpl::setup(int argc, char**argv) {
    if(getLocalFunction("setup")) {
        // TODO: pass the parameters as argc, argv
        lua_pushstring(L, getParam().c_str());
        if(lua_pcall(L, 1, 1, 0) != 0) {
            error = Asserter::format(lua_tostring(L, -1));
            lua_pop(L, 1);
            RTF_ASSERT_ERROR(error);
        }

        // converting the results
        bool result = (bool) lua_toboolean(L, -1);
        lua_pop(L, 1);
        return result;
    }

    lua_pop(L, 1);
    return true;
}

// TODO: in the Lua test plugin, the teardown will not be called
//       after any exception. This is not coherent with the c++
//       implementaion of test cases.
void LuaPluginLoaderImpl::tearDown() {
    if(getLocalFunction("tearDown")) {
        if(lua_pcall(L, 0, 0, 0) != 0) {
            error = Asserter::format(lua_tostring(L, -1));
            RTF_ASSERT_ERROR(error);
        }
    }
    lua_pop(L, 1);
}

void LuaPluginLoaderImpl::run() {
    if(getLocalFunction("run")) {
        if(lua_pcall(L, 0, 0, 0) != 0) {
            error = Asserter::format(lua_tostring(L, -1));
            RTF_ASSERT_ERROR(error);
        }
    }
    lua_pop(L, 1);
}

bool LuaPluginLoaderImpl::getLocalFunction(const char *name) {
    lua_pushstring(L, name);
    lua_gettable(L, -2);
    return (lua_isfunction(L, -1) == 1);
}

bool LuaPluginLoaderImpl::registerExtraFunctions()
{
#if LUA_VERSION_NUM > 501
    lua_newtable(L);
    luaL_setfuncs (L, LuaPluginLoaderImpl::luaPluginLib, 0);
    lua_pushvalue(L, -1);
    lua_setglobal(L, "RTF");
#else
    luaL_register(L, "RTF", LuaPluginLoaderImpl::luaPluginLib);
#endif
    return true;
}

int LuaPluginLoaderImpl::setName(lua_State* L) {
    const char *cst = luaL_checkstring(L, 1);
    if(cst) {
        lua_getglobal(L, "TestCase_Owner");
        if(!lua_islightuserdata(L, -1)) {
            lua_pop(L, 1);
            RTF_ASSERT_ERROR("Cannot get TestCase_Owner");
            return 0;
        }
        LuaPluginLoaderImpl* owner = static_cast<LuaPluginLoaderImpl*>(lua_touserdata(L, -1));
        lua_pop(L, 1);
        RTF_ASSERT_ERROR_IF(owner!=NULL, "A null instance of TestCase_Owner");
        owner->setTestName(cst);
    }
    return 0;
}

int LuaPluginLoaderImpl::assertError(lua_State* L) {
    const char *cst = luaL_checkstring(L, 1);
    if(cst) {
        lua_getglobal(L, "TestCase_Owner");
        if(!lua_islightuserdata(L, -1)) {
            lua_pop(L, 1);
            RTF_ASSERT_ERROR("Cannot get TestCase_Owner");
            return 0;
        }
        LuaPluginLoaderImpl* owner = static_cast<LuaPluginLoaderImpl*>(lua_touserdata(L, -1));
        lua_pop(L, 1);
        RTF_ASSERT_ERROR_IF(owner!=NULL, "A null instance of TestCase_Owner");
        RTF::Asserter::error(RTF::TestMessage("asserts error with exception",
                                              cst, owner->getFileName(), 0));
    }
    return 0;
}

int LuaPluginLoaderImpl::assertFail(lua_State* L) {
    const char *cst = luaL_checkstring(L, 1);
    if(cst) {
        lua_getglobal(L, "TestCase_Owner");
        if(!lua_islightuserdata(L, -1)) {
            lua_pop(L, 1);
            RTF_ASSERT_ERROR("Cannot get TestCase_Owner");
            return 0;
        }
        LuaPluginLoaderImpl* owner = static_cast<LuaPluginLoaderImpl*>(lua_touserdata(L, -1));
        lua_pop(L, 1);
        RTF_ASSERT_ERROR_IF(owner!=NULL, "A null instance of TestCase_Owner");
        RTF::Asserter::fail(RTF::TestMessage("asserts failure with exception",
                                              cst, owner->getFileName(), 0));
    }
    return 0;
}

int LuaPluginLoaderImpl::testReport(lua_State* L) {
    const char *cst = luaL_checkstring(L, 1);
    if(cst) {
        lua_getglobal(L, "TestCase_Owner");
        if(!lua_islightuserdata(L, -1)) {
            lua_pop(L, 1);
            RTF_ASSERT_ERROR("Cannot get TestCase_Owner");
            return 0;
        }
        LuaPluginLoaderImpl* owner = static_cast<LuaPluginLoaderImpl*>(lua_touserdata(L, -1));
        lua_pop(L, 1);
        RTF_ASSERT_ERROR_IF(owner!=NULL, "A null instance of TestCase_Owner");
        RTF::Asserter::report(RTF::TestMessage("reports",
                                               cst, owner->getFileName(), 0), (TestCase*)owner);
    }
    return 0;
}

int LuaPluginLoaderImpl::testFail(lua_State* L) {
    const char *cond = luaL_checkstring(L, 1);
    const char *cst = luaL_checkstring(L, 2);
    if(cond && cst) {
        lua_getglobal(L, "TestCase_Owner");
        if(!lua_islightuserdata(L, -1)) {
            lua_pop(L, 1);
            RTF_ASSERT_ERROR("Cannot get TestCase_Owner");
            return 0;
        }
        LuaPluginLoaderImpl* owner = static_cast<LuaPluginLoaderImpl*>(lua_touserdata(L, -1));
        lua_pop(L, 1);
        RTF_ASSERT_ERROR_IF(owner!=NULL, "A null instance of TestCase_Owner");
        RTF::Asserter::check(false, RTF::TestMessage("checking ("+string(cond)+")",
                                               cst, owner->getFileName(), 0), (TestCase*)owner);
    }
    return 0;
}

std::string LuaPluginLoaderImpl::extractFileName(const std::string& path) {

#ifdef _WIN32
    size_t i = path.rfind('\\', s.length());
#else
   size_t i = path.rfind('/', path.length());
#endif
   if(i != string::npos)
      return(path.substr(i+1, path.length()-i));
   return(path);
}

/**
 * @brief LuaPluginLoader
 */
LuaPluginLoader::LuaPluginLoader()
    : implementaion(NULL) { }

LuaPluginLoader::~LuaPluginLoader() {
    close();
}

void LuaPluginLoader::close() {
    if(implementaion)
        delete ((LuaPluginLoaderImpl*)implementaion);
    implementaion = NULL;
}

TestCase* LuaPluginLoader::open(const std::string filename) {
    close();
    implementaion = new LuaPluginLoaderImpl();
    return ((LuaPluginLoaderImpl*)implementaion)->open(filename);
}

const std::string LuaPluginLoader::getLastError() {
    if(implementaion)
        return ((LuaPluginLoaderImpl*)implementaion)->getLastError();
    return string("");
}


