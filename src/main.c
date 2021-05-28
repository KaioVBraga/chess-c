#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int bool;

char matChess[8][8][10] = {
    "bR1",
    "bN1",
    "bB1",
    "bQ1",
    "bK",
    "bB2",
    "bN2",
    "bR2",
    "bP1",
    "bP2",
    "bP3",
    "bP4",
    "bP5",
    "bP6",
    "bP7",
    "bP8",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    "wP1",
    "wP2",
    "wP3",
    "wP4",
    "wP5",
    "wP6",
    "wP7",
    "wP8",
    "wR1",
    "wN1",
    "wB1",
    "wQ1",
    "wK",
    "wB2",
    "wN2",
    "wR2",
};

//DISPLAY
void showGrid();

//MOVES
void getMove(char colorTeam);
int getCollumn();
int getRow();
void getPawnMove(char *piece, int rowPos, int colPos);
void getKnightMove(char *piece, int rowPos, int colPos);
void getBishopMove(char *piece, int rowPos, int colPos);
void getRookMove(char *piece, int rowPos, int colPos);
void getQueenMove(char *piece, int rowPos, int colPos);
void getKingMove(char *piece, int rowPos, int colPos);

//MOVES VALIDATION
int pawnMoveValidation(char *piece);

//CHARACTER HANDLING
int initstrcmp(char *str, char *str1);
int simbComp(int num, char simb);

int main()
{
  int asktimes = 0;
  char lose_pl1[2], lose_pl2[2];

  showGrid();

  do
  {
    /*Player 1 turn*/
    /*DID YOU LOSE ? --missing*/

    printf("PLAYER 1 TURN\n\n");
    getMove('w');
    showGrid();

    /*Player 2 turn*/
    /*DID YOU LOSE ? --missing*/

    printf("PLAYER 2 TURN\n\n");
    getMove('b');
    showGrid();

  } while (1);

  if (lose_pl2[0] == 'y')
    printf("PLAYER 1 WINS !!!\n");
  else
    printf("PLAYER 2 WINS !!!\n");

  return 0;
}

/*Shows the board on screen*/
void showGrid()
{
  int i, j;
  printf("       a       b       c       d       e       f       g       h\n");
  printf("   +-------+-------+-------+-------+-------+-------+-------+-------+\n");
  for (i = 0; i < 8; i++)
  {
    printf("   |       |       |       |       |       |       |       |       |\n");
    printf("%d  ", 8 - i);
    for (j = 0; j < 8; j++)
    {
      if (matChess[i][j][0] == ' ')
      {
        printf("|       ");
      }
      else
      {
        printf("|  %s", matChess[i][j]);
        simbComp(5 - strlen(matChess[i][j]), ' ');
      }
    }
    printf("|  %d\n", 8 - i);
    printf("   |       |       |       |       |       |       |       |       |\n");
    printf("   +-------+-------+-------+-------+-------+-------+-------+-------+\n");
  }
  printf("       a       b       c       d       e       f       g       h\n");
}

/*Gets the moves from the players*/
void getMove(char colorTeam)
{
  int i_search, j_search, numColMove, numRowMove, val;
  bool isTeamPiece = FALSE;
  char piece[5];

  /*Get piece*/
  do
  {
    printf("Enter a piece: ");
    gets(piece);

    if (piece[0] == colorTeam)
    {
      for (i_search = 0; i_search < 8; i_search++)
      {
        for (j_search = 0; j_search < 8; j_search++)
        {
          if (!strcmp(piece, matChess[i_search][j_search]))
          {
            isTeamPiece = TRUE;
            break;
          }
        }

        if (isTeamPiece)
        {
          break;
        }
      }
    }

    if (piece[1] == 'P')
    {
      val = pawnMoveValidation(piece);
    }
    else
    {
      val = FALSE;
    }
  } while (!isTeamPiece || !val);

  /*Movement type selection*/
  if (piece[1] == 'P')
  {
    getPawnMove(piece, i_search, j_search);
  }
  else if (piece[1] == 'N')
  {
    getKnightMove(piece, i_search, j_search);
  }
  else if (piece[1] == 'B')
  {
    getBishopMove(piece, i_search, j_search);
  }
  else if (piece[1] == 'R')
  {
    getRookMove(piece, i_search, j_search);
  }
  else if (piece[1] == 'Q')
  {
    getQueenMove(piece, i_search, j_search);
  }
  else if (piece[1] == 'K')
  {
    getKingMove(piece, i_search, j_search);
  }
}

/*Gets the collumns in characters ['a'-'h'] and translate those to integers [0-7]*/
int getCollumn()
{
  int numColMove;
  char ch_col_move[2];

  do
  {
    printf("Enter a collumn: ");
    gets(ch_col_move);
    numColMove = ch_col_move[0] - 97;
  } while (numColMove >= 8 || numColMove < 0);

  return numColMove;
}

/*Gets the rows in characters ['8'-'1'] and translate those to integers [0-7]*/
int getRow()
{
  int numRowMove;
  char ch_row_move[2];

  do
  {
    printf("Enter a row: ");
    gets(ch_row_move);
    numRowMove = 8 - (ch_row_move[0] - 48);
  } while (numRowMove >= 8 || numRowMove < 0);

  return numRowMove;
}

/*Gets the move of pawns*/
void getPawnMove(char *piece, int rowPos, int colPos)
{
  int i, j, numRowMove, numColMove, bp_index;
  static int w_twostp[8] = {0, 0, 0, 0, 0, 0, 0, 0}, b_twostp[8] = {0, 0, 0, 0, 0, 0, 0, 0}, big_piece[4] = {2, 2, 2, 1};
  ;
  char promo_piece[10], newPiece[10];

  if (piece[0] == 'w')
  {
    for (;;)
    {
      numColMove = getCollumn();
      numRowMove = getRow();

      if (matChess[numRowMove][numColMove][0] != 'w')
      {
        /*Breaks the for if it's making a valid capture*/
        if (matChess[numRowMove][numColMove][0] == 'b' && (numRowMove == rowPos - 1) && (numColMove == colPos + 1 || numColMove == colPos - 1))
          break;

        /*Breaks the for if it's making a non capture movement or enpassant*/
        if (matChess[numRowMove][numColMove][0] != 'b')
        {
          if (numColMove == colPos)
          {
            /*Double initial move*/
            if (!w_twostp[piece[2] - 49] && numRowMove == rowPos - 2)
              break;

            /*Simple move*/
            if (numRowMove == rowPos - 1)
              break;
          }
          else
          {
            /*En passant*/
            if ((numColMove == colPos + 1 || numColMove == colPos - 1) && numRowMove == rowPos - 1)
              if (!initstrcmp(matChess[numRowMove + 1][numColMove], "bP"))
                if (b_twostp[matChess[numRowMove + 1][numColMove][2] - 49] == 1 && numRowMove == 2)
                {
                  strcpy(matChess[numRowMove + 1][numColMove], " ");
                  break;
                }
          }
        }
      }
    }

    for (i = 0; i < 8; i++)
      if (w_twostp[i] == 1)
        w_twostp[i]++;

    w_twostp[piece[2] - 49]++;
  }
  else if (piece[0] == 'b')
  {
    for (;;)
    {
      numColMove = getCollumn();
      numRowMove = getRow();

      if (matChess[numRowMove][numColMove][0] != 'b')
      {
        /*Breaks the for if it's making a valid capture*/
        if (matChess[numRowMove][numColMove][0] == 'w' && (numRowMove == rowPos + 1) && (numColMove == colPos + 1 || numColMove == colPos - 1))
          break;

        /*Breaks the for if it's making a non capture movement or enpassant*/
        if (matChess[numRowMove][numColMove][0] != 'w')
        {
          if (numColMove == colPos)
          {
            /*Double initial move*/
            if (!b_twostp[piece[2] - 49] && numRowMove == rowPos + 2)
              break;

            /*Simple move*/
            if (numRowMove == rowPos + 1)
              break;
          }
          else
          {
            /*En passant*/
            if ((numColMove == colPos + 1 || numColMove == colPos - 1) && numRowMove == rowPos + 1)
              if (!initstrcmp(matChess[numRowMove - 1][numColMove], "wP"))
                if (w_twostp[matChess[numRowMove - 1][numColMove][2] - 49] == 1 && numRowMove == 5)
                {
                  strcpy(matChess[numRowMove - 1][numColMove], " ");
                  break;
                }
          }
        }
      }
    }

    for (i = 0; i < 8; i++)
      if (b_twostp[i] == 1)
        b_twostp[i]++;

    b_twostp[piece[2] - 49]++;
  }

  if (numRowMove == 0 || numRowMove == 7)
  {
    do
    {
      printf("Enter a piece to be promoted: \n");
      printf("[N] knight\n");
      printf("[B] bishop\n");
      printf("[R] rook\n");
      printf("[Q] queen\n\n");

      printf("Choice: ");
      gets(promo_piece);
    } while (promo_piece[0] != 'Q' && promo_piece[0] != 'R' && promo_piece[0] != 'B' && promo_piece[0] != 'N');

    if (promo_piece[0] == 'N')
      bp_index = 0;
    else if (promo_piece[0] == 'B')
      bp_index = 1;
    else if (promo_piece[0] == 'R')
      bp_index = 2;
    else if (promo_piece[0] == 'Q')
      bp_index = 3;

    big_piece[bp_index]++;

    newPiece[0] = piece[0];
    newPiece[1] = promo_piece[0];
    newPiece[2] = big_piece[bp_index] + 48;
    newPiece[3] = '\0';

    strcpy(matChess[numRowMove][numColMove], newPiece);
    strcpy(matChess[rowPos][colPos], " ");
  }
  else
  {
    strcpy(matChess[numRowMove][numColMove], piece);
    strcpy(matChess[rowPos][colPos], " ");
  }
}

void getKnightMove(char *piece, int rowPos, int colPos)
{
  int i, j, numRowMove, numColMove;

  for (;;)
  {
    numColMove = getCollumn();
    numRowMove = getRow();

    /*Checks if the square that the knight is moving to isn't an ally piece*/
    if (matChess[numRowMove][numColMove][0] != piece[0])
      /*Checks if the movement is a 'L'*/
      if (numRowMove == rowPos - 1 || numRowMove == rowPos + 1)
      {
        if ((numColMove == colPos + 2 || numColMove == colPos - 2))
          break;
      }
      else if (numRowMove == rowPos - 2 || numRowMove == rowPos + 2)
      {
        if ((numColMove == colPos + 1 || numColMove == colPos - 1))
          break;
      }
  }

  strcpy(matChess[numRowMove][numColMove], piece);
  strcpy(matChess[rowPos][colPos], " ");
}

void getBishopMove(char *piece, int rowPos, int colPos)
{
  int i, j, numRowMove, numColMove, rowPace, colPace, found;

  for (;;)
  {
    numColMove = getCollumn();
    numRowMove = getRow();

    /*Checks if the square that the bishop is moving to isn't an ally piece*/
    if (matChess[numRowMove][numColMove][0] != piece[0])
      if ((numRowMove - rowPos == numColMove - colPos) || (numRowMove - rowPos == -(numColMove - colPos)))
      {
        /*if the the movement is growing vertically then rowPace is 1 else it's -1, them same thing is horizontally with colPace*/
        rowPace = (numRowMove - rowPos > 0) ? 1 : (-1);
        colPace = (numColMove - colPos > 0) ? 1 : (-1);

        /*searches for a piece in the way of the bishop, if rowPace < 0 then condition is i<numRowMove else then i>numRowMove*/
        found = 0;
        for ((i = rowPos + rowPace, j = colPos + colPace); (rowPace > 0 ? i < numRowMove : i > numRowMove); (i += rowPace, j += colPace))
          if (matChess[i][j][0] != ' ')
          {
            found = 1;
            if (found)
              break;
          }

        if (!found)
          break;
      }
  }

  strcpy(matChess[numRowMove][numColMove], piece);
  strcpy(matChess[rowPos][colPos], " ");
}

void getRookMove(char *piece, int rowPos, int colPos)
{
  int i, j, numRowMove, numColMove, rowPace, colPace, found;

  for (;;)
  {
    numColMove = getCollumn();
    numRowMove = getRow();

    /*Checks if the square that the bishop is moving to isn't an ally piece*/
    if (matChess[numRowMove][numColMove][0] != piece[0])
      if (numRowMove == rowPos)
      {
        /*if the the movement is growing vertically then rowPace is 1 else it's -1, them same thing is horizontally with colPace*/
        colPace = (numColMove - colPos > 0) ? 1 : (-1);

        /*searches for a piece in the way of the bishop, if rowPace < 0 then condition is i<numRowMove else then i>numRowMove*/
        found = 0;
        for ((j = colPos + colPace); (colPace > 0 ? j < numColMove : j > numColMove); j += colPace)
          if (matChess[rowPos][j][0] != ' ')
          {
            found = 1;
            if (found)
              break;
          }

        if (!found)
          break;
      }
      else if (numColMove == colPos)
      {
        /*if the the movement is growing vertically then rowPace is 1 else it's -1, them same thing is horizontally with colPace*/
        rowPace = (numRowMove - rowPos > 0) ? 1 : (-1);

        /*searches for a piece in the way of the bishop, if rowPace < 0 then condition is i<numRowMove else then i>numRowMove*/
        found = 0;
        for ((i = rowPos + rowPace); (rowPace > 0 ? i < numRowMove : i > numRowMove); i += rowPace)
          if (matChess[i][colPos][0] != ' ')
          {
            found = 1;
            if (found)
              break;
          }

        if (!found)
          break;
      }
  }

  strcpy(matChess[numRowMove][numColMove], piece);
  strcpy(matChess[rowPos][colPos], " ");
}

void getQueenMove(char *piece, int rowPos, int colPos)
{
  int i, j, numRowMove, numColMove, rowPace, colPace, found;

  for (;;)
  {
    numColMove = getCollumn();
    numRowMove = getRow();

    /*Checks if the square that the bishop is moving to isn't an ally piece*/
    if (matChess[numRowMove][numColMove][0] != piece[0])
      /*Breaks the for if it's a valid bishop's move*/
      if ((numRowMove - rowPos == numColMove - colPos) || (numRowMove - rowPos == -(numColMove - colPos)))
      {
        /*if the the movement is growing vertically then rowPace is 1 else it's -1, them same thing is horizontally with colPace*/
        rowPace = (numRowMove - rowPos > 0) ? 1 : (-1);
        colPace = (numColMove - colPos > 0) ? 1 : (-1);

        /*searches for a piece in the way of the bishop, if rowPace < 0 then condition is i<numRowMove else then i>numRowMove*/
        found = 0;
        for ((i = rowPos + rowPace, j = colPos + colPace); (rowPace > 0 ? i < numRowMove : i > numRowMove); (i += rowPace, j += colPace))
          if (matChess[i][j][0] != ' ')
          {
            found = 1;
            if (found)
              break;
          }

        if (!found)
          break;
      }
      else
      {
        /*Breaks the for if it's a valid rook's move*/
        if (numRowMove == rowPos)
        {
          /*if the the movement is growing vertically then rowPace is 1 else it's -1, them same thing is horizontally with colPace*/
          colPace = (numColMove - colPos > 0) ? 1 : (-1);

          /*searches for a piece in the way of the bishop, if rowPace < 0 then condition is i<numRowMove else then i>numRowMove*/
          found = 0;
          for ((j = colPos + colPace); (colPace > 0 ? j < numColMove : j > numColMove); j += colPace)
            if (matChess[rowPos][j][0] != ' ')
            {
              found = 1;
              if (found)
                break;
            }

          if (!found)
            break;
        }
        else if (numColMove == colPos)
        {
          /*if the the movement is growing vertically then rowPace is 1 else it's -1, them same thing is horizontally with colPace*/
          rowPace = (numRowMove - rowPos > 0) ? 1 : (-1);

          /*searches for a piece in the way of the bishop, if rowPace < 0 then condition is i<numRowMove else then i>numRowMove*/
          found = 0;
          for ((i = rowPos + rowPace); (rowPace > 0 ? i < numRowMove : i > numRowMove); i += rowPace)
            if (matChess[i][colPos][0] != ' ')
            {
              found = 1;
              if (found)
                break;
            }

          if (!found)
            break;
        }
      }
  }

  strcpy(matChess[numRowMove][numColMove], piece);
  strcpy(matChess[rowPos][colPos], " ");
}

void getKingMove(char *piece, int rowPos, int colPos)
{
  int i, j, numRowMove, numColMove, rowPace, colPace, found;

  for (;;)
  {
    numColMove = getCollumn();
    numRowMove = getRow();

    /*Checks if the square that the bishop is moving to isn't an ally piece*/
    if (matChess[numRowMove][numColMove][0] != piece[0])
      /*Breaks the for if it's a valid bishop's move, one unit*/
      if ((numRowMove - rowPos == numColMove - colPos) || (numRowMove - rowPos == -(numColMove - colPos)))
      {
        if ((numRowMove - rowPos == 1) || (numRowMove - rowPos == -1))
          break;
      }
      else
      {
        /*Breaks the for if it's a valid rook's move, one unit*/
        if (numRowMove == rowPos)
        {
          if ((numColMove - colPos == 1) || (numColMove - colPos == -1))
            break;
        }
        else if (numColMove == colPos)
        {
          if ((numRowMove - rowPos == 1) || (numRowMove - rowPos == -1))
            break;
        }
      }
  }

  strcpy(matChess[numRowMove][numColMove], piece);
  strcpy(matChess[rowPos][colPos], " ");
}

int pawnMoveValidation(char *piece)
{
}

/*Compares the first characters of str with all the characters of str1, returns 0 if they are all equal, 1 if not*/
int initstrcmp(char *str, char *str1)
{
  int i, compare = 0;
  for (i = 0; i < strlen(str1); i++)
    if (str[i] != str1[i])
    {
      compare = 1;
      break;
    }
  return compare;
}

/*Prints a symbol (simb) on screen num times*/
int simbComp(int num, char simb)
{
  int i;
  for (i = 0; i < num; i++)
    printf("%c", simb);
}
