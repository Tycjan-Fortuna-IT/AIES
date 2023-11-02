#pragma once

#include "Puzzle/Solver.hpp"

namespace AI {
    class DFS : public Solver {
    public:

        DFS(Board* board, int maxDepth, bool randomize);

        void Solve() override;

    private:

        int m_MaxDepth;
        bool m_Randomize;
    };
}
