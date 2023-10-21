#pragma once

#include "Panel.hpp"
#include "Puzzle/Board.hpp"

namespace AI {
    class ControlPanel final : public Panel {
    public:

        ControlPanel(Board*& board, const char* name = "Unnamed Panel", const char8_t* icon = u8"");
        ~ControlPanel() override = default;

        void OnRender() override;

        ControlPanel(const ControlPanel&) = delete;
        ControlPanel& operator=(const ControlPanel&) = delete;
        ControlPanel(ControlPanel&&) = delete;
        ControlPanel& operator=(ControlPanel&&) = delete;

    private:

        Board*& m_Board;

        std::vector<MoveDirection> m_Solution{};

        bool m_DeleteBoardRequest = false;
    };
}
