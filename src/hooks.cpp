#include "hooks.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/native_window.h>
#include <dobby.h>
#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"
#include "menu.h"
#include "esp.h"

EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface) = nullptr;
bool g_ImGuiInitialized = false;
bool g_ShowMenu = true;

EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    if (!g_ImGuiInitialized) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = nullptr;
        
        ImGui::StyleColorsDark();
        ImGui_ImplAndroid_Init(nullptr); 
        ImGui_ImplOpenGL3_Init("#version 300 es");
        
        g_ImGuiInitialized = true;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();

    if (g_ShowMenu) {
        RenderMenu();
    }
    
    RenderESP();

    ImGui::Render();
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return orig_eglSwapBuffers(dpy, surface);
}

void setup_egl_hooks() {
    void* egl_handle = dlopen("libEGL.so", RTLD_LAZY);
    void* swap_buffers = dlsym(egl_handle, "eglSwapBuffers");
    DobbyHook(swap_buffers, (void*)hook_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
}
