#include "BestFirstSearch.hpp"

#include <queue>
#include <functional>
#include <unordered_set>

#include "HeuresticCalculationWizard.hpp"
#include "Engine/Core/Debug/Logger.hpp"
#include "GUI/Utils.hpp"

namespace AI {
    BestFirstSearch::BestFirstSearch(Board *board)
        : Solver(board) {}

    void BestFirstSearch::Solve() {
        SOLVED_CHECK()

        auto startTime = std::chrono::steady_clock::now();

        std::priority_queue<HeuristicState> queue;
        std::unordered_set<Board> visited;

        GET_HEURESTIC_FN(heuristicFn, m_Heurestic)

        HeuristicState start(*m_Board, 0, heuristicFn(*m_Board), m_Solution.moves);
        queue.push(start);

        while (
            !queue.empty() &&
            m_Solution.processed < MAX_STATES
        ) {
            HeuristicState currentState = queue.top();
            queue.pop();

            m_Solution.processed++;

            if (currentState.board.IsSolved()) {
                *m_Board = currentState.board;
                m_Solution.moves = currentState.moves;
                break;
            }

            for (const MoveDirection& direction : { UP, DOWN, RIGHT, LEFT }) {
                if (currentState.board.CanMove(direction)) {
                    Board nextBoard = currentState.board;

                    nextBoard.Move(direction);

                    if (!visited.contains(nextBoard)) {
                        int evaluation = heuristicFn(nextBoard);

                        visited.insert(nextBoard);

                        std::vector<MoveDirection> nextMoves = currentState.moves;
                        nextMoves.push_back(direction);

                        HeuristicState nextState(nextBoard, 0, evaluation, nextMoves);

                        queue.push(nextState);
                        m_Solution.maxRecursion = std::max(m_Solution.maxRecursion, (int)nextMoves.size());
                    }
                }
            }
        }

        m_Solution.visited = (int)visited.size();

        if (m_Solution.processed >= MAX_STATES) {
            CONSOLE_WARN("Best First Search reached max states limit!");
            CONSOLE_ERROR("Solution not found!!"); return;
        }

        const auto endTimepoint = std::chrono::steady_clock::now();
        const auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch()
                                  - std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch();

        CONSOLE_INFO("Solution found! Best First Search took {} us", elapsedTime.count());
        CONSOLE_INFO("Solution moves: {}", Solver::GetMoveSetString(m_Solution.moves));
        CONSOLE_INFO("Visited places: {}, Processed places: {}, Max recursion: {}", m_Solution.visited, m_Solution.processed, m_Solution.maxRecursion);
    }
}
