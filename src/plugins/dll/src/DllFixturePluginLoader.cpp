// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <rtf/dll/Plugin.h>
#include <rtf/TestCase.h>
#include <rtf/dll/DllFixturePluginLoader.h>
#include <rtf/dll/impl/DllPluginLoader_impl.h>

using namespace std;
using namespace RTF;
using namespace RTF::plugin;
using namespace shlibpp;

/**
 * @brief DllFixturePluginLoader
 */
DllFixturePluginLoader::DllFixturePluginLoader()
    : implementation(nullptr) { }

DllFixturePluginLoader::~DllFixturePluginLoader() {
    close();
}

void DllFixturePluginLoader::close() {
    if(implementation)
        delete ((DllPluginLoaderImpl<TestCase>*)implementation);
    implementation = nullptr;
}

FixtureManager* DllFixturePluginLoader::open(const std::string filename) {
    close();
    implementation = new DllPluginLoaderImpl<FixtureManager>();
    return ((DllPluginLoaderImpl<FixtureManager>*)implementation)->open(filename,
                                                                 RTF_FIXTURE_FACTORY_NAME);
}

const std::string DllFixturePluginLoader::getLastError() {
    if(implementation)
        return ((DllPluginLoaderImpl<FixtureManager>*)implementation)->getLastError();
    return string("");
}
