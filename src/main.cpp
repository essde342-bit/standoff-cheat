#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <android/log.h>
#include "hooks.h"
#include "il2cpp_resolver.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "FoxMod", __VA_ARGS__)

bool is_library_loaded(const char* lib) {
    char filename[256] = {0};
    FILE* fp = fopen("/proc/self/maps", "r");
    if (!fp) return false;
    while (fgets(filename, sizeof(filename), fp)) {
        if (strstr(filename, lib)) {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

void* hack_thread(void* arg) {
    LOGI("Hack thread started");
    
    while (!is_library_loaded("libEGL.so")) usleep(100000);
    LOGI("libEGL.so loaded, hooking...");
    setup_egl_hooks();

    while (!is_library_loaded("libil2cpp.so")) usleep(100000);
    LOGI("libil2cpp.so loaded, resolving...");
    init_il2cpp();

    return nullptr;
}

__attribute__((constructor)) void lib_main() {
    LOGI("Lib injected");
    pthread_t thread;
    pthread_create(&thread, nullptr, hack_thread, nullptr);
}
