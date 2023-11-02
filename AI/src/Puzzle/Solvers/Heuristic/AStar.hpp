#pragma once

#include "Puzzle/Solver.hpp"

namespace AI {
    class AStar : public Solver {
    public:

        AStar(Board* board);

        void Solve() override;
    };
}
