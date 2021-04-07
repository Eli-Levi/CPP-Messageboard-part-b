#include "Board.hpp"
#include <iostream>
using namespace ariel;

void Board::post(unsigned int row, unsigned int col, const Direction direction, string message)
{
    if (message.empty() || message.length() == 0)
    {
        return;
    }
    if (row < min_x)
    {
        min_x = row;
    }
    if (max_x < row)
    {
        max_x = row;
    }
    if (col < min_y)
    {
        min_y = col;
    }
    if (max_y < col)
    {
        max_y = col;
    }

    string location;
    if (direction == Direction::Horizontal)
    {
        for (size_t char_index = 0;
             char_index < message.size(); char_index++, col++)
        {
            location = to_string(row) + '.' + to_string(col);
            theBoard[location] = message[char_index];
        }
    }
    else
    {
        for (size_t char_index = 0;
             char_index < message.size(); char_index++, row++)
        {
            location = to_string(row) + '.' + to_string(col);
            theBoard[location] = message[char_index];
        }
    }
}

std::string Board::read(unsigned int row, unsigned int col, const Direction direction, unsigned int numOfChars)
{
    string result;
    if (numOfChars == 0)
    {
        return result;
    }

    string location = to_string(row) + '.' + to_string(col);
    for (size_t i = 0; i < numOfChars; i++)
    {
        if (direction == Direction::Vertical)
        {
            if (theBoard[location] == '\0')
            {
                result += '_';
            }
            else
            {
                result += theBoard[location];
            }
            location = to_string(++row) + '.' + to_string(col);
        }
        else
        {
            if (theBoard[location] == '\0')
            {
                result += '_';
            }
            else
            {
                result += theBoard[location];
            }
            location = to_string(row) + '.' + to_string(++col);
        }
    }
    return result;
}

void Board::show()
{
    for (size_t row_counter = min_x; row_counter <= max_x; row_counter++)
    {
        for (size_t col_counter = min_y; col_counter <= max_y; col_counter++)
        {
            string curr_index = to_string(col_counter) + '.' + to_string(row_counter);
            if (theBoard.count(curr_index) == 1)
            {
                cout << theBoard.at(curr_index);
            }
            else
            {
                cout << '_';
            }
        }
        cout << endl;
    }
}
