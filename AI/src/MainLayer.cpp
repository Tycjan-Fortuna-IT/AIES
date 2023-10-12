#include "pch.hpp"
#include "MainLayer.hpp"

#include "Platform/GUI/Core/GUIApplication.hpp"
#include "Platform/GUI/Core/OpenGL/OpenGlRendererAPI.hpp"

namespace ImgProc {
    MainLayer::MainLayer(const std::string& name)
        : Layer(name) {}

    void MainLayer::OnAttach() {
        Core::OpenGlRendererAPI::Init();

        Core::Application::Get().GetGuiLayer()->SetBlockEvents(false);
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
        
    }

    bool MainLayer::OnKeyPressed(Core::KeyPressedEvent& event) {

        return false;
    }

    bool MainLayer::OnMouseKeyPressed(Core::MouseButtonPressedEvent& event) {

        return false;
    }
}

