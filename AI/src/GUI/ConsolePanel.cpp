#include "pch.hpp"
#include "ConsolePanel.hpp"

#include <imgui.h>

#include "Platform/GUI/Core/UI/UI.hpp"

namespace AI {
    ConsolePanel::ConsolePanel(const char* name, const char8_t* icon)
        : Panel(name, icon) {}

    void ConsolePanel::OnRender() {
        ImGui::Begin(m_ID.c_str());

        {
            Core::ScopedStyle FramePadding(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));

        }

        ImGui::End();
    }
}
