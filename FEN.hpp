#ifndef FEN_HPP
#define FEN_HPP
#include <string>
#include <vector>

class FEN_Games{
    

    private:
    std::vector<char> FEN;
    bool FEN_broken;
    bool Playerturn;   //which color goes next black = false, white = true
    std::vector<char> Castling_Rights; 
    int halfmoves = 0;
    int Turns = 1;
    std::vector<char> En_Passant;


    bool setValidityPrivate(bool broken);
    std::vector<char> SetCalculatedFENPrivate(std::vector<char> FENvalue);
    bool setPlayerTurnPrivate(bool playerturn);
    std::vector<char> setCastlingRightsPrivate(std::vector<char> CastlingRights);
    std::vector<char> setEnPassantPrivate(std::vector<char> EnPassant);

    public:


    FEN_Games(){};

    bool setValidity(bool broken);
    bool CheckisValid() const { return FEN_broken; }

    std::vector<char> SetCalculatedFEN(std::vector<char> FENvalue);
    std::vector<char> GetFEN() { return FEN; }

    bool setPlayerTurn(bool playerTurn);
    bool getPlayerTurn() { return Playerturn; }

    std::vector<char> setCastlingRights(std::vector<char> CastlingRights);
    std::vector<char> getCastlingRights() { return Castling_Rights; }

    std::vector<char> setEnPassant(std::vector<char> EnPassant);
    std::vector<char> getEnPassant() { return En_Passant; }
};

FEN_Games CreateFEN(std::string FEN);

std::vector<char> FEN_converter(std::string FEN);

bool FEN_Check_Piece_Count(std::vector<char> FEN_converted);

int FigureOutPlayerTurn(std::string FEN, int FENStartOfRules);

std::vector<char>FigureOutCastlingRights(std::string FEN, int FENStartOfRules);

std::vector<char>FigureOutEnPassant(std::string FEN, int *FENStartOfRules);

int FigureOutTheNumber(std::string FEN, int *FENStartOfRulesPointer, bool *brokenPointer);

void board(std::vector<char> FEN_converted);

char** boardinitiliazer(int rows, int cols, FEN_Games game);

void printboard(char** myboard, int rows, int cols);

void deletemyboard(char** myboard, int rows);



#endif
