#pragma once

#include "Board.hpp"

namespace AI {
    class HeuresticCalculationWizard final {
    public:

        /**
         * Returns 0, indicating that the board has no heuristic value.
         * @param board The board to evaluate.
         * @return 0.
         */
        static int GetZeroHeuresticEvaluation(const Board* board);

        /**
         * Calculates the Manhattan distance between each tile and its goal position, and returns the sum of these distances.
         * @param board The board to evaluate.
         * @return The Manhattan distance heuristic value.
         */
        static int GetManhattanHeuresticEvaluation(const Board* board);

        /**
         * Counts the number of tiles that are not in their goal position, and returns this count.
         * @param board The board to evaluate.
         * @return The Hamming distance heuristic value.
         */
        static int GetHammingHeuresticEvaluation(const Board* board);

        /**
         * Calculates the number of conflicting tile pairs in each row and column, and returns the sum of these conflicts.
         * @param board The board to evaluate.
         * @return The linear conflict heuristic value.
         */
        static int GetLinearConflictHeuresticEvaluation(const Board* board);

        /**
         * Calculates the Euclidean distance between each tile and its goal position, and returns the sum of these distances.
         * @param board The board to evaluate.
         * @return The Euclidean distance heuristic value.
         */
        static int GetEuclideanHeuresticEvaluation(const Board* board);

        /**
         * Calculates the Chebyshev distance between each tile and its goal position, and returns the sum of these distances.
         * @param board The board to evaluate.
         * @return The Chebyshev distance heuristic value.
         */
        static int GetChebyshevHeuresticEvaluation(const Board* board);

        /**
         * Calculates the Gaschnig heuristic value, which is a combination of the Manhattan and linear conflict heuristics.
         * @param board The board to evaluate.
         * @return The Gaschnig heuristic value.
         */
        static int GetGaschnigHeuresticEvaluation(const Board* board);
    };
}
