#include "IDFS.hpp"

#include <functional>
#include "GUI/Utils.hpp"

namespace AI {
    IDFS::IDFS(Board *board, int maxDepth, bool randomize)
        : Solver(board), m_MaxDepth(maxDepth), m_Randomize(randomize) {}

    void IDFS::Solve() {
        std::vector<MoveDirection> moveSet = Solver::GetMoveSet(m_SearchOrder);

        SOLVED_CHECK()
        CLOCK_START()

        bool solutionFound = false;

        for (int i = 0; i < m_MaxDepth; i++) {
            std::function<bool(Board*, int)> DFS = [&](Board* board, int depth) {
                if (depth > i)
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

        CLOCK_STOP()

        m_Solution.duration = elapsedTime.count();

        CONSOLE_INFO("Solution found! IDFS took {} us", elapsedTime.count());
        CONSOLE_INFO("Solution moves count: {}", m_Solution.moves.size());
        CONSOLE_INFO("Solution moves: {}", Solver::GetMoveSetString(m_Solution.moves));
        CONSOLE_INFO("Visited places: {}, Processed places: {}, Max recursion: {}", m_Solution.visited, m_Solution.processed, m_Solution.maxRecursion);
    }
}
