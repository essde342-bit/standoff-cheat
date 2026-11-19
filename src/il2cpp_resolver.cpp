#include "il2cpp_resolver.h"
#include <android/log.h>
#include <dlfcn.h>

void* g_il2cpp_handle = nullptr;

typedef void* (*Camera_get_main_t)();
typedef void (*Camera_WorldToScreenPoint_t)(void* cam, Vector3 pos, int eye, Vector3* out);

Camera_get_main_t orig_Camera_get_main = nullptr;
Camera_WorldToScreenPoint_t orig_Camera_WorldToScreenPoint = nullptr;

void init_il2cpp() {
    g_il2cpp_handle = dlopen("libil2cpp.so", RTLD_NOW);
    if (g_il2cpp_handle) {
        uintptr_t base = (uintptr_t)g_il2cpp_handle; 
        orig_Camera_get_main = (Camera_get_main_t)(base + Offsets::Camera_Main);
        orig_Camera_WorldToScreenPoint = (Camera_WorldToScreenPoint_t)(base + Offsets::Camera_WorldToScreen);
    }
}

bool WorldToScreen(Vector3 world, Vector2& screen) {
    if (!orig_Camera_get_main || !orig_Camera_WorldToScreenPoint) {
        return false; 
    }
    void* main_cam = orig_Camera_get_main();
    if (!main_cam) return false;

    Vector3 out;
    orig_Camera_WorldToScreenPoint(main_cam, world, 2, &out);

    if (out.z < 0.0f) return false; 
    
    screen.x = out.x;
    screen.y = out.y; 
    return true;
}
