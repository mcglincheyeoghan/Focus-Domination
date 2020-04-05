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

bool checkValidMove(square board [BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol){
    if((fromRow == toRow) && (fromCol == toCol))
        return false;
    else if((toRow < 0 || toRow >= BOARD_SIZE) || (toCol < 0 || toCol >= BOARD_SIZE))
        return false;
        //If the combined difference between the rows and the columns is greater than the number of pieces on the square
        //from which the piece is being moved it is an invalid move
    else if((abs(toRow - fromRow) + abs(toCol - fromCol)) > board[fromRow][fromCol].num_pieces)
        return false;
    else{
        if(checkValid(board, toRow, toCol))
            return true;
        else
            return false;
    }
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
    int fromRow, fromCol, toRow, toCol;
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

            while (1) {
                printf("%s, please select the row you wish to move this stack to\n", players[i].name);
                scanf("%d", &toRow);
                printf("Please select the column you wish to move this stack to\n");
                scanf("%d", &toCol);

                //if the player makes a valid move
                if (checkValidMove(board, fromRow, fromCol, toRow, toCol)) {
                    printf("Ok!\n");
                    //Increment the number of pieces on the square to which the piece is being placed
                    board[toRow][toCol].num_pieces++;
                    board[toRow][toCol].stack = push(board[fromRow][fromCol].stack->p_color, board[toRow][toCol].stack);
                    board[fromRow][fromCol].stack = pop(board[fromRow][fromCol].stack);
                    //Decrement the number of pieces from which the piece was moved
                    board[fromRow][fromCol].num_pieces--;
                    if (board[fromRow][fromCol].num_pieces == 0) {
                        board[fromRow][fromCol].stack = NULL;
                        print_board(board);
                    } else
                        print_board(board);
                    break;
                } else
                    printf("Invalid choice!\n");
            }
        }
    }
}