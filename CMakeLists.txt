cmake_minimum_required(VERSION 3.0.0)
project(MuserSDL VERSION 0.1.0)

set(MUSER_VERSION "0.0.1-alpha")

include(CTest)
enable_testing()

add_subdirectory(spdlog)

include_directories(${PROJECT_SOURCE_DIR}/sdl/include
                    res include spdlog/include/spdlog)
link_directories(${PROJECT_SOURCE_DIR}/sdl/lib/x64)
link_libraries(SDL2 SDL2main spdlog)
message(${PROJECT_SOURCE_DIR})
aux_source_directory(src MUSER_SOURCE_FILES)
aux_source_directory(include MUSER_INCLUDE_FILES)

add_compile_definitions(MUSER_VERSION="${MUSER_VERSION}")

add_executable(MuserSDL ${MUSER_SOURCE_FILES} ${MUSER_INCLUDE_FILES})

set_property(TARGET MuserSDL PROPERTY CXX_STANDARD 17)

target_link_libraries(MuserSDL SDL2 SDL2main spdlog)
target_include_directories(MuserSDL PUBLIC sdl/include include spdlog/include/spdlog)

add_custom_command(TARGET MuserSDL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/sdl/lib/x64"
        $<TARGET_FILE_DIR:MuserSDL>)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
