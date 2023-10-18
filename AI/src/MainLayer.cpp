#include "pch.hpp"
#include "MainLayer.hpp"

#include <icons/include/icons/IconsMaterialDesignIcons.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "Engine/Core/Utils/StringUtils.hpp"
#include "Platform/GUI/Core/GUIApplication.hpp"
#include "Platform/GUI/Core/OpenGL/OpenGlRendererAPI.hpp"
#include "Puzzle/Board.hpp"
#include "Platform/GUI/Core/UI/Theme.hpp"
#include "Platform/GUI/Core/UI/UI.hpp"
#include "Puzzle/BFS.hpp"

namespace AI {
    MainLayer::MainLayer(const std::string& name)
        : Layer(name) {}

    void MainLayer::OnAttach() {
        Core::OpenGlRendererAPI::Init();

        Core::Theme::SetFont();
        Core::Theme::SetStyle();
        Core::Theme::ApplyTheme();

        Core::Application::Get().GetGuiLayer()->SetBlockEvents(false);

        // 1 2 3 4
        // 5 6 7 0
        // 9 10 11 8
        // 13 14 15 12

        // Testing stuff
        Board board(4, 4);

        board.SetPuzzle(0, 0, 1);
        board.SetPuzzle(1, 0, 2);
        board.SetPuzzle(2, 0, 3);
        board.SetPuzzle(3, 0, 4);
        board.SetPuzzle(0, 1, 5);
        board.SetPuzzle(1, 1, 6);
        board.SetPuzzle(2, 1, 7);
        board.SetPuzzle(3, 1, 0);
        board.SetPuzzle(0, 2, 9);
        board.SetPuzzle(1, 2, 10);
        board.SetPuzzle(2, 2, 11);
        board.SetPuzzle(3, 2, 8);
        board.SetPuzzle(0, 3, 13);
        board.SetPuzzle(1, 3, 14);
        board.SetPuzzle(2, 3, 15);
        board.SetPuzzle(3, 3, 12);

        Solver* solver = new BFS(&board);

        solver->GetBoard()->LogDisplay();
        solver->Solve("RD7UL");
        solver->GetBoard()->LogDisplay();

        delete solver;

        ///*board.SetPuzzle(0, 0, 1);
        //board.SetPuzzle(1, 0, 2);
        //board.SetPuzzle(0, 1, 3);
        //board.SetPuzzle(1, 1, 0);*/
        //board.SetPuzzle(0, 1);
        //board.SetPuzzle(1, 2);
        //board.SetPuzzle(2, 3);
        //board.SetPuzzle(3, 0);

        //board.Move(MoveDirection::UP);
        //board.Move(MoveDirection::DOWN);
        //board.Move(MoveDirection::LEFT);
        //board.Move(MoveDirection::RIGHT);
        //board.Move(MoveDirection::LEFT);

        //board.LogDisplay();

        //CORE_INFO("Board is solved: {0}", board.IsSolved());

        //CORE_INFO("Empty puzzle position: {0}, {1}", board.GetEmptyPuzzlePosition().first, board.GetEmptyPuzzlePosition().second);
        //CORE_INFO("Board at [0][0]: {0}", board.GetPuzzle(0, 0).GetValue());
        //CORE_INFO("Board at [0][1]: {0}", board.GetPuzzle(0, 1).GetValue());
        //CORE_INFO("Board at [1][0]: {0}", board.GetPuzzle(1, 0).GetValue());
        //CORE_INFO("Board at [1][1]: {0}", board.GetPuzzle(1, 1).GetValue());
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

                        bool isNormalCursor = ImGui::GetMouseCursor() == ImGuiMouseCursor_Arrow;

                        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0.0f, 0.0f });
                        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
                        ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.0f, 0.0f });

                        if (ImGui::Button(Core::StringUtils::FromChar8T(ICON_MDI_NUKE), buttonSize) && isNormalCursor) {}

                        ImGui::PopStyleVar(4);
                        ImGui::PopStyleColor();

                        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, windowPadding);

                        if (ImGui::BeginMenu("File")) {
                            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, Core::Theme::PopupItemSpacing);

                            if (ImGui::MenuItem("Load Board")) {

                            }

                            if (ImGui::MenuItem("Save Board")) {

                            }

                            ImGui::Separator();
                            if (ImGui::MenuItem("Exit"))
                                Core::Application::Get().Close();

                            ImGui::PopStyleVar();
                            ImGui::EndMenu();
                        }

                        ImGui::PopStyleVar();

                        ImVec2 windowGrabAreaStart = ImGui::GetCursorPos();
                        float buttonStartRegion = region.x - 3.0f * buttonSize.x + ImGui::GetStyle().WindowPadding.x;
                        ImGui::InvisibleButton("TitlebarGrab1", { buttonStartRegion - windowGrabAreaStart.x, frameHeight + windowPadding.y });
                        if (ImGui::IsItemHovered())
                            Core::Application::Get().GetWindow().RegisterOverTitlebar(true);

