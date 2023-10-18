#include "pch.hpp"
#include "Solver.hpp"

namespace AI {
    Solver::Solver(Board *board)
        : m_Board(board) {}

    std::vector<MoveDirection> Solver::GetMoveSet(const std::string &permutation) {
        std::vector<MoveDirection> directions;

        for (const char way : permutation) {
            switch (way) {
                case 'U': directions.push_back(MoveDirection::UP); break;
                case 'D': directions.push_back(MoveDirection::DOWN); break;
                case 'L': directions.push_back(MoveDirection::LEFT); break;
                case 'R': directions.push_back(MoveDirection::RIGHT); break;
            }
        }

        return directions;
    }
}
