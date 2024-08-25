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
"src/main.cpp" "src/core/application.h" "src/core/application.cpp" "src/ext/glad.c")

add_executable (voxey ${SOURCES} )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET voxey PROPERTY CXX_STANDARD 20)
endif()


target_link_libraries(voxey "${PROJECT_SOURCE_DIR}/lib/libglfw3.a")

find_package(OpenGL REQUIRED)
target_link_libraries(voxey OpenGL::GL)