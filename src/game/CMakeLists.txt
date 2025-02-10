add_subdirectory(player)
add_subdirectory(scene)

target_sources("${PROJECT_NAME}" PRIVATE
  main.cpp
  picnic_app.cpp
)
