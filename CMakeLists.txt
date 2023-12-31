cmake_minimum_required(VERSION 3.12)
project(RavenEngine)

# Find packages
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Define source files
set(PROJECT_SOURCES
    src/main.cpp
    src/WindowManager.cpp
    src/MenuSystem.cpp
    src/ImGuiSetup.cpp
    src/ResourceManager.cpp
    src/Workspace.cpp
    resources.rc
)

# Glob ImGui sources and backends
file(GLOB IMGUI_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp"
)

# Add subdirectories
add_subdirectory(Components)

# Add executable target
add_executable(RavenEngine ${PROJECT_SOURCES} ${IMGUI_SOURCES} ${COMPONENTS_SOURCES})

# Include directories
target_include_directories(RavenEngine PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends" # Include backends directory
    "${CMAKE_CURRENT_SOURCE_DIR}/Components" # Include Components directory
)

# Link libraries
target_link_libraries(RavenEngine PRIVATE glfw OpenGL::GL)