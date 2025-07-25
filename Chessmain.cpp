#include <iostream>
#include <vector>
#include <string>
#include "Piecemovement.hpp"
#include "FEN.hpp"


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


int main() {


        FEN_Games game;

        bool CheckFEN = false;
        while(CheckFEN == false){

            std::string FEN;
            std::cout << "please give the FEN to generate the desired board: \n";
            std::getline(std::cin, FEN);

            game = CreateFEN(FEN);

            if(game.CheckisValid() == 1){
                std::cout << "invalid FEN, please submit a working one. \n";
                CheckFEN = false;
            } 
            else 
            {CheckFEN = true;}

        }



    int rows = 8;
    int cols = 8;
    char** myboard = boardinitiliazer(rows, cols, game);
    printboard(myboard, rows, cols);




    if (game.getPlayerTurn() == 0){
        std::cout << "Black's turn";
    }  else {
        std::cout << "White's turn";
    }
    for(int i = 0; i < game.getCastlingRights().size(); i++){
        std::cout << "\nCastling Rights: " << game.getCastlingRights()[i];
    }
    std::cout << "\nEnPassant rights: " << game.getEnPassant()[0] << game.getEnPassant()[1];
    std::cout << "\nHalf Moves: " << game.getHalfMoves();
    std::cout << "\nFull Moves: " << game.getFullMoves();



   std::vector<char**> FutureBoards = CalculateFutureBoards(myboard, game);



   // std::vector<std::string>CheckMoves = checkmoves(myboard, game);


        std::cout << '\n' << "Legal positions following ";
        if (game.getPlayerTurn() == 0){
            std::cout << "Black";
        } else {
            std::cout << "White";
        }
        std::cout << "'s move: " << '\n';


    if(FutureBoards.empty()){
        std::cout << '\n' << "No more legal moves. Stalemate";
    } else {
        for(char** x : FutureBoards){
            printboard(x, rows, cols);
        }
        std::cout << '\n';

    }
    


    

//set up board
//Check whos turn it is
//Ask player what he wants to move
//check if the move is legal -> Once we know which moves are legal we implement an if statement checking that checks if the board is legal






    


    

   // std::cout << "\n\n\n" << CheckMoves[0] << CheckMoves[1] << CheckMoves[2];

    // myboard = CanEatKing(myboard);

     deletemyboard(myboard, rows);



return 0;

}
 






   
