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

FetchContent_MakeAvailable(glm)

add_executable("${PROJECT_NAME}"
  src/engine/logging/logger.cpp
  src/engine/messaging/messenger.cpp
  src/game/main.cpp)

target_link_libraries("${PROJECT_NAME}"
  PRIVATE glm::glm-header-only
)

target_include_directories("${PROJECT_NAME}"
  PRIVATE "src")
