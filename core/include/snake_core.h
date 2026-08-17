#ifndef SNAKE_CORE_H
#define SNAKE_CORE_H

#include <stdint.h>

#define SNAKE_CORE_VERSION 4

#ifdef _WIN32
    #ifdef DLL_EXPORT
        #define CORE_API __declspec(dllexport)
    #else
        #define CORE_API __declspec(dllimport)
    #endif
    #define CORE_CALL __cdecl
#else 
    #ifdef __EMSCRIPTEN__
        #include <emscripten/emscripten.h>
        #define CORE_API EMSCRIPTEN_KEEPALIVE
        #define CORE_CALL
    #else
        #define CORE_API __attribute__((visibility("default")))
        #define CORE_CALL
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum SNAKE_STATUS : int32_t
{
    SNAKE_SUCCESS = 0,
    SNAKE_FAILURE = -1
};

typedef struct SnakeGame SnakeGame;

typedef struct SnakeConfig {
    int32_t width;
    int32_t height;
} SnakeConfig;

typedef struct SnakeSegmentData 
{
    int32_t x;
    int32_t y;
    int32_t direction;
    int32_t color;
} SnakeSegmentData;

typedef struct SnakeGameState
{
    int8_t isRunning; // Careful about padding!
    int32_t segmentCount;
    const SnakeSegmentData* pSegmentData;
} SnakeGameState;

CORE_API int32_t CORE_CALL snake_core_version(void);

CORE_API SnakeGame* CORE_CALL snake_create(SnakeConfig config);

CORE_API SNAKE_STATUS CORE_CALL snake_destroy(SnakeGame* pGame);

CORE_API SNAKE_STATUS CORE_CALL snake_grid_dimensions(SnakeGame* pGame, int32_t* out_width, int32_t* out_height);

CORE_API SNAKE_STATUS CORE_CALL snake_game_state(SnakeGame* pGame, SnakeGameState* pState);

CORE_API SNAKE_STATUS CORE_CALL snake_change_direction(SnakeGame* pGame, int32_t direction);

CORE_API SNAKE_STATUS CORE_CALL snake_update(SnakeGame* pGame);

#ifdef __cplusplus
}
#endif

#endif //SNAKE_CORE_H