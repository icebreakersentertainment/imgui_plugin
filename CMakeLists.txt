cmake_minimum_required(VERSION 3.1.0)

project(imgui_plugin)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(IMGUI_PLUGIN_COMPILER_FLAGS "")
set(IMGUI_PLUGIN_DEFINITIONS "")
if(MSVC)
  set(IMGUI_PLUGIN_COMPILER_FLAGS "/EHsc /MP")
  if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(IMGUI_PLUGIN_COMPILER_FLAGS "/EHsc /MP")
  endif()
endif()

if(NOT TARGET glew)
  add_subdirectory(./glew/glew/build/cmake)
endif()

find_package(OpenGL REQUIRED)

include_directories(glew/glew/include)

if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo OR ICEENGINE_ENABLE_DEBUG_LOGGING)
  list(APPEND IMGUI_PLUGIN_DEFINITIONS -DICEENGINE_ENABLE_DEBUG_LOGGING)
endif()

if(ICEENGINE_ENABLE_TRACE_LOGGING)
  list(APPEND IMGUI_PLUGIN_DEFINITIONS -DICEENGINE_ENABLE_TRACE_LOGGING)
endif()

# Headers
include_directories(include)

# Source
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(imgui_plugin SHARED ${SOURCES})

target_include_directories(imgui_plugin PRIVATE ${ICEENGINE_INCLUDE_DIRS})
target_include_directories(imgui_plugin PRIVATE ${BOOST_INCLUDE_DIRS})
target_include_directories(imgui_plugin PRIVATE ${GLM_INCLUDE_DIRS})
target_include_directories(imgui_plugin PRIVATE ${FREEIMAGE_INCLUDE_DIRS})

target_compile_definitions(imgui_plugin PRIVATE $IMGUI_PLUGIN_DEFINITIONS})
target_compile_options(imgui_plugin PRIVATE ${IMGUI_PLUGIN_COMPILER_FLAGS})

target_link_libraries(imgui_plugin glew)
target_link_libraries(imgui_plugin ${OPENGL_gl_LIBRARY})
