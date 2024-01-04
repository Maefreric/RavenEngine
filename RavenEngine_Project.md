# RavenEngine Project Documentation

## Overview

RavenEngine is an aspiring game engine built primarily in C++ and aimed at providing a comprehensive platform for game development. It focuses on utilizing OpenGL and GLFW for rendering and window management. The engine is designed with the goal of simplicity, performance, and usability. The project's home is hosted on GitHub at [RavenEngine Repository](https://github.com/Maefreric/RavenEngine).

## Goals

- Develop a game engine that adopts best practices and structures aligned with industry standards.
- Implement both 2D and 3D rendering capabilities, starting with 2D.
- Create an engine that supports the development process from ideation to final build.

## Core Components

- **Window Management**: Leveraging GLFW for efficient window creation and management.
- **Rendering**: Implementing a rendering system that supports both 2D and 3D graphics.
- **Input Handling**: A robust input system for user interaction with games and the engine itself.
- **UI/UX**: Intuitive and responsive user interfaces for the engine tools and in-game components.
- **Asset Management**: Efficient management and manipulation of various game assets.
- **Audio Engine**: Integrating an audio system for in-game sounds and music.
- **Animation**: Tools for creating and managing animations.
- **Documentation Builder**: A component allowing developers to create game design documents and resources within the engine environment.
- **Utility Tools**: Various tools such as a 'Checklist Maker' for task management within the engine.

## Special Features

- **Liquid Windows**: An innovative UI concept for a more dynamic and interactive window management experience within the engine's workspace. (Note: This feature is considered an easter egg and may be adjusted based on resource implications.)

## Color Palette

- Background: `#181818`
- Foreground/Text: `#FEFEFE`
- Main Accent: `#2F2B42`
- Blue `#6969B3`
- Red `#E32A46`
- Green `#69B578`

## Logo

The RavenEngine logo, featuring a stylized raven, is a key visual element of the engine's branding. The logo is not subject to change and is an integral part of the engine's identity.

![RavenEngine Logo](Assets/RavenLogoImgs/ravenPFP.png)

## Development Roadmap

1. Initialize project structure and set up basic window management.
2. Develop a rendering pipeline for 2D graphics.
3. Expand the engine with additional core components.
4. Iteratively add features and improve the engine based on user feedback and testing.
5. Implement the Documentation Builder and Utility Tools to enhance developer productivity.
6. Finalize the UI/UX of the engine, ensuring a seamless user experience.

## Current Directory Structure

RAVENENGINE
├── .vscode
├── Assets
│ └── images
│ | ├── cursors
│ | ├── icons
│ | └── logoStuff
│ ├── models
│ ├── sounds
│ └── textures
├── build
├── docs
├── include
│ └── components
│ | ├── component.h
│ | ├── componentcreator.h
│ | └── componentmanager.h
│ └── core
│ | ├──windowmanager.h
│ | └──workspace.h
│ └── utils
│ | ├── imguisetup.h
│ | ├── menusystem.h
│ | └── resourcemanager.h
├── libs
│ ├── imgui
│ └── stb
├── src
│ └── components
│ | ├── component.cpp
│ | ├── componentcreator.cpp
│ | └── componentmanager.cpp
│ ├── main.cpp
│ ├── MenuSystem.cpp
│ ├── ResourceManager.cpp
│ ├── WindowManager.cpp
│ └── Workspace.cpp
├── CMakeLists.txt
├── fileStructure.md
├── README.md
└── resources.rc

## Contribution Guidelines

Contributors are welcome to join the RavenEngine project. Please refer to the [CONTRIBUTING.md](https://github.com/Maefreric/RavenEngine/blob/main/CONTRIBUTING.md) file for guidelines on how to contribute effectively.

## License

RavenEngine is licensed under the [MIT License](https://github.com/Maefreric/RavenEngine/blob/main/LICENSE).

## Contact

For any inquiries or contributions, please open an issue on the GitHub repository or contact the maintainers at [RavenEngine Contact](mailto:contact@example.com).
