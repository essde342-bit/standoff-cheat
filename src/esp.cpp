#include "esp.h"
#include "imgui.h"
#include "il2cpp_resolver.h"
#include <vector>

bool g_ESP_Enabled = true;

void RenderESP() {
    if (!g_ESP_Enabled) return;

    std::vector<Vector3> fake_players = { {10.0f, 0.0f, 10.0f}, {-5.0f, 2.0f, 15.0f} };

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    
    for (const auto& pos : fake_players) {
        Vector2 screen_pos;
        if (WorldToScreen(pos, screen_pos)) {
            float height = 150.0f; 
            float width = height / 2.5f;
            
            ImVec2 top_left(screen_pos.x - width/2, screen_pos.y - height);
            ImVec2 bottom_right(screen_pos.x + width/2, screen_pos.y);
            
            draw_list->AddRect(top_left, bottom_right, IM_COL32(255, 0, 0, 255), 0.0f, 0, 2.0f);
        }
    }
}
