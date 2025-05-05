cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("AnimationEngine")

add_subdirectory("external/glfw-3.4")

set(OPEN_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

file(GLOB SOURCES src/*.h src/*.cpp)

add_executable(AnimationEngine ${SOURCES})

target_link_libraries(AnimationEngine PRIVATE glfw OpenGL::GL)

target_include_directories(AnimationEngine PRIVATE "external/glfw-3.4/include")

set_target_properties(AnimationEngine PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
