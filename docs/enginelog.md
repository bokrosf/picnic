# Engine evolution

Engine architectural decisions, problems. Used as a development diary to look back later on the process.

# Imported engine code from snake project
2025-02-01

Imported basic engine classes from the snake project because this engine will use the same Entity Component System architecture and considered an evolution of the previous engine. The concepts are similar but in some cases it favours modules instead of classes.

# SDL2 lib referencing
2025-01-31

There is no seperate **lib/<library_name>/include** directory because dependencies managed entirely by CMake configuration. Only the SDL_image header copied to the SDL2 dependency's include directory because it references SDL2 header.

# glm library usage
2025-01-31

glm library used instead of the custom vector2 implementation because the engine will support OpenGL in the future and it's GLSL language. glm library is designed to seamlessly integrate with OpenGL and it's also a fast and reliable library. 

# Modularization instead of singleton
2025-01-31

Refactored some engine related singleton classes to modules because but they are truly modules. No need for class definitions because there is no plan to load multiple app instances by a parent process that manages their lifetimes. Only one engine instance runs per app instances.
- logger
- messenger
- scene_loader
- rendering_engine
- gameplay_engine
- collision_engine

