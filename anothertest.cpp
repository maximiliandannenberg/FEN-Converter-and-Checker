#include <iostream>
#include <vector>
#include <string>


class FEN_Games{
    public:
    std::vector <char> FEN;
    bool FEN_valid;
    bool Playerturn = 0;
    std::vector<char> CastlingRights;
    int halfmoves = 0;
    int Turns = 1;

    FEN_Games(std::vector<char> &fen) : FEN(fen){}
};


FEN_Games CreateFEN(std::string FEN){
    std::vector<char> FENvalue;
    int broken = 0;
    int slashes = 0;
    char AllowedBoardPieces[14] = {'k','K','r','R','n','N','p','P','b','B','0','q','Q'};
    char AllowedCharactersInFEN[22] = {'k','K','r','R','n','N','p','P','b','B','0','q','Q','0','1','2','3','4','5','6','7','8'};

    //we are counting the spaces after the first FEN string.
    //The amount of spaces = the type of chess information (playerturn, castlingrights)
    for (int i = 0; i < FEN.length(); i++){
             //checks if FEN ends exactly at 64
            if(FEN[i] == ' ' && FENvalue.size() == 63 && slashes == 7){
                std::cout << "perfect! \n";
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
        
    FEN_Games game(FENvalue);
    return game;
}


int main() {

std::string FEN;

std::cout << "please give the FEN to generate the desired board: \n";
std::getline(std::cin, FEN);

FEN_Games game = CreateFEN(FEN);

std::cout << game.FEN[1];

return 0;

}
