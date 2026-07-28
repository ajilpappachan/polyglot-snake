#ifndef CORE_API_H
#define CORE_API_H

#define CORE_ABI_VERSION 1

#ifdef _WIN32
    #ifdef DLL_EXPORT
        #define CORE_API __declspec(dllexport)
    #else
        #define CORE_API __declspec(dllimport)
    #endif
    #define CORE_CALL __cdecl
#else
    #define CORE_API __attribute__((visibility("default")))
    #define CORE_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

CORE_API int CORE_CALL core_abi_version();

CORE_API int CORE_CALL core_add(int a, int b);

#ifdef __cplusplus
}
#endif

#endif //CORE_API_H