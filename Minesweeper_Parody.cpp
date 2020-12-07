#include "minesweeper_parody_lib.h"
#include <iostream>

char * createBoard(std::size_t xdim, std::size_t ydim){
 
    char * new_board {new char[xdim*ydim]{0}};
    
    return new_board;
    
}

//Helper Function that checks the block selected and all the adjacent blocks around it
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


//Calculates if a "mine" is around the block or in an adjacent block
void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
    int index{0};
    for (index = 0; index < xdim*ydim; index++){
        computeNeighbors(board, xdim, ydim, index%xdim, index/xdim);
    }
    return;
}
    
//Hides all the characters of the board using the hiddenbit() function.
void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
    int index = 0;
    for (index = 0; index < xdim*ydim ; index++){
        board[index] = board[index] | hiddenBit();
    }
}
//deletes the board when finished.
void cleanBoard(char * board){
    delete[] board;
    board = nullptr;
}
//Prints to the board depending on what the user selects by using the different bit functions given.
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

//reveals the block chosen by the user.
//if block containing 9 is revealed, game is lost immediately.
//if block contains 1-8 by computing neighbors, just this block alone is revealed.
//if block is Marked, it outputs "Block is already Marked".
//if block is already revealed, nothing happens
//if the block contains 0 which means no neighbours around it is a "mine", then it reveals the adjacent blocks as well that do not contain a "mine" or is marked.
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

//Mark function marks the block chosen by the user.
//The board prints a "M" to indicate this block is marked
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

//Function checks to see if the game is won depending on the values marked or remaining on the board. 
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    unsigned long index = xdim*ydim -1;
    
    for (index = 0; index < xdim*ydim; index++){
        if(((board[index] & valueMask()) != 9) && ((board[index] & hiddenBit()) != 0) ){
            return false;
        }
    }
    return true;
}
    
