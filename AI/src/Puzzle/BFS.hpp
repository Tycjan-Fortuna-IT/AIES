#pragma once

#include "Solver.hpp"

namespace AI {
    class BFS : public Solver {
    public:

        BFS(Board* board);

        /**
         * @brief Solves the puzzle after moving in given initial directions
         *
         * @param param A permutation of a set of move directions
         */
        void Solve(const std::string& param) override;
    };
}
