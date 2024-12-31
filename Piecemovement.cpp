#include <iostream>
#include "Piecemovement.hpp"
#include "FEN.hpp"





     std::string WhiteCheckPawnMoves(char** myboard, int i, int j){
        std::string moves;
        if(myboard[i-1][j] == '0'){
            moves = std::to_string(i-1) + std::to_string(j);
            //std::cout << "\n\n\n" << "This is a possible pawn move: " << moves;
            return moves;
        }

        return 0;

     }


    std::string BlackCheckPawnMoves(char** myboard, int i, int j){



        return 0;

      }

std::vector<std::string>checkmoves(char** myboard, FEN_Games game){

    // std::string WhiteCheckedPawnMoves = CheckPawnMoves(myboard);
    
    std::vector<std::string> broken = {"broken"};
    std::vector<std::string> moves;
// if player's turn is white then only check for white pieces
    if (game.getPlayerTurn() == 1){
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if (myboard[i][j] == 'P'){
                    std::string WhiteCheckedPawnMoves = WhiteCheckPawnMoves(myboard, i, j);
                    moves.push_back(WhiteCheckedPawnMoves);                 
                }
            }
        }
    }
    //If the players turn is 0, (black) then only check for black pieces.
    if (game.getPlayerTurn() == 0){
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if (myboard[i][j] == 'p'){
                    std::string BlackCheckedPawnMoves = BlackCheckPawnMoves(myboard, i, j);                
                        moves.push_back(BlackCheckedPawnMoves);
                    }
                }
            }
        }


    return moves;

}


// // std::cout << "enter coordinates of what you want to move: " << '\n';
// // int findrow;
// // int findcol;
// // std::cin>> findrow, findcol;

// // int gotorow;
// // int gotocol;
// // std::cout << "enter coordinates of where you want to move it: " << '\n';
// // std::cin>> gotorow, gotocol;


// // if(myboard[findrow][findcol] == 'P'){
// //     if(myboard[findrow + 1][findcol] == myboard[gotorow][gotocol]){

// //         myboard[gotorow][gotocol] = 'P';
// //         myboard[findrow][findcol] = '0';
// //     }
// // //    myboard[findrow][findcol] myboard[gotorow][gotocol]
// // }






// // //     int findrow, findcol;
// // // std::cout << "select what number you want to get, insert first the row, then the column." << "\n";

// // // std::cin >> findrow >> findcol;
// // // std::cout << myboard[fin drow][findcol];


// std::cout << "\n" << FEN_checked_pieces;

