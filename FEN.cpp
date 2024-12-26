#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include "FEN.hpp"


//sample FENs to use: 8/8/8/4p1K1/2k1P3/8/8/8 b - - 0 1
//A broken FEN with an extra slash: 8//8/8/4p1K1/2k1P3/8/8/8
//Fen broken at the start 8/g/8/4p1K1/2k1P3/8/8/8


FEN_Games CreateFEN(std::string FEN){

    FEN_Games game;

    std::vector<char> FENvalue;
    bool broken = 0;
    int slashes = 0;
    char AllowedBoardPieces[14] = {'k','K','r','R','n','N','p','P','b','B','0','q','Q'};
    char AllowedCharactersInFEN[22] = {'k','K','r','R','n','N','p','P','b','B','0','q','Q','0','1','2','3','4','5','6','7','8'};

    //we are counting the spaces after the first FEN string.
    //The amount of spaces = the type of chess information (PlayerTurn, castlingrights)
    int FENStartOfRules = 0; //this will keep track when the FEN string is finished with the position. So we can run another for loop for game rules starting were game rules are in the FEN.
    for (int i = 0; i < FEN.length(); i++){
             //checks if FEN ends exactly at 64, this marks the end of the displayed board
             //and shows that everything has been properly written.
            if(FEN[i] == ' ' && FENvalue.size() == 64 && slashes == 7){
                FENStartOfRules = i;
                break;
            }
            //checks if each row has exactly 8 spaces
            if(FEN[i] == '/' && FENvalue.size() % 8 != 0){
                std::cout << "Row is not exactly 8 \n";
                broken = 1;
                break;
            } 
            //counts slashes in FEN to make not too many
            if(FEN[i] == '/'){
                slashes++;
            }
            if(slashes > 7){
                std::cout << "Too many slashes \n";
                broken = 1;
                break;
            }
            if(FENvalue.size() > 64){
                broken = 1;
                break;
            }
            if (FEN[i]>= '0' && FEN[i] <= '9'){
            int repeat = FEN[i] - '0';
                 /* basically FEN[i] uses acsii values meaning that if you have the value of
                 3 it will be like 51 since digits 0 - 9 have ascii values of 48 to 57. 
                we subtract ascii value of '0' which is 48 so we 51 - 48 which is 3. 
                 which is the int value we want */
                for (int j = 0; j < repeat; j++){
                    if(FENvalue.size() < 64){
                        FENvalue.push_back('0');
                        } else {
                            broken = 1;
                            break;
                        }
                    }
                }
            //checks for chars which aren't allowed in the FENs    
            bool allowedcharacters = false;
            for(int y = 0; y < 22; y++){
                if(FEN[i] == AllowedCharactersInFEN[y] || FEN[i] == '/' || FEN[i] == '0'){
                    allowedcharacters = true;
                    break;
                }
            }
            if (!allowedcharacters){ 
                    broken = 1;
                    break;
            }
            //check for chars which aren't allowed to be displayed on the board

            for(int y = 0; y < 14; y++){
                if(FEN[i] == AllowedBoardPieces[y]){
                    FENvalue.push_back(FEN[i]);
                    break;
                }
            } 
                if(broken == 1){
                    break;
                }
        }
    
        if (broken == false){
        bool FEN_checked_pieces = FEN_Check_Piece_Count(FENvalue);
        if(FEN_checked_pieces == true){
            broken = 1;
        }
        }

//   This code will be used to figure out the player turn of the game.
    bool playerTurn = 0;
    int TurnNUM = FigureOutPlayerTurn(FEN, FENStartOfRules);
    if (TurnNUM == 1){
        playerTurn = 1;
    }
    if (TurnNUM == 2){
        broken = true;
    }
    //   This code will be used to figure out the castling rights of the game.
    std::vector<char> castlingrights = FigureOutCastlingRights(FEN, FENStartOfRules);
        if (castlingrights[0] == '0'){
            broken = true;
        }

    //This changes the point where we look at the FEN for the game rules.
    FENStartOfRules = FENStartOfRules + castlingrights.size() + 4;
    //This code will be used to figure out the en passant square of the game.   
    std::vector<char> EnPassant = FigureOutEnPassant(FEN, &FENStartOfRules);
        if (EnPassant[0] == '0'){
            broken = true;
        }
 


    int HalfTurns = FigureOutTheNumber(FEN, &FENStartOfRules, &broken);

 std::cout << "\n\n\n" << "Here are the halfturns: " << HalfTurns << '\n';

    int FullMoves = FigureOutTheNumber(FEN, &FENStartOfRules, &broken);
        if (FullMoves > 50){
            broken = true;
        }
 std::cout << "Here are the HalfMoves: " << FullMoves << "\n\n\n";

   if (broken == true){
        bool ItIsBroken = true;
        game.setValidity(ItIsBroken);
        return game;
   }else{
        bool ItIsBroken = false;
        game.setValidity(ItIsBroken);
        game.SetCalculatedFEN(FENvalue);
        game.setPlayerTurn(playerTurn);
        game.setCastlingRights(castlingrights);
        game.setEnPassant(EnPassant);
    return game;
   }
    
}


