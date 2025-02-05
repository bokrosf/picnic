# Engine evolution

Engine architectural decisions, problems. Used as a development diary to look back later on the process.

# Modularization instead of singleton
2025-01-31

Refactored some engine related singleton classes to modules because but they are truly modules. No need for class definitions because there is no plan to load multiple app instances by a parent process that manages their lifetimes. Only one engine instance runs per app instances.
- logger
- messenger
- scene_loader
- rendering_engine
- gameplay_engine
- collision_engine

