#pragma once

#include "Puzzle/Board.hpp"

namespace AI {
    class PuzzleGUIManager final {
    public:

        PuzzleGUIManager(Board* board);
        ~PuzzleGUIManager() = default;

        void OnRender();

    private:

        Board* m_Board{ nullptr };

        std::pair<uint32_t, uint32_t> m_SelectedPuzzle{ 0, 0 };
    };
}
