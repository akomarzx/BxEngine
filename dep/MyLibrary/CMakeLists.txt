set(SOURCE_FILES "IndexBuffer.cpp" "VertexBuffer.cpp" "VertexArray.cpp" "GDebugMessageCallBack")
add_library(MyLibrary STATIC ${SOURCE_FILES})

target_include_directories	(MyLibrary  PUBLIC ${CMAKE_SOURCE_DIR}/dep/MyLibrary/header
										PUBLIC ${CMAKE_SOURCE_DIR}/dep/glew/include
										PUBLIC ${CMAKE_SOURCE_DIR}/dep/glfw/include
							)

