#include "TestingFramework.hpp"
#include "cache/Board.hpp"

TEST_INIT()
{
    TEST_CASE("Check if board was created correctly and can set every puzzle")
    {
        // 1 2
        // 3 4
        // 5 6
        // 7 8
        AI::Board board(2, 4);

        board.SetPuzzle(0, 0, 1);
        board.SetPuzzle(1, 0, 2);
        board.SetPuzzle(0, 1, 3);
        board.SetPuzzle(1, 1, 4);
        board.SetPuzzle(0, 2, 5);
        board.SetPuzzle(1, 2, 6);
        board.SetPuzzle(0, 3, 7);
        board.SetPuzzle(1, 3, 8);

        ASSERT_EQUALS(board.GetPuzzle(0, 0).GetValue(), 1)
        ASSERT_EQUALS(board.GetPuzzle(1, 0).GetValue(), 2)
        ASSERT_EQUALS(board.GetPuzzle(0, 1).GetValue(), 3)
        ASSERT_EQUALS(board.GetPuzzle(1, 1).GetValue(), 4)
        ASSERT_EQUALS(board.GetPuzzle(0, 2).GetValue(), 5)
        ASSERT_EQUALS(board.GetPuzzle(1, 2).GetValue(), 6)
        ASSERT_EQUALS(board.GetPuzzle(0, 3).GetValue(), 7)
        ASSERT_EQUALS(board.GetPuzzle(1, 3).GetValue(), 8)
    }
    TEST_CASE_END()

    TEST_CASE("Board movement test with empty puzzle position check")
    {
        // 1 0
        // 3 4
        // 5 6
        // 7 8
        AI::Board board(2, 4);

        board.SetPuzzle(0, 0, 1);
        board.SetPuzzle(1, 0, 0);
        board.SetPuzzle(0, 1, 3);
        board.SetPuzzle(1, 1, 4);
        board.SetPuzzle(0, 2, 5);
        board.SetPuzzle(1, 2, 6);
        board.SetPuzzle(0, 3, 7);
        board.SetPuzzle(1, 3, 8);

        board.Move(AI::MoveDirection::LEFT);
        ASSERT_EQUALS(board.GetPuzzle(0, 0).GetValue(), 0)

        board.Move(AI::MoveDirection::DOWN);
        ASSERT_EQUALS(board.GetPuzzle(0, 1).GetValue(), 0)

        board.Move(AI::MoveDirection::RIGHT);
        ASSERT_EQUALS(board.GetPuzzle(1, 1).GetValue(), 0)

        board.Move(AI::MoveDirection::UP);
        ASSERT_EQUALS(board.GetPuzzle(1, 0).GetValue(), 0)
    }
    TEST_CASE_END()
}
TEST_END()
