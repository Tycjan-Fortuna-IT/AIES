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
            break;
        }

        for (const MoveDirection direction : moveSet) {
            if (currentState.board.CanMove(direction)) {
                BFSState nextState = currentState;

                nextState.board.Move(direction);
                nextState.moves.push_back(direction);
                nextState.board.LogDisplay();

                if (!visited.contains(nextState.board)) {
                    visited.insert(nextState.board);
                    q.push(nextState);
                }
            }
        }
    }
}

}

