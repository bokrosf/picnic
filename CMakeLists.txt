cmake_minimum_required(VERSION 3.29.0)
project(picnic)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable("${PROJECT_NAME}"
  src/engine/logging/logger.cpp
  src/engine/messaging/messenger.cpp
  src/game/main.cpp)

target_include_directories("${PROJECT_NAME}"
  PRIVATE "src")
