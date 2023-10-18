#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "Puzzle.hpp"

// width -> x -> column
// height -> y -> row

// for each column (x) in width
//    for each row (y) in height

#define FOR_EACH_COLUMN for (uint32_t x = 0; x < m_Width; ++x)
#define FOR_EACH_ROW for (uint32_t y = 0; y < m_Height; ++y)
#define FOR_EACH_PUZZLE FOR_EACH_COLUMN FOR_EACH_ROW

#define FOR_EACH_COLUMN_W(w) for (uint32_t x = 0; x < (w); ++x)
#define FOR_EACH_ROW_H(h) for (uint32_t y = 0; y < (h); ++y)
#define FOR_EACH_PUZZLE_W_H(w, h) FOR_EACH_COLUMN_W(w) FOR_EACH_ROW_H(h)

namespace AI {

    enum MoveDirection {
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4,
    };

    class Board final {
    public:

        Board(uint32_t width, uint32_t height);
        ~Board() = default;

        uint32_t GetWidth() const { return m_Width; }
        uint32_t GetHeight() const { return m_Height; }

        Puzzle GetEmptyPuzzle() const;
        std::pair<uint32_t, uint32_t> GetEmptyPuzzlePosition() const;

        Puzzle GetPuzzle(uint32_t x, uint32_t y) const;
        Puzzle GetPuzzle(uint32_t index) const;

        void SetPuzzle(uint32_t x, uint32_t y, uint32_t val);

        const std::vector<std::vector<Puzzle>>& GetPuzzles() const { return m_Puzzles; }

        bool CanMove(MoveDirection direction) const;
        void Move(MoveDirection direction);

        void LogDisplay() const;

        bool IsSolved() const;

        static MoveDirection GetOpositeDirection(MoveDirection direction);
        bool operator==(const Board& other) const;

    private:

        uint32_t m_Width;
        uint32_t m_Height;

        std::vector<std::vector<Puzzle>> m_Puzzles{};
    };
}

namespace std {
    template<>
    struct hash<AI::Board> {
        size_t operator()(const AI::Board& board) const noexcept {
            size_t hash = 0;

            const int width = board.GetWidth();
            const int height = board.GetHeight();

            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    hash = (hash * 31) ^ std::hash<int>{}(board.GetPuzzle(i, j).GetValue());
                }
            }

            return hash;
        }
    };
}
