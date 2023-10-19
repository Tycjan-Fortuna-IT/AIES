#include "pch.hpp"
#include "DFS.hpp"

#include <functional>

#include "Engine/Core/Debug/Logger.hpp"
#include "GUI/Utils.hpp"

namespace AI {

    DFS::DFS(Board* board)
        : Solver(board) {}

    void DFS::Solve(const std::string &param) {
        std::vector<MoveDirection> moveSet = Solver::GetMoveSet(param);

        auto startTime = std::chrono::steady_clock::now();

        std::function<bool(Board*, int)> DFS = [&](Board* board, int depth) {
            if (depth > 25)
                return false;

            if (depth > m_Solution.maxRecursion)
                m_Solution.maxRecursion = depth;

            m_Solution.processed++;

            if (board->IsSolved())
                return true;

            for (const MoveDirection direction : moveSet) {
                if (board->CanMove(direction)) {
                    board->Move(direction);
                    m_Solution.moves.push_back(direction);
                    m_Solution.visited++;

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
            CONSOLE_ERROR("Solution not found!!"); return;
        }

        const auto endTimepoint = std::chrono::steady_clock::now();
        const auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch()
                                  - std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch();

        CONSOLE_INFO("Solution found! DFS took {} us", elapsedTime.count());
        CONSOLE_INFO("Solution moves: {}", Solver::GetMoveSetString(m_Solution.moves));
        CONSOLE_INFO("Visited places: {}, Processed places: {}, Max recursion: {}", m_Solution.visited, m_Solution.processed, m_Solution.maxRecursion);
    }
}

