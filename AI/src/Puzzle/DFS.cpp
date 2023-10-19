#include "pch.hpp"
#include "DFS.hpp"

#include <functional>

#include "Engine/Core/Debug/Logger.hpp"

namespace AI {

    DFS::DFS(Board* board)
        : Solver(board) {}

    void DFS::Solve(const std::string &param) {
        APP_TRACE("Solving with DFS, with strategy param: {}", param);

        std::vector<MoveDirection> moveSet = Solver::GetMoveSet(param);

        std::function<bool(Board*, int)> DFS = [&](Board* board, int depth) {
            if (depth > 25)
                return false;

            if (board->IsSolved())
                return true;

            for (const MoveDirection direction : moveSet) {
                if (board->CanMove(direction)) {
                    board->Move(direction);
                    m_Solution.moves.push_back(direction);

                    if (DFS(board, depth + 1)) {
                        return true;
                    }

                    board->Move(Board::GetOppositeDirection(direction));
                    m_Solution.moves.pop_back();
                }
            }

            return false;
        };

        if (!DFS(m_Board, 0)) {
            APP_ERROR("Solution not found!!");
        }
    }
}

