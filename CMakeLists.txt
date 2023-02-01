cmake_minimum_required(VERSION 3.11)
project(loup-3d)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        src/main.cpp
        src/Window.cpp
        src/Window.h
        src/Config.h
        src/Game.cpp
        src/Game.h
        src/Map.cpp
        src/Map.h
        src/Player.cpp
        src/Player.h
        src/Raycaster.cpp
        src/Raycaster.h
        src/Minimap.cpp
        src/Minimap.h src/EntityType.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

unset(ENV{http_proxy})
unset(ENV{https_proxy})
include(${CMAKE_CURRENT_LIST_DIR}/cmake/raylib.cmake)
include_directories(${CMAKE_CURRENT_LIST_DIR}/jevarg/include)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()

target_link_libraries(${PROJECT_NAME} raylib)