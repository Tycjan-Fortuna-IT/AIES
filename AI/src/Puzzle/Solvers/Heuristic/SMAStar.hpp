#pragma once

#include "Puzzle/Solver.hpp"

namespace AI {
    class SMAStar : public Solver {
    public:

        SMAStar(Board* board, int memoryLimit);

        void Solve() override;

    private:

        int m_MemoryLimit;
    };
}
