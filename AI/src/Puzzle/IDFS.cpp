#include "IDFS.hpp"

#include <functional>
#include "GUI/Utils.hpp"

namespace AI {
    IDFS::IDFS(Board *board, int maxDepth, bool randomize)
        : Solver(board), m_MaxDepth(maxDepth), m_Randomize(randomize) {}

    void IDFS::Solve(const std::string &param) {
        std::vector<MoveDirection> moveSet = Solver::GetMoveSet(param);

        SOLVED_CHECK()

        auto startTime = std::chrono::steady_clock::now();

        bool solutionFound = false;

        for (; m_MaxDepth <= 20; m_MaxDepth++) {
            std::function<bool(Board*, int)> DFS = [&](Board* board, int depth) {
                if (depth > m_MaxDepth)
                    return false;

                if (depth > m_Solution.maxRecursion)
                    m_Solution.maxRecursion = depth;

                m_Solution.processed++;

                if (board->IsSolved())
                    return true;

                SHUFFLE_IF(m_Randomize, moveSet)

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

            if (DFS(m_Board, 0))
                solutionFound = true;
        }

        if (!solutionFound) {
            CONSOLE_ERROR("Solution not found!!"); return;
        }

        const auto endTimepoint = std::chrono::steady_clock::now();
        const auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch()
                                  - std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch();

        CONSOLE_INFO("Solution found! IDFS took {} us", elapsedTime.count());
        CONSOLE_INFO("Solution moves: {}", Solver::GetMoveSetString(m_Solution.moves));
        CONSOLE_INFO("Visited places: {}, Processed places: {}, Max recursion: {}", m_Solution.visited, m_Solution.processed, m_Solution.maxRecursion);
    }
}
