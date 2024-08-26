cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("voxey")

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/include/GLFW"
	"${PROJECT_SOURCE_DIR}/include/KHR"
)

set(SOURCES
"src/main.cpp" "src/ext/glad.c" "src/core/application.h" "src/core/application.cpp" "src/core/logger.h" "src/core/logger.cpp" "src/core/engine.h" "src/core/engine.cpp" "src/utils/time.h" "src/utils/time.cpp" "src/input/inputManager.h" "src/input/inputManager.cpp" "src/rendering/renderer.h" "src/rendering/renderer.cpp" "src/utils/fileManager.h" "src/utils/fileManager.cpp")

add_executable (voxey ${SOURCES} )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET voxey PROPERTY CXX_STANDARD 20)
endif()

set(GLFW_LIB_DIR "${PROJECT_SOURCE_DIR}/lib")

target_link_libraries(voxey
	${OPENGL_LIBRARIES}
	"${GLFW_LIB_DIR}/glfw3.lib"
	opengl32
	gdi32
	user32
	ws2_32
	winmm
)

if(MINGW)
	target_link_libraries(voxey 
		mingw32
		gcc
		stdc++
		${CMAKE_SOURCE_DIR}/C:/msys64/ucrt/lib/libmingwex.a
)
endif()

set_target_properties(voxey PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

message(STATUS "OpenGL Libraries: ${OPENGL_LIBRARIES}")
message(STATUS "GLFW Library Directory: ${GLFW_LIB_DIR}")