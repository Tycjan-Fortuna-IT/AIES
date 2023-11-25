#include "ControlPanel.hpp"

#include <imgui.h>

#include "Utils.hpp"
#include "Engine/Core/Debug/Logger.hpp"
#include "Platform/GUI/Core/UI/Color.hpp"
#include "Platform/GUI/Core/UI/UI.hpp"
#include "Puzzle/Solver.hpp"
#include "Puzzle/Solvers/BruteForce/BFS.hpp"
#include "Puzzle/Solvers/BruteForce/DFS.hpp"
#include "Puzzle/Solvers/BruteForce/IDFS.hpp"
#include "Puzzle/Solvers/Heuristic/AStar.hpp"
#include "Puzzle/Solvers/Heuristic/BestFirstSearch.hpp"
#include "Puzzle/Solvers/Heuristic/SMAStar.hpp"

#define _BFS 0
#define _DFS 1
#define _IDFS 2
#define _HBFS 3
#define _ASTAR 4
#define _SMASTAR 5
#define IS_BRUTE_FORCE(x) (x == _BFS || x == _DFS || x == _IDFS)
#define IS_HEURESTIC(x) (x == _HBFS || x == _ASTAR || x == _SMASTAR)

namespace AI {
    ControlPanel::ControlPanel(Board*& board, const char* name, const char8_t* icon)
        : Panel(name, icon), m_Board(board) {}

    void ControlPanel::OnRender() {
        ImGui::Begin(m_ID.c_str());

        {
            Core::ScopedStyle FramePadding(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));

            static const char* strategies[] = { "BFS", "DFS", "IDFS", "BestFirstSearch", "A*", "SMA*"};
            static const char* orders[] = { // All permutations of "LRUD", 4! -> 24
                "LRUD", "LRDU", "LURD", "LUDR", "LDRU", "LDUR",
                "RLUD", "RLDU", "RULD", "RUDL", "RDLU", "RDUL",
                "ULRD", "ULDR", "URLD", "URDL", "UDLR", "UDRL",
                "DLRU", "DLUR", "DRLU", "DRUL", "DULR", "DURL"
            };

            static const char* heurestics[] = { "Zero", "Manhattan", "Hamming", "Chebyshev", "Euclidean" };

            static int32_t index = -2;
            static int strategy = 0;
            static int order = 0;
            static int heurestic = 0;
            static int maxDepth = 5;
            static int memoryLimit = 1000;
            static bool randomize = false;

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
                    } else {
                        CONSOLE_ERROR("Invalid width or height!");
                    }
                }
            } else if (m_Solution.empty()) {
                if (Core::UI::PropertyDropdown("Select search strategy", strategies, (int32_t)std::size(strategies), &strategy)) {}

                if (IS_BRUTE_FORCE(strategy)) {
                    ImGui::Checkbox("Random order", &randomize);

                    if (!randomize) {
                        if (Core::UI::PropertyDropdown("Select order", orders, (int32_t)std::size(orders), &order)) {}
                    }

                    if (strategy != _BFS) {
                        ImGui::Spacing();
                        ImGui::InputInt("Max depth", &maxDepth);
                    }
                } else if (IS_HEURESTIC(strategy)) {
                    if (Core::UI::PropertyDropdown("Select heurestic", heurestics, (int32_t)std::size(heurestics), &heurestic)) {}

                    if (strategy == _SMASTAR) {
                        ImGui::Spacing();
                        ImGui::InputInt("Memory limit", &memoryLimit);
                    }
                }

                {
                    Core::ScopedColor ButtonColor(ImGuiCol_Button, Core::Color::DarkBlue);

                    if (ImGui::Button("Solve")) {
                        if (IS_BRUTE_FORCE(strategy)) {
                            CONSOLE_INFO("Solving the board using {} with search order: {}", strategies[strategy], randomize ? "Random" : orders[order]);
                        } else {
                            CONSOLE_INFO("Solving the board using {} with heurestic: {}", strategies[strategy], heurestics[heurestic]);
                        }

                        if (Solver::IsBoardSolvable(m_Board)) {
                            Solver* solver = nullptr;

                            switch (strategy) {
                                case _BFS: solver = new BFS(m_Board, randomize); break;
                                case _DFS: solver = new DFS(m_Board, maxDepth, randomize); break;
                                case _IDFS: solver = new IDFS(m_Board, maxDepth, randomize); break;
                                case _HBFS: solver = new BestFirstSearch(m_Board); break;
                                case _ASTAR: solver = new AStar(m_Board); break;
                                case _SMASTAR: solver = new SMAStar(m_Board, memoryLimit); break;
                                default: CONSOLE_ERROR("Invalid strategy!"); break;
                            }

                            solver->SetSearchOrder(orders[order]);
                            solver->SetHeurestic(heurestics[heurestic]);

                            m_BoardCopy = new Board(*m_Board);

                            solver->Solve();

                            m_Solution = solver->GetSolution().moves;

                            delete solver;
                        } else {
                            CONSOLE_ERROR("Board is not solvable!");
                        }
                    }
                }

            }

            if (!m_Solution.empty()) {
                ImGui::Separator();
                ImGui::Spacing();

                if (ImGui::Button("Reload")) {
                    delete m_Board;
                    m_Board = new Board(*m_BoardCopy);
                    m_Solution.clear();
                    index = -2;
                    CONSOLE_WARN("Board has been reloaded!");
                }

                if (ImGui::Button("Copy to clipboard")) {
                    std::string solution;

                    for (const auto& move : m_Solution) {
                        solution += Solver::GetStringifiedDirection(move);
                    }

                    ImGui::SetClipboardText(solution.c_str());
                }

                if (index == -2) {
                    index = (int32_t)(m_Solution.size() - 1);
                }

                {
                    Core::ScopedColor ButtonColor(ImGuiCol_Button, Core::Color::DarkRed);

                    if (index >= 0) {
                        if (ImGui::Button("Previous")) {
                            const MoveDirection direction = m_Solution[index];
                            const MoveDirection opposite = Board::GetOppositeDirection(direction);

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

                    if (index + 1 < m_Solution.size()) {
                        if (ImGui::Button("Next")) {
                            const MoveDirection direction = m_Solution[++index];

                            if (m_Board->CanMove(direction)) {
                                m_Board->Move(direction);
                            } else {
                                CONSOLE_ERROR("Can't move in this direction {}", Solver::GetStringifiedDirection(direction));
                            }
                        }
                    }
                }

                ImGui::Separator();
                ImGui::Spacing();
            }

            if (m_Board) {
                Core::ScopedColor ButtonColor(ImGuiCol_Button, Core::Color::Orange);

                if (ImGui::Button("Reset")) {
                    m_DeleteBoardRequest = true;
                    m_Solution.clear();
                    index = -2;
                    CONSOLE_WARN("Board has been reset!");
                }
            }
        }


        if (m_DeleteBoardRequest) {
            delete m_Board;
            m_Board = nullptr;
            m_DeleteBoardRequest = false;
        }


        ImGui::End();
    }
}
