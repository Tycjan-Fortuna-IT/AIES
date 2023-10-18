#include "pch.hpp"
#include "BFS.hpp"

#include <queue>
#include <unordered_set>

#include "Engine/Core/Debug/Logger.hpp"

namespace AI {

    struct BFSState final {
        Board board;
        std::vector<MoveDirection> moves;

        BFSState(Board board, std::vector<MoveDirection> moves)
            : board(board), moves(moves) {}
    };

    BFS::BFS(Board* board)
        : Solver(board) {}

    void BFS::Solve(const std::string& param) {
        APP_TRACE("Solving with BFS, with strategy param: {}", param);

        std::vector<MoveDirection> moveSet = Solver::GetMoveSet(param);

        std::queue<BFSState> q;
        std::unordered_set<Board> visited;

        if (m_Board->IsSolved()) {
            APP_WARN("Puzzle is already solved!");
            return;
        }

        q.push({ *m_Board, {} });

        while (!q.empty()) {
            BFSState currentState = q.front();
            q.pop();

            if (currentState.board.IsSolved()) {
                APP_WARN("SOLVED!!");
                *m_Board = currentState.board;
                m_Solution.moves = currentState.moves;
                break;
            }

            for (const MoveDirection direction : moveSet) {
                if (currentState.board.CanMove(direction)) {
                    BFSState nextState = currentState;

                    nextState.board.Move(direction);
                    nextState.moves.push_back(direction);

                    if (visited.find(nextState.board) == visited.end()) {
                        q.push(nextState);
                        visited.insert(nextState.board);
                    }
                }
            }
        }
    }

}

