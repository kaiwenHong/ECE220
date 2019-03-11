#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.

//This program solves a 9x9 sudoku given to it using recursion.
//Partners: Manan Mittal (manansm2), Luis Aragon (laragon2)
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int x;
  // BEG TODO
  for(x = 0;x<9;x++)
  {
    if(sudoku[i][x]==val)
    {
      return 1;
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);
  int x;
  // BEG TODO
  for(x = 0;x<9;x++)
  {
    if(sudoku[x][j]==val)
    {
      return 1;
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int fc, fr, x, y;
  fr = (i/3)*3;
  fc = (j/3)*3;
  // BEG TODO
  for(x = fr; x<=fr+2;x++)
  {
    for(y = fc; y<=fc+2;y++)
    {
      if(sudoku[x][y]==val)
      {
        return 1;
      }
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val, i,sudoku)==1
    ||is_val_in_col(val, j, sudoku)==1
    ||is_val_in_3x3_zone(val, i, j, sudoku)==1)
    {
      return 0;
    }
  else
  {
    return 1;
  }
  // END TODO
}

//Function: Checks if table is full.
//return 1 if full and 0 if not full.
int check_full(int sudoku[9][9])
{
  int x,y;
  for(x = 0; x<9;x++)
  {
    for(y=0;y<9;y++)
    {
      if(sudoku[x][y]==0)
      {
        return 0;
      }
    }
  }
  return 1;
}
// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  int x,y,i,j;
  // BEG TODO.
  if(check_full(sudoku)==1)
  {
    return 1;
  }
  else
  {
    for(x=0;x<9;x++)
    {
      for(y=0;y<9;y++)
      {
        if(sudoku[x][y]==0)
        break;
      }
      if(y<9){break;}
    }
  }
  for(i=1;i<=9;i++)
  {
    if(is_val_valid(i,x,y,sudoku)==1)
    {
      sudoku[x][y]=i;
      if(solve_sudoku(sudoku)==1)
      {
        return 1;
      }
      sudoku[x][y]=0;
    }
  }

  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
