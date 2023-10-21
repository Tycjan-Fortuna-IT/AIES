#include "Puzzle.hpp"

namespace AI {

    Puzzle::Puzzle(uint32_t val)
        : m_Value(val) {}

    bool Puzzle::operator==(const Puzzle &other) const {
        return m_Value == other.GetValue();
    }

    bool Puzzle::operator!=(const Puzzle &other) const {
        return m_Value != other.GetValue();
    }
}