int FigureOutPlayerTurn(std::string FEN, int FENStartOfRules){
    int i = FENStartOfRules;
   if (FEN[i+1] == 'b'){
        return 0;
    } if (FEN[i+1] == 'w'){
        return 1;
    } else 
    {
        return 2;
    }
    //true (1) = white, false (2) = black
}
//Figures out the castling rights
std::vector<char>FigureOutCastlingRights(std::string FEN, int FENStartOfRules){
    int i = FENStartOfRules;
    std::unordered_map<char, int> CastlingRightsMap = {{'K', 0}, {'Q', 0}, {'k', 0}, {'q', 0}};
    std::vector<char> CastlingRights;
    if (FEN[i+2] != ' '){
        return CastlingRights = {0};
    }
    if (FEN[i+3] == '-'){
        return CastlingRights = {'-'};
    }
   for (int x = 0; x < 4; x++){
        char charadded = FEN[i+3+x];
        if (charadded == ' '){
            break;
        }
        if(CastlingRightsMap.find(charadded) != CastlingRightsMap.end()){
            CastlingRightsMap[charadded]++;
            if (CastlingRightsMap[charadded] > 1){
                return CastlingRights = {'0'};
            } 
                CastlingRights.push_back(charadded);
        }
        else if (charadded != ' '){
        return CastlingRights = {'0'};
    }


    }
    return CastlingRights;
}
//Figures out if and what the enpassant move is
std::vector<char>FigureOutEnPassant(std::string FEN, int *FENStartOfRulesPointer){
    int i = *FENStartOfRulesPointer;
    std::vector<char> EnPassant;
    if (FEN[i] == '-'){
        *FENStartOfRulesPointer = *FENStartOfRulesPointer + 1;
        return EnPassant = {'-'};
    }

    if (FEN[i] != '-'){
        std::unordered_map<char, int> PossibleEnpassantChar = {{'a', 0}, {'b', 0}, {'c', 0}, {'d', 0}, {'e', 0}, {'f', 0}, {'g', 0}, {'h', 0}};
        std::unordered_map<char, int> PossibleEnpassantNum = {{'1', 0}, {'2', 0}, {'3', 0}, {'4', 0}, {'5', 0}, {'6', 0}, {'7', 0}, {'8', 0}};
        if(PossibleEnpassantChar.find(FEN[i]) != PossibleEnpassantChar.end()){
            EnPassant.push_back(FEN[i]);
        } else {
            return EnPassant = {'0'};
        }
        if(PossibleEnpassantNum.find(FEN[i+1]) != PossibleEnpassantNum.end()){
            EnPassant.push_back(FEN[i+1]);
            *FENStartOfRulesPointer = *FENStartOfRulesPointer + 2;
            return EnPassant;
        } 
        //this seems redundant but it is to make sure that the first char is a letter and the second char is a number.
        else {
            return EnPassant = {'0'};
        }
    }
    else {
        return EnPassant = {'0'};
    }
}
//Figures out what the HalfMoves is
int FigureOutTheNumber(std::string FEN, int *FENStartOfRulesPointer, bool *brokenPointer){
    int PosInFEN = *FENStartOfRulesPointer;
    int HalfMovesTotal;
    if (FEN[PosInFEN] == ' '){
        PosInFEN++;
        *FENStartOfRulesPointer = PosInFEN;
    } else {
        *brokenPointer = true;
        return -1;
    }
    int HalfMoveFirstDigit = FEN[PosInFEN] - '0';
    if (HalfMoveFirstDigit >= 0 || HalfMoveFirstDigit <= 9){
        PosInFEN++;
        *FENStartOfRulesPointer = PosInFEN;
        if (FEN[PosInFEN] == ' '){
            HalfMovesTotal = HalfMoveFirstDigit;
            return HalfMovesTotal;
        }
        int HalfMoveSecondDigit = FEN[PosInFEN] - '0';
        if (HalfMoveSecondDigit >= 0 && HalfMoveSecondDigit <= 9 ){
            PosInFEN++;
            *FENStartOfRulesPointer = PosInFEN;
            HalfMovesTotal = (HalfMoveFirstDigit * 10) + HalfMoveSecondDigit;
            return HalfMovesTotal;
        }
    } 
            *brokenPointer = true;
            return -1;
}

