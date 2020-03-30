//
// Created by Eoghan on 27/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game_init.h"

void initialize_players(player players[PLAYERS_NUM]){

    for(int i = 0; i < PLAYERS_NUM; i++){
        printf("Player %d, please enter your name.\n", i+1);
        scanf(" %s", players[i].name);
        //boolean variable to check if user inputs a valid colour
        bool validColour = false;
        if(i == 0){
            //will continue to ask user to enter a valid colour until a valid colour is entered
            while(!validColour){
                char chosenColour;
                printf("%s, please choose your colour. Type 'R' for red and 'G' for green.\n", players[i].name);
                scanf(" %c", &chosenColour);
                    switch (chosenColour) {
                        case 'R':
                            players[i].player_color = RED;
                            printf("%s, you have chosen red\n", players[i].name);;
                            //breaks while loop
                            validColour = true;
                            break;
                        case 'G':
                            players[i].player_color = GREEN;
                            printf("%s, you have chosen green\n", players[i].name);
                            //breaks while loop
                            validColour = true;
                            break;
                        default:
                            printf("You have not chosen a valid colour!\n");
                    }
            }
        }else{
            if(players[i-1].player_color == RED) {
                players[i].player_color = GREEN;
                printf("%s, your colour is green\n", players[i].name);
            }
            else {
                players[i].player_color = RED;
                printf("%s, your colour is red\n", players[i].name);
            }
        }
    }

}

//Set Invalid Squares (where it is not possible to place stacks)
int set_invalid(square * s){
s->type = INVALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
int set_empty(square * s){
s->type = VALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set squares  with a GREEN piece
int set_green(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = GREEN;
s->stack->next = NULL;
s->num_pieces = 1;
}

//Set squares with a RED piece
int set_red(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = RED;
s->stack->next = NULL;
s->num_pieces = 1;
}

//initializes the board
void initialize_board(square board [BOARD_SIZE][BOARD_SIZE]){

    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j< BOARD_SIZE; j++){
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&board[i][j]);

            else{
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    set_empty(&board[i][j]);
                else{
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4)))
                        set_red(&board[i][j]);
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }


    }


}