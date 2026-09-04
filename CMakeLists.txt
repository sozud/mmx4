cmake_minimum_required(VERSION 3.20)

project(mmx4_pc C)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(FATAL_ERROR "The MMX4 PC build currently supports Linux only")
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tools/psyz/psyz/CMakeLists.txt")
    message(FATAL_ERROR
        "Psy-Z is missing; run: git submodule update --init tools/psyz")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/D9840.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_30.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_31.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_32.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_33.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_34.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_35.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_36.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_38.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_39.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_40.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_42.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_43.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_44.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_45.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_46.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_49.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_50.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_51.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_52.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_53.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_55.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/misc/misc_57.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/quads/quad_03.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/quads/quad_04.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/quads/quad_05.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/quads/quad_06.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/quads/quad_08.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/quads/quad_09.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/quads/quad_10.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/unks/unk_00.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/unks/unk_01.c
)

file(GLOB MMX4_PC_FUNCTION_TABLE_SOURCES CONFIGURE_DEPENDS
    src/main/function_tables/*.c)
list(APPEND MMX4_PC_GAME_SOURCES ${MMX4_PC_FUNCTION_TABLE_SOURCES})

add_executable(mmx4_pc
    src/pc/main.c
    src/pc/oracle_capture.c
    src/pc/placeholder.c
    src/pc/stubs.c
    ${MMX4_PC_GAME_SOURCES}
)

target_compile_definitions(mmx4_pc PRIVATE MMX4_PC=1 __psyz=1 SKIP_MDEC=1)
target_compile_options(mmx4_pc PRIVATE -ffunction-sections -fdata-sections)
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(mmx4_pc PRIVATE
        -Wno-error=implicit-function-declaration)
endif()
target_include_directories(mmx4_pc PRIVATE include tools/psyz/psyz/include)
target_link_libraries(mmx4_pc PRIVATE psyz)
target_link_options(mmx4_pc PRIVATE -Wl,--gc-sections)

psyz_title(mmx4_pc "Mega Man X4")

include(CTest)
if(BUILD_TESTING)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
    add_test(
        NAME oracle_black_capture
        COMMAND "${Python3_EXECUTABLE}"
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/oracle/run_pc_scene_suite.py"
            --binary "$<TARGET_FILE:mmx4_pc>"
            --output "${CMAKE_CURRENT_BINARY_DIR}/oracle-black-capture"
    )
endif()
