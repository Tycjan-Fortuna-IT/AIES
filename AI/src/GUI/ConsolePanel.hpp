#pragma once

#include <glm/vec4.hpp>

#include "Panel.hpp"
#include "Engine/Core/Debug/Logger.hpp"

namespace AI {
    class ConsolePanel final : public Panel {
    public:

        struct Message final {
            uint32_t ID;
            std::string Buffer;
            Core::LogLevel Level;

            Message(uint32_t id, std::string_view message, Core::LogLevel level = Core::LogLevel::Trace);

            void OnRender() const;

            static const char* GetLevelName(Core::LogLevel level);
            static glm::vec4 GetRenderColor(Core::LogLevel level);
            static const char8_t* GetLevelIcon(Core::LogLevel level);
        };

        ConsolePanel(const char* name = "Unnamed Panel", const char8_t* icon = u8"");
        ~ConsolePanel() override = default;

        ConsolePanel(const ConsolePanel& other) = delete;
        ConsolePanel(ConsolePanel&& other) = delete;
        ConsolePanel& operator=(const ConsolePanel& other) = delete;
        ConsolePanel& operator=(ConsolePanel&& other) = delete;

        void OnRender() override;

        void AddMessage(std::string_view message, Core::LogLevel level);

        void SetCommandCallback(std::function<void(const char*)> callback) { m_CommandCallback = callback; }
        void ClearCommandCallback() { m_CommandCallback = nullptr; }

        static ConsolePanel* GetInstance() { return s_Instance; }

    private:

        void GuiRenderMessages();

        static ConsolePanel* s_Instance;

        uint16_t m_Capacity = 200;
        uint16_t m_BufferSize = 0;
        uint16_t m_BufferBegin = 0;

        bool m_RequestScrollToBottom = false;
        std::vector<std::shared_ptr<Message>> m_MessageBuffer;

        std::function<void(const char*)> m_CommandCallback{ nullptr };
    };
}
