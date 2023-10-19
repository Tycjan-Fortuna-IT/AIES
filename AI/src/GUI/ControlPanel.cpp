#include "pch.hpp"
#include "ControlPanel.hpp"

#include <imgui.h>

#include "Platform/GUI/Core/UI/UI.hpp"

namespace AI {
    ControlPanel::ControlPanel(const char* name, const char8_t* icon, Board* board)
        : Panel(name, icon), m_Board(board) {}

    void ControlPanel::OnRender() {
        ImGui::Begin(m_ID.c_str());

        {
            Core::ScopedStyle FramePadding(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));

        }

        ImGui::End();
    }
}
