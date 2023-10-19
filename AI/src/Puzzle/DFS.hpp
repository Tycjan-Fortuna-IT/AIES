#pragma once

#include "Solver.hpp"

namespace AI {
    class DFS : public Solver {
    public:

        DFS(Board* board);

        void Solve(const std::string& param) override;
    };
}
