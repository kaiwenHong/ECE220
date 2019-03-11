/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

// Partners - Manan Mittal (manansm2), Luis Aragon (laragon2)
 // i check the 8 or less neigbours by first deciding the bounds around the current cell
 // for update board i use a temp board and then copy those values in
 // for alivestable i update a temp board that is identical to the current board and then compare
 int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
     int count=0;
     int rowstart;
     int rowend;
     int colstart;
     int colend;
     //setting the values of rowstart,rowend , colstart and colend depending on the position of the current cell
     if(row-1<0)
         rowstart=0;
     else
         rowstart=row-1;

     if(row+1==boardRowSize)
         rowend=boardRowSize-1;
     else
         rowend=row+1;

     if((col-1)<0)
         colstart=0;
     else
         colstart=col-1;

     if((col+1)==boardColSize)
         colend=boardColSize-1;
     else
         colend=col+1;


     int i=rowstart;
     int j;
     for(;i<=rowend;i++)
     {
         for(j=colstart;j<=colend;j++)
         {
             if(i==row && j==col)
                 continue;
             else{
                 if(board[i*boardColSize+j]==1)
                 count++;
             }
         }
     }
     return count;
 }

 void updateBoard(int* board, int boardRowSize, int boardColSize) {
     int i=0;
     int j;
     int arraycheck[boardRowSize*boardColSize];
     int position=0;
     //transferring the contents of the board to a temporary board
     for(;position<(boardColSize*boardRowSize);position++)
         arraycheck[position]=board[position];
         //updating the temporary board because updating the actual board would modify all values
     for(;i<boardRowSize;i++){

         for(j=0;j<boardColSize;j++){
             int count = countLiveNeighbor(board, boardRowSize, boardColSize , i, j);
             if(board[( i*boardColSize)+j]==1){ // checking whether the neighbour is alive or dead
                 if(count<2 || count>3)
                     arraycheck[( i*boardColSize)+j]=0;
             }
             else{
                 if(count==3)
                     arraycheck[( i*boardColSize)+j]=1;
             }

         }
     }
     position=0;
     for(;position<(boardColSize*boardRowSize);position++)
         board[position]=arraycheck[position];
 }

 int aliveStable(int* board, int boardRowSize, int boardColSize){
     int i=0;
     int j;
     int arraycheck[boardRowSize*boardColSize];
     int position=0;
         //transferring the contents of the board to a temporary board
     for(;position<(boardColSize*boardRowSize);position++)
         arraycheck[position]=board[position];
         //updating the temp board
     updateBoard(arraycheck,boardRowSize,boardColSize);
     for(i=0;i<boardRowSize;i++){
 //if the contents are exactly the same return 1 else returns 0
         for(j=0;j<boardColSize;j++){
                 if(arraycheck[i*boardColSize+j]!=board[i*boardColSize+j])
                     return 0;
         }
     }
 return 1;
 }
