/*
 * Name  : DeclSpec
 * Path  : 
 * Use   : 
 * Author: Sven Schmidt
 * Date  : 03/03/2012
 */
#pragma once

// EXPORT_SYMBOLS is defined by the compiler in this project only
#ifdef FINITEVOLUME2DLIB_EXPORTS
#define DECL_SYMBOLS_2DLIB __declspec(dllexport)
//#define EXPIMP_TEMPLATE
#else
#define DECL_SYMBOLS_2DLIB __declspec(dllimport)
//#define EXPIMP_TEMPLATE extern
#endif
