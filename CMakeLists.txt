cmake_minimum_required(VERSION 3.0.0)
project(MuserSDL VERSION 0.1.0)

set(MUSER_VERSION "0.0.1-alpha")
set(EMBED_RESOURCE_SOURCE "src/resource.cpp")

#Write the resource source

# include(CTest)
# enable_testing()

add_subdirectory(spdlog)

include_directories(${PROJECT_SOURCE_DIR}/sdl/include
                    res include spdlog/include/spdlog)
link_directories(${PROJECT_SOURCE_DIR}/sdl/lib/x64)
link_libraries(SDL2 SDL2main spdlog)
message(${PROJECT_SOURCE_DIR})
aux_source_directory(src MUSER_SOURCE_FILES)
aux_source_directory(include MUSER_INCLUDE_FILES)

message("Resource files: ${MUSER_RESOURCE_FILES}")

add_compile_definitions(MUSER_VERSION="${MUSER_VERSION}")

add_executable(MuserSDL 
    ${MUSER_SOURCE_FILES} ${MUSER_INCLUDE_FILES}
    $<TARGET_OBJECTS:muser_resources>)

add_library(muser_resources OBJECT IMPORTED GLOBAL)
file(TOUCH "${CMAKE_CURRENT_BINARY_DIR}/resource.o")
set_property(TARGET muser_resources PROPERTY IMPORTED_OBJECTS ${CMAKE_CURRENT_BINARY_DIR}/resource.o)

set_property(TARGET MuserSDL PROPERTY CXX_STANDARD 17)

# Generate resource.cpp
if(1)
get_filename_component(MUSER_RESOURCE_ABSOLUTE_PATH res ABSOLUTE)
file(GLOB_RECURSE MUSER_RESOURCE_FILES_ABS res/*)
message("Abs files: ${MUSER_RESOURCE_FILES_ABS}")

file(WRITE "${EMBED_RESOURCE_SOURCE}" "\
#include \"resource.hpp\"\n")
foreach(ABS_RES_FILE ${MUSER_RESOURCE_FILES_ABS})
    file(RELATIVE_PATH MUSER_RESOURCE_FILE_NAME ${PROJECT_SOURCE_DIR}/build ${ABS_RES_FILE})
    file(RELATIVE_PATH MUSER_RESOURCE_KEY_NAME ${MUSER_RESOURCE_ABSOLUTE_PATH} ${ABS_RES_FILE})
    message("Resource file found: ${ABS_RES_FILE} -> key ${MUSER_RESOURCE_FILE_NAME}")
    set(RESOURCE_OUTPUT_FILE ${MUSER_RESOURCE_FILE_NAME}.o)
    string(REGEX REPLACE "/|\\." "_"  MUSER_RESOURCE_NAME "${MUSER_RESOURCE_FILE_NAME}")
    # http://gareus.org/wiki/embedding_resources_in_executables#architecture_abstraction_--_working_solution
    if(APPLE)
        target_compile_options(MuserSDL PRIVATE -sectcreate __DATA __${MUSER_RESOURCE_NAME} ${MUSER_RESOURCE_FILE_NAME})
    else()
        message("$<TARGET_FILE:MuserSDL>")
        # target_link_options(MuserSDL BEFORE PRIVATE -r -b binary ${ABS_RES_FILE})
        
    endif()
    file(APPEND "${EMBED_RESOURCE_SOURCE}" "EXTLD(${MUSER_RESOURCE_NAME});\n\t")
    list(APPEND MUSER_RESOURCE_INIT_FN "\
resources.insert_or_assign(\"${MUSER_RESOURCE_KEY_NAME}\", \n\t\t\t\
ResourceEntry{reinterpret_cast<const char*>(LDVAR(${MUSER_RESOURCE_NAME})),static_cast<len_t>(LDLEN(${MUSER_RESOURCE_NAME}))})?\n\t\t")
    list(APPEND MUSER_RESOURCE_FILES "${MUSER_RESOURCE_FILE_NAME}")
endforeach()

if(NOT APPLE)
    add_custom_command(
            PRE_LINK
            TARGET MuserSDL
            COMMAND ld -r -b binary -o ${CMAKE_CURRENT_BINARY_DIR}/resource.o ${MUSER_RESOURCE_FILES}
            COMMAND objcopy --rename-section .data=.rodata,alloc,load,readonly,data,contents ${CMAKE_CURRENT_BINARY_DIR}/resource.o ${CMAKE_CURRENT_BINARY_DIR}/resource.o
            COMMAND echo "${MUSER_RESOURCE_FILES} compiled to ${CMAKE_CURRENT_BINARY_DIR}/resource.o"
            COMMENT "Adding resource files...")
endif()


file(APPEND "${EMBED_RESOURCE_SOURCE}" "
namespace muser::resource {\n\
\tdecltype(resources) resources;\n\t\
")
string(REPLACE ";" "" MUSER_RESOURCE_INIT_FN "${MUSER_RESOURCE_INIT_FN}")
string(REPLACE "?" ";" MUSER_RESOURCE_INIT_FN "${MUSER_RESOURCE_INIT_FN}")
file(APPEND "${EMBED_RESOURCE_SOURCE}" "\
void InitResources() {\n\t\t")
file(APPEND "${EMBED_RESOURCE_SOURCE}" "${MUSER_RESOURCE_INIT_FN}")
file(APPEND "${EMBED_RESOURCE_SOURCE}" "\n\t\
}\n\
}\n\
")
endif()

target_link_libraries(MuserSDL SDL2 SDL2main spdlog)
target_include_directories(MuserSDL PUBLIC sdl/include include spdlog/include/spdlog visit_struct/include/visit_struct)

add_custom_command(TARGET MuserSDL POST_BUILD
    COMMAND echo "MuserSDL Target Dir: $<TARGET_FILE_DIR:MuserSDL>"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/sdl/lib/x64"
        $<TARGET_FILE_DIR:MuserSDL>)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
