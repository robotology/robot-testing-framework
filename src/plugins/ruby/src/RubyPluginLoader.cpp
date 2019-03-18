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


#include <robottestingframework/Asserter.h>
#include <robottestingframework/TestAssert.h>
#include <robottestingframework/dll/Plugin.h>
#include <robottestingframework/ruby/RubyPluginLoader.h>
#include <robottestingframework/ruby/impl/RubyPluginLoader_impl.h>

using namespace std;
using namespace robottestingframework;
using namespace robottestingframework::plugin;


/**
 * @brief RubyPluginLoaderImpl
 */

RubyPluginLoaderImpl::RubyPluginLoaderImpl() :
        TestCase("")
{
}

RubyPluginLoaderImpl::~RubyPluginLoaderImpl()
{
    close();
}

void RubyPluginLoaderImpl::close()
{
    ruby_cleanup(0);
}


VALUE RubyPluginLoaderImpl::wrapSetup(VALUE args)
{
    auto* values = (VALUE*)args;
    VALUE setup = values[0];
    ID id_setup = values[1];
    VALUE param = values[2];
    return rb_funcall(setup, id_setup, 1, param);
}

VALUE RubyPluginLoaderImpl::protectedSetup(VALUE testcase, ID id, VALUE param, RubyPluginLoaderImpl* impl)
{
    int state;
    VALUE args[3];
    args[0] = testcase;
    args[1] = id;
    args[2] = param;
    rb_protect(RubyPluginLoaderImpl::wrapSetup, (VALUE)args, &state);
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(state == 0,
                                                Asserter::format("Error in calling setup() within %s because %s",
                                                                 impl->getFileName().c_str(),
                                                                 RubyPluginLoaderImpl::getRubyErrorMessage().c_str()));
    return state;
}


VALUE RubyPluginLoaderImpl::wrapRun(VALUE args)
{
    auto* values = (VALUE*)args;
    VALUE run = values[0];
    ID id_run = values[1];
    return rb_funcall(run, id_run, 0);
}

VALUE RubyPluginLoaderImpl::protectedRun(VALUE testcase, ID id, RubyPluginLoaderImpl* impl)
{
    int state;
    VALUE args[2];
    args[0] = testcase;
    args[1] = id;
    rb_protect(RubyPluginLoaderImpl::wrapRun, (VALUE)args, &state);
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(state == 0,
                                                Asserter::format("Error in calling run() within %s because %s",
                                                                 impl->getFileName().c_str(),
                                                                 RubyPluginLoaderImpl::getRubyErrorMessage().c_str()));
    return state;
}

VALUE RubyPluginLoaderImpl::wrapTearDown(VALUE args)
{
    auto* values = (VALUE*)args;
    VALUE teardown = values[0];
    ID id_teardown = values[1];
    return rb_funcall(teardown, id_teardown, 0);
}

VALUE RubyPluginLoaderImpl::protectedTearDown(VALUE testcase, ID id, RubyPluginLoaderImpl* impl)
{
    int state;
    VALUE args[2];
    args[0] = testcase;
    args[1] = id;
    rb_protect(RubyPluginLoaderImpl::wrapTearDown, (VALUE)args, &state);
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(state == 0,
                                                Asserter::format("Error in calling tearDown() within %s because %s",
                                                                 impl->getFileName().c_str(),
                                                                 RubyPluginLoaderImpl::getRubyErrorMessage().c_str()));
    return state;
}

TestCase* RubyPluginLoaderImpl::open(const std::string filename)
{
    this->filename = filename;
    string bname = extractFileName(filename);
    RUBY_INIT_STACK;
    ruby_init();
    ruby_script(bname.c_str());
    ruby_init_loadpath();

    // add robottestingframework module functions
    RobotTestingFrameworkModule = rb_define_module("RobotTestingFramework"); // Module name must be uppercase in ruby
    rb_define_module_function(RobotTestingFrameworkModule, "setName", (VALUE(*)(...))RubyPluginLoaderImpl::setName, 1);
    rb_define_module_function(RobotTestingFrameworkModule, "assertError", (VALUE(*)(...))RubyPluginLoaderImpl::assertError, 1);
    rb_define_module_function(RobotTestingFrameworkModule, "assertFail", (VALUE(*)(...))RubyPluginLoaderImpl::assertFail, 1);
    rb_define_module_function(RobotTestingFrameworkModule, "testReport", (VALUE(*)(...))RubyPluginLoaderImpl::testReport, 1);
    rb_define_module_function(RobotTestingFrameworkModule, "testCheck", (VALUE(*)(...))RubyPluginLoaderImpl::testCheck, 2);

    // load the ruby script
    int state = 0;
    rb_protect((VALUE(*)(VALUE))rb_require, (VALUE)filename.c_str(), &state);
    if (state != 0) {
        error = Asserter::format("Cannot load %s because %s.",
                                 filename.c_str(),
                                 RubyPluginLoaderImpl::getRubyErrorMessage().c_str());
        return nullptr;
    }

    // get an instance of TestCase
    // TODO: check the availablities!!!!!
    VALUE cls = rb_const_get(rb_cObject, rb_intern("TestCase"));
    rb_define_const(cls, "TESTCASE_IMPL", Data_Wrap_Struct(cls, 0, 0, this));
    testcase = rb_class_new_instance(0, nullptr, cls);

    setTestName(bname);
    return this;
}

void RubyPluginLoaderImpl::setTestName(const std::string name)
{
    Test::setName(name);
}

