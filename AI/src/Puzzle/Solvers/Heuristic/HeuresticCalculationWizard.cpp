#include "HeuresticCalculationWizard.hpp"

namespace AI {
    int HeuresticCalculationWizard::GetZeroHeuresticEvaluation(const Board &board) {
        return 0;
    }

    int HeuresticCalculationWizard::GetManhattanHeuresticEvaluation(const Board& board) {
        int eval = 0;

        for (uint32_t i = 0; i < board.GetWidth(); i++) {
            for (uint32_t j = 0; j < board.GetHeight(); j++) {
                const uint32_t tile = board.GetPuzzle(i, j).GetValue();

                if (tile == 0) {
                    continue;
                }

                const int targetX = (int)((tile - 1) % board.GetWidth());
                const int targetY = (int)((tile - 1) / board.GetWidth());

                eval += std::abs((int)i - targetX) + std::abs((int)j - targetY);
            }
        }

        return eval;
    }

    int HeuresticCalculationWizard::GetHammingHeuresticEvaluation(const Board& board) {
        int eval = 0;

        for (uint32_t i = 0; i < board.GetWidth(); i++) {
            for (uint32_t j = 0; j < board.GetHeight(); j++) {
                const uint32_t tile = board.GetPuzzle(i, j).GetValue();

                if (tile == 0) {
                    continue;
                }

                const int targetX = (int)((tile - 1) % board.GetWidth());
                const int targetY = (int)((tile - 1) / board.GetWidth());

                if ((int)i != targetX || (int)j != targetY) {
                    eval++;
                }
            }
        }

        return eval;
    }

    int HeuresticCalculationWizard::GetLinearConflictHeuresticEvaluation(const Board& board) {
        int eval = 0;

        return eval;
    }

    int HeuresticCalculationWizard::GetEuclideanHeuresticEvaluation(const Board& board) {
        int eval = 0;

        return eval;
    }

    int HeuresticCalculationWizard::GetChebyshevHeuresticEvaluation(const Board& board) {
        int eval = 0;

        return eval;
    }

    int HeuresticCalculationWizard::GetGaschnigHeuresticEvaluation(const Board& board) {
        int eval = 0;

        return eval;
    }
}
