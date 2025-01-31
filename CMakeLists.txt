cmake_minimum_required(VERSION 3.29.0)
project(picnic)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 0af55ccecd98d4e5a8d1fad7de25ba429d60e863 # v1.0.1
)

FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL
  GIT_TAG f461d91cd265d7b9a44b4d472b1df0c0ad2855a0 # release-2.30.2
)

FetchContent_Declare(
  SDL2_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
  GIT_TAG abcf63aa71b4e3ac32120fa9870a6500ddcdcc89 # release-2.8.2
)

FetchContent_MakeAvailable(glm SDL2 SDL2_image)

add_executable("${PROJECT_NAME}"
  src/engine/logging/logger.cpp
  src/engine/messaging/messenger.cpp
  src/game/main.cpp)

target_link_libraries("${PROJECT_NAME}"
  PRIVATE glm::glm-header-only
  PRIVATE SDL2::SDL2main
  PRIVATE SDL2::SDL2
  PRIVATE SDL2_image::SDL2_image
)

file(
  COPY "${SDL2_image_SOURCE_DIR}/include/SDL_image.h"
  DESTINATION "${SDL2_BINARY_DIR}/include/SDL2"
  PATTERN "*.h")

target_include_directories("${PROJECT_NAME}"
  PRIVATE "src"
  PRIVATE "${SDL2_BINARY_DIR}/include/")
