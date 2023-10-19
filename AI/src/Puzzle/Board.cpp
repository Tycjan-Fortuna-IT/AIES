#include "pch.hpp"
#include "Board.hpp"

#include <iostream>

#include "Engine/Core/Debug/Logger.hpp"

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
                return { x, y };
        }

        APP_CRITICAL("There is no empty puzzle! Board is not valid!");

        return { 0, 0 };
    }

    Puzzle Board::GetPuzzle(uint32_t x, uint32_t y) const {
        ASSERT(x < m_Width && y < m_Height, "Invalid puzzle position!")

        return m_Puzzles[x][y];
    }

    void Board::SetPuzzle(uint32_t x, uint32_t y, uint32_t val) {
        ASSERT(x < m_Width && y < m_Height, "Invalid puzzle position!")

            m_Puzzles[x][y] = val;
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

        m_Puzzles[x][y] = m_Puzzles[x + dx][y + dy];
        m_Puzzles[x + dx][y + dy] = 0;
    }

    void Board::LogDisplay() const {
        std::stringstream ss;

        for (uint32_t y = 0; y < m_Height; ++y) {
            std::string row;

            for (uint32_t x = 0; x < m_Width; ++x) {
                row += std::to_string(m_Puzzles[x][y].GetValue()) + " ";
            }

            ss << row << "\n";
        }

        APP_INFO("Board:\n{0}", ss.str());
    }

    bool Board::IsSolved() const {
        // Solved state e.g. [4x4]
        // 1 2 3 4
        // 5 6 7 8
        // 9 10 11 12
        // 13 14 15 0

        FOR_EACH_PUZZLE{
            if (
                m_Puzzles[x][y].GetValue() != 0 &&
                (
                    m_Puzzles[x][y].GetValue() != y * m_Width + x + 1 ||
                    (x == m_Width - 1 && y == m_Height - 1)
                )
            ) {
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

        APP_ERROR("Invalid move direction!");

        return MoveDirection::DOWN;
    }

    bool Board::operator==(const Board& other) const {
        if (m_Width != other.GetWidth() || m_Height != other.GetHeight()) {
            return false;
        }

        FOR_EACH_PUZZLE{
            if (m_Puzzles[x][y].GetValue() != other.GetPuzzle(x, y).GetValue())
                return false;
        }

        return true;
    }
}
