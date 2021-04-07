#include "doctest.h" 
#include "Direction.hpp"
#include "Board.hpp"
#include <iostream>

using namespace std;
using namespace ariel;


TEST_CASE("good input - horizontal message")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "bla");
    CHECK(board.read(0, 0, Direction::Horizontal, 3) == "bla");
}


TEST_CASE("good input - vertical message")
{
    Board board;
    board.post(0, 0, Direction::Vertical, "vertical bla");
    CHECK(board.read(0, 0, Direction::Vertical, 12) == "vertical bla");
}

TEST_CASE("horizontal post overwrites part of a vertical message - T form")
{
    Board board;
    board.post(0, 0, Direction::Vertical, "dad");
    board.post(0, 0, Direction::Horizontal, "bard");
    CHECK(board.read(0, 0, Direction::Vertical, 3) == "bad");
    CHECK(board.read(0, 0, Direction::Horizontal, 4) == "bard");
}

TEST_CASE("horizontal post overwrites part of a vertical message - + form")
{
    Board board;
    board.post(10, 10, Direction::Horizontal, "supercalifragilisticexpialidocious"); // char len = 34
    board.post(9, 15, Direction::Vertical, "excaliber");
    CHECK(board.read(10, 10, Direction::Horizontal, 34) == "supexcalifragilisticexpialidocious");
    CHECK(board.read(9, 15, Direction::Vertical, 9) == "excaliber");
}

TEST_CASE("vertical post overwrites part of a horizontal message - T form")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "bard");    
    board.post(0, 0, Direction::Vertical, "caduceus");
    CHECK(board.read(0, 0, Direction::Horizontal, 4) == "card");
    CHECK(board.read(0, 0, Direction::Vertical, 8) == "caduceus");
}

TEST_CASE("vertical post overwrites part of a horizontal message - + form")
{
    Board board;
    board.post(10, 10, Direction::Horizontal, "beholder");
    board.post(8, 14, Direction::Vertical, "boomerang");
    CHECK(board.read(10, 10, Direction::Horizontal, 8) == "behooder");
    CHECK(board.read(8, 14, Direction::Vertical, 9) == "boomerang");
}

TEST_CASE("using an empty string input to try and overide existing message - nothing changed")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "blue eyes white dragon");
    board.post(0, 0, Direction::Vertical, "");
    CHECK(board.read(0, 0, Direction::Horizontal, 22) == "blue eyes white dragon");
}

TEST_CASE("read with size 0 chars returns an empty string")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "Sonata Arctica");
    CHECK(board.read(0, 0, Direction::Horizontal, 0) == "");
}

TEST_CASE("reading more then string size will return string + _____")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "test");
    CHECK(board.read(0, 0, Direction::Horizontal, 7) == "test___");
}

TEST_CASE("checks to see that ' ' is placed horizontally on the board")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, " ");
    CHECK(board.read(0, 0, Direction::Horizontal, 2) == " _");
}

TEST_CASE("checks to see that ' ' is placed vertically on the board")
{
    Board board;
    board.post(0, 0, Direction::Vertical, " ");
    CHECK(board.read(0, 0, Direction::Vertical, 2) == " _");
}

TEST_CASE("properly read part of vertical message")
{
    Board board;
    board.post(0, 0, Direction::Vertical, "big bumbling baboon");
    CHECK(board.read(0, 5, Direction::Vertical, 8) == "bumbling");
}

TEST_CASE("properly read part of a horizontal message")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "a meh string");
    CHECK(board.read(0, 3, Direction::Horizontal, 3) == "meh");    
}

TEST_CASE("vertical posts - short post partialy & properly overiders original post")
{
    Board board;
    board.post(0, 0, Direction::Vertical, "hamburger");
    board.post(0, 0, Direction::Vertical, "pizza");
    CHECK(board.read(0, 0, Direction::Vertical, 9) == "pizzarger");
}

TEST_CASE("horizontal posts - short post partialy & properly overiders original post")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "woodpecker");
    board.post(0, 0, Direction::Horizontal, "berserker");
    CHECK(board.read(0, 0, Direction::Horizontal, 9) == "berserkerr");
}

TEST_CASE("vertical posts - long post completely overiders original post")
{
    Board board;
    board.post(0, 0, Direction::Vertical, "pizza");
    board.post(0, 0, Direction::Vertical, "hamburger");
    CHECK(board.read(0, 0, Direction::Vertical, 9) == "hamburger");
}

TEST_CASE("horizontal posts - long post completely overiders original post")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "berserker");
    board.post(0, 0, Direction::Horizontal, "woodpecker");
    CHECK(board.read(0, 0, Direction::Horizontal, 9) == "woodpecker");
}

TEST_CASE("reading horizontally from an empty board should return \"____\"")
{
     Board board;
     CHECK(board.read(0, 0, Direction::Horizontal, 5) == "_____");
}

TEST_CASE("reading vertically from an empty board should return \"____\"")
{
     Board board;
     CHECK(board.read(0, 0, Direction::Vertical, 5) == "_____");
}

TEST_CASE("Checks that \\n is read as a char an not a new line horizontally")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "no \n new line");
    CHECK(board.read(0, 0, Direction::Horizontal, 13) == "no \n new line");
}

TEST_CASE("Checks that \\n is read as a char an not a new line vertically")
{
    Board board;
    board.post(0, 0, Direction::Vertical, "no \n new line");
    CHECK(board.read(0, 0, Direction::Vertical, 13) == "no \\n new line");
}

TEST_CASE("Checks that \\t is read as a char an not a tabbed line vertically")
{
    Board board;
    board.post(0, 0, Direction::Vertical, "no \t tabbed line");
    CHECK(board.read(0, 0, Direction::Vertical, 16) == "no \\t tabbed line");
}

TEST_CASE("Checks that \\t is read as a char an not a tabbed line horizontally")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "no \t tabbed line");
    CHECK(board.read(0, 0, Direction::Horizontal, 16) == "no \\t tabbed line");
}

