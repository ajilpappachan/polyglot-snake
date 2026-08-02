cmake_minimum_required(VERSION 3.20)

project(Snake_Core)

add_library(core SHARED src/snake_core.cpp)
target_include_directories(core PUBLIC include)
target_compile_definitions(core PRIVATE DLL_EXPORT)

# enable_testing()
# add_executable(core_test test/core_api_test.cpp)
# target_link_libraries(core_test PRIVATE core)
# add_test(NAME smoke COMMAND core_test)