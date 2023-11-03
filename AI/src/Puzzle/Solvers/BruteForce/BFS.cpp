#include "BFS.hpp"

#include <queue>
#include <unordered_set>

#include "Engine/Core/Debug/Logger.hpp"
#include "GUI/Utils.hpp"
#include "Puzzle/Board.hpp"

namespace AI {

    struct BFSState final {
        Board board;
        std::vector<MoveDirection> moves;

        BFSState(Board board, std::vector<MoveDirection> moves)
            : board(board), moves(moves) {}
    };

    BFS::BFS(Board* board, bool randomize)
        : AI::Solver(board), m_Randomize(randomize) {}

    void BFS::Solve() {
        std::vector<MoveDirection> moveSet = Solver::GetMoveSet(m_SearchOrder);

        std::queue<BFSState> q;
        std::unordered_set<Board> visited;

        SOLVED_CHECK()
        CLOCK_START()

        q.push({ *m_Board, {} });

        while (!q.empty()) {
            BFSState currentState = q.front();
            q.pop();

            m_Solution.processed++;

            if (currentState.board.IsSolved()) {
                *m_Board = currentState.board;
                m_Solution.moves = currentState.moves;
                break;
            }

            SHUFFLE_IF(m_Randomize, moveSet)

            for (const MoveDirection direction : moveSet) {
                if (currentState.board.CanMove(direction)) {
                    BFSState nextState = currentState;

                    nextState.board.Move(direction);
                    nextState.moves.push_back(direction);

                    if (!visited.contains(nextState.board)) {
                        q.push(nextState);
                        visited.insert(nextState.board);
                        m_Solution.maxRecursion = std::max(m_Solution.maxRecursion, static_cast<int>(nextState.moves.size()));
                    }
                }
            }
        }

        m_Solution.visited = (int)visited.size();

        CLOCK_STOP()

        CONSOLE_INFO("Solution found! BFS took {} us", elapsedTime.count());
        CONSOLE_INFO("Solution moves: {}", Solver::GetMoveSetString(m_Solution.moves));
        CONSOLE_INFO("Visited places: {}, Processed places: {}, Max recursion: {}", m_Solution.visited, m_Solution.processed, m_Solution.maxRecursion);
    }

}

