// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2011 Ali Paikan
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_CONFIG_
#define _RTF_CONFIG_

#if defined(WIN32)
#    define RTF_FILTER_API
#endif

#if defined _WIN32 || defined __CYGWIN__
#  define RTF_HELPER_DLL_IMPORT __declspec(dllimport)
#  define RTF_HELPER_DLL_EXPORT __declspec(dllexport)
#  define RTF_HELPER_DLL_LOCAL
#  define RTF_HELPER_DLL_IMPORT_EXTERN extern
#  define RTF_HELPER_DLL_EXPORT_EXTERN
#  ifndef RTF_NO_DEPRECATED_WARNINGS
#    define RTF_HELPER_DLL_DEPRECATED __declspec(deprecated)
#  endif
#else
#  if __GNUC__ >= 4
#    define RTF_HELPER_DLL_IMPORT __attribute__ ((visibility("default")))
#    define RTF_HELPER_DLL_EXPORT __attribute__ ((visibility("default")))
#    define RTF_HELPER_DLL_LOCAL  __attribute__ ((visibility("hidden")))
#    define RTF_HELPER_DLL_IMPORT_EXTERN
#    define RTF_HELPER_DLL_EXPORT_EXTERN
#  else
#     define RTF_HELPER_DLL_IMPORT
#     define RTF_HELPER_DLL_EXPORT
#     define RTF_HELPER_DLL_LOCAL
#     define RTF_HELPER_DLL_IMPORT_EXTERN
#     define RTF_HELPER_DLL_EXPORT_EXTERN
#  endif
#  if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#    ifndef RTF_NO_DEPRECATED_WARNINGS
#      define RTF_HELPER_DLL_DEPRECATED __attribute__ ((__deprecated__))
#    endif
#  endif
#endif

#ifndef RTF_HELPER_DLL_DEPRECATED
#  define RTF_HELPER_DLL_DEPRECATED
#endif

#if defined RTF_FILTER_API
#  define RTF_IMPORT RTF_HELPER_DLL_IMPORT
#  define RTF_EXPORT RTF_HELPER_DLL_EXPORT
#  define RTF_LOCAL RTF_HELPER_DLL_LOCAL
#  define RTF_IMPORT_EXTERN RTF_HELPER_DLL_IMPORT_EXTERN
#  define RTF_EXPORT_EXTERN RTF_HELPER_DLL_EXPORT_EXTERN
#  define RTF_DEPRECATED RTF_HELPER_DLL_DEPRECATED
#else
#  define RTF_IMPORT
#  define RTF_EXPORT
#  define RTF_LOCAL
#  define RTF_IMPORT_EXTERN
#  define RTF_EXPORT_EXTERN
#  define RTF_DEPRECATED
#endif

//  always export symbols
//#define RTF_API RTF_EXPORT
#define RTF_API

#if (__cplusplus >= 201103L)
#  define RTF_NORETURN //TODO [[noreturn]] see issue #66
#else
#  define RTF_NORETURN
#endif

#endif //_RTF_CONFIG_
