#pragma once

#include "Engine/Core/Layer.hpp"
#include "GUI/ConsolePanel.hpp"
#include "GUI/ControlPanel.hpp"
#include "Platform/GUI/Core/Events/KeyEvent.hpp"
#include "Platform/GUI/Core/Events/MouseEvent.hpp"
#include "GUI/PuzzlePanel.hpp"

namespace AI {
    class MainLayer final : public Core::Layer {
    public:

        MainLayer(const std::string& name = "MainLayer");

        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(Core::Event& event) override;
        void OnUpdate(Core::Timestep dt) override;
        void OnGuiRender() override;

    private:

        float m_TopMenuBarHeight = 10.0f;

        Board* m_Board{ nullptr };
        PuzzlePanel* m_PuzzlePanel{ nullptr };
        ConsolePanel* m_ConsolePanel{ nullptr };
        ControlPanel* m_ControlPanel{ nullptr };

        bool OnKeyPressed(Core::KeyPressedEvent& event);
        bool OnMouseKeyPressed(Core::MouseButtonPressedEvent& event);

        void BeginDockspace(const char* name) const;
        void EndDockspace() const;

        void LoadBoard();
    };
}
