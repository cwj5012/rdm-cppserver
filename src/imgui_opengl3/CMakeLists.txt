add_executable(
        imgui_opengl3
        main.cpp
        imgui_impl_glfw.cpp
        imgui_impl_glfw.h
        imgui_impl_opengl3.cpp
        imgui_impl_opengl3.h
        ./gl3w/GL/gl3w.c
        ./gl3w/GL/gl3w.h
        ./gl3w/GL/glcorearb.h
        ./imgui/imconfig.h
        ./imgui/imgui.cpp
        ./imgui/imgui.h
        ./imgui/imgui_demo.cpp
        ./imgui/imgui_draw.cpp
        ./imgui/imgui_internal.h
        ./imgui/imgui_widgets.cpp
)

if (MSVC)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set_property(TARGET imgui_opengl3 APPEND PROPERTY LINK_FLAGS "/NODEFAULTLIB:MSVCRT")
    endif ()
endif ()

target_link_libraries(
        imgui_opengl3
        "C:/Users/IGG/Desktop/learn-cpp/src/imgui_opengl3/glfw3.lib"
        opengl32.lib
)

include_directories(
        ./imgui
        ./gl3w
        ./include
)