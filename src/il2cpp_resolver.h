#pragma once
#include <cstdint>

struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };

namespace Offsets {
    constexpr uintptr_t Camera_Main = 0x2B4A100; 
    constexpr uintptr_t Camera_WorldToScreen = 0x2B4A5F0;
    constexpr uintptr_t GameManager_Instance = 0x2C11000;
    constexpr uintptr_t Player_GetTransform = 0x1A2F300;
    constexpr uintptr_t Transform_GetPosition = 0x1A30100;
}

void init_il2cpp();
bool WorldToScreen(Vector3 world, Vector2& screen);
