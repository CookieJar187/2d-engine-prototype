# Army Defense

A simple C++ OpenGL 2D video game project.
Defend your position against attackers with your comrades.
To mission is to hold out for a defined amount of time.

## Requirements

- CMake
- C++17 compiler
- OpenGL-capable system

## Setup [DON'T DO THIS YET, POSSIBLE MISTAKES IN INSTRUCTIONS]

This project uses **vcpkg** to manage dependencies. To build the project, run the following commands:

1. Clone and bootstrap `vcpkg`:
    Choose a stable location outside the project.
    Example on Windows:
    ```cd C:\```
    ```git clone https://github.com/microsoft/vcpkg.git```
    ```cd vcpkg```
    ```.\bootstrap-vcpkg.bat```
    
2. Set environment variable:
    ```setx VCPKG_ROOT "C:\vcpkg"```

3. In the project directory, run:
    ```cmake --preset default```
    ```cmake --build --preset default```