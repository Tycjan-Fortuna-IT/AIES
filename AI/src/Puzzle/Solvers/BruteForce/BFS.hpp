#pragma once

#include "Puzzle/Solver.hpp"

namespace AI {
    class BFS : public Solver {
    public:

        BFS(Board* board, bool randomize);

        void Solve(const std::string& param) override;

    private:

        bool m_Randomize;
    };
}
