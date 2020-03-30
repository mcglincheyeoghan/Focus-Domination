//
// Created by Eoghan on 29/03/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "input_output.h"

struct piece*push(enum color col, struct piece*top){
    struct piece * curr=top;
    top=( piece *)malloc(sizeof(piece));
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
    if(checkValid(board, toRow, toCol)){
        if(board[fromRow][fromCol].num_pieces < (abs(toRow - fromRow) + abs(toCol - fromCol)))
            return false;
        else
            return true;
    } else
        return false;
}

void place_pieces(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]){
    int fromRow, fromCol, toRow, toCol;

    for(int i = 0; i < PLAYERS_NUM; i++){
        while(1) {
            printf("%s, please select the row from which you wish to move a stack\n", players[i].name);
            scanf("%d", &fromRow);
            printf("Please select the column from which you wish to move a stack\n");
            scanf("%d", &fromCol);

            //if the player chooses a valid square
            if (checkValid(board, fromRow, fromCol)) {
                //if the player chooses a non-empty square
                if (!checkEmpty(board, fromRow, fromCol)) {
                    //if the
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

        while(1){
            printf("%s, please select the row you wish to move this stack to\n", players[i].name);
            scanf("%d", &toRow);
            printf("Please select the column you wish to move this stack to\n");
            scanf("%d", &toCol);

            //if the player makes a valid move
            if(checkValidMove(board, fromRow, fromCol, toRow, toCol)){
                printf("Ok!\n");
                break;
            } else
                printf("Invalid choice!\n");
        }
    }
}