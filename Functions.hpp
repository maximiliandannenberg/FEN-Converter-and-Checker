#ifndef FEN_HPP
#define FEN_HPP
#include <string>
#include <vector>

class FEN_Games{
    public:
    std::vector <char> FEN;
    bool FEN_valid;
    bool Playerturn = 0;
    std::vector<char> CastlingRights;
    int halfmoves = 0;
    int Turns = 1;

    FEN_Games(std::vector<char> &fen, bool &broke) : FEN(fen), FEN_valid(broke){}
};

FEN_Games CreateFEN(std::string FEN);

std::vector<char> FEN_converter(std::string FEN);

bool FEN_Check_Piece_Count(std::vector<char> FEN_converted);

void board(std::vector<char> FEN_converted);

char** boardinitiliazer(int rows, int cols, FEN_Games game);

void printboard(char** myboard, int rows, int cols);

void deletemyboard(char** myboard, int rows, int cols);



#endif
