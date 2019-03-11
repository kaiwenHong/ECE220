//this code takes a text file as an input and creates a maze. Then using recursive methods solves it using one possible path from S to E.
//Partners: Luis Arargon(laragon2) and Manan Mittal (manansm2);

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */

maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    FILE *fptr=fopen(fileName,"r");
    if(fptr==NULL) return NULL;


    maze_t *maze = (maze_t*)malloc(sizeof(maze_t));
    fscanf(fptr,"%d %d",&maze->width, &maze->height);
    fgetc(fptr);
    maze->cells=(char **)malloc((maze->height)*sizeof(char*));
    int i;
    maze->startRow=-1;
    maze->startColumn=-1;
    maze->endRow=-1;
    maze->endColumn=-1;

    for(i=0;i<maze->height;i++)
    {
      maze->cells[i]=(char *)malloc(sizeof(char)*(maze->width));
    }
    char cc;
    int j = 0;
    i=0;
    while((cc=fgetc(fptr))!=EOF)
    {
      if(cc=='\n')
      {
        i++;
        j=0;
      }
      else
      {
        maze->cells[i][j]=cc;
        if(cc=='S')
        {
          maze->startRow = i;
          maze->startColumn = j;
        }
        j++;
      }
    }
    fclose(fptr);
    return maze;
  }

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for(i = 0; i<maze->height;i++)
    {
      free(maze->cells[i]);
    }
    free(maze->cells);
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i,j;
    for(i = 0; i<maze->height;i++)
    {
      for(j=0;j<maze->width;j++)
      {
        printf("%c",maze->cells[i][j]);
      }
      printf("%s\n", "");
    }

}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    //this code recursively solves the maze.There are 2 base cases which do the final returns.
    if(maze->cells[row][col]=='E')
    {
      maze->cells[maze->startRow][maze->startColumn]='S';
      return 1;
    }

    if(row<0||row>=maze->height-1||col<0||col>=maze->width-1) return 0;
    if(maze->cells[row][col]!=' '&& maze->cells[row][col]!='S') return 0;

    maze->cells[row][col]='*';

    if(solveMazeDFS(maze,col-1,row)==1) return 1;
    if(solveMazeDFS(maze,col,row+1)==1) return 1;
    if(solveMazeDFS(maze,col+1,row)==1) return 1;
    if(solveMazeDFS(maze,col,row-1)==1) return 1;

    maze->cells[row][col]='~';
    return 0;
}
