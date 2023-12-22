cmake_minimum_required(VERSION 3.12)
project(RavenEngine)

# Find the GLFW3 package using vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Add the ImGui directory to your include paths
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends")

# Add all the Dear ImGui source files and the specific backends you want to compile
file(GLOB IMGUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.cpp")
set(IMGUI_BACKENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp"
)

# Add your main.cpp file from the "src" directory and the ImGui source files to the executable
add_executable(RavenEngine src/main.cpp ${IMGUI_SOURCES} ${IMGUI_BACKENDS})

# Link your executable with the GLFW library and OpenGL (required by ImGui)
target_link_libraries(RavenEngine PRIVATE glfw OpenGL::GL)
