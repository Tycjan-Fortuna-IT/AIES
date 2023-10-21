#pragma once

#include <random>
#include <string>
#include <vector>

#include "Board.hpp"

#define SOLVED_CHECK() if (m_Board->IsSolved()) { CONSOLE_WARN("Puzzle is already solved!"); return; }
#define SHUFFLE_IF(cond, vec) if (cond) { m_RandomEngine.seed(std::chrono::steady_clock::now().time_since_epoch().count()); std::shuffle(vec.begin(), vec.end(), m_RandomEngine); }

namespace AI {
    struct Solution final {
        std::vector<MoveDirection> moves;
        int visited;
        int processed;
        int maxRecursion;
        double duration;
    };

    class Solver {
    public:

        Solver(Board* board);
        virtual ~Solver() = default;

        virtual void Solve(const std::string& param) = 0;

        const Solution& GetSolution() const { return m_Solution; }

        Board* GetBoard() const { return m_Board; }

        static std::vector<MoveDirection> GetMoveSet(const std::string& permutation);
        static std::vector<std::string> GetMoveSetChars(const std::vector<MoveDirection> directions);

        static std::string GetMoveSetString(const std::vector<MoveDirection>& directions);
        static std::string GetStringifiedDirection(MoveDirection direction);

        static bool IsBoardSolvable(const Board* board);

    protected:

        Board* m_Board{ nullptr };
        Solution m_Solution{};

        std::mt19937 m_RandomEngine;
    };
}
