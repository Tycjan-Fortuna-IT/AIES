#include "pch.hpp"
#include "Board.hpp"

#include "Engine/Core/Debug/Logger.hpp"

// width -> x -> column
// height -> y -> row

#define FOR_EACH_COLUMN for (uint32_t x = 0; x < m_Width; ++x)
#define FOR_EACH_ROW for (uint32_t y = 0; y < m_Height; ++y)
#define FOR_EACH_PUZZLE FOR_EACH_ROW FOR_EACH_COLUMN

namespace AI {

    Board::Board(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height) {
        m_Puzzles = new Puzzle*[width];

        FOR_EACH_COLUMN {
            m_Puzzles[x] = new Puzzle[width];
        }
    }

    Puzzle Board::GetEmptyPuzzle() const {
        FOR_EACH_PUZZLE {
            if (m_Puzzles[x][y].IsEmpty())
                return m_Puzzles[x][y];
        }

        CORE_ERROR("There is no empty puzzle! Board is not valid!");
    }

    std::pair<uint32_t, uint32_t> Board::GetEmptyPuzzlePosition() const {
        FOR_EACH_PUZZLE {
            if (m_Puzzles[x][y].IsEmpty())
                return { x, y };
        }

        CORE_ERROR("There is no empty puzzle! Board is not valid!");
    }

    Puzzle Board::GetPuzzle(uint32_t x, uint32_t y) const {
        ASSERT(x >= 0 && x < m_Width && y >= 0 && y < m_Height, "Invalid puzzle position!")

        return m_Puzzles[y][x];
    }

    Puzzle Board::GetPuzzle(int index) const {
        ASSERT(index >= 0 && index < m_Width * m_Height, "Invalid puzzle position!")

        return m_Puzzles[index / m_Width][index % m_Width];
    }

    void Board::SetPuzzle(uint32_t x, uint32_t y, uint32_t val) {
        ASSERT(x >= 0 && x < m_Width && y >= 0 && y < m_Height, "Invalid puzzle position!")

        m_Puzzles[y][x] = val;
    }

    void Board::SetPuzzle(int index, uint32_t val) {
        ASSERT(index >= 0 && index < m_Width * m_Height, "Invalid puzzle position!")

        m_Puzzles[index / m_Width][index % m_Width] = val;
    }

    bool Board::CanMove(MoveDirection direction) const {
        return false;
    }

    void Board::Move(MoveDirection direction) {

    }

    bool Board::IsSolved() const {
        // Solved state e.g. [4x4]
        // 1 2 3 4
        // 5 6 7 8
        // 9 10 11 12
        // 13 14 15 0

        for (int i = 0; i < (m_Width * m_Height) - 1; ++i) {
            if (m_Puzzles[i / m_Width][i % m_Height].GetValue() != i + 1) {
                return false;
            }
        }

        return true;
    }

    MoveDirection Board::GetOpositeDirection(MoveDirection direction) {
        switch (direction) {
            case MoveDirection::UP: return MoveDirection::DOWN;
            case MoveDirection::DOWN: return MoveDirection::UP;
            case MoveDirection::LEFT: return MoveDirection::RIGHT;
            case MoveDirection::RIGHT: return MoveDirection::LEFT;
        }
    }

    bool Board::operator==(const Board &other) const {
        if (m_Width != other.GetWidth() || m_Height != other.GetHeight()) {
            return false;
        }

        FOR_EACH_PUZZLE {
            if (m_Puzzles[x][y] != other.GetPuzzles()[x][y])
                return false;
        }

        return true;
    }
}
