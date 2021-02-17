add_library(fs_imgui_gl3_glfw STATIC 
	imgui.cpp
	imgui_impl_opengl3.cpp
	imgui_impl_glfw.cpp
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_tables.cpp
	imgui_widgets.cpp
)

target_compile_definitions(fs_imgui_gl3_glfw PRIVATE "IMGUI_IMPL_OPENGL_LOADER_GLAD")

target_include_directories(fs_imgui_gl3_glfw 

	PUBLIC include
)

target_link_libraries(fs_imgui_gl3_glfw
	PUBLIC glfw
	PUBLIC Farscape::glad
)


add_library(Farscape::imgui_gl3glfw ALIAS fs_imgui_gl3_glfw)