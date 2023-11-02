#pragma once

#include "Puzzle/Solver.hpp"

namespace AI {
    class BestFirstSearch : public Solver {
    public:

        BestFirstSearch(Board* board);

        void Solve() override;
    };
}