#ifdef CORE_PLATFORM_WINDOWS
                        // Minimize/Maximize/Close buttons
                        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0.0f, 0.0f });
                        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
                        ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.0f, 0.0f });

                        ImGui::SetCursorPosX(buttonStartRegion);

                        // Minimize Button
                        if (ImGui::Button(Core::StringUtils::FromChar8T(ICON_MDI_MINUS), buttonSize) && isNormalCursor) {
                            Core::Application::Get().GetWindow().Minimize();
                        }

                        // Maximize Button
                        if (ImGui::Button(Core::StringUtils::FromChar8T(ICON_MDI_WINDOW_MAXIMIZE), buttonSize) && isNormalCursor)
                        {
                            Core::Window& window = Core::Application::Get().GetWindow();
                            if (window.IsMaximized())
                                window.Restore();
                            else
                                window.Maximize();
                        }

                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.909f, 0.066f, 0.137f, 1.0f });
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.920f, 0.066f, 0.120f, 1.0f });
                        // Close Button
                        if (ImGui::Button(Core::StringUtils::FromChar8T(ICON_MDI_WINDOW_CLOSE), buttonSize) && isNormalCursor)
                            Core::Application::Get().Close();
                        ImGui::PopStyleColor(2);

                        ImGui::PopStyleColor();
                        ImGui::PopStyleVar(4);
#endif

                        ImGui::EndMenuBar();
                    }

                    ImGui::End();
                }
                ImGui::PopStyleVar();
            }
            ImGui::PopStyleVar(2);

            ImGui::Begin("Puzzle preview");

#if 0 // WORK IN PROGRESS DO NOT TOUCH, DO NOT INLCUDE IN THE REVIEW - TEMPOARY CODE
            const int puzzleWidth = 2;
            const int puzzleHeight = 4;
            static const int puzzleBoard[puzzleWidth][puzzleHeight] = {
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                //{9, 10, 11, 12},
                //{13, 14, 15, 0}
            };

            static ImU32 lightOrange = IM_COL32(255, 200, 100, 255);
            static ImU32 black = IM_COL32(0, 0, 0, 255);
            static ImU32 lightGray = IM_COL32(240, 240, 240, 255);
            static ImU32 lightBlue = IM_COL32(100, 100, 255, 255);


            ImGui::PushStyleColor(ImGuiCol_WindowBg, lightGray);

            for (int row = 0; row < puzzleWidth; ++row) {
                for (int col = 0; col < puzzleHeight; ++col) {
                    int pieceValue = puzzleBoard[row][col];

                    float margin = 5.0f;
                    float posX = col * (600.0f / 4.0f + margin);
                    float posY = row * (600.0f / 4.0f + margin) + 40.f;

                    ImGui::PushStyleColor(ImGuiCol_Button, pieceValue == 0 ? lightBlue : lightOrange);
                    ImGui::PushStyleColor(ImGuiCol_Text, black);
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

                    ImGui::SetCursorPos(ImVec2(posX, posY));

                    {
                        //Core::ScopedFont bigFont(ImGui::GetIO().Fonts->Fonts[2]);
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
                        if (ImGui::Button(std::to_string(pieceValue).c_str(), ImVec2(600.0f / 4.0f, 600.0f / 4.0f))) {

                        }
                        ImGui::PopStyleVar();
                    }

                    ImGui::PopStyleColor(2);
                    ImGui::PopStyleVar();
                }
            }

            ImGui::PopStyleColor();
#endif
            ImGui::End();

            ImGui::Begin("Controller");

            ImGui::End();

            ImGui::Begin("Console trace");

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

