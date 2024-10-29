# 3D Renderer

## Overview

This project is a 3D Renderer developed using OpenGL in C++, designed to provide an interactive environment for rendering and manipulating 3D models. The application utilizes ImGui for a user-friendly graphical interface and Assimp for importing a variety of 3D model formats. The goal is to create a versatile tool for visualizing 3D assets in real-time.

### Features

- Real-Time Rendering: Efficient rendering of 3D graphics using OpenGL, supporting advanced techniques such as lighting, shading, and texture mapping
- Interactive User Interface: Built with ImGui, the interface allows for easy interaction with the 3D scene, including model transformations and property adjustments.
- Camera Controls: Smooth camera navigation for exploring the 3D environment with zoom, pan, and rotation functionalities.
- Custom Shader Support: Ability to apply custom shaders for enhanced visual effects and rendering quality.
- Logging with spdlog

## Technologies Used

- C++: The primary programming language for implementing the renderer.
- OpenGL: Graphics API for rendering 3D graphics.
- ImGui: Immediate mode GUI library for creating the user interface.
- Assimp: Library for importing 3D model files in various formats.

## Installation
1. Run `git clone --recursive https://github.com/rxxxge/Renderer-in-opengl.git`
2. ```cd Renderer-in-opengl```

## Build
### Windows
1. Run `Setup.bat` in scripts folder. This will generate Visual Studio 2022 solution, `Setup.bat` can be modified for different VS versions.
2. Run GeckoApp project in Visual Studio as it is project executable.

### Other systems
Not supported for now, it is planned to add support for Linux.

## Screenshots

![image](https://github.com/user-attachments/assets/fd5e7750-d6bc-4546-9713-08d43b9a58ed)
![gecko](https://github.com/user-attachments/assets/a8f4803b-fad5-4097-8597-237f8d535090)
