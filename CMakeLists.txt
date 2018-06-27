cmake_minimum_required(VERSION 3.1.0)

IF(DEFINED CMAKE_BUILD_TYPE)
  set(
    CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING
    "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
  )
else()
  set(
    CMAKE_BUILD_TYPE Release CACHE STRING
    "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
  )
endif()

project(imgui_plugin)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(IMGUI_PLUGIN_COMPILER_FLAGS "")
if(MSVC)
  set(IMGUI_PLUGIN_COMPILER_FLAGS "/EHsc /MP")
  if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(IMGUI_PLUGIN_COMPILER_FLAGS "/EHsc /MP")
  endif()
endif()

# Dependencies
set(PROJECT_LINK_LIBRARY_DIRECTORIES
  ../../ice_engine/deps/glew/lib
)

find_library(GLEW_LIBRARY NAMES libGLEW.so.2.0 glew32 PATHS ${PROJECT_LINK_LIBRARY_DIRECTORIES})

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

include_directories(../../ice_engine/deps/boost/include)
include_directories(../../ice_engine/deps/glew/include)
include_directories(../../ice_engine/deps/glm/include)
include_directories(../../ice_engine/deps/freeimage/include)

include_directories(../../ice_engine/include)

# Headers
include_directories(include)

# Source
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Flags
#set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${IMGUI_PLUGIN_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${IMGUI_PLUGIN_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${IMGUI_PLUGIN_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${IMGUI_PLUGIN_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${IMGUI_PLUGIN_COMPILER_FLAGS}")

add_library(imgui_plugin SHARED ${SOURCES})

target_link_libraries(imgui_plugin ${GLEW_LIBRARY} )

target_link_libraries(imgui_plugin ${OPENGL_gl_LIBRARY})
