#pragma once

#include <string>
#include <vector>

#include "Board.hpp"

namespace AI {
    struct Solution final {
        std::vector<MoveDirection> moves;
        int visited;
        double duration;
    };

    class Solver {
    public:

        Solver(Board* board);

        virtual void Solve(const std::string& param) = 0;

        const Solution& GetSolution() const { return m_Solution; }

        Board* GetBoard() const { return m_Board; }

        static std::vector<MoveDirection> GetMoveSet(const std::string& permutation);
        static std::vector<std::string> GetMoveSetChars(const std::vector<MoveDirection> directions);

    protected:

        Board* m_Board{ nullptr };
        Solution m_Solution{};
    };
}
