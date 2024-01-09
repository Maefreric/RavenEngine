cmake_minimum_required(VERSION 3.12)
project(RavenEngine)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find packages
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Define source files
set(PROJECT_SOURCES
    src/main.cpp
    src/Core/AppWindow.cpp
    src/Core/Workspace.cpp
    src/Core/Scene.cpp
    src/Components/Component.cpp
    src/Components/ComponentCreator.cpp
    src/Components/ComponentManager.cpp
    src/Components/TransformComponent.cpp
    src/Components/SceneNode.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/Viewport.cpp
    src/Utils/FileDialog.cpp
    src/Utils/ImGuiManager.cpp
    src/Utils/MenuSystem.cpp
    src/Utils/ResourceManager.cpp
    src/Utils/SceneHierarchyPanel.cpp
)

# Add resources file for Windows
if(WIN32)
  list(APPEND PROJECT_SOURCES "resources.rc")
endif()

# Glob ImGui sources and backends
file(GLOB IMGUI_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp"
)

# Add GLAD source
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")

# Add executable target
add_executable(RavenEngine ${PROJECT_SOURCES} ${IMGUI_SOURCES} ${GLAD_SOURCE})

# Include directories
target_include_directories(RavenEngine PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Core"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Components"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Scene"  # Added include directory for scene
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glad"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/KHR"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm"
)

# Link libraries
target_link_libraries(RavenEngine PRIVATE glfw OpenGL::GL)