// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <Plugin.h>
#include <Asserter.h>
#include <TestAssert.h>
#include <RubyPluginLoader.h>
#include <RubyPluginLoader_impl.h>

using namespace std;
using namespace RTF;
using namespace RTF::plugin;


/**
 * @brief RubyPluginLoaderImpl
 */

RubyPluginLoaderImpl::RubyPluginLoaderImpl()
    : TestCase("") {
}

RubyPluginLoaderImpl::~RubyPluginLoaderImpl() {
    close();
}

void RubyPluginLoaderImpl::close() {

}

TestCase* RubyPluginLoaderImpl::open(const std::string filename) {
    close();
    this->filename = filename;

    setTestName(extractFileName(filename));

    return this;
}

void RubyPluginLoaderImpl::setTestName(const std::string name) {
    Test::setName(name);
}

const std::string RubyPluginLoaderImpl::getLastError() {

    return error;
}

const std::string RubyPluginLoaderImpl::getFileName() {
    return filename;
}

bool RubyPluginLoaderImpl::setup(int argc, char**argv) {

    return true;
}

void RubyPluginLoaderImpl::tearDown() {
}

void RubyPluginLoaderImpl::run() {
}
/*
int RubyPluginLoaderImpl::setName(lua_State* L) {
    return 0;
}

int RubyPluginLoaderImpl::assertError(lua_State* L) {
    return 0;
}

int RubyPluginLoaderImpl::assertFail(lua_State* L) {
    return 0;
}

int RubyPluginLoaderImpl::testReport(lua_State* L) {
    return 0;
}

int RubyPluginLoaderImpl::testFail(lua_State* L) {
    return 0;
}
*/

std::string RubyPluginLoaderImpl::extractFileName(const std::string& path) {

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
 * @brief RubyPluginLoader
 */
RubyPluginLoader::RubyPluginLoader()
    : implementaion(NULL) { }

RubyPluginLoader::~RubyPluginLoader() {
    close();
}

void RubyPluginLoader::close() {
    if(implementaion)
        delete ((RubyPluginLoaderImpl*)implementaion);
    implementaion = NULL;
}

TestCase* RubyPluginLoader::open(const std::string filename) {
    close();
    implementaion = new RubyPluginLoaderImpl();
    return ((RubyPluginLoaderImpl*)implementaion)->open(filename);
}

const std::string RubyPluginLoader::getLastError() {
    if(implementaion)
        return ((RubyPluginLoaderImpl*)implementaion)->getLastError();
    return string("");
}


