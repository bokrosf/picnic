# Picnic

A 2D game where the player controls a bear to steal picnic baskets without being detected by the guards.

It's a project to learn how to make a game engine.

## Getting started

The project uses [CMake](https://cmake.org/) to generate the build system.

### 1. Cloning the repositoy:
```git clone https://gitub.com/bokrosf/picnic.git```

### 2. Setting up the project:
The platform specific init script. It generates a Debug mode build system with CMake.
- [Linux](https://github.com/bokrosf/picnic/blob/master/scripts/linux/init.sh): uses the default CMake generator.
- [Windows](https://github.com/bokrosf/picnic/blob/master/scripts/windows/init.ps1): uses **MinGW MakeFiles** generator but it can be modified by editing the **init.ps1** file [MinGW Releases](https://github.com/niXman/mingw-builds-binaries/releases)

### 3. Building the project:
```
cd build/debug
cmake --build .
```

### 4. Creating Release mode build system:
```
mkdir -p build/release
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release ..
```

If necessary specify the generator. For example to use **MinGW** on Windows: ```cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release```