std::string RubyPluginLoaderImpl::getLastError()
{
    return error;
}

std::string RubyPluginLoaderImpl::getFileName()
{
    return extractFileName(filename);
}

//TODO: check the return value!!!
bool RubyPluginLoaderImpl::setup(int argc, char** argv)
{
    VALUE param = rb_ary_new();
    for (int i = 0; i < argc; i++)
        rb_ary_push(param, rb_str_new_cstr(argv[i]));
    ID id = rb_intern("setup");
    // TODO: check the return value
    int state = protectedSetup(testcase, id, param, this);
    return true;
}

void RubyPluginLoaderImpl::tearDown()
{
    ID id = rb_intern("tearDown");
    int state = protectedRun(testcase, id, this);
}

void RubyPluginLoaderImpl::run()
{
    ID id_run = rb_intern("run");
    int state = protectedRun(testcase, id_run, this);
}

VALUE RubyPluginLoaderImpl::setName(VALUE self, VALUE obj)
{
    char* name = StringValueCStr(obj);
    RubyPluginLoaderImpl* impl = RubyPluginLoaderImpl::getImpFromRuby();
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(impl, "error in RubyPluginLoaderImpl::getImpFromRuby()");
    impl->setTestName(name);
    return self;
}

VALUE RubyPluginLoaderImpl::assertError(VALUE self, VALUE obj)
{
    char* msg = StringValueCStr(obj);
    RubyPluginLoaderImpl* impl = RubyPluginLoaderImpl::getImpFromRuby();
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(impl, "error in RubyPluginLoaderImpl::getImpFromRuby()");
    Asserter::error(TestMessage("asserts error with exception", msg, impl->getFileName(), 0));
    return self;
}

VALUE RubyPluginLoaderImpl::assertFail(VALUE self, VALUE obj)
{
    char* msg = StringValueCStr(obj);
    RubyPluginLoaderImpl* impl = RubyPluginLoaderImpl::getImpFromRuby();
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(impl, "error in RubyPluginLoaderImpl::getImpFromRuby()");
    Asserter::fail(TestMessage("asserts failure with exception", msg, impl->getFileName(), 0));
    return self;
}

VALUE RubyPluginLoaderImpl::testReport(VALUE self, VALUE obj)
{
    char* msg = StringValueCStr(obj);
    RubyPluginLoaderImpl* impl = RubyPluginLoaderImpl::getImpFromRuby();
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(impl, "error in RubyPluginLoaderImpl::getImpFromRuby()");
    Asserter::report(TestMessage("reports", msg, impl->getFileName(), 0), (TestCase*)impl);
    return self;
}


VALUE RubyPluginLoaderImpl::testCheck(VALUE self, VALUE cond, VALUE message)
{
    char* msg = StringValueCStr(message);
    RubyPluginLoaderImpl* impl = RubyPluginLoaderImpl::getImpFromRuby();
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(impl, "error in RubyPluginLoaderImpl::getImpFromRuby()");
    //std::string str_cond = "false";
    Asserter::testCheck(RTEST(cond), TestMessage("checks", msg, impl->getFileName(), 0), (TestCase*)impl);
    return self;
}


RubyPluginLoaderImpl* RubyPluginLoaderImpl::getImpFromRuby()
{
    VALUE cls = rb_const_get(rb_cObject, rb_intern("TestCase"));
    VALUE testcase_impl = rb_const_get(cls, rb_intern("TESTCASE_IMPL"));
    RubyPluginLoaderImpl* impl = nullptr;
    Data_Get_Struct(testcase_impl, RubyPluginLoaderImpl, impl);
    return impl;
}

std::string RubyPluginLoaderImpl::getRubyErrorMessage()
{
    VALUE lasterr = rb_gv_get("$!");
    VALUE message = rb_obj_as_string(lasterr);
    return StringValueCStr(message);
}

std::string RubyPluginLoaderImpl::getRubyBackTrace()
{
    string btrace;
    if (!NIL_P(rb_errinfo())) {
        VALUE ary = rb_funcall(
            rb_errinfo(), rb_intern("backtrace"), 0);
        int c;
        for (c = 0; c < (RARRAY_LEN(ary)); c++)
            btrace += Asserter::format("%s, ", StringValueCStr(RARRAY_PTR(ary)[c]));
    }
    return btrace;
}

std::string RubyPluginLoaderImpl::extractFileName(const std::string& path)
{
#ifdef _WIN32
    size_t i = path.rfind('\\', s.length());
#else
    size_t i = path.rfind('/', path.length());
#endif
    if (i != string::npos)
        return (path.substr(i + 1, path.length() - i));
    return (path);
}

/**
 * @brief RubyPluginLoader
 */
RubyPluginLoader::RubyPluginLoader() :
        implementation(nullptr)
{
}

RubyPluginLoader::~RubyPluginLoader()
{
    close();
}

void RubyPluginLoader::close()
{
    if (implementation)
        delete ((RubyPluginLoaderImpl*)implementation);
    implementation = nullptr;
}

TestCase* RubyPluginLoader::open(const std::string filename)
{
    close();
    implementation = new RubyPluginLoaderImpl();
    return ((RubyPluginLoaderImpl*)implementation)->open(filename);
}

std::string RubyPluginLoader::getLastError()
{
    if (implementation)
        return ((RubyPluginLoaderImpl*)implementation)->getLastError();
    return string("");
}
