#pragma once

#include "Puzzle/Solver.hpp"

namespace AI {
    class IDFS : public Solver {
    public:

        IDFS(Board* board, int maxDepth, bool randomize);

        void Solve() override;

    private:

        int m_MaxDepth;
        bool m_Randomize;
    };
}
