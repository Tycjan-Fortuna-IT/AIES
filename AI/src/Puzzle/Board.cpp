#include "pch.hpp"
#include "Board.hpp"

#include "Engine/Core/Debug/Logger.hpp"

// width -> x -> column
// height -> y -> row

// for each column (x) in width
//    for each row (y) in height

#define FOR_EACH_COLUMN for (uint32_t x = 0; x < m_Width; ++x)
#define FOR_EACH_ROW for (uint32_t y = 0; y < m_Height; ++y)
#define FOR_EACH_PUZZLE FOR_EACH_COLUMN FOR_EACH_ROW

namespace AI {

    Board::Board(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height) {
        m_Puzzles = std::vector<std::vector<Puzzle>>(width, std::vector<Puzzle>(height));
    }

    Puzzle Board::GetEmptyPuzzle() const {
        FOR_EACH_PUZZLE {
            if (m_Puzzles[x][y].IsEmpty())
                return m_Puzzles[x][y];
        }

        APP_CRITICAL("There is no empty puzzle! Board is not valid!");

        return Puzzle();
    }

    std::pair<uint32_t, uint32_t> Board::GetEmptyPuzzlePosition() const {
        FOR_EACH_PUZZLE {
            if (m_Puzzles[x][y].IsEmpty())
                return { y, x };
        }

        APP_CRITICAL("There is no empty puzzle! Board is not valid!");

        return { 0, 0 };
    }

    Puzzle Board::GetPuzzle(uint32_t x, uint32_t y) const {
        ASSERT(x < m_Width && y < m_Height, "Invalid puzzle position!")

        return m_Puzzles[x][y];
    }

    Puzzle Board::GetPuzzle(uint32_t index) const {
        ASSERT(index < m_Width * m_Height, "Invalid puzzle position!")

        return m_Puzzles[index % m_Height][index / m_Width];
    }

    void Board::SetPuzzle(uint32_t x, uint32_t y, uint32_t val) {
        ASSERT(x < m_Width && y < m_Height, "Invalid puzzle position!")

        m_Puzzles[y][x] = val;
    }

    void Board::SetPuzzle(uint32_t index, uint32_t val) {
        ASSERT(index < m_Width * m_Height, "Invalid puzzle position!")

        m_Puzzles[index / m_Width][index % m_Height] = val;
    }

    bool Board::CanMove(MoveDirection direction) const {
        auto [x, y] = GetEmptyPuzzlePosition();

        switch (direction) {
            case MoveDirection::UP: return y > 0;
            case MoveDirection::DOWN: return y < m_Height - 1;
            case MoveDirection::LEFT: return x > 0;
            case MoveDirection::RIGHT: return x < m_Width - 1;
        }

        return false;
    }

    void Board::Move(MoveDirection direction) {
        ASSERT(CanMove(direction), "Can't move in this direction {}, empty puzzle position: {}, {}",
            direction, GetEmptyPuzzlePosition().first, GetEmptyPuzzlePosition().second)

        auto [x, y] = GetEmptyPuzzlePosition();

        int dx = 0, dy = 0;

        switch (direction) {
            case MoveDirection::UP: dy = -1; break;
            case MoveDirection::DOWN: dy = 1; break;
            case MoveDirection::LEFT: dx = -1; break;
            case MoveDirection::RIGHT: dx = 1; break;
        }

        m_Puzzles[y][x] = m_Puzzles[y + dy][x + dx];
        m_Puzzles[y + dy][x + dx] = 0;
    }

    void Board::LogDisplay() const {
        std::stringstream ss;

        FOR_EACH_PUZZLE {
            ss << m_Puzzles[x][y].GetValue() << " ";
                if (y == m_Height - 1) {
                    ss << "\n";
            }
        }

        APP_INFO("Board:\n{0}", ss.str());
    }

    bool Board::IsSolved() const {
        // Solved state e.g. [4x4]
        // 1 2 3 4
        // 5 6 7 8
        // 9 10 11 12
        // 13 14 15 0

        for (uint32_t i = 0; i < m_Width * m_Height - 1; ++i) {
            if (m_Puzzles[i / m_Width][i % m_Height].GetValue() != i + 1)
                return false;
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

        APP_ERROR("Invalid move direction!");

        return MoveDirection::DOWN;
    }

    bool Board::operator==(const Board &other) const {
        if (m_Width != other.GetWidth() || m_Height != other.GetHeight()) {
            return false;
        }

        FOR_EACH_PUZZLE {
            if (m_Puzzles[x][y].GetValue() != other.GetPuzzle(x, y).GetValue())
                return false;
        }

        return true;
    }
}
