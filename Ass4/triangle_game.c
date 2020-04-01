/*
 * CS 11 C track, Winter 2019
 * Shubh Agrawal, Class of 2022
 * Assignment 4
 * 
 * triangle_game.c
 */


#define NMOVES 36
#define NHOLES 15

#include <stdio.h>
#include <stdlib.h>
#include "triangle_routines.h"

int moves[NMOVES][3] =
{
  {0, 1, 3}, {0, 2, 5}, {14, 9, 5}, {14, 13, 12},
  {1, 3, 6}, {1, 4, 8}, {13, 8, 4}, {13, 12, 11},
  {2, 4, 7}, {2, 5, 9}, {12, 7, 3}, {12, 8, 5},
  {3, 4, 5}, {3, 1, 0}, {12, 11, 10}, {12, 13, 14},
  {3, 6, 10}, {3, 7, 12}, {11, 7, 4}, {11, 12, 13},
  {4, 7, 11}, {4, 8, 13}, {10, 11, 12}, {10, 6, 3},
  {5, 4, 3}, {5, 2, 0}, {9, 5, 2}, {9, 8, 7},
  {5, 9, 14}, {5, 8, 12}, {8, 7, 6}, {8, 4, 1},
  {6, 3, 1}, {6, 7, 8}, {7, 4, 2}, {7, 8, 9}
};

/* Return the number of pegs on the board. 
  * 
  * Passed arguments:
  * board: array of integers representing the
  *             current state of pegs on board.
  */
int npegs(int board[]);

/* Return 1 if the move is valid on this board, otherwise return 0. 
  * 
  * Passed arguments:
  * board: array of integers representing the
  *             current state of pegs on board.
  * move: array of 3 integers denoting the move attempted.
  */
int valid_move(int board[], int move[]);

/* Make this move on this board. 
  * 
  * Passed arguments:
  * board: array of integers representing the
  *             current state of pegs on board.
  * move: array of 3 integers denoting the move attempted.
  */
void make_move(int board[], int move[]);

/* Unmake this move on this board. 
  * 
  * Passed arguments:
  * board: array of integers representing the
  *             current state of pegs on board.
  * move: array of 3 integers denoting the move attempted.
  */
void unmake_move(int board[], int move[]);

/* 
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order. 
  * 
  * Passed arguments:
  * board: array of integers representing the
  *             current(initial) state of pegs on board.
 */
int solve(int board[]);



int npegs(int board[])
{
  int pegs = 0, i;
  
  for (i = 0; i < NHOLES; i++)
   {
      if (board[i])
       {
          pegs++;
       }
   }

  return pegs;
}


int valid_move(int board[], int move[])
{
  /* Assumes that "move" is a possible move on board, i.e.,
   * "move" is a member of the global 2-D array "moves".
   */
  
  if (board[move[0]] == 0)
   {
      return 0;
   }

  if (board[move[1]] == 0)
   {
      return 0;
   }

  if (board[move[2]] == 1)
   {
      return 0;
   }

   return 1;
}


void make_move(int board[], int move[])
{
  board[move[0]] = 0;
  board[move[1]] = 0;
  board[move[2]] = 1;
}


void unmake_move(int board[], int move[])
{
  board[move[0]] = 1;
  board[move[1]] = 1;
  board[move[2]] = 0;
}


int solve(int board[])
{
  int result = 0, i; 

  if (npegs(board) == 1)
   {
      triangle_print(board);
      return 1;
   }

  for (i = 0; i < NMOVES; i++)
   {
      if (valid_move(board, moves[i]))
       {
          make_move(board, moves[i]);
          result = solve(board);

          if (result)
           {
              unmake_move(board, moves[i]);
              triangle_print(board);
              break;
           }
          
          /* Maintains the state of board, if "break" is not executed. */
          unmake_move(board, moves[i]);

       }
   }

  return result;
}

/* Starting point of program. */
int main(void)
{
  int board[NHOLES];
  triangle_input(board);

  if (!(solve(board)))
   {
     printf("No required set of moves exist.\n");
   }
  return 0;
}