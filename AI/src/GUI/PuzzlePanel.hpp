#pragma once

#include "Panel.hpp"
#include "Puzzle/Board.hpp"

namespace AI {
    class PuzzlePanel final : public Panel {
    public:

        PuzzlePanel(Board*& board, const char* name = "Unnamed Panel", const char8_t* icon = u8"");
        ~PuzzlePanel() override = default;

        void OnRender() override;

    private:

        Board*& m_Board;

        std::pair<uint32_t, uint32_t> m_SelectedPuzzle{ 0, 0 };
    };
}
