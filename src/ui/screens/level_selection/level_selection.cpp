#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "level_selection.h"

LevelSelection::LevelSelection(GameFsm* gameFsm)
{ LevelSelection::gameFsm = gameFsm; }

void LevelSelection::buildUi()
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

    ImGui::Begin("Main Menu", nullptr, flags);

    ImVec2 titleSize = ImVec2(160.0f, 80.0f);
    ImVec2 btnSize = ImVec2(160.0f, 40.0f);

    if (ImGui::Button("Back")) {
        gameFsm->setState(GameState::MainMenu);
    }

    ImGui::SetCursorPosY(height * 0.35f);
    
    const char* titleText = "LEVEL SELECTION";
    float titleWidth = ImGui::CalcTextSize(titleText).x;
    ImGui::SetCursorPosX((width - titleWidth) * 0.5f);
    ImGui::TextUnformatted(titleText);

    ImGui::SetCursorPosX((width - btnSize.x) * 0.5f);
    if (ImGui::Button("Level 1", btnSize)) {
        gameFsm->setState(GameState::Playing);
    }

    ImGui::SetCursorPosX((width - btnSize.x) * 0.5f);
    if (ImGui::Button("Level 2", btnSize)) {
        gameFsm->setState(GameState::Playing);
    }

    ImGui::SetCursorPosX((width - btnSize.x) * 0.5f);
    if (ImGui::Button("Level 3", btnSize)) {
        gameFsm->setState(GameState::Playing);
    }

    ImGui::End();
}