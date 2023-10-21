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

    std::vector<std::string> Solver::GetMoveSetChars(const std::vector<MoveDirection> directions) {
        std::vector<std::string> moves;

        for (MoveDirection move : directions) {
            switch (move) {
                case MoveDirection::UP: moves.push_back("U"); break;
                case MoveDirection::DOWN: moves.push_back("D"); break;
                case MoveDirection::LEFT: moves.push_back("L"); break;
                case MoveDirection::RIGHT: moves.push_back("R"); break;
            }
        }

        return moves;
    }

    std::string Solver::GetMoveSetString(const std::vector<MoveDirection>& directions) {
        std::string moves;

        for (MoveDirection move : directions) {
            switch (move) {
                case MoveDirection::UP: moves += "U"; break;
                case MoveDirection::DOWN: moves += "D"; break;
                case MoveDirection::LEFT: moves += "L"; break;
                case MoveDirection::RIGHT: moves += "R"; break;
            }
        }

        return moves;
    }

    std::string Solver::GetStringifiedDirection(MoveDirection direction) {
        switch (direction) {
            case MoveDirection::UP: return "U";
            case MoveDirection::DOWN: return "D";
            case MoveDirection::LEFT: return "L";
            case MoveDirection::RIGHT: return "R";
        }

        return "";
    }

    bool Solver::IsBoardSolvable(const Board* board) {
        // Consider counting inversions in the board

        return board->HasEmptyPuzzle();
    }
}
