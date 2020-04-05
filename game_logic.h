//
// Created by Eoghan on 29/03/2020.
//
//Function to place the pieces on a square
#include <stdbool.h>

//Function that allows pieces to be pushed from one square to another
struct piece*push(enum color col, struct piece*top);

//Function that remove pieces from a square
struct piece*pop(struct piece*top);

//Function to play the game
void play_game(square board[BOARD_SIZE][BOARD_SIZE], player players[]);

//Function to check if the square is valid
bool checkValid(square board[BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo);

//Function to check if the square is empty
bool checkEmpty(square board[BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo);

//Function to check if the piece on the top of the stack is the same colour as the player's
bool checkSameColour(square board[BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo, player players[PLAYERS_NUM], int playerNumber);

//Function to check if the player has made a valid move
bool checkValidMove(square board [BOARD_SIZE][BOARD_SIZE], int rowNo, int colNo);

//Recursive function to display the pieces a particular square on the board
void displayPiecesOnSquare(struct piece*tile);

//Function to display all the pieces on the board, using the displayPiecesOnSquare function as a helper function
void displayPieces(square board[BOARD_SIZE][BOARD_SIZE]);

//Function to check if player with red pieces has won the game
bool checkREDWins(square board [BOARD_SIZE][BOARD_SIZE]);

//Function to check if player with green pieces has won the game
bool checkGREENGameWins(square board [BOARD_SIZE][BOARD_SIZE]);