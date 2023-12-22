cmake_minimum_required(VERSION 3.12)
project(RavenEngine)

# Find the GLFW3 package using vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Set the include directories for your project
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends"
)

# Glob all the ImGui source files
file(GLOB IMGUI_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp"
)

# Define all the source files for your project
set(PROJECT_SOURCES
    src/main.cpp
    src/WindowManager.cpp
    src/MenuSystem.cpp
    src/ImGuiSetup.cpp
    src/ResourceManager.cpp
    resources.rc # Assuming resources.rc is in the project root directory
)

# Define all the header files for your project
set(PROJECT_HEADERS
    include/WindowManager.h
    include/MenuSystem.h
    include/ImGuiSetup.h
    include/ResourceManager.h
)

# Add executable target with the source and header files
add_executable(RavenEngine 
    ${PROJECT_SOURCES} 
    ${IMGUI_SOURCES} 
    ${PROJECT_HEADERS}
)

# Link your executable with the GLFW library and OpenGL (required by ImGui)
target_link_libraries(RavenEngine PRIVATE glfw OpenGL::GL)
