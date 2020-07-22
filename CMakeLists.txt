cmake_minimum_required(VERSION 3.0.0)
project(MuserSDL VERSION 0.1.0)

set(MUSER_VERSION "0.0.1-alpha")
set(EMBED_RESOURCE_SOURCE "src/resource.cpp")

#Write the resource source

file(WRITE ${EMBED_RESOURCE_SOURCE} 
"\
#include \"resource.hpp\"\n\
namespace muser::resource{\n\
    std::map<std::string, std::string> resources{\n\t\t\
")

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

# Generate resource.cpp
get_filename_component(MUSER_RESOURCE_ABSOLUTE_PATH res ABSOLUTE)
file(GLOB_RECURSE MUSER_RESOURCE_FILES_ABS res/*)
message("Abs files: ${MUSER_RESOURCE_FILES_ABS}")
foreach(ABS_RES_FILE ${MUSER_RESOURCE_FILES_ABS})
    
    file(RELATIVE_PATH MUSER_RESOURCE_FILE_NAME ${MUSER_RESOURCE_ABSOLUTE_PATH} ${ABS_RES_FILE})
    # string(REGEX REPLACE "/|\\." "_" RESOURCE_NAME ${MUSER_RESOURCE_FILE_NAME})
    message("Resource file found: ${ABS_RES_FILE} -> key ${MUSER_RESOURCE_FILE_NAME}")

    # Read the resource file and convert its info to a hex string
    file(READ "${ABS_RES_FILE}" RES_INFO)
    string(LENGTH "${RES_INFO}" RES_INFO_LENGTH)
    string(HEX "${RES_INFO}" RES_INFO)

    # Group the string by 2 bytes
    string(LENGTH "${RES_INFO}" RES_INFO_HEX_LENGTH)
    foreach(INDEX RANGE 0 ${RES_INFO_HEX_LENGTH} 2)
        string(SUBSTRING "${RES_INFO}" ${INDEX} 2 GROUPED)
        list(APPEND GROUPED_RES_INFO "0x${GROUPED}")
    endforeach()

    # Create a declaration in C++
    string(REPLACE ";" "," RESOURCE_INFO_CHAR_LIST "{${GROUPED_RES_INFO}}")
    string(REPLACE ",0x}" "}" RESOURCE_INFO_CHAR_LIST "${RESOURCE_INFO_CHAR_LIST}")
    list(APPEND RESOURCE_LIST "{\"${MUSER_RESOURCE_FILE_NAME}\", std::string(new char[${RES_INFO_LENGTH}]${RESOURCE_INFO_CHAR_LIST})}")

    list(APPEND MUSER_RESOURCE_FILES ${MUSER_RESOURCE_FILE_NAME})
    set(GROUPED_RES_INFO)
    set(GROUPED)
endforeach()

string(REPLACE ";" ",\n\t\t" RESOURCE_LIST "${RESOURCE_LIST}")
file(APPEND "${EMBED_RESOURCE_SOURCE}" "${RESOURCE_LIST}")
file(APPEND "${EMBED_RESOURCE_SOURCE}" "\n\t};\n}")

message("Resource files: ${MUSER_RESOURCE_FILES}")

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
