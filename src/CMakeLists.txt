
file(GLOB_RECURSE ENGINE_SRC "Engine/*.cpp" "Engine/*.hpp")
file(GLOB_RECURSE GAME_SRC "Game/*.cpp" "Game/*.hpp")

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE main.cpp ${ENGINE_SRC}  ${GAME_SRC} )
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Engine ${CMAKE_CURRENT_SOURCE_DIR}/Game)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}  # Project root
)

target_link_libraries(${PROJECT_NAME} PRIVATE vendor)