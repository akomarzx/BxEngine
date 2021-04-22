set(SOURCE_FILES "IndexBuffer.cpp" "VertexBuffer.cpp" "VertexArray.cpp" "GDebugMessageCallBack")
add_library(MyLibrary STATIC ${SOURCE_FILES})

find_package(OpenGL REQUIRED)

target_include_directories	(MyLibrary  PUBLIC ${CMAKE_SOURCE_DIR}/dep/MyLibrary/header
										PUBLIC ${CMAKE_SOURCE_DIR}/dep/glew/include
										PUBLIC ${CMAKE_SOURCE_DIR}/dep/glfw/include
							)

target_link_libraries	(MyLibrary PRIVATE OpenGL::GL
										 PRIVATE glfw
										 PRIVATE libglew_static
						)
