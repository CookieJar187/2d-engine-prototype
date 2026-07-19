#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "main_menu.h"

MainMenu::MainMenu(GameFsm* gameFsm)
{ MainMenu::gameFsm = gameFsm; }

void MainMenu::buildUi()
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

    ImGui::SetCursorPosY(height * 0.35f);
    
    const char* titleText = "ARMY DEFENSE";
    float titleWidth = ImGui::CalcTextSize(titleText).x;
    ImGui::SetCursorPosX((width - titleWidth) * 0.5f);
    ImGui::TextUnformatted(titleText);
    /*
    const char* descrText = "A COMPUTER VIDEO GAME";
    float descrWidth = ImGui::CalcTextSize(descrText).x;
    ImGui::SetCursorPosX((width - descrWidth) * 0.5f);
    ImGui::TextUnformatted("A COMPUTER VIDEO GAME");
    */
    ImGui::SetCursorPosX((width - btnSize.x) * 0.5f);
    if (ImGui::Button("Level Selection", btnSize)) {
        gameFsm->setState(GameState::LevelSelection);
    }

    ImGui::SetCursorPosX((width - btnSize.x) * 0.5f);
    if (ImGui::Button("Settings", btnSize)) {
        gameFsm->setState(GameState::Settings);
    }

    ImGui::SetCursorPosX((width - btnSize.x) * 0.5f);
    if (ImGui::Button("Quit", btnSize)) {
        gameFsm->setState(GameState::Quit);
    }

    ImGui::End();
}