#include <iostream>
#include <vector>
#include <string>

#include "FEN.hpp"
#include "Piecemovement.hpp"

/* 
Problems with the program:

States FEN is broken when finished with FENvalue and if we have the additional characters (game characteristics)
-fixed 

object is out of scope trying to run print function for board when function is out of the while loop.
Create pointer for object to be referenced outside of the while loop?? - solution? 
-fixed

fix memory leak from 2d array initialization
-fixed

Create new file with piece movement
-done

Implement all the game rules from FEN into game ojbect

segmentation fault due to return value from Piecemovement

*/



//This is a test to see if I am in the new branch

int main() {

        std::vector<char> FENvalue;
        bool broken = 1;
        FEN_Games game(FENvalue, broken);


        bool CheckFEN = false;
        while(CheckFEN == false){

            std::string FEN;
            std::cout << "please give the FEN to generate the desired board: \n";
            std::getline(std::cin, FEN);

            game = CreateFEN(FEN);

            if(game.FEN_valid == 1){
                std::cout << "invalid FEN, please submit a working one. \n";
                CheckFEN = false;
            } else {CheckFEN = true;}
            
        }

    int rows = 8;
    int cols = 8;
    char** myboard = boardinitiliazer(rows, cols, game);
    printboard(myboard, rows, cols);


//set up board
//Check whos turn it is
//Ask player what he wants to move
//check if the move is legal -> Once we know which moves are legal we implement an if statement checking that checks if the board is legal


    myboard = PawnMoves(myboard);

    deletemyboard(myboard, rows, cols);

return 0;

}
 






   
