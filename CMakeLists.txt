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
option(MMX4_PC_COVERAGE "Collect LLVM source coverage during movie checks" OFF)
if(MMX4_PC_COVERAGE AND NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "MMX4_PC_COVERAGE requires Clang and matching LLVM coverage tools")
endif()
set(MMX4_PC_VERSION "us" CACHE STRING "Game version to build: us, jp or eu")
set_property(CACHE MMX4_PC_VERSION PROPERTY STRINGS us jp eu)
if(NOT MMX4_PC_VERSION MATCHES "^(us|jp|eu)$")
    message(FATAL_ERROR "MMX4_PC_VERSION must be us, jp or eu, got ${MMX4_PC_VERSION}")
endif()
string(TOUPPER "${MMX4_PC_VERSION}" MMX4_PC_VERSION_UPPER)

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

add_library(mmx4_game OBJECT
    src/pc/bg_tile_cache.c
    src/pc/input.c
    src/pc/loading.c
    src/pc/memcard.c
    src/pc/objectlog.c
    src/pc/oracle.c
    src/pc/placeholder.c
    src/pc/playerdump.c
    src/pc/renderlog.c
    src/pc/scratchpad.c
    src/pc/screenshot.c
    src/pc/stubs.c
    src/pc/threads.c
    ${MMX4_PC_GAME_SOURCES}
)
target_compile_definitions(mmx4_game PUBLIC MMX4_PC=1 __psyz=1 SKIP_MDEC=1
    VERSION_${MMX4_PC_VERSION_UPPER}=1)
target_compile_options(mmx4_game PUBLIC -ffunction-sections -fdata-sections)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(mmx4_game PUBLIC
        -fno-strict-aliasing
        -Werror=implicit-function-declaration)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(mmx4_game PUBLIC
        -Wno-error=int-conversion
        -Wno-error=incompatible-function-pointer-types)
endif()
target_include_directories(mmx4_game PUBLIC include tools/psyz/psyz/include)
target_link_libraries(mmx4_game PUBLIC psyz z)
if(MMX4_PC_COVERAGE)
    target_compile_options(mmx4_game PUBLIC -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(mmx4_game PUBLIC -fprofile-instr-generate)
endif()
if(APPLE)
    target_link_options(mmx4_game PUBLIC -Wl,-dead_strip)
else()
    target_link_options(mmx4_game PUBLIC -Wl,--gc-sections)
endif()
if(MMX4_PC_ASAN AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_definitions(mmx4_game PUBLIC MMX4_PC_ASAN=1)
    target_compile_options(mmx4_game PUBLIC
        -fsanitize=address
        -fno-omit-frame-pointer)
    target_link_options(mmx4_game PUBLIC -fsanitize=address)
endif()

add_executable(mmx4_pc src/pc/main.c)
target_link_libraries(mmx4_pc PRIVATE mmx4_game)

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

    if(MMX4_PC_VERSION STREQUAL "us")
        file(GLOB_RECURSE MMX4_TEST_SOURCES CONFIGURE_DEPENDS tests/main/*.c tests/integration/*.c)
        set(MMX4_TEST_REGISTRY "#include \"test_runtime.h\"\n")
        set(MMX4_TEST_SUITES "")
        foreach(source IN LISTS MMX4_TEST_SOURCES)
            file(RELATIVE_PATH suite "${CMAKE_CURRENT_SOURCE_DIR}/tests" "${source}")
            string(REGEX REPLACE "\\.c$" "" suite "${suite}")
            string(MAKE_C_IDENTIFIER "suite_${suite}" symbol)
            set_source_files_properties("${source}" PROPERTIES COMPILE_DEFINITIONS
                "c_test_groups=${symbol}_groups;c_test_group_count=${symbol}_group_count;c_test_count=${symbol}_count")
            string(APPEND MMX4_TEST_REGISTRY
                "extern const struct CTestGroup ${symbol}_groups[];\nextern const u32 ${symbol}_group_count;\n")
            string(APPEND MMX4_TEST_SUITES "    { \"${suite}\", ${symbol}_groups, &${symbol}_group_count },\n")
        endforeach()
        string(APPEND MMX4_TEST_REGISTRY
            "struct CTestSuite { const char* name; const struct CTestGroup* groups; const u32* group_count; };\n"
            "const struct CTestSuite c_test_suites[] = {\n${MMX4_TEST_SUITES}};\n"
            "const u32 c_test_suite_count = COUNT(c_test_suites);\n")
        file(CONFIGURE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/test_registry.c" CONTENT "${MMX4_TEST_REGISTRY}")

        add_library(mmx4_test_application_globals OBJECT src/pc/main.c)
        target_compile_definitions(mmx4_test_application_globals PRIVATE
            main=mmx4_pc_application_main)
        target_link_libraries(mmx4_test_application_globals PRIVATE mmx4_game)

        add_executable(mmx4_tests
            tests/runtime/runner.c
            tests/runtime/test_runtime.c
            "${CMAKE_CURRENT_BINARY_DIR}/test_registry.c"
            $<TARGET_OBJECTS:mmx4_test_application_globals>
            ${MMX4_TEST_SOURCES}
        )
        target_include_directories(mmx4_tests PRIVATE tests tests/runtime)
        if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(mmx4_tests PRIVATE -UNDEBUG)
        endif()
        target_link_libraries(mmx4_tests PRIVATE mmx4_game)
        add_test(NAME unit_tests COMMAND mmx4_tests)
    endif()
endif()
