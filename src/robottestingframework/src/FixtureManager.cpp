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


#include <robottestingframework/Arguments.h>
#include <robottestingframework/FixtureManager.h>

#include <cstring>
#include <utility>

using namespace robottestingframework;
using namespace std;

FixtureManager::FixtureManager(std::string param) :
        dispatcher(nullptr), param(std::move(param))
{
}


FixtureManager::FixtureManager(FixtureEvents* dispatcher,
                               string param) :
        dispatcher(dispatcher),
        param(std::move(param))
{
}

FixtureManager::~FixtureManager() = default;

bool FixtureManager::setup()
{
    char* szenv = new char[param.size() + 1];
    strcpy(szenv, param.c_str());
    int argc = 0;
    char** argv = new char*[128]; // maximum 128
    Arguments::parse(szenv, &argc, argv);
    argv[argc] = nullptr;
    bool ret = setup(argc, argv);
    delete[] szenv;
    delete[] argv;
    return ret;
}

bool FixtureManager::setup(int argc, char** argv)
{
    return true;
}


void FixtureManager::tearDown()
{
}


bool FixtureManager::check()
{
    return true;
}


void FixtureManager::setDispatcher(FixtureEvents* dispatcher)
{
    this->dispatcher = dispatcher;
}


FixtureEvents* FixtureManager::getDispatcher()
{
    return dispatcher;
}


void FixtureManager::setParam(const std::string param)
{
    this->param = param;
}

std::string FixtureManager::getParam()
{
    return param;
}
