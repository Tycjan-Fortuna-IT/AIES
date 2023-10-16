#include "pch.hpp"
#include "MainLayer.hpp"

#include <icons/include/icons/IconsMaterialDesignIcons.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "Platform/GUI/Core/GUIApplication.hpp"
#include "Platform/GUI/Core/OpenGL/OpenGlRendererAPI.hpp"
#include "Puzzle/Board.hpp"

namespace AI {
    MainLayer::MainLayer(const std::string& name)
        : Layer(name) {}

    void MainLayer::OnAttach() {
        Core::OpenGlRendererAPI::Init();

        Core::Application::Get().GetGuiLayer()->SetBlockEvents(false);

        // Testing stuff
        Board board(2, 2);

        /*board.SetPuzzle(0, 0, 1);
        board.SetPuzzle(1, 0, 2);
        board.SetPuzzle(0, 1, 3);
        board.SetPuzzle(1, 1, 0);*/
        board.SetPuzzle(0, 1);
        board.SetPuzzle(1, 2);
        board.SetPuzzle(2, 3);
        board.SetPuzzle(3, 0);

        board.Move(MoveDirection::UP);

        board.LogDisplay();

        CORE_INFO("Board is solved: {0}", board.IsSolved());

        CORE_INFO("Empty puzzle position: {0}, {1}", board.GetEmptyPuzzlePosition().first, board.GetEmptyPuzzlePosition().second);
        CORE_INFO("Board at [0][0]: {0}", board.GetPuzzle(0, 0).GetValue());
        CORE_INFO("Board at [0][1]: {0}", board.GetPuzzle(0, 1).GetValue());
        CORE_INFO("Board at [1][0]: {0}", board.GetPuzzle(1, 0).GetValue());
        CORE_INFO("Board at [1][1]: {0}", board.GetPuzzle(1, 1).GetValue());
    }

    void MainLayer::OnDetach() {

    }

    void MainLayer::OnEvent(Core::Event& event) {
        Core::EventDispatcher dispatcher(event);

        dispatcher.Dispatch<Core::KeyPressedEvent>(BIND_FN(MainLayer::OnKeyPressed));
        dispatcher.Dispatch<Core::MouseButtonPressedEvent>(BIND_FN(MainLayer::OnMouseKeyPressed));
    }

    void MainLayer::OnUpdate(Core::Timestep dt) {
        Core::OpenGlRendererAPI::SetClearColor({ 0.6f, 0.6f, 0.6f, 0.4 });
        Core::OpenGlRendererAPI::Clear();
    }

    void MainLayer::OnGuiRender() {
        return;
        Core::Application::Get().GetWindow().RegisterOverTitlebar(false);

        // ImGui::ShowDemoWindow();

        BeginDockspace("MyDockSpace");
        {
            auto* viewport = ImGui::GetMainViewport();
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar
                | ImGuiWindowFlags_NoSavedSettings
                | ImGuiWindowFlags_MenuBar
                | ImGuiWindowFlags_NoNavFocus;

            ImVec2 windowPadding = ImGui::GetStyle().WindowPadding;
            float frameHeight = ImGui::GetFrameHeight();
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            {
                //////////////////////////////////////////////////////////////////////////
                // PRIMARY TOP MENU BAR //////////////////////////////////////////////////
                //////////////////////////////////////////////////////////////////////////
                ImVec2 framePadding = ImGui::GetStyle().FramePadding;
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { framePadding.x, 6.5f });
                m_TopMenuBarHeight = ImGui::GetFrameHeight();
                if (ImGui::BeginViewportSideBar("##PrimaryMenuBar", viewport, ImGuiDir_Up, m_TopMenuBarHeight, window_flags)) {
                    if (ImGui::BeginMenuBar()) {
                        ImVec2 region = ImGui::GetContentRegionMax();
                        ImVec2 buttonSize = { region.y * 1.7f, region.y };

                        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, windowPadding);
                        if (ImGui::BeginMenu("File")) {
                            if (ImGui::MenuItem("Exit"))
                                Core::Application::Get().Close();

                            ImGui::EndMenu();
                        }
                        ImGui::PopStyleVar();

                        ImVec2 windowGrabAreaStart = ImGui::GetCursorPos();
                        float buttonStartRegion = region.x - 3.0f * buttonSize.x + ImGui::GetStyle().WindowPadding.x;
                        ImGui::InvisibleButton("TitlebarGrab1", { buttonStartRegion - windowGrabAreaStart.x, frameHeight + windowPadding.y });
                        if (ImGui::IsItemHovered())
                            Core::Application::Get().GetWindow().RegisterOverTitlebar(true);

                        ImGui::EndMenuBar();
                    }

                    ImGui::End();
                }
                ImGui::PopStyleVar();
            }
            ImGui::PopStyleVar(2);

            ImGui::Begin("Puzzle Preview");

            ImGui::End();

            ImGui::Begin("Controls");

            ImGui::End();

            ImGui::Begin("Trace output");

            ImGui::End();

            Core::Application::Get().GetGuiLayer()->SetBlockEvents(false);
        }
        EndDockspace();
    }

    bool MainLayer::OnKeyPressed(Core::KeyPressedEvent& event) {

        return false;
    }

    bool MainLayer::OnMouseKeyPressed(Core::MouseButtonPressedEvent& event) {

        return false;
    }

    void MainLayer::BeginDockspace(const char* name) const {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        const bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_NoCloseButton;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dock-able into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        if (opt_fullscreen) {
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become un-docked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dock-space/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace

        const float frameHeight = ImGui::GetFrameHeight();
        const float menuBarSize = 0.2f * frameHeight;
        const float bottomMenuBarSize = 0.2f * frameHeight;
        const float dockSpaceOffsetY = ImGui::GetCursorPosY() + menuBarSize + (m_TopMenuBarHeight - frameHeight);

        const ImVec2 dockSpaceSize = ImVec2(viewport->Size.x, viewport->Size.y - (menuBarSize + bottomMenuBarSize + m_TopMenuBarHeight));

        ImGuiStyle& style = ImGui::GetStyle();
        const float minWinSizeX = style.WindowMinSize.x;
        const float minWinSizeY = style.WindowMinSize.y;
        style.WindowMinSize.x = 370.0f;
        style.WindowMinSize.y = 150.0f;
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGui::SetCursorPosY(dockSpaceOffsetY);
            const ImGuiID dockspace_id = ImGui::GetID(name);
            ImGui::DockSpace(dockspace_id, dockSpaceSize, dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;
        style.WindowMinSize.y = minWinSizeY;
    }

    void MainLayer::EndDockspace() const {
        ImGui::End();
    }
}

