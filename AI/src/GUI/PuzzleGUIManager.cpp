#include "pch.hpp"
#include "PuzzleGUIManager.hpp"

#include <string>

#include "imgui.h"
#include "imgui_internal.h"

namespace AI {
    PuzzleGUIManager::PuzzleGUIManager(Board* board)
        : m_Board(board) {

    }

    void PuzzleGUIManager::OnRender() {
        ImGui::Begin("Puzzle preview");

        static const ImU32 lightOrange = IM_COL32(255, 200, 100, 255);
        static const ImU32 black = IM_COL32(0, 0, 0, 255);
        static const ImU32 lightGray = IM_COL32(240, 240, 240, 255);
        static const ImU32 lightBlue = IM_COL32(100, 100, 255, 255);

        static const uint32_t w = m_Board->GetWidth();
        static const uint32_t h = m_Board->GetHeight();

        ImGui::PushStyleColor(ImGuiCol_WindowBg, lightGray);

        FOR_EACH_PUZZLE_W_H(w, h) {
            int pieceValue = m_Board->GetPuzzle(x, y).GetValue();

            float margin = 5.0f;
            float posX = x * (600.0f / 4.0f + margin); // Swap x and y
            float posY = y * (600.0f / 4.0f + margin) + 40.f;

            ImGui::PushStyleColor(ImGuiCol_Button, pieceValue == 0 ? lightBlue : lightOrange);
            ImGui::PushStyleColor(ImGuiCol_Text, black);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

            ImGui::SetCursorPos(ImVec2(posX, posY));

            {
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
                if (ImGui::Button(std::to_string(pieceValue).c_str(), ImVec2(600.0f / 4.0f, 600.0f / 4.0f))) {

                }
                ImGui::PopStyleVar();
            }

            ImGui::PopStyleColor(2);
            ImGui::PopStyleVar();
        }

        ImGui::PopStyleColor();

        ImGui::End();
    }
}
