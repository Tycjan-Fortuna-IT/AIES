#include "pch.hpp"

#include "MainLayer.hpp"
#include "Engine/Core/Entrypoint.hpp"
#include "Engine/Core/Application.hpp"

namespace AI {
    class AIApplication final : public Core::Application {
    public:

        explicit AIApplication(const Core::ApplicationSpecification& specification)
            : Application(specification) {
            PushLayer(new MainLayer());
        }

        ~AIApplication() override {

        }
    };
}

Core::Application* Core::CreateApplication([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    ApplicationSpecification specification;
    specification.Name = "AIApplication Application";
    specification.Type = ApplicationType::Window;
    specification.Width = 1700;
    specification.Height = 950;

    return new AI::AIApplication(specification);
}
