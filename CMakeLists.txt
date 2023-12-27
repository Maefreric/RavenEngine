cmake_minimum_required(VERSION 3.12)
project(RavenEngine)

# Find the GLFW3 package using vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Define all the source files for your project
set(PROJECT_SOURCES
    src/main.cpp
    src/WindowManager.cpp
    src/MenuSystem.cpp
    src/ImGuiSetup.cpp
    src/ResourceManager.cpp
    resources.rc # Assuming resources.rc is in the project root directory
    Components/Doodle/Doodle.cpp       # Corrected path for Doodle.cpp
    Components/Doodle/DoodleManager.cpp # Corrected path for DoodleManager.cpp
)

# Glob all the ImGui source files
file(GLOB IMGUI_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp"
)

# Include the subdirectory for Components which will in turn add each component
add_subdirectory(Components)

# Add executable target with the source files
add_executable(RavenEngine 
    ${PROJECT_SOURCES} 
    ${IMGUI_SOURCES}
)

# Include directories for the Doodle component
target_include_directories(RavenEngine PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends"
    "${CMAKE_CURRENT_SOURCE_DIR}/Components/Doodle" # Include path for DoodleManager
)

# Link your executable with the GLFW library and OpenGL (required by ImGui)
target_link_libraries(RavenEngine PRIVATE glfw OpenGL::GL)
