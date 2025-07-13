#ifndef PM_HPP
#define PM_HPP
#include <iostream>
#include "FEN.hpp"

std::vector<std::string> checkmoves(char** myboard, FEN_Games game);

std::vector<char**> CalculateFutureBoards(char** myboard, FEN_Games game);


#endif
