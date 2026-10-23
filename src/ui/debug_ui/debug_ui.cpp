#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "debug_ui.hpp"

DebugUi::DebugUi()
{ }

void DebugUi::buildUi()
{
    ImGuiIO& io = ImGui::GetIO();
    float width = io.DisplaySize.x;
    float height = io.DisplaySize.y;

    ImGui::Begin("Explorer", nullptr);

    if (ImGui::CollapsingHeader("collapsing header test 1"))
    {
        ImGui::Indent();

        if (ImGui::CollapsingHeader("collapsing header test 2"))
        {
            
        }

        ImGui::Unindent();
    }

    if (ImGui::CollapsingHeader("collapsing header test 3"))
    {
        ImGui::Indent();
        
        if (ImGui::CollapsingHeader("collapsing header test 4"))
        {
            
        }

        ImGui::Unindent();
    }

    ImGui::End();
}