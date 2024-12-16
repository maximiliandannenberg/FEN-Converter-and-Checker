#ifndef FEN_HPP
#define FEN_HPP
#include <string>
#include <vector>

class FEN_Games{
    

    private:
    std::vector<char> FEN;
    bool FEN_broken;
    bool Playerturn;   //which color goes next black = false, white = true
    std::vector<char> CastlingRights;
    int halfmoves = 0;
    int Turns = 1;


    bool setValidityPrivate(bool broken);
    std::vector<char> SetCalculatedFENPrivate(std::vector<char> FENvalue);
    bool setPlayerTurnPrivate(bool playerturn);
    

    public:


    FEN_Games(){};

    bool setValidity(bool broken);
    bool CheckisValid() const { return FEN_broken; }

    std::vector<char> SetCalculatedFEN(std::vector<char> FENvalue);
    std::vector<char> GetFEN() { return FEN; }

    bool setPlayerTurn(bool playerTurn);
    bool getPlayerTurn() { return Playerturn; }

};

FEN_Games CreateFEN(std::string FEN);

std::vector<char> FEN_converter(std::string FEN);

bool FEN_Check_Piece_Count(std::vector<char> FEN_converted);

int FigureOutPlayerTurn(std::string FEN, int FENStartOfRules);

void board(std::vector<char> FEN_converted);

char** boardinitiliazer(int rows, int cols, FEN_Games game);

void printboard(char** myboard, int rows, int cols);

void deletemyboard(char** myboard, int rows);



#endif
