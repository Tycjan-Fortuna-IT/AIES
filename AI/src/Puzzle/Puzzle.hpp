#pragma once

#include <cstdint>

namespace AI {
    class Puzzle final {
    public:

        Puzzle() = default;
        Puzzle(uint32_t val);

        ~Puzzle() = default;

        uint32_t GetValue() const { return m_Value; }
        void SetValue(uint32_t value) { m_Value = value; }

        bool IsEmpty() const { return m_Value == 0; }

        bool operator==(const Puzzle& other) const;
        bool operator!=(const Puzzle& other) const;

    private:

        uint32_t m_Value;
    };
}
