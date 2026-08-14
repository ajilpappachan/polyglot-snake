#ifndef SNAKE_CORE_H
#define SNAKE_CORE_H

#include <stdint.h>

#define SNAKE_CORE_VERSION 3

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

enum SNAKE_STATUS : int32_t
{
    SNAKE_SUCCESS = 0,
    SNAKE_FAILURE = -1
};

CORE_API int32_t CORE_CALL snake_core_version(void);
CORE_API SnakeGame* CORE_CALL snake_create(SnakeConfig config);

CORE_API SNAKE_STATUS CORE_CALL snake_destroy(SnakeGame* pGame);

CORE_API SNAKE_STATUS CORE_CALL snake_grid_dimensions(SnakeGame* pGame, int32_t* out_width, int32_t* out_height);

CORE_API SNAKE_STATUS CORE_CALL snake_segment_count(SnakeGame* pGame, int32_t* out_count);
CORE_API SNAKE_STATUS CORE_CALL snake_segment_data_size(SnakeGame* pGame, int32_t* out_size);
CORE_API SNAKE_STATUS CORE_CALL snake_segment_data(SnakeGame* pGame, int32_t bufferSize, int32_t* pBuffer);

#ifdef __cplusplus
}
#endif

#endif //SNAKE_CORE_H