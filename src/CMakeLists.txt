
file(GLOB_RECURSE ENGINE_SRC "Engine/*.cpp" "Engine/*.hpp")
file(GLOB_RECURSE GAME_SRC "Game/*.cpp" "Game/*.hpp")

add_library(GameLib STATIC ${ENGINE_SRC} ${GAME_SRC})

target_include_directories(GameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GameLib PUBLIC
        SDL3::SDL3
        $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>
        glm::glm
        nlohmann_json::nlohmann_json
        imgui::imgui
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
        vendor
)

if (USE_TRACY)
    target_link_libraries(GameLib PUBLIC Tracy::TracyClient)
    target_compile_definitions(GameLib PUBLIC TRACY_ENABLE)
endif ()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE GameLib)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXCEPTIONS ON)

if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index" SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PRIVATE
            "SHELL:--shell-file ${CMAKE_SOURCE_DIR}/web/shell.html"
            "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/assets@/assets"
            -sALLOW_MEMORY_GROWTH=1
            -sINITIAL_MEMORY=268435456
            -sSTACK_SIZE=1048576
            -sEXIT_RUNTIME=0
            -fexceptions)
    target_compile_options(GameLib PUBLIC -fexceptions)
    target_compile_options(${PROJECT_NAME} PRIVATE -fexceptions)
endif ()
