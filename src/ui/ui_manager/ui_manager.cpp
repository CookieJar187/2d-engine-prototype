#include "ui_manager.h"

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int UiManager::init(GLFWwindow* window, GameFsm* gameFsm)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        std::cerr << "Failed to initialize ImgGui GLFW backend" << std::endl;
        return 1;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 330")) {
        std::cerr << "Failed to initialize ImgGui OpenGL backend" << std::endl;
        return 1;
    }

    UiManager::gameFsm = gameFsm;
    UiManager::mainMenu = new MainMenu(gameFsm);
    UiManager::settings = new Settings(gameFsm);
    UiManager::levelSelection = new LevelSelection(gameFsm);
    
    return 0;
}

void UiManager::buildUi()
{
    // Begin ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Build ui
    if (gameFsm->isState(GameState::Playing))
        return;
    if (gameFsm->isState(GameState::MainMenu))
        UiManager::mainMenu->buildUi();
    else if (gameFsm->isState(GameState::LevelSelection))
        UiManager::levelSelection->buildUi();
    else if (gameFsm->isState(GameState::Settings))
        UiManager::settings->buildUi();
    else
        std::cerr << "UiManager: unsuported state" << std::endl;
}

void UiManager::drawUi()
{
    // Draw ui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UiManager::destroyUi()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}