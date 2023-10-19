#pragma once

#include "Panel.hpp"
#include "Puzzle/Board.hpp"

namespace AI {
    class PuzzlePanel final : public Panel {
    public:

        PuzzlePanel(const char* name = "Unnamed Panel", const char8_t* icon = u8"", Board* board = nullptr);
        ~PuzzlePanel() override = default;

        void OnRender() override;

    private:

        Board* m_Board{ nullptr };

        std::pair<uint32_t, uint32_t> m_SelectedPuzzle{ 0, 0 };
    };
}
