#include <iostream>
#include <vector>
#include <string>
#include "Functions.hpp"


/*Problems with the program:
States FEN is broken when finished with FENvalue and if we have the additional characters (game characteristics)
-fixed 

New problem
object is out of scope trying to run print function for board when function is out of the while loop.
Create pointer for object to be referenced outside of the while loop?? - solution? 
*/


int main() {


bool CheckFEN = false;
while(CheckFEN == false){

std::string FEN;

std::cout << "please give the FEN to generate the desired board: \n";
std::getline(std::cin, FEN);

FEN_Games game = CreateFEN(FEN);

std::cout << game.FEN_valid << "\n";

std::cout << game.FEN[1];

if(game.FEN_valid == 1){
    std::cout << "invalid FEN, please submit a working one. \n";
    CheckFEN = false;
} else {CheckFEN = true;}

int rows = 8;
int cols = 8;

char** myboard = boardinitiliazer(rows, cols);


    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int position = (i * 8) + j;
            myboard[i][j] = game.FEN[position];
        }
    }

for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            std::cout << myboard[i][j] << " ";
        }
        std::cout << '\n';
    }


}










// std::vector<char> FEN_converted = FEN_converter(FEN);
// // This function takes our fen string and converts it into a vector 
// // This vector has 64 positions each representing each square on the board.





//bool FEN_checked_pieces = FEN_Check_Piece_Count(FEN_converted); 
//checks if their are the correct amount of pieces



// //board(FEN_converted);
// //prints the FEN.

// // std::cout << '\n';
// // std::cout << '\n';
// std::cout << '\n';







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



return 0;

}
 
   