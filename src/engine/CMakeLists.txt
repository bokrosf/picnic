add_subdirectory(collision)
add_subdirectory(component)
add_subdirectory(logging)
add_subdirectory(messaging)
add_subdirectory(rendering)
add_subdirectory(scene)
add_subdirectory(time)

target_sources("${PROJECT_NAME}" PRIVATE
  activatable.cpp
  app.cpp
  assett.cpp
  display.cpp
  entity.cpp
  entity_name_collision.cpp
  gameplay_engine.cpp
  input.cpp
  object_initializer.cpp
  subsystem_initialization_failed.cpp
)
