#include "TicTacToeBoard.h"
/**
 * Class for representing a 3x3 Tic-Tac-Toe game board, using the Piece enum
 * to represent the spaces on the board.
**/

//Constructor sets an empty board and specifies it is X's turn first
TicTacToeBoard::TicTacToeBoard()
{
  turn = X;
  for(int i=0; i<BOARDSIZE; i++)
    for(int j=0; j<BOARDSIZE; j++)
      board[i][j] = Blank;
}

/**
 * Switches turn member variable to represent whether it's X's or O's turn
 * and returns whose turn it is
**/
Piece TicTacToeBoard::toggleTurn()
{
  turn = turn == X ? O : X;
  return turn;
}

/**
 * Places the piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. placePiece does 
 * NOT allow to place a piece in a location where there is already a piece.
 * In that case, placePiece just returns what is already at that location. 
 * Out of bounds coordinates return the Piece Invalid value. When the game
 * is over, no more pieces can be placed so attempting to place a piece
 * should neither change the board nor change whose turn it is.
**/ 
Piece TicTacToeBoard::placePiece(int row, int col)
{
  if(row < 0 || row >= BOARDSIZE)
    return Invalid;
  if(col < 0 || col >= BOARDSIZE)
    return Invalid;

  Piece toPut = turn;
  
  //Make sure location is currently Blank
  if(board[row][col] == Blank)
  {
    board[row][col] = toPut;
    return toPut;
  }
  else
  {
    //Leave the existing piece
    return board[row][col];
  }
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece TicTacToeBoard::getPiece(int row, int col)
{
  if(row < 0 || row >= BOARDSIZE)
    return Invalid;
  if(col < 0 || col >= BOARDSIZE)
    return Invalid;
    
  return board[row][col];
}

Piece TicTacToeBoard::checkFullRow(int row)
{
  Piece piece = getPiece(row, 0);
  for(int col = 1; col < BOARDSIZE; col++)
  {
    Piece cur = getPiece(row, col);
    if(cur != piece)
      return Invalid;
  }
  return piece;
}

Piece TicTacToeBoard::checkFullCol(int col)
{
  Piece piece = getPiece(0, col);
  for(int row = 1; row < BOARDSIZE; row++)
  {
    Piece cur = getPiece(row, col);
    if(cur != piece)
      return Invalid;
  }
  return piece;
}

Piece TicTacToeBoard::checkFullDiagonal(bool back)
{
  int end = BOARDSIZE-1;
  Piece top = back ? getPiece(0,0) : getPiece(0,end);
  Piece middle = getPiece(BOARDSIZE/2, BOARDSIZE/2);
  Piece bottom = back ? getPiece(end,end) : getPiece(end,0);

  if(top == middle && middle == bottom)
    return top;
  else
    return Invalid;
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won.
**/
Piece TicTacToeBoard::getWinner()
{
  for(int row = 0; row < BOARDSIZE; row++)
  {
    Piece rowWinner = checkFullRow(row);
    if(rowWinner != Invalid && rowWinner != Blank)
      return rowWinner;
  }
  
  for(int col = 0; col < BOARDSIZE; col++)
  {
    Piece colWinner = checkFullCol(col);
    if(colWinner != Invalid && colWinner != Blank)
      return colWinner;
  }
  
  Piece backDiagonalWinner = checkFullDiagonal(true);
  if(backDiagonalWinner != Invalid && backDiagonalWinner != Blank)
    return backDiagonalWinner;
  Piece forwardDiagonalWinner = checkFullDiagonal(false);
  if(forwardDiagonalWinner != Invalid && forwardDiagonalWinner != Blank)
    return forwardDiagonalWinner;
    
  //No possible win case here, check for tie
  for(int row = 0; row < BOARDSIZE; row++)
  {
    for(int col = 0; col < BOARDSIZE; col++)
    {
      if(getPiece(row, col) == Blank)
      {
        //Found a blank, so there's still a potential winner
        return Invalid;//Not over yet
      }
    }
  }
  
  //The board is full and there is no winner (tie)
  return Blank;
}
