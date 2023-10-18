#pragma once

#include "Puzzle/Board.hpp"

namespace AI {
    class PuzzleGUIManager final {
    public:

        PuzzleGUIManager(Board* board);
        ~PuzzleGUIManager() = default;

        void OnRender();

    private:

        Board* m_Board;
    };
}
