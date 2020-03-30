//
// Created by Eoghan on 29/03/2020.
//
//Function to place the pieces on a square
#include <stdbool.h>
void place_pieces(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]);

//Function to play the game
void play_game(square board[BOARD_SIZE][BOARD_SIZE], player players[], int numPlayers);

bool checkValid(square board[BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo);

bool checkEmpty(square board[BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo);

bool checkSameColour(square board[BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo, player players[PLAYERS_NUM], int playerNumber);

bool checkValidMove(square board [BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo);

struct token*push(enum color col, struct token*top);

struct token*pop(struct token*top);