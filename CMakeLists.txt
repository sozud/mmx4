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

set(MMX4_PC_GAME_SOURCES
    src/main/data/archive_destination_data.c
    src/main/data/archive_selector_data.c
    src/main/data/archive_path_data.c
    src/main/data/archive_data.c
    src/main/data/background_init_data.c
    src/main/data/background_camera_mode_data.c
    src/main/data/background_layout_data.c
    src/main/data/bar_object_update_data.c
    src/main/data/bar_state_update_data.c
    src/main/data/bss.c
    src/main/data/boot_mode_update_data.c
    src/main/data/boot_transition_data.c
    src/main/data/briefing_data.c
    src/main/data/briefing_script_data.c
    src/main/data/briefing_target_data.c
    src/main/data/checkpoint_data.c
    src/main/data/character_select_object_data.c
    src/main/data/character_select_init_data.c
    src/main/data/cd_audio_data.c
    src/main/data/collision_descriptor_data.c
    src/main/data/briefing_layout_data.c
    src/main/data/data.c
    src/main/data/dialogue_window_data.c
    src/main/data/engine_update_data.c
    src/main/data/engine_substate_data.c
    src/main/data/engine_object_aux_data.c
    src/main/data/engine_transition_data.c
    src/main/data/game_info_engine_data.c
    src/main/data/game_info_layout_data.c
    src/main/data/game_info_menu_data.c
    src/main/data/game_info_mode_data.c
    src/main/data/game_info_screen_data.c
    src/main/data/game_info_screen_data_alt.c
    src/main/data/game_info_state_data.c
    src/main/data/game_info_update_data.c
    src/main/data/main_object_data.c
    src/main/data/main_id10_animation_data.c
    src/main/data/layout_dimensions_data.c
    src/main/data/menu_layout_data.c
    src/main/data/menu_character_data.c
    src/main/data/mission_select_data.c
    src/main/data/object_id_data.c
    src/main/data/object_id_data_alt.c
    src/main/data/object_update_data.c
    src/main/data/palette_data.c
    src/main/data/player_mode_data_a.c
    src/main/data/player_mode_data_b.c
    src/main/data/player_animation_flags.c
    src/main/data/player_animation_class_data.c
    src/main/data/player_charge_data.c
    src/main/data/player_collision_data.c
    src/main/data/player_effect_id_data.c
    src/main/data/player_x_animation_data.c
    src/main/data/player_zero_animation_data.c
    src/main/data/player_zero_animation_table.c
    src/main/data/quad_color_data.c
    src/main/data/ready_title_data.c
    src/main/data/ready_line_data.c
    src/main/data/ready_line_pattern_data.c
    src/main/data/ready_text_data.c
    src/main/data/search_light_data.c
    src/main/data/search_light_spawner_data.c
    src/main/data/stage_layout_data.c
    src/main/data/stage_layout_table.c
    src/main/data/stage_layout_briefing_tail.c
    src/main/data/stage_layout_tail.c
    src/main/data/stage0_effect_data.c
    src/main/data/stage_object_margin_data.c
    src/main/data/stage_object_data.c
    src/main/data/stage_object_table_data.c
    src/main/data/tile_effect_data.c
    src/main/1A5BC.c
    src/main/1EC20.c
    src/main/1FD10.c
    src/main/21AB4.c
    src/main/23C14.c
    src/main/2824.c
    src/main/323C.c
    src/main/395D0.c
    src/main/A7878.c
    src/main/BBE34.c
    src/main/C49B0.c
    src/main/C7F34.c
    src/main/character_select.c
    src/main/effect_objs.c
    src/main/data/effect_stage_data.c
    src/main/ready_line.c
    src/main/ready_text.c
    src/main/search_light.c
    src/main/search_light_maker.c
    src/main/select_a_character.c
    src/main/shot_objs.c
    src/main/title_logo.c
    src/main/data/title_animation_data.c
    src/main/data/title_logo_data.c
    src/main/data/title_point_data.c
    src/main/data/title_scaling_data.c
    src/main/data/title_color_data.c
    src/main/title_quad.c
    src/main/data/title_quad_data.c
    src/main/data/title_white_quad_data.c
    src/main/visual_objs.c
    src/main/data/visual_control_data_a.c
    src/main/data/visual_animation_data_a.c
    src/main/data/visual_animation_data_b.c
    src/main/data/visual_palette_index_data.c
    src/main/data/visual_offset_data.c
    src/main/data/visual_sequence_index_data.c
    src/main/data/quad_index_data.c
    src/main/data/quad_sequence_index_data.c
    src/main/data/xa_sequence_data.c
    src/main/data/xa_archive_data.c
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
