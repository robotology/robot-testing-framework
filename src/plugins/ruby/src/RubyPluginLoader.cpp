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
    ruby_cleanup(0);
}


VALUE RubyPluginLoaderImpl::wrapSetup(VALUE args) {
    VALUE *values = (VALUE *) args;
    VALUE setup = values[0];
    ID id_setup = values[1];
    VALUE param = values[2];    
    return rb_funcall(setup, id_setup, 1, param);
}

VALUE RubyPluginLoaderImpl::protectedSetup(VALUE testcase, ID id,
                                           VALUE param, RubyPluginLoaderImpl* impl) {
    int state;    
    VALUE args[3];
    args[0] = testcase;
    args[1] = id;
    args[2] = param;
    rb_protect(RubyPluginLoaderImpl::wrapSetup, (VALUE)args, &state);
    RTF_ASSERT_ERROR_IF(state == 0,
                        Asserter::format("Error in calling setup() within %s because %s",
                                         impl->getFileName().c_str(),
                                         RubyPluginLoaderImpl::getRubyErrorMessage().c_str()));
    return state;
}


VALUE RubyPluginLoaderImpl::wrapRun(VALUE args) {
    VALUE *values = (VALUE *) args;
    VALUE run = values[0];
    ID id_run = values[1];
    return rb_funcall(run, id_run, 0);
}

VALUE RubyPluginLoaderImpl::protectedRun(VALUE testcase, ID id,
                           RubyPluginLoaderImpl* impl) {
    int state;
    VALUE args[1];
    args[0] = testcase;
    args[1] = id;
    rb_protect(RubyPluginLoaderImpl::wrapRun, (VALUE)args, &state);
    RTF_ASSERT_ERROR_IF(state == 0,
                        Asserter::format("Error in calling run() within %s because %s",
                                         impl->getFileName().c_str(),
                                         RubyPluginLoaderImpl::getRubyErrorMessage().c_str()));
    return state;
}

VALUE RubyPluginLoaderImpl::wrapTearDown(VALUE args) {
    VALUE *values = (VALUE *) args;
    VALUE teardown = values[0];
    ID id_teardown = values[1];
    return rb_funcall(teardown, id_teardown, 0);
}

VALUE RubyPluginLoaderImpl::protectedTearDown(VALUE testcase, ID id,
                           RubyPluginLoaderImpl* impl) {
    int state;
    VALUE args[1];
    args[0] = testcase;
    args[1] = id;
    rb_protect(RubyPluginLoaderImpl::wrapTearDown, (VALUE)args, &state);
    RTF_ASSERT_ERROR_IF(state == 0,
                        Asserter::format("Error in calling tearDown() within %s because %s",
                                         impl->getFileName().c_str(),
                                         RubyPluginLoaderImpl::getRubyErrorMessage().c_str()));
    return state;
}

TestCase* RubyPluginLoaderImpl::open(const std::string filename) {    
    this->filename = filename;
    string bname = extractFileName(filename);
    RUBY_INIT_STACK;
    ruby_init();
    ruby_script(bname.c_str());
    ruby_init_loadpath();

    // load the ruby script
    int state = 0;
    rb_protect((VALUE (*)(VALUE))rb_require, (VALUE)filename.c_str(), &state);
    if(state != 0) {
        error = Asserter::format("Cannot load %s because %s.",
                                 filename.c_str(),
                                 RubyPluginLoaderImpl::getRubyErrorMessage().c_str());
        return NULL;
    }

    // TODO: fix it to be defined under 'rtf' module
    // add rtf related fucntions to ruby
    //rtfModule = rb_define_module("rtf");
    //rb_define_method(rtfModule, "setName", RubyPluginLoaderImpl::setName, 0);
    //rb_define_module_function(rtfModule, "setName",
    //                          (VALUE(*) (...)) RubyPluginLoaderImpl::setName, 0);
    //rb_define_variable("rtf_impl", );
    //rb_define_global_function("setName",
    //                          (VALUE(*) (...)) RubyPluginLoaderImpl::setName, 1);
    //rb_eval_string("require rtf2");

    // get an instance of TestCase
    // TODO check the availablities!!!!!
    VALUE cls = rb_const_get(rb_cObject, rb_intern("TestCase"));
    rb_define_const(cls, "TESTCASE_IMPL", Data_Wrap_Struct(cls, 0, 0, this));
    rb_define_method(cls,"setName", (VALUE(*) (...)) RubyPluginLoaderImpl::setName, 1);
    testcase = rb_class_new_instance(0, 0, cls);

    setTestName(bname);
    return this;
}

void RubyPluginLoaderImpl::setTestName(const std::string name) {
    Test::setName(name);
}

const std::string RubyPluginLoaderImpl::getLastError() {

    return error;
}

const std::string RubyPluginLoaderImpl::getFileName() {
    return extractFileName(filename);
}

bool RubyPluginLoaderImpl::setup(int argc, char**argv) {

    VALUE param = rb_ary_new();
    for(int i=0; i<argc; i++)
        rb_ary_push(param, rb_str_new_cstr(argv[i]));
    ID id = rb_intern("setup");
    // TODO: check the return value
    int state = protectedSetup(testcase, id, param, this);
    return true;
}

void RubyPluginLoaderImpl::tearDown() {
    ID id = rb_intern("tearDown");
    int state = protectedRun(testcase, id, this);
}

void RubyPluginLoaderImpl::run() {
    ID id_run = rb_intern("run");
    int state = protectedRun(testcase, id_run, this);
}

VALUE RubyPluginLoaderImpl::setName(VALUE self, VALUE obj) {
    char* name = StringValueCStr(obj);
    RubyPluginLoaderImpl* impl = RubyPluginLoaderImpl::getImpFromRuby();
    RTF_ASSERT_ERROR_IF(impl, "error in RubyPluginLoaderImpl::getImpFromRuby()");
    impl->setTestName(name);
    return self;
}

/*
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

RubyPluginLoaderImpl* RubyPluginLoaderImpl::getImpFromRuby() {
    VALUE cls = rb_const_get(rb_cObject, rb_intern("TestCase"));
    VALUE testcase_impl = rb_const_get(cls, rb_intern("TESTCASE_IMPL"));
    RubyPluginLoaderImpl* impl = NULL;
    Data_Get_Struct(testcase_impl, RubyPluginLoaderImpl, impl);
    return impl;
}

std::string RubyPluginLoaderImpl::getRubyErrorMessage() {
    VALUE lasterr = rb_gv_get("$!");
    VALUE message = rb_obj_as_string(lasterr);
    return StringValueCStr(message);
}

std::string RubyPluginLoaderImpl::getRubyBackTrace() {
    string btrace;
    if(!NIL_P(rb_errinfo())) {
        VALUE ary = rb_funcall(
            rb_errinfo(), rb_intern("backtrace"), 0);
        int c;
        for (c=0; c<(RARRAY_LEN(ary)); c++)
            btrace += Asserter::format("%s, ", StringValueCStr(RARRAY_PTR(ary)[c]));
    }
    return btrace;
}

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


