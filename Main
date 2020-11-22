# Geesespotter

#include "geesespotter_lib.h"
#include <iostream>

char * createBoard(std::size_t xdim, std::size_t ydim){
 
    char * new_board {new char[xdim*ydim]{0}};
    
    return new_board;
    
}

//Helper function for compute neighbours
//Double nested for loops iterates through the entire board looking for fields that contain the value '9' which is marked as the geese.
//It then looks at the adjacent fields to the '9' and assigns a value to the field indicating if there is a goose near this field. 
void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    int i{0};
    int j{0};
    int counter{0};
    if ((board[yloc*xdim + xloc] & valueMask()) == 9){
        return ;
    }
    for (i=-1; i<2; i++){
        for (j=-1; j<2; j++){
            if (((yloc+j)>=0) && ((yloc+j)< ydim) && ((xloc + i) >= 0) && ((xloc + i) < xdim)){
                if(((board[(yloc+j)*xdim +(xloc+i)]) & valueMask()) == 0x09){
                    counter++;
                }
                    
            }
        }
    }
    board[yloc*xdim + xloc] = board[yloc*xdim + xloc] + counter;
}


//Compute Neighbours returns the number of geese that are adjacent to a square if it does not contain a goose. 
//Helper function above is called in this program which iterates the entire board.
void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
    int index{0};
    for (index = 0; index < xdim*ydim; index++){
        computeNeighbors(board, xdim, ydim, index%xdim, index/xdim);
    }
    return;
}
    
    
//Function hides the entire board regardless of it's value by masking it with 'hiddenbit'.
void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
    int index = 0;
    for (index = 0; index < xdim*ydim ; index++){
        board[index] = board[index] | hiddenBit();
    }
}

//cleanboard simply deletes the board array then sets it to null to avoid any dangling or wild pointer as well as avoid memory leaks.
void cleanBoard(char * board){
    delete[] board;
    board = nullptr;
}

//Printboard does most of the work. On starting, it outputs a board of size nxn with all fields being first output as "*".
//If the Mark function is called through the game, the field now outputs a "M" instead of the asterisk. 
//It also switches back to asterisk, if the field is unmarked (i.e the mark function is called on the same field.)
void printBoard(char * board, std::size_t xdim, std::size_t ydim){
    int index{0};
    for (int i = 0; i < ydim ; i++){
        for (int j = 0; j < xdim ; j++){
            if ((board[index] & markedBit()) == markedBit() ){
                std::cout <<'M' ;
            }
            else if((board[index] & hiddenBit()) == hiddenBit() ){
                    std::cout<<'*';
            }
            else{
                std::cout<<(board[index] & valueMask()) ;
            }
            index++;
        
    }
        std::cout<<'\n';
  }
    
}

//reveal when called outputs the value the field contains
//When the field is chosen to be revealed, this function removed the hiddenBit() or markedBit() and outputs the value the field has which is based on compute //neighbours and the random generated geese.
int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    unsigned long index{0};
    index = yloc*xdim + xloc;
        if ((board[index] & markedBit()) == markedBit()){
            return 1;
        }
        else if ((board[index]  & (hiddenBit()) ) == 0x00){
            return 2;
        }
        else if ((board[index] & valueMask()) ==  0x9){
            board[index] = board[index] & valueMask();
            return 9;
        }
        else if ((board[index] & valueMask()) ==  0x8){
            board[index] = board[index] & valueMask();
            return 0;
        }
        else if ((board[index] & valueMask()) ==  0x7){
            board[index] = board[index] & valueMask();
            return 0;
        }
        else if ((board[index] & valueMask()) ==  0x6){
            board[index] = board[index] & valueMask();
            return 0;
        }
        else if ((board[index] & valueMask()) ==  0x5){
            board[index] = board[index] & valueMask();
            return 0;
        }
        else if ((board[index] & valueMask()) ==  0x4){
            board[index] = board[index] & valueMask();
            return 0;
        }
        else if ((board[index] & valueMask()) ==  0x3){
            board[index] = board[index] & valueMask();
            return 0;
        }
        else if ((board[index] & valueMask()) ==  0x2){
            board[index] = board[index] & valueMask();
            return 0;
        }
        else if ((board[index] & valueMask()) ==  0x1){
            board[index] = board[index] & valueMask();
            return 0;
        }
        //If the field has a zero value, then the surrounding adjacent fields are also revealed automatically. However, if it contains a '9' it is not revealed.
        //Similarly, if the field is marked it will also not be revealed.
        else if((board[yloc*xdim + xloc] & valueMask()) == 0x00){
            int yloc_tmp = int(yloc);
            int xloc_tmp = int(xloc);
            
            for (int reveal_y{ yloc_tmp - 1}; reveal_y <= (yloc_tmp + 1); reveal_y++){
                for (int reveal_x{xloc_tmp -1}; reveal_x <= (xloc_tmp + 1) ; reveal_x++){
    
                    if ((reveal_x < xdim) && (reveal_y < ydim) && (reveal_x >= 0) && (reveal_y >= 0)){
                        
                        if((board[yloc*xdim + xloc] & markedBit()) == 0 ){
                           
                        board[((yloc+reveal_x)*xdim) + (xloc+reveal_y)] = board[((yloc+reveal_x)*xdim) + (xloc+reveal_y)] & valueMask();
                            
                        }
                    }
                }
            }
        }
    
    
   
    return 0;
    
}

//Mark function has two primary roles; It first can mark a field, which makes it output as "M" and unmarks a field if the function is called on the same field //reverting it back to the hidden state.
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    unsigned long index = yloc*xdim + xloc;
    
        if ((board[index] & markedBit()) == 0x00){
            board[index] = board[index] | markedBit() ;
            return board[index];
        }
        else if ((board[index] & hiddenBit() ) == 0x00){
            return 2;
        }
        else if ((board[index] & markedBit()) == markedBit()){
            board[index] = board[index] & ~(markedBit());
        }
        
    return 0;
}

//Function tests if the game is won depending if all fields with "9" are marked and all the other fields have been revealed.
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    unsigned long index = xdim*ydim -1;
    
    for (index = 0; index < xdim*ydim; index++){
        if(((board[index] & valueMask()) != 9) && ((board[index] & hiddenBit()) != 0) ){
            return false;
        }
    }
    return true;
}
    
