cmake_minimum_required(VERSION 3.20)
project(FiatLux)

set(CMAKE_CXX_STANDARD 14)
set(FIATLUX_SRC
        main.cpp
        src/glad.c
        src/windowManager.cpp
        include/imgui/imgui.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_impl_glfw.cpp
        include/imgui/imgui_impl_opengl3.cpp
        include/imgui/imgui_tables.cpp
        include/imgui/imgui_widgets.cpp
        src/shaders/blinn_phong_vs.glsl
        src/shaders/blinn_phong_fs.glsl
        src/Shader.cpp
        include/Shader.h
        src/Camera.cpp
        include/Camera.h)
set(DEMO_SRC
        sample_main.cpp
        src/glad.c
        # src/windowManager.cpp
        include/imgui/imgui.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_impl_glfw.cpp
        include/imgui/imgui_impl_opengl3.cpp
        include/imgui/imgui_tables.cpp
        include/imgui/imgui_widgets.cpp
        src/shaders/blinn_phong_vs.glsl
        src/shaders/blinn_phong_fs.glsl
        # src/Shader.cpp
        include/Shader.h
        # src/Camera.cpp
        include/Camera.h)

include_directories(include)
link_directories(lib)

add_executable(LiqSurface ${FIATLUX_SRC})
target_link_libraries(LiqSurface glfw3 opengl32 gdi32)