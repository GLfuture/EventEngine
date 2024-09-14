#ifndef __GALAY_BASE_H__
#define __GALAY_BASE_H__

#if defined(__linux__)
typedef int GSocket;
#elif defined(__APPLE__)
typedef int GSocket;
#elif defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
typedef HANDLE GSocket;
#else
#error "Unsupported platform"
#endif

#endif