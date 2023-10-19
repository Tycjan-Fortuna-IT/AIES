#include "pch.hpp"
#include "ConsolePanel.hpp"

#include <imgui.h>
#include <icons/include/icons/IconsMaterialDesignIcons.h>

#include "Engine/Core/Utils/StringUtils.hpp"
#include "Platform/GUI/Core/UI/Theme.hpp"
#include "Platform/GUI/Core/UI/UI.hpp"

namespace AI {
    ConsolePanel::ConsolePanel(const char* name, const char8_t* icon)
        : Panel(name, icon) {
        m_MessageBuffer = std::vector<std::shared_ptr<Message>>(m_Capacity);
    }

    void ConsolePanel::OnRender() {
        ImGui::Begin(m_ID.c_str());

        {
            Core::ScopedStyle FramePadding(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));

            ImGui::Separator();
            ImGui::Spacing();
            ImGui::Spacing();

            ImGui::Separator();

            GuiRenderMessages();
        }

        ImGui::End();
    }

    void ConsolePanel::AddMessage(const std::string_view message, Core::LogLevel level) {
        static uint32_t id = 0;

        *(m_MessageBuffer.begin() + m_BufferBegin) = std::make_shared<Message>(id, message, level);

        if (++m_BufferBegin == m_Capacity)
            m_BufferBegin = 0;
        if (m_BufferSize < m_Capacity)
            m_BufferSize++;

        m_RequestScrollToBottom = true;

        id++;
    }

    void ConsolePanel::GuiRenderMessages() {
        constexpr ImGuiTableFlags tableFlags = ImGuiTableFlags_ContextMenuInBody | ImGuiTableFlags_ScrollY;

        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, { 1, 1 });
        if (ImGui::BeginTable("ScrollRegionTable", 1, tableFlags)) {
            ImGui::SetWindowFontScale(1.f);

            const auto& messageStart = m_MessageBuffer.begin() + m_BufferBegin;

            if (m_BufferBegin != 0) {
                for (auto message = m_MessageBuffer.begin(); message != messageStart; ++message) {
                    (*message)->OnRender();
                }
            }

            ImGui::SetScrollY(ImGui::GetScrollMaxY()); // temporary fix

            ImGui::EndTable();
        }
        ImGui::PopStyleVar();
    }

    ConsolePanel::Message::Message(uint32_t id, std::string_view message, Core::LogLevel level)
        : ID(id), Buffer(message.data(), message.size()), Level(level) {}

    void ConsolePanel::Message::OnRender() const {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();

        ImGuiTreeNodeFlags flags = 0;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanFullWidth;
        flags |= ImGuiTreeNodeFlags_FramePadding;
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

        {
            Core::ScopedID ScopeID(static_cast<int>(ID));

            glm::vec4 c = GetRenderColor(Level);
            ImGui::PushStyleColor(ImGuiCol_Text, { c.r, c.g, c.b, c.a });
            ImGui::PushFont(Core::Theme::BoldFont);
            const auto levelIcon = GetLevelIcon(Level);
            ImGui::TreeNodeEx(&ID, flags, "%s  %s", Core::StringUtils::FromChar8T(levelIcon), Buffer.c_str());
            ImGui::PopFont();
            ImGui::PopStyleColor();

            if (ImGui::BeginPopupContextItem("Popup")) {
                if (ImGui::MenuItem("Copy"))
                    ImGui::SetClipboardText(Buffer.c_str());

                ImGui::EndPopup();
            }
        }
    }

    const char* ConsolePanel::Message::GetLevelName(Core::LogLevel level) {
        switch (level) {
            case Core::LogLevel::Trace:			return "Trace";
            case Core::LogLevel::Info:			return "Info";
            case Core::LogLevel::Debug:			return "Debug";
            case Core::LogLevel::Warn:			return "Warning";
            case Core::LogLevel::Error:			return "Error";
            case Core::LogLevel::Critical:		return "Critical";
        }

        return "Unknown name";
    }

    glm::vec4 ConsolePanel::Message::GetRenderColor(Core::LogLevel level) {
        switch (level) {
            case Core::LogLevel::Trace:			return { 0.50f, 0.50f, 0.50f, 1.00f }; // Grey
            case Core::LogLevel::Info:			return { 0.10f, 0.60f, 0.10f, 1.00f }; // Green
            case Core::LogLevel::Debug:			return { 0.00f, 0.50f, 0.50f, 1.00f }; // Cyan
            case Core::LogLevel::Warn:			return { 0.60f, 0.60f, 0.10f, 1.00f }; // Yellow
            case Core::LogLevel::Error:			return { 0.90f, 0.25f, 0.25f, 1.00f }; // Red
            case Core::LogLevel::Critical:		return { 0.60f, 0.20f, 0.80f, 1.00f }; // Purple
        }

        return { 1.00f, 1.00f, 1.00f, 1.00f };
    }

    const char8_t* ConsolePanel::Message::GetLevelIcon(Core::LogLevel level) {
        switch (level) {
            case Core::LogLevel::Trace:				return ICON_MDI_MESSAGE_TEXT;
            case Core::LogLevel::Info:				return ICON_MDI_INFORMATION;
            case Core::LogLevel::Debug:				return ICON_MDI_BUG;
            case Core::LogLevel::Warn:				return ICON_MDI_ALERT;
            case Core::LogLevel::Error:				return ICON_MDI_CLOSE_OCTAGON;
            case Core::LogLevel::Critical:			return ICON_MDI_ALERT_OCTAGRAM;
        }

        return u8"Unknown name";
    }
}