//Checks to see if piece counts make sense. 1 king, no more than 8 pawns, etc.
bool FEN_Check_Piece_Count(std::vector<char> FENvalue) {
bool broken = false;
int TotalWhitePieces = 0;
int TotalBlackPieces = 0;
int wKing = 0, bKing = 0, wKnights = 0, bKnights = 0, wRooks = 0, bRooks = 0, wPawns = 0, bPawns = 0, wBishops = 0, bBishops = 0, wQueen = 0, bQueen = 0;

    for (int i = 0; i < 64; i++) {
        if(FENvalue[i] == 'k') {
            TotalBlackPieces++;
            bKing++;
            if(bKing > 1){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'K') {
            wKing++;
            TotalWhitePieces++;
            if(wKing > 1){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'n') {
            bKnights++;
            TotalBlackPieces++;
            if(bKnights > 10){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'N') {
            wKnights++;
            TotalWhitePieces++;
            if(wKnights > 10){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'b') {
            bBishops++;
            TotalBlackPieces++;
            if(bBishops > 10){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'B') {
            wBishops++;
            TotalWhitePieces++;
            if(wBishops > 10){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'r') {
            bRooks++;
            TotalBlackPieces++;
            if(bRooks > 10){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'R') {
            wRooks++;
            TotalWhitePieces++;
            if(wRooks > 10){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'p') {
            bPawns++;
            TotalBlackPieces++;
            if(bPawns > 8){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'P') {
            wPawns++;
            TotalWhitePieces++;
            if(bPawns > 8){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'q') {
            bQueen++;
            TotalBlackPieces++;
            if(bQueen > 8){
                broken = true;
            }
        } 
        if(FENvalue[i] == 'Q') {
            wQueen++;
            TotalWhitePieces++;
            if (wQueen > 8){
                broken = true;
            }
        } 
    if (TotalWhitePieces > 16 || TotalBlackPieces > 16){
        broken = true;
    }

    }
    
    return broken;
}

bool FEN_Games::setValidity(bool broken)
{
  return setValidityPrivate(broken);
}
bool FEN_Games::setValidityPrivate(bool broken)
{
    if (broken == false){
        return FEN_broken = false;
    }
    else
    {
        return FEN_broken = true;
    }
}

std::vector<char> FEN_Games::SetCalculatedFEN(std::vector<char> FENvalue)
{
    return SetCalculatedFENPrivate(FENvalue);
}

std::vector<char> FEN_Games::SetCalculatedFENPrivate(std::vector<char> FENvalue)
{
    return FEN = FENvalue;
}


bool FEN_Games::setPlayerTurn(bool playerTurn)
{
    return setPlayerTurnPrivate(playerTurn);
}
bool FEN_Games::setPlayerTurnPrivate(bool playerTurn)
{
    return Playerturn = playerTurn;
}

std::vector<char> FEN_Games::setCastlingRights(std::vector<char> CastlingRights)
{
    return setCastlingRightsPrivate(CastlingRights);
}
std::vector<char> FEN_Games::setCastlingRightsPrivate(std::vector<char> CastlingRights)
{
    return Castling_Rights = CastlingRights;
}

std::vector<char> FEN_Games::setEnPassant(std::vector<char> EnPassant){
    return setEnPassantPrivate(EnPassant);
}
std::vector<char> FEN_Games::setEnPassantPrivate(std::vector<char> EnPassant){
    return En_Passant = EnPassant;
}

char** boardinitiliazer(int rows, int cols, FEN_Games game){


    std::vector<char> FENstring;
    FENstring = game.GetFEN();

    char** myboard = new char*[rows];

    for(int i = 0; i < rows; i++ ){
        myboard[i] = new char[cols]; 
        //at each memory address, which is a pointer to an array, you assign the length of the array.
    }


        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                int position = (i * 8) + j;
                myboard[i][j] = FENstring[position]; //error here
            }
        }
    
    return myboard;

}

 void printboard(char** myboard, int rows, int cols){
    for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                std::cout << myboard[i][j] << " ";
            }
            std::cout << '\n';
        }
    }

void deletemyboard(char** myboard, int rows){
    for(int i = 0; i < rows; i++ ){
        delete[] myboard[i];
    }
    delete[] myboard;
    myboard = nullptr;
}





    // std::cout << "\n\n\n\n" << "TEST block" << "\n";
    // std::cout << FEN[PosInFEN];
    // std::cout << "\n\n\n\n";



 