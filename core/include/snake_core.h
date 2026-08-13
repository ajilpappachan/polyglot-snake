#ifndef SNAKE_CORE_H
#define SNAKE_CORE_H

#include <stdint.h>

#define SNAKE_CORE_VERSION 2

#define SNAKE_SUCCESS 0
#define SNAKE_FAILURE -1

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

typedef struct SnakeGame SnakeGame;

typedef struct SnakeConfig {
    int32_t width;
    int32_t height;
} SnakeConfig;

CORE_API int32_t CORE_CALL snake_core_version(void);

CORE_API SnakeGame* CORE_CALL snake_create(SnakeConfig config);
CORE_API int32_t CORE_CALL snake_destroy(SnakeGame* pGame);

CORE_API int32_t CORE_CALL snake_grid_width(SnakeGame* pGame);
CORE_API int32_t CORE_CALL snake_grid_height(SnakeGame* pGame);

#ifdef __cplusplus
}
#endif

#endif //SNAKE_CORE_H