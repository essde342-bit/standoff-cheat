#include "menu.h"
#include "imgui.h"
#include "esp.h"

extern bool g_ShowMenu;
extern bool g_ESP_Enabled;

void RenderMenu() {
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
    ImGui::Begin("Fox Mod | Standoff 2", &g_ShowMenu);

    ImGui::Text("Status: Injected & Hooked");
    ImGui::Separator();

    ImGui::Checkbox("Enable ESP", &g_ESP_Enabled);
    
    if (ImGui::Button("Unload Mod")) {
        g_ShowMenu = false;
    }

    ImGui::End();
}
