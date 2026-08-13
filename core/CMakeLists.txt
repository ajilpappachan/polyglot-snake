cmake_minimum_required(VERSION 3.20)

project(Snake_Core)

# Use all warnings
add_library(core_warnings INTERFACE)
if(MSVC)
    target_compile_options(core_warnings INTERFACE /W4 /WX)
else()
    target_compile_options(core_warnings INTERFACE -Wall -Wextra -Wpedantic -Werror)
endif()

# Core
add_library(snake_core SHARED
            src/snake_core.cpp 
            src/Game.cpp 
            src/Grid.cpp)
target_include_directories(snake_core PUBLIC include)
target_compile_definitions(snake_core PRIVATE DLL_EXPORT)
target_link_libraries(snake_core PRIVATE core_warnings)

# Tests
enable_testing()

function(add_test_executable target_name)
    add_executable(${target_name} test/${target_name}.cpp)
    target_link_libraries(${target_name} PRIVATE snake_core core_warnings)
    add_test(NAME ${target_name} COMMAND ${target_name})
endfunction()

add_test_executable(core_version)
add_test_executable(create_destroy)
add_test_executable(create_destroy_multiple)
add_test_executable(grid_dimensions)
