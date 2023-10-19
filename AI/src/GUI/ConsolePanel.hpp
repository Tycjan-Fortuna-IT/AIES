#pragma once

#include "Panel.hpp"

namespace AI {
    class ConsolePanel final : public Panel {
    public:

        ConsolePanel(const char* name = "Unnamed Panel", const char8_t* icon = u8"");
        ~ConsolePanel() override = default;

        void OnRender() override;
    };
}
