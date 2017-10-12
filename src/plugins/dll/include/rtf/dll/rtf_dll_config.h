// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2011 Ali Paikan
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _SHLIBPP_CONFIG_
#define _SHLIBPP_CONFIG_

#if defined _WIN32 || defined __CYGWIN__
#  define SHLIBPP_EXPORT __declspec(dllexport)
#else 
#  if defined SHLIBPP_FILTER_API && __GNUC__ >= 4
#    define SHLIBPP_EXPORT __attribute__ ((visibility("default")))
#  else
#    define SHLIBPP_EXPORT
#  endif
#endif

#define SHLIBPP_POINTER_SIZE    8
#define SHLIBPP_SHAREDLIBRARYCLASSAPI_PADDING (30-2*(SHLIBPP_POINTER_SIZE/4))

#endif //_SHLIBPP_CONFIG_
