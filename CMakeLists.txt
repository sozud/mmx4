cmake_minimum_required(VERSION 3.20)

project(mmx4_pc C)

if(NOT CMAKE_SYSTEM_NAME MATCHES "Linux|Darwin")
    message(FATAL_ERROR "The MMX4 PC build currently supports Linux and macOS only")
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tools/psyz/psyz/CMakeLists.txt")
    message(FATAL_ERROR
        "Psy-Z is missing; run: git submodule update --init tools/psyz")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(MMX4_PC_ASAN "Trap accesses to placeholder game data" ON)

add_subdirectory(tools/psyz/psyz tools/psyz-build)

file(GLOB MMX4_PC_GAME_SOURCES CONFIGURE_DEPENDS
    src/main/*.c
    src/main/data/*.c
    src/main/effects/*.c
    src/main/items/*.c
    src/main/layers/*.c
    src/main/mains/*.c
    src/main/misc/*.c
    src/main/quads/*.c
    src/main/shots/*.c
    src/main/unks/*.c
    src/main/visuals/*.c
    src/main/weapons/*.c
)

list(REMOVE_ITEM MMX4_PC_GAME_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/D9840.c)

file(GLOB MMX4_PC_FUNCTION_TABLE_SOURCES CONFIGURE_DEPENDS
    src/main/function_tables/*.c)
list(REMOVE_ITEM MMX4_PC_FUNCTION_TABLE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010EC30.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010EC38.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010ECD8.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010EDDC.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010EED8.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010EEF4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010EF00.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010EF0C.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010EF20.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010EFC4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010EFD0.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F014.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F188.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F1A4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F1E0.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F4AC.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F4BC.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F528.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F530.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F538.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F544.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F58C.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/function_tables/D_8010F5BC.c
)
list(APPEND MMX4_PC_GAME_SOURCES ${MMX4_PC_FUNCTION_TABLE_SOURCES})

add_executable(mmx4_pc
    src/pc/input.c
    src/pc/loading.c
    src/pc/main.c
    src/pc/objectlog.c
    src/pc/oracle.c
    src/pc/placeholder.c
    src/pc/renderlog.c
    src/pc/screenshot.c
    src/pc/stubs.c
    src/pc/threads.c
    ${MMX4_PC_GAME_SOURCES}
)

target_compile_definitions(mmx4_pc PRIVATE MMX4_PC=1 __psyz=1 SKIP_MDEC=1)
target_compile_options(mmx4_pc PRIVATE -ffunction-sections -fdata-sections)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(mmx4_pc PRIVATE
        -fno-strict-aliasing
        -Werror=implicit-function-declaration)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(mmx4_pc PRIVATE
        -Wno-error=int-conversion
        -Wno-error=incompatible-function-pointer-types)
endif()
target_include_directories(mmx4_pc PRIVATE include tools/psyz/psyz/include)
target_link_libraries(mmx4_pc PRIVATE psyz)
if(APPLE)
    target_link_options(mmx4_pc PRIVATE -Wl,-dead_strip)
else()
    target_link_options(mmx4_pc PRIVATE -Wl,--gc-sections)
endif()
if(MMX4_PC_ASAN AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_definitions(mmx4_pc PRIVATE MMX4_PC_ASAN=1)
    target_compile_options(mmx4_pc PRIVATE
        -fsanitize=address
        -fno-omit-frame-pointer)
    target_link_options(mmx4_pc PRIVATE -fsanitize=address)
endif()

psyz_title(mmx4_pc "Mega Man X4")

include(CTest)
if(BUILD_TESTING)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
    add_test(
        NAME pc_scene_suite
        COMMAND "${Python3_EXECUTABLE}"
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/oracle/run_pc_scene_suite.py"
            --binary "$<TARGET_FILE:mmx4_pc>"
            --output "${CMAKE_CURRENT_BINARY_DIR}/pc-object-changes"
    )
endif()
