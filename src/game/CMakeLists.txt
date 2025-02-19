add_subdirectory(player)
add_subdirectory(scene)

target_sources("${PROJECT_NAME}" PRIVATE
  fill_screen_renderer.cpp
  game_coordinator.cpp
  main.cpp
  picnic_app.cpp
)
