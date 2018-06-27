// ImGui SDL2 binding with OpenGL3
// In this binding, ImTextureID is used to store an OpenGL 'GLuint' texture identifier. Read the FAQ about ImTextureID in imgui.cpp.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you use this binding you'll need to call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(), ImGui::Render() and ImGui_ImplXXXX_Shutdown().
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

//struct SDL_Window;
//typedef union SDL_Event SDL_Event;

// Data
struct SdlData
{
	double       time = 0.0f;
	bool         mousePressed[3] = { false, false, false };
	float        mouseWheel = 0.0f;
	GLuint       fontTexture = 0;
	int          shaderHandle = 0, vertHandle = 0, fragHandle = 0;
	int          attribLocationTex = 0, attribLocationProjMtx = 0;
	int          attribLocationPosition = 0, attribLocationUV = 0, attribLocationColor = 0;
	unsigned int vboHandle = 0, vaoHandle = 0, elementsHandle = 0;
};

IMGUI_API bool        ImGui_ImplSdlGL3_Init(SdlData* sdl_data);
IMGUI_API void        ImGui_ImplSdlGL3_Shutdown(SdlData* sdl_data);
IMGUI_API void        ImGui_ImplSdlGL3_NewFrame(SdlData* sdl_data);
//IMGUI_API bool        ImGui_ImplSdlGL3_ProcessEvent(SDL_Event* event);

IMGUI_API void        ImGui_ImplSdlGL3_RenderDrawLists(SdlData* sdl_data, ImDrawData* draw_data);

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void        ImGui_ImplSdlGL3_InvalidateDeviceObjects(SdlData* sdl_data);
IMGUI_API bool        ImGui_ImplSdlGL3_CreateDeviceObjects(SdlData* sdl_data);
