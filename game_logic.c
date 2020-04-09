//
// Created by Eoghan on 29/03/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "input_output.h"

struct piece*push(enum color col, struct piece*top){
    struct piece * curr=top;
    top = ( piece *)malloc(sizeof(piece));
    top->p_color=col;
    top->next=curr;
    return top;
}
struct piece*pop(struct piece*top){
    struct piece*curr=top;
    if(curr!=NULL){
        top = curr->next;
        free(curr);
    }
    return top;
}

bool checkValid(square board[BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo){
    if (board[rowNo][colNo].type == VALID)
        return true;
    else
        return false;
}

bool checkEmpty(square board[BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo){
    if (board[rowNo][colNo].stack == NULL)
        return true;
    else
        return false;
}

bool checkSameColour(square board[BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo, player players[PLAYERS_NUM], int playerNumber){
    if(board[rowNo][colNo].stack->p_color == players[playerNumber].player_color)
        return true;
    else
        return false;
}

bool checkValidMove(square board [BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol, int amount){
    if((fromRow == toRow) && (fromCol == toCol))
        return false;
    else if((toRow < 0 || toRow >= BOARD_SIZE) || (toCol < 0 || toCol >= BOARD_SIZE))
        return false;
        //If the combined difference between the rows and the columns is greater than the number of pieces on the square
        //from which the piece is being moved it is an invalid move
    else if((abs(toRow - fromRow) + abs(toCol - fromCol)) > amount)
        return false;
    else{
        if(checkValid(board, toRow, toCol))
            return true;
        else
            return false;
    }
}

struct piece*maintainStackSize5(struct piece*tile){
    //Create a temporary array to store the top 5 pieces from the array
    square temp[1];
    //Push the top 5 pieces from the stack to the temp array
    for(int i = 0; i < 5; i++){
        temp[0].num_pieces++;
        temp[0].stack = push(tile->p_color, temp[0].stack);
        //Remove this piece from the stack
        tile = pop(tile);
    }
    //Get rid of the remaining pieces in the stack
    while(tile != NULL)
        tile = pop(tile);

    //Push the elements from the temp array back into the stack
    for(int i = 0; i < 5; i++){
        tile = push(temp[0].stack->p_color, tile);
        temp[0].stack = pop(temp[0].stack);
        temp[0].num_pieces--;
    }
    //Return the new stack
    return tile;
}

struct piece*transferStack(square board [BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int numTransferred){
    //Create a temporary array to store the pieces being moved from the stack
    square temp[1];

    //Push the elements form the stack into the temp array
    for(int i = 0; i < numTransferred; i++){
        temp[0].num_pieces++;
        temp[0].stack = push(board[fromRow][fromCol].stack->p_color, temp[0].stack);
        //Decrement the number of pieces on the square from which the stack is being moved
        board[fromRow][fromCol].num_pieces--;
        //Pop the top element of the stack from which the pieces are being moved so that the temp stack can access the next
        //element of the stack from which the pieces are being moved
        board[fromRow][fromCol].stack = pop(board[fromRow][fromCol].stack);
    }

    //Return the temp array
    return temp[0].stack;
}

void displayPiecesOnSquare(struct piece*tile, int size){
    //Base case
    if(size > 0){
        if(tile->p_color == RED){
            printf("[R]");
            //Use recursion to find the colour of the next piece
            displayPiecesOnSquare(tile->next, size-1);
        }else{
            printf("[G]");
            displayPiecesOnSquare(tile->next, size-1);
        }
    }else
        return;
}

void displayPieces(square board[BOARD_SIZE][BOARD_SIZE]){
    printf("The pieces on each square from top piece to bottom piece are as follows:\n");
    for(int rowNo = 0; rowNo < BOARD_SIZE; rowNo++){
        printf("\n");
        for(int colNo = 0; colNo < BOARD_SIZE; colNo++){
            if(checkValid(board, rowNo, colNo)){
                if(!checkEmpty(board, rowNo, colNo)){
                    printf("  board[%d][%d]:", rowNo, colNo);
                    if(board[rowNo][colNo].stack->p_color == RED){
                        printf("[R]");
                        displayPiecesOnSquare(board[rowNo][colNo].stack->next, board[rowNo][colNo].num_pieces-1);
                    }else{
                        printf("[G]");
                        displayPiecesOnSquare(board[rowNo][colNo].stack->next, board[rowNo][colNo].num_pieces-1);
                    }
                }
            }
        }
    }
}

bool checkREDWins(square board [BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]){
    for(int rowNo = 0; rowNo < BOARD_SIZE; rowNo++){
        for(int colNo = 0; colNo < BOARD_SIZE; colNo++){
            if(checkValid(board, rowNo, colNo)){
                if(!checkEmpty(board, rowNo, colNo)){
                    if(board[rowNo][colNo].stack->p_color == GREEN) {
                        return false;
                    }
                }
            }
        }
    }

    if(players[0].player_color == RED)
        printf("%s wins!\n", players[0].name);
    else
        printf("%s wins!\n", players[1].name);
    return true;
}

bool checkGREENWins(square board [BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]){
    for(int rowNo = 0; rowNo < BOARD_SIZE; rowNo++){
        for(int colNo = 0; colNo < BOARD_SIZE; colNo++){
            if(checkValid(board, rowNo, colNo)){
                if(!checkEmpty(board, rowNo, colNo)){
                    if(board[rowNo][colNo].stack->p_color == RED) {
                        return false;
                    }
                }
            }
        }
    }

    if(players[0].player_color == GREEN)
        printf("%s wins!\n", players[0].name);
    else
        printf("%s wins!\n", players[1].name);
    return true;
}

bool endGame(bool REDWon, bool GREENWon){
    if(REDWon || GREENWon)
        return true;
    else
        return false;
}

void play_game(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]){
    int fromRow, fromCol, numPiecesMoved, toRow, toCol;
    while(1) {
        for (int i = 0; i < PLAYERS_NUM; i++) {
            if (!checkREDWins(board, players) && !checkGREENWins(board, players)) {
                //Display all the pieces on the board so that the player can make a better decision as to which stack they wish to move
                displayPieces(board);
                while (1) {
                    printf("\n%s, please select the row from which you wish to move a stack\n", players[i].name);
                    scanf("%d", &fromRow);
                    printf("Please select the column from which you wish to move a stack\n");
                    scanf("%d", &fromCol);

                    //if the player chooses a valid square
                    if (checkValid(board, fromRow, fromCol) && (fromRow > -1 && fromRow < BOARD_SIZE) && (fromCol > -1 && fromCol < BOARD_SIZE)) {
                        //if the player chooses a non-empty square
                        if (!checkEmpty(board, fromRow, fromCol)) {
                            //if the player chooses a square that has their colour on top of the stack
                            if (checkSameColour(board, fromRow, fromCol, players, i)) {
                                printf("Ok!\n");
                                break;
                            } else
                                printf("You must choose a square that has your colour on the top of the stack\n");
                        } else
                            printf("Empty!\n");
                    } else
                        printf("Invalid!\n");
                }
            } else
                exit(0);

            if(board[fromRow][fromCol].num_pieces > 1){
                while(1){
                    printf("How many pieces do you wish to move form this stack?\n");
                    scanf("%d", &numPiecesMoved);
                    if(numPiecesMoved < 1 || numPiecesMoved > board[fromRow][fromCol].num_pieces)
                        printf("You must move between 1 and %d pieces!\n", board[fromRow][fromCol].num_pieces);
                    else
                        break;
                }
            }else
                numPiecesMoved = 1;

            while (1) {
                printf("%s, please select the row you wish to move this stack to\n", players[i].name);
                scanf("%d", &toRow);
                printf("Please select the column you wish to move this stack to\n");
                scanf("%d", &toCol);

                //if the player makes a valid move
                if (checkValidMove(board, fromRow, fromCol, toRow, toCol, numPiecesMoved)) {
                    printf("Ok!\n");
                    if(numPiecesMoved > 1){
                        //Create a temporary array to store the pieces about to be moved
                        square movedPieces[1];
                        //The movedPieces array becomes the temporary array returned by the function transferStack()
                        movedPieces[0].stack = transferStack(board, fromRow, fromCol, numPiecesMoved);
                        //The number of pieces in the movedPieces stack is equal to the number of pieces being moved
                        movedPieces[0].num_pieces = numPiecesMoved;
                        while(movedPieces[0].num_pieces > 0){
                            board[toRow][toCol].num_pieces++;
                            board[toRow][toCol].stack = push(movedPieces[0].stack->p_color, board[toRow][toCol].stack);
                            if(board[toRow][toCol].num_pieces > 5){
                                board[toRow][toCol].stack = maintainStackSize5(board[toRow][toCol].stack);
                                //Update the size of the stack so that it can be accessed by the displayPieces() function
                                board[toRow][toCol].num_pieces = 5;
                            }
                            movedPieces[0].stack = pop(movedPieces[0].stack);
                            movedPieces[0].num_pieces--;
                        }
                        if (board[fromRow][fromCol].num_pieces == 0) {
                            board[fromRow][fromCol].stack = NULL;
                            print_board(board);
                        } else
                            print_board(board);
                    }else{
                        //Increment the number of pieces on the square to which the piece is being placed
                        board[toRow][toCol].num_pieces++;
                        board[toRow][toCol].stack = push(board[fromRow][fromCol].stack->p_color, board[toRow][toCol].stack);
                        if(board[toRow][toCol].num_pieces > 5){
                            board[toRow][toCol].stack = maintainStackSize5(board[toRow][toCol].stack);
                            //Update the size of the stack so that it can be accessed by the displayPieces() function
                            board[toRow][toCol].num_pieces = 5;
                        }
                        board[fromRow][fromCol].stack = pop(board[fromRow][fromCol].stack);
                        //Decrement the number of pieces from which the piece was moved
                        board[fromRow][fromCol].num_pieces--;
                        if (board[fromRow][fromCol].num_pieces == 0) {
                            board[fromRow][fromCol].stack = NULL;
                            print_board(board);
                        } else
                            print_board(board);
                    }
                    break;
                } else
                    printf("Invalid choice!\n");
            }
        }
    }
}