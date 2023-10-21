#include "PuzzlePanel.hpp"

#include <string>

#include "imgui.h"
#include "imgui_internal.h"
#include "Engine/Core/Debug/Logger.hpp"
#include "Platform/GUI/Core/UI/Color.hpp"
#include "Platform/GUI/Core/UI/UI.hpp"

namespace AI {
    PuzzlePanel::PuzzlePanel(Board*& board, const char* name, const char8_t* icon)
        : Panel(name, icon), m_Board(board) {}

    void PuzzlePanel::OnRender() {
        ImGui::Begin(m_ID.c_str());

        if (m_Board) {
            Core::ScopedStyle FramePadding(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));

            static const uint32_t w = m_Board->GetWidth();
            static const uint32_t h = m_Board->GetHeight();

            static const float windowWidth = ImGui::GetWindowWidth();
            static const float windowHeight = ImGui::GetWindowHeight();
            static const float size = std::min(windowHeight / h, 600.0f / w); // puzzle size
            static const float margin = 15.0f;

            const float startX = (windowWidth - (w * size + margin)) / 2.0f;

            FOR_EACH_PUZZLE_W_H(w, h) {
                uint32_t value = m_Board->GetPuzzle(x, y).GetValue();

                const float posX = startX + x * size + margin;
                const float posY = y * size + 40.f + margin;

                Core::ScopedColor ButtonColor(ImGuiCol_Button, value == 0 ? Core::Color::LightBlue : Core::Color::BrightOrange);
                Core::ScopedColor ButtonHoveredColor(ImGuiCol_ButtonHovered, Core::Color::LightGreen);
                Core::ScopedColor TextColor(ImGuiCol_Text, Core::Color::LightBlack);

                ImGui::SetCursorPos(ImVec2(posX, posY));

                {
                    Core::ScopedStyle FrameBorderSize(ImGuiStyleVar_FrameBorderSize, 4.0f);
                    Core::ScopedColor BorderColor(ImGuiCol_Border, Core::Color::White);

                    static bool opened = false;

                    {
                        Core::ScopedID ID(x * w + y);

                        if (ImGui::Button(std::to_string(value).c_str(), ImVec2(size, size))) {
                            m_SelectedPuzzle = { x, y };

                            opened = true;
                        }
                    }

                    if (opened) {
                        ImGui::OpenPopup("Change value");
                        opened = false;
                    }
                }
            }

            if (ImGui::BeginPopup("Change value", ImGuiWindowFlags_AlwaysAutoResize)) {
                static int32_t newValue = 0;

                ImGui::InputInt("New value", &newValue);

                if (ImGui::Button("OK", ImVec2(120, 0))) {
                    if (newValue < 0) {
                        APP_ERROR("Invalid value! Value must be greater or equal 0");
                        ImGui::CloseCurrentPopup();
                    } else {
                        m_Board->SetPuzzle(m_SelectedPuzzle.first, m_SelectedPuzzle.second, newValue);
                    }
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SameLine();

                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
        } else {
            ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2.0f - 100.f, ImGui::GetWindowHeight() / 2.0f - 50.0f));

            Core::ScopedColor ButtonColor(ImGuiCol_Button, Core::Color::DarkRed);
            Core::ScopedColor ButtonHoveredColor(ImGuiCol_ButtonHovered, Core::Color::DarkRed);

            if (ImGui::Button("No board", ImVec2(300.0f, 100.0f))) {}
        }

        ImGui::End();
    }
}
