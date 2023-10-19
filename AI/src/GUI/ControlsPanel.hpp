#pragma once

#include "Panel.hpp"
#include "Puzzle/Board.hpp"

namespace AI {
    class ControlsPanel final : public Panel {
    public:

        ControlsPanel(const char* name = "Unnamed Panel", const char8_t* icon = u8"", Board* board = nullptr);
        ~ControlsPanel() override = default;

        void OnRender() override;

    private:

        Board* m_Board{ nullptr };
    };
}
