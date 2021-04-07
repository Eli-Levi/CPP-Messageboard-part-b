#pragma once
#include <string>
#include <unordered_map>
#include "Direction.hpp"
#include <climits>
using ariel::Direction;
using namespace std;

namespace ariel
{
    class Board
    {
        unordered_map<string, char> theBoard;
        unsigned int min_x, max_x, min_y, max_y;
        
        public:
        Board(): min_x(UINT_MAX), max_x(0.0), min_y(UINT_MAX), max_y(0.0){};
        void post(unsigned int row, unsigned int col, Direction direction, string message);

        std::string read(unsigned int row, unsigned int col, Direction direction, unsigned int numOfChars);

        void show();
        // clean up function?
    };

}
