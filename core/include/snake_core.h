#ifndef CORE_API_H
#define CORE_API_H

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

CORE_API int CORE_CALL snake_core_version();

CORE_API int CORE_CALL snake_game_width();
CORE_API int CORE_CALL snake_game_height();

CORE_API void CORE_CALL snake_init();
CORE_API void CORE_CALL snake_update(float deltatime);
CORE_API void CORE_CALL snake_destroy();

CORE_API int CORE_CALL snake_snake_segments();
CORE_API int CORE_CALL snake_segment_position_x(int segment);
CORE_API int CORE_CALL snake_segment_position_y(int segment);

#ifdef __cplusplus
}
#endif

#endif //CORE_API_H