#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdio.h>

#define LOG(level, ...)  _LOG_ ## level(__VA_ARGS__)

#if LOG_LEVEL >= 1
#define _LOG_ERROR(...)  __LOG(ERROR, __VA_ARGS__)
#else
#define _LOG_ERROR(...)
#endif

#if LOG_LEVEL >= 2
#define _LOG_DEBUG(...)  __LOG(DEBUG, __VA_ARGS__)
#else
#define _LOG_DEBUG(...)
#endif

#define _LOG_SIZEOF(...)  __LOG_SIZEOF(__VA_ARGS__,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0)
#define __LOG_SIZEOF(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,N,...)  N
#define _LOG_EVAL(x) x
#define __LOG(level, ...)  ___LOG(_LOG_SIZEOF(__VA_ARGS__), level, __VA_ARGS__)
#define ___LOG(n, ...)  ____LOG(n, __VA_ARGS__)
#define ____LOG(n, ...)  ____LOG ## n(__VA_ARGS__)
#define ____LOG1(level, format)  printf(#level "\t" format "\n\r")
#define ____LOG2(level, format, ...)  printf(#level "\t" format "\n\r", __VA_ARGS__)

#define UNUSED(...)  (void)sizeof(__unused_log_f(__VA_ARGS__))
int __unused_log_f(const char *fmt, ...);

#endif //_LOGGER_H_