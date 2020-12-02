/**
 * Unit Tests for TicTacToeBoard
**/

#include <gtest/gtest.h>
#include "TicTacToeBoard.h"
 
class TicTacToeBoardTest : public ::testing::Test
{
	protected:
		TicTacToeBoardTest(){} //constructor runs before each test
		virtual ~TicTacToeBoardTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(TicTacToeBoardTest, ToggleTurnInitialValueWorks)
{
  TicTacToeBoard board;
  Piece got = board.toggleTurn();
  ASSERT_EQ(O, got);
}

TEST(TicTacToeBoardTest, ToggleTurnSecondValueWorks)
{
  TicTacToeBoard board;
  board.toggleTurn();
  Piece got = board.toggleTurn();
  ASSERT_EQ(X, got);
}

TEST(TicTacToeBoardTest, ToggleTurnThirdValueWorks)
{
  TicTacToeBoard board;
  board.toggleTurn();
  board.toggleTurn();
  Piece got = board.toggleTurn();
  ASSERT_EQ(O, got);
}

TEST(TicTacToeBoardTest, PlacePieceInNegativeRow)
{
  TicTacToeBoard board;
  Piece got = board.placePiece(-1, 0);
  ASSERT_EQ(Invalid, got);
}

TEST(TicTacToeBoardTest, PlacePieceInNegativeCol)
{
  TicTacToeBoard board;
  Piece got = board.placePiece(0, -1);
  ASSERT_EQ(Invalid, got);
}

TEST(TicTacToeBoardTest, PlacePieceInOverflowRow)
{
  TicTacToeBoard board;
  Piece got = board.placePiece(BOARDSIZE, 0);
  ASSERT_EQ(Invalid, got);
}

TEST(TicTacToeBoardTest, PlacePieceInOverflowCol)
{
  TicTacToeBoard board;
  Piece got = board.placePiece(0, BOARDSIZE);
  ASSERT_EQ(Invalid, got);
}

TEST(TicTacToeBoardTest, PlacePieceInZeroCorner)
{
  TicTacToeBoard board;
  Piece placeStatus = board.placePiece(0, 0);
  Piece getStatus = board.getPiece(0, 0);
  ASSERT_EQ(X, placeStatus);
  ASSERT_EQ(X, getStatus);
}

TEST(TicTacToeBoardTest, PlacePieceInMaxCorner)
{
  TicTacToeBoard board;
  Piece placeStatus = board.placePiece(BOARDSIZE-1, BOARDSIZE-1);
  Piece getStatus = board.getPiece(BOARDSIZE-1, BOARDSIZE-1);
  ASSERT_EQ(X, placeStatus);
  ASSERT_EQ(X, getStatus);
}

TEST(TicTacToeBoardTest, PlacePieceInMiddleAsX)
{
  TicTacToeBoard board;
  Piece placeStatus = board.placePiece(BOARDSIZE/2, BOARDSIZE/2);
  Piece getStatus = board.getPiece(BOARDSIZE/2, BOARDSIZE/2);
  ASSERT_EQ(X, placeStatus);
  ASSERT_EQ(X, getStatus);
}

TEST(TicTacToeBoardTest, PlacePieceInMiddleAsO)
{
  TicTacToeBoard board;
  Piece turnStatus = board.toggleTurn();
  ASSERT_EQ(O, turnStatus);
  Piece placeStatus = board.placePiece(BOARDSIZE/2, BOARDSIZE/2);
  Piece getStatus = board.getPiece(BOARDSIZE/2, BOARDSIZE/2);
  ASSERT_EQ(O, placeStatus);
  ASSERT_EQ(O, getStatus);
}

TEST(TicTacToeBoardTest, PlacePieceWillNotOverwrite)
{
  TicTacToeBoard board;
  
  //Place a X piece at (0,0)
  ASSERT_EQ(X, board.placePiece(0,0));
  
  //Try to place a O piece in the same location
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(0,0));
  
  //Make sure the location did not change
  ASSERT_EQ(X, board.getPiece(0,0));
}





TEST(TicTacToeBoardTest, GetPieceInNegativeRow)
{
  TicTacToeBoard board;
  Piece got = board.getPiece(-1, 0);
  ASSERT_EQ(Invalid, got);
}

TEST(TicTacToeBoardTest, GetPieceInNegativeCol)
{
  TicTacToeBoard board;
  Piece got = board.getPiece(0, -1);
  ASSERT_EQ(Invalid, got);
}

TEST(TicTacToeBoardTest, GetPieceInOverflowRow)
{
  TicTacToeBoard board;
  Piece got = board.getPiece(BOARDSIZE, 0);
  ASSERT_EQ(Invalid, got);
}

TEST(TicTacToeBoardTest, GetPieceInOverflowCol)
{
  TicTacToeBoard board;
  Piece got = board.getPiece(0, BOARDSIZE);
  ASSERT_EQ(Invalid, got);
}

TEST(TicTacToeBoardTest, GetBlankPiece)
{
  TicTacToeBoard board;
  Piece got = board.getPiece(1, 1);
  ASSERT_EQ(Blank, got);
}


TEST(TicTacToeBoardTest, GetWinnerInvalidOnEmptyBoard)
{
  TicTacToeBoard board;
  Piece got = board.getWinner();
  ASSERT_EQ(Invalid, got);
}

TEST(TicTacToeBoardTest, GetWinnerInvalidOnIncompleteBoard)
{
  TicTacToeBoard board;
  
  //Place a few pieces, but not enough to win/tie
  board.placePiece(0,0);
  board.toggleTurn();
  board.placePiece(1,0);
  board.toggleTurn();
  board.placePiece(1,1);
  
  Piece got = board.getWinner();
  ASSERT_EQ(Invalid, got);
}

TEST(TicTacToeBoardTest, GetWinnerBlankOnTie)
{
  TicTacToeBoard board;
  
  //Setup a tie condition
  /*  XOX
   *  OXX
   *  OXO */
  
  ASSERT_EQ(X, board.placePiece(0,0));//X (initially)
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(0, 1));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(0, 2));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(1,1));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(2,2));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(2,1));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(2,0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(1,2));//X
  
  ASSERT_EQ(Blank, board.getWinner());
}

TEST(TicTacToeBoardTest, GetWinnerX315)
{
  TicTacToeBoard board;
  
  //Setup a win condition for X in a 315* diagonal
  /*  XOX
   *  OXO
   *    X */
  
  ASSERT_EQ(X, board.placePiece(0,0));//X (initially)
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(0, 1));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(0, 2));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(1,1));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,2));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(2,2));//X
  
  ASSERT_EQ(X, board.getWinner());
}

TEST(TicTacToeBoardTest, GetWinnerX45)
{
  TicTacToeBoard board;
  
  //Setup a win condition for X in a 45* diagonal
  /*  XOX
   *  OXO
   *  X   */
  
  ASSERT_EQ(X, board.placePiece(0,0));//X (initially)
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(0, 1));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(0, 2));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(1,1));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,2));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(2,0));//X
  
  ASSERT_EQ(X, board.getWinner());
}

TEST(TicTacToeBoardTest, GetWinnerXTopRow)
{
  TicTacToeBoard board;
  
  //Setup a win condition for X in the top row
  /*  XXX
   *  OO
   *      */
  
  ASSERT_EQ(X, board.placePiece(0,0));//X (initially)
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(0,1));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,1));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(0,2));//X
  
  ASSERT_EQ(X, board.getWinner());
}

TEST(TicTacToeBoardTest, GetWinnerXSecondRow)
{
  TicTacToeBoard board;
  
  //Setup a win condition for X in the second row
  /*  OO
   *  XXX
   *      */
  
  ASSERT_EQ(X, board.placePiece(1,0));//X (initially)
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(0, 0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(1, 1));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(0,1));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(1,2));//X
  
  ASSERT_EQ(X, board.getWinner());
}

TEST(TicTacToeBoardTest, GetWinnerXThirdRow)
{
  TicTacToeBoard board;
  
  //Setup a win condition for X in the third row
  /*  O
   *  O
   *  XXX */
  
  ASSERT_EQ(X, board.placePiece(0,2));//X (initially)
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(0, 0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(1, 2));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(2,2));//X
  
  ASSERT_EQ(X, board.getWinner());
}

TEST(TicTacToeBoardTest, GetWinnerXFirstCol)
{
  TicTacToeBoard board;
  
  //Setup a win condition for X in the left col
  /*  XO 
   *  XO 
   *  X    */
  
  ASSERT_EQ(X, board.placePiece(0,0));//X (initially)
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(0,1));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(1,0));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,1));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(2,0));//X
  
  ASSERT_EQ(X, board.getWinner());
}

TEST(TicTacToeBoardTest, GetWinnerXSecondCol)
{
  TicTacToeBoard board;
  
  //Setup a win condition for X in the second col
  /*  OX 
   *  OX 
   *   X  */
  
  ASSERT_EQ(X, board.placePiece(0,1));//X (initially)
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(0,0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(1,1));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(2,1));//X
  
  ASSERT_EQ(X, board.getWinner());
}

TEST(TicTacToeBoardTest, GetWinnerXThirdCol)
{
  TicTacToeBoard board;
  
  //Setup a win condition for X in the third col
  /*  O X
   *  O X
   *    X */
  
  ASSERT_EQ(X, board.placePiece(0,2));//X (initially)
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(0,0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(1,2));//X
  ASSERT_EQ(O, board.toggleTurn());
  ASSERT_EQ(O, board.placePiece(1,0));//O
  ASSERT_EQ(X, board.toggleTurn());
  ASSERT_EQ(X, board.placePiece(2,2));//X
  
  ASSERT_EQ(X, board.getWinner());
}

