# Army Defense

A simple C++ OpenGL 2D video game project.
Defend your position against attackers with your comrades.
The mission is to hold out for a defined amount of time.

## Technologies

- C++20
- OpenGL
- GLFW
- GLAD
- CMake
- vcpkg

## Requirements

- CMake
- Git
- vcpkg
- A C++20 compiler

---

## Setup

The setup instructions bellow were tested on Windows 11 using PowerShell and MSVC. Minor adjustments may be required for other environments.

This project uses **vcpkg** to manage dependencies. To build the project, run the following commands:

### 1. Clone and bootstrap `vcpkg` (Skip this step if you already have vcpkg installed):
   Choose a location outside the project directory. For example:
   `cd C:\`
   `git clone https://github.com/microsoft/vcpkg.git`
   `cd vcpkg`
   `.\bootstrap-vcpkg.bat`

### 2. Set environment variable:
   `setx VCPKG_ROOT "C:\vcpkg"`

### 3. Clone this repository:
   `git clone https://github.com/CookieJar187/army-defense.git`
   `cd army-defense`

### 4. In the project directory, configure the project by running:
   ``cmake -S . -B build ` -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"``

This will automatically install any dependencies listed in `vcpkg.json`.

### 5. Build
   `cmake --build build`

### 6. Run the project with:
   `./build/Debug/ArmyDefense.exe`

---

## Current Project Status

This project is still in early development. Issues are to be expected and features may be subject to change.