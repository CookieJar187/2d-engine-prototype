#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "settings.h"

Settings::Settings(GameFsm* gameFsm)
{
    Settings::gameFsm = gameFsm;
}

void Settings::buildUi()
{
    ImGuiIO& io = ImGui::GetIO();
    float width = io.DisplaySize.x;
    float height = io.DisplaySize.y;

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Settings", nullptr, flags);

    ImVec2 btnSize = ImVec2(160.0f, 40.0f);
    ImVec2 listBoxSize = ImVec2(400.0f, 500.0f);

    if (ImGui::Button("Back")) {
        gameFsm->setState(GameState::MainMenu);
    }

    ImGui::SetCursorPosY(height * 0.1f);
    
    const char* titleText = "SETTINGS";
    float titleWidth = ImGui::CalcTextSize(titleText).x;
    ImGui::SetCursorPosX((width - titleWidth) * 0.5f);
    ImGui::TextUnformatted(titleText);

    ImGui::SetCursorPosX((width - listBoxSize.x) * 0.5f);
    ImGui::BeginListBox("##ScrollThing", listBoxSize);
    ImGui::Button("A");
    ImGui::Button("B");
    ImGui::Button("C");
    ImGui::Button("D");
    ImGui::EndListBox();

    /*
    ImGui::SetCursorPosX((width - btnSize.x) * 0.5f);
    if (ImGui::Button("Back", btnSize)) {
        gameFsm->setState(GameState::MainMenu);
    }*/

    ImGui::End();
}