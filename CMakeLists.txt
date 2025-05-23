cmake_minimum_required(VERSION 3.29.0)
project(picnic)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.tar.gz
)

FetchContent_Declare(
  SDL3
  URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.2.14.tar.gz
)

set(SDL_LIBURING OFF)
set(SDL_TEST_LIBRARY OFF)
set(SDL_TESTS OFF)
FetchContent_MakeAvailable(glm SDL3)

add_executable("${PROJECT_NAME}")
add_subdirectory(src/engine)
add_subdirectory(src/game)
target_compile_options("${PROJECT_NAME}" PRIVATE -Wall)

target_link_libraries("${PROJECT_NAME}"
  PRIVATE glm::glm-header-only
  PRIVATE SDL3::SDL3
)

target_include_directories("${PROJECT_NAME}"
  PRIVATE "src"
  PRIVATE "${SDL3_BINARY_DIR}/include/"
)
