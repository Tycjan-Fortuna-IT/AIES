#pragma once

#include <string>

#include "Board.hpp"

namespace AI {
    class PuzzleSerializer {
    public:

        static void Load(Board*& board, const std::string& path);
    };
}
