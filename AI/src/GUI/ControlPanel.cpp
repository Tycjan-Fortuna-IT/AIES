#include "pch.hpp"
#include "ControlPanel.hpp"

#include <imgui.h>

#include "Utils.hpp"
#include "Engine/Core/Debug/Logger.hpp"
#include "Platform/GUI/Core/UI/Color.hpp"
#include "Platform/GUI/Core/UI/UI.hpp"
#include "Puzzle/BFS.hpp"
#include "Puzzle/DFS.hpp"
#include "Puzzle/Solver.hpp"

#define _BFS 0
#define _DFS 1

namespace AI {
    ControlPanel::ControlPanel(Board*& board, const char* name, const char8_t* icon)
        : Panel(name, icon), m_Board(board) {}

    void ControlPanel::OnRender() {
        ImGui::Begin(m_ID.c_str());

        {
            Core::ScopedStyle FramePadding(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));

            if (!m_Board) {
                static int32_t width = 0;
                static int32_t height = 0;

                ImGui::Text("Create a new board:");
                ImGui::Separator();

                ImGui::InputInt("Width", &width);
                ImGui::InputInt("Height", &height);

                ImGui::Spacing();

                if (ImGui::Button("Create new board")) {
                    CONSOLE_INFO("Creating new board with width = {} and height = {}", width, height);

                    if (width > 0 && height > 0) {
                        m_Board = new Board(width, height);
                    }
                    else {
                        CONSOLE_ERROR("Invalid width or height!");
                    }
                }
            } else if (m_Solution.empty()) {
                static const char* strategies[] = { "BFS", "DFS" };
                static const char* orders[] = { // All permutations of "LRUD"
                        "LRUD", "LURD", "LUDR", "RLUD", "RULD", "RUDL",
                        "ULRD", "ULDR", "URLD", "URDL", "UDLR", "UDRL",
                        "RLDU", "RDLU", "RULD", "RUDL", "RDUL",
                        "DRLU", "DRUL", "DLRU", "DLUR", "DURL", "DULR"
                };

                static int strategy = 0;
                static int order = 0;

                if (Core::UI::PropertyDropdown("Select search strategy", strategies, 2, &strategy)) {}

                if (strategy == _BFS || strategy == _DFS) {
                    if (Core::UI::PropertyDropdown("Select order", orders, 24, &order)) {}
                }

                {
                    Core::ScopedColor ButtonColor(ImGuiCol_Button, Core::Color::DarkBlue);

                    if (ImGui::Button("Solve")) {
                        CONSOLE_INFO("Solving the board using {} with parameter {}", strategies[strategy], orders[order]);

                        Solver* solver = nullptr;

                        switch (strategy) {
                            case _BFS: solver = new BFS(m_Board); break;
                            case _DFS: solver = new DFS(m_Board); break;
                        }

                        solver->Solve(orders[order]);

                        m_Solution = solver->GetSolution().moves;

                        delete solver;
                    }
                }

            }

            if (m_Solution.size() > 1) {
                ImGui::Separator();
                ImGui::Spacing();

                static int32_t index = m_Solution.size() - 1;

                {
                    Core::ScopedColor ButtonColor(ImGuiCol_Button, Core::Color::DarkRed);

                    if (ImGui::Button("Previous")) {
                        if (index - 1 >= 0) {
                            MoveDirection direction = m_Solution[index];
                            MoveDirection opposite = Board::GetOppositeDirection(direction);

                            if (m_Board->CanMove(opposite)) {
                                m_Board->Move(opposite);

                                index--;
                            } else {
                                CONSOLE_ERROR("Can't move in this direction {}", Solver::GetStringifiedDirection(opposite));
                            }
                        }
                    }
                }

                ImGui::SameLine();

                {
                    Core::ScopedColor ButtonColor(ImGuiCol_Button, Core::Color::DarkGreen);

                    if (ImGui::Button("Next")) {
                        if (index + 1 < m_Solution.size()) {
                            MoveDirection direction = m_Solution[index];

                            if (m_Board->CanMove(direction)) {
                                m_Board->Move(direction);

                                index++;
                            } else {
                                CONSOLE_ERROR("Can't move in this direction {}", Solver::GetStringifiedDirection(direction));
                            }
                        }
                    }
                }
            }
        }

        ImGui::End();
    }
}
