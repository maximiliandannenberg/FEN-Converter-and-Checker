#include <iostream>
#include <vector>
#include <string>
#include <list>
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
    //The amount of spaces = the type of chess information (playerturn, castlingrights)
    int FENposition = 0; //this will keep track when the FEN string is finished with the position. So we can run a for loop for the spaces following.
    for (int i = 0; i < FEN.length(); i++){
             //checks if FEN ends exactly at 64
            if(FEN[i] == ' ' && FENvalue.size() == 64 && slashes == 7){
                std::cout << "perfect! \n";
                FENposition = i;
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
        std::cout << "\n\n\n" << FEN_checked_pieces << "\n";
        if(FEN_checked_pieces == true){
            broken = 1;
        }
        }

        //Checking the game rules after the FEN position creation. (Hope that made sense)
        int SpaceCounter = 0;
        bool playerturn = false; //false = black, true = white
        for(int i = FENposition; i < FEN.length(); i++){
            if(FEN[i] == ' '){
                SpaceCounter++;
                switch(SpaceCounter){
                    case 1:
                        if(FEN[i+1] == 'b'){
                            playerturn = false;
                        }
                        if(FEN[i+1] == 'w')
                        {
                            playerturn = true;
                        }
                        else
                        {
                            broken = true;
                        }
                    break;

                    case 2:
                    //create hashmap of the 4 chars(Not necessary but I want to practice hashmaps), 
                    //if any character shows up more than once then it is broken, if any character besides K,k,Q,q shows up then it is also invalid

                    break;

                    case 3:
                    break;
                    case 4:
                    break;
                    case 5:
                    break;

                }
            
            }

        }


   if (broken == true){
        bool ItIsBroken = true;
        game.setValidity(ItIsBroken);
        game.SetCalculatedFEN(FENvalue);
        return game;
   }else{
        bool ItIsBroken = false;
        game.setValidity(ItIsBroken);
        game.SetCalculatedFEN(FENvalue);
        game.setPlayerTurn(playerturn);
    return game;
   }
    
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

bool FEN_Games::setPlayerTurn(bool playerturn)
{
    return setPlayerTurnPrivate(playerturn);
}

bool FEN_Games::setPlayerTurnPrivate(bool playerturn)
{
    return playerturn;
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









