cmake_minimum_required(VERSION 3.0.0)
project(MuserSDL VERSION 0.1.0)

include(CTest)
enable_testing()

include(sdl/lib/cmake/SDL2/sdl2-config.cmake)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(MuserSDL main.cpp)

target_include_directories(MuserSDL PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(MuserSDL ${SDL2_LIBRARIES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
