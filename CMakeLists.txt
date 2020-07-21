cmake_minimum_required(VERSION 3.0.0)
project(MuserSDL VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(sdl/include)
link_directories(sdl/lib/x64)
message(${PROJECT_SOURCE_DIR})
add_executable(MuserSDL src/main.cpp)
target_link_libraries(MuserSDL SDL2 SDL2main)

target_include_directories(MuserSDL PUBLIC sdl/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
