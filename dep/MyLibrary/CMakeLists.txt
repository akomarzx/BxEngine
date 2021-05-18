set(SOURCE_FILES "${CMAKE_SOURCE_DIR}/vendor/stb_image.cpp" "IndexBuffer.cpp" "VertexBuffer.cpp" "VertexArray.cpp" "GDebugMessageCallBack.cpp" "Shader.cpp" "Renderer.cpp"
	"Texture.cpp" 	
   )
add_library(MyLibrary STATIC ${SOURCE_FILES})

find_package(OpenGL REQUIRED)

target_include_directories	(MyLibrary  					PUBLIC ${CMAKE_SOURCE_DIR}/dep/MyLibrary/header
										PUBLIC ${CMAKE_SOURCE_DIR}/dep/glew/include
										PUBLIC ${CMAKE_SOURCE_DIR}/dep/glfw/include
										PUBLIC ${PROJECT_BINARY_DIR}
										PUBLIC ${CMAKE_SOURCE_DIR}/vendor/include			
				)

target_link_libraries	(      MyLibrary PRIVATE OpenGL::GL
										 PRIVATE glfw
										 PRIVATE libglew_static
						)
