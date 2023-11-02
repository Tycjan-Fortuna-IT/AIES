#include "SMAStar.hpp"

#include <queue>
#include <functional>
#include <unordered_set>
#include <algorithm>
#include <set>

#include "HeuresticCalculationWizard.hpp"
#include "Engine/Core/Debug/Logger.hpp"
#include "GUI/Utils.hpp"

namespace AI {
    SMAStar::SMAStar(Board *board, int memoryLimit)
        : Solver(board), m_MemoryLimit(memoryLimit) {}

    void SMAStar::Solve() {
        SOLVED_CHECK()

        auto startTime = std::chrono::steady_clock::now();

        std::multiset<HeuristicState> queue;
        std::unordered_set<Board> visited;

        GET_HEURESTIC_FN(heuristicFn, m_Heurestic)

        HeuristicState start(*m_Board, 0, heuristicFn(*m_Board), m_Solution.moves);
        queue.insert(start);

        while (
            !queue.empty() &&
            m_Solution.processed < MAX_STATES
        ) {
            if (queue.size() + visited.size() > m_MemoryLimit) {
                HeuristicState exceedingState = *queue.begin();
                queue.erase(queue.begin());

                if (!exceedingState.moves.empty()) {
                    MoveDirection lastMove = exceedingState.moves.back();
                    Board lastBoard = exceedingState.board;

                    lastBoard.Move(Board::GetOppositeDirection(lastMove));

                    auto it = std::find_if(queue.begin(), queue.end(), [&lastBoard](const HeuristicState& state) {
                        return state.board == lastBoard;
                    });

                    if (it != queue.end()) {
                        HeuristicState state = *it;

                        state.evaluation = std::numeric_limits<int>::max();
                        queue.erase(it);
                        queue.insert(state);
                    }
                }
            }
            APP_INFO("Queue size: {}, Visited size: {}", queue.size(), visited.size());
            HeuristicState currentState = *queue.begin();
            queue.erase(queue.begin());

            m_Solution.processed++;

            if (currentState.board.IsSolved()) {
                *m_Board = currentState.board;
                m_Solution.moves = currentState.moves;
                break;
            }

            visited.insert(currentState.board);

            for (const MoveDirection& direction : { UP, DOWN, RIGHT, LEFT }) {
                if (currentState.board.CanMove(direction)) {
                    Board nextBoard = currentState.board;

                    nextBoard.Move(direction);

                    if (!visited.contains(nextBoard)) {
                        int cost = currentState.cost + 1;
                        int evaluation = heuristicFn(nextBoard);

                        visited.insert(nextBoard);

                        std::vector<MoveDirection> nextMoves = currentState.moves;
                        nextMoves.push_back(direction);

                        HeuristicState nextState(nextBoard, cost, evaluation, nextMoves);

                        queue.insert(nextState);
                        m_Solution.maxRecursion = std::max(m_Solution.maxRecursion, (int)nextMoves.size());
                    }
                }
            }
        }

        const auto endTimepoint = std::chrono::steady_clock::now();
        const auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch()
                                  - std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch();

        CONSOLE_INFO("Solution found! SMA* took {} us", elapsedTime.count());
        CONSOLE_INFO("Solution moves: {}", Solver::GetMoveSetString(m_Solution.moves));
        CONSOLE_INFO("Visited places: {}, Processed places: {}, Max recursion: {}", m_Solution.visited, m_Solution.processed, m_Solution.maxRecursion);
    }
}
