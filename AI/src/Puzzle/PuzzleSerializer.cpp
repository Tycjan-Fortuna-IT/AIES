#include "pch.hpp"
#include "PuzzleSerializer.hpp"

#include <fstream>

#include "GUI/Utils.hpp"

namespace AI {
    void PuzzleSerializer::Load(Board *&board, const std::string &path) {
        std::ifstream file(path);

        uint32_t m_Width, m_Height;

        if (!(file >> m_Width >> m_Height))
            CONSOLE_ERROR("Invalid board file, expected width and height in the first line.");

        if (m_Width <= 0 || m_Height <= 0)
            CONSOLE_ERROR("Invalid board file, width and height must be greater than 0.");

        if (m_Width && m_Height) {
            board = new Board(m_Width, m_Height);

            FOR_EACH_PUZZLE_W_H(m_Width, m_Height) {
                uint32_t tile;

                if (!(file >> tile))
                    CONSOLE_ERROR("Invalid board file, expected {} tiles.", m_Width * m_Height);
                else
                    board->SetPuzzle(y, x, tile);
            }
        }
    }
}
