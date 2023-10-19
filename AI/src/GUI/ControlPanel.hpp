#pragma once

#include "Panel.hpp"
#include "Puzzle/Board.hpp"

namespace AI {
    class ControlPanel final : public Panel {
    public:

        ControlPanel(const char* name = "Unnamed Panel", const char8_t* icon = u8"", Board* board = nullptr);
        ~ControlPanel() override = default;

        void OnRender() override;

    private:

        Board* m_Board{ nullptr };
    };
}
