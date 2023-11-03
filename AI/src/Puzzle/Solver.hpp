#pragma once

#include <random>
#include <string>
#include <vector>

#include "Board.hpp"

#define SOLVED_CHECK() if (m_Board->IsSolved()) { CONSOLE_WARN("Puzzle is already solved!"); return; }
#define SHUFFLE_IF(cond, vec) if (cond) { m_RandomEngine.seed(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())); std::shuffle((vec).begin(), (vec).end(), m_RandomEngine); }
#define CLOCK_START() auto startTime = std::chrono::steady_clock::now();
#define CLOCK_STOP() const auto endTimepoint = std::chrono::steady_clock::now(); const auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch();

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

        virtual void Solve() = 0;

        const Solution& GetSolution() const { return m_Solution; }

        Board* GetBoard() const { return m_Board; }

        void SetSearchOrder(const std::string& order) { m_SearchOrder = order; }
        void SetHeurestic(const std::string& heurestic) { m_Heurestic = heurestic; }

        static std::vector<MoveDirection> GetMoveSet(const std::string& permutation);
        static std::vector<std::string> GetMoveSetChars(const std::vector<MoveDirection> directions);

        static std::string GetMoveSetString(const std::vector<MoveDirection>& directions);
        static std::string GetStringifiedDirection(MoveDirection direction);

        static bool IsBoardSolvable(const Board* board);

    protected:

        Board* m_Board{ nullptr };
        Solution m_Solution{};

        std::string m_SearchOrder{};
        std::string m_Heurestic{};

        std::mt19937 m_RandomEngine;
    };
}
