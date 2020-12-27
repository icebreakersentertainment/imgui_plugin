cmake_minimum_required(VERSION 3.1.0)

project(imguicolortextedit_plugin)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(IMGUICOLORTEXTEDIT_PLUGIN_COMPILER_FLAGS "")
set(IMGUICOLORTEXTEDIT_PLUGIN_DEFINITIONS "")
if(MSVC)
  list(APPEND IMGUICOLORTEXTEDIT_PLUGIN_COMPILER_FLAGS /EHsc /MP)
  if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    list(APPEND IMGUICOLORTEXTEDIT_PLUGIN_COMPILER_FLAGS /EHsc /MP)
  endif()
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo OR ICEENGINE_ENABLE_DEBUG_LOGGING)
  list(APPEND IMGUICOLORTEXTEDIT_PLUGIN_DEFINITIONS -DICEENGINE_ENABLE_DEBUG_LOGGING)
endif()

if(ICEENGINE_ENABLE_TRACE_LOGGING)
  list(APPEND IMGUICOLORTEXTEDIT_PLUGIN_DEFINITIONS -DICEENGINE_ENABLE_TRACE_LOGGING)
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(angelscript REQUIRED)
find_package(glm REQUIRED)
find_package(Boost REQUIRED)

# Source
file(GLOB_RECURSE SOURCES "src/*.cpp"
  "../imgui/imgui/imgui.cpp"
  "../imgui/imgui/imgui_draw.cpp"
  "../imgui/imgui/imgui_widgets.cpp"
#  "../imgui/imgui/imgui_tables.cpp"
  #  "../imgui/imgui/imgui_demo.cpp"
  "../imgui/imgui/misc/cpp/imgui_stdlib.cpp"
  "../ImGuiColorTextEdit/ImGuiColorTextEdit/TextEditor.cpp"
)

add_library(imguicolortextedit_plugin SHARED ${SOURCES})

target_include_directories(imguicolortextedit_plugin PRIVATE ../imgui)
target_include_directories(imguicolortextedit_plugin PRIVATE ../imgui/imgui) # for the ImGuiColorTextEdit CPP file
target_include_directories(imguicolortextedit_plugin PRIVATE ../ImGuiColorTextEdit) # for the ImGuiColorTextEdit CPP file
target_include_directories(imguicolortextedit_plugin PRIVATE ../ImGuiColorTextEdit/ImGuiColorTextEdit)
target_include_directories(imguicolortextedit_plugin PRIVATE ../include) # for the TextEditor CPP file

target_include_directories(imguicolortextedit_plugin PRIVATE include)

target_include_directories(imguicolortextedit_plugin PRIVATE ${ICEENGINE_INCLUDE_DIRS})
target_include_directories(imguicolortextedit_plugin PRIVATE ${Boost_INCLUDE_DIRS})

target_compile_definitions(imguicolortextedit_plugin PRIVATE $IMGUICOLORTEXTEDIT_PLUGIN_DEFINITIONS})
target_compile_options(imguicolortextedit_plugin PRIVATE ${IMGUICOLORTEXTEDIT_PLUGIN_COMPILER_FLAGS})

target_link_libraries(imguicolortextedit_plugin PRIVATE GLEW::GLEW)
target_link_libraries(imguicolortextedit_plugin PRIVATE angelscript::angelscript)
target_link_libraries(imguicolortextedit_plugin PRIVATE glm::glm)
target_link_libraries(imguicolortextedit_plugin PRIVATE OpenGL::GL)
