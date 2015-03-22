// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_PLUGIN_H
#define _RTF_PLUGIN_H

#include <SharedLibraryClass.h>

#define RTF_PLUGIN_FACTORY_NAME     "rtf_dll_factory"
#define RTF_FIXTURE_FACTORY_NAME    "rtf_fixture_factory"

#define PREPARE_PLUGIN(classname) SHLIBPP_DEFINE_SHARED_SUBCLASS(rtf_dll_factory, classname, classname)
#define PREPARE_FIXTURE_PLUGIN(classname) SHLIBPP_DEFINE_SHARED_SUBCLASS(rtf_fixture_factory, classname, classname)

#endif // _RTF_PLUGIN_H
