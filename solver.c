#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define for_row for(int y = 0; y < HEIGHT; y++)
#define for_col for(int x = 0; x < WIDTH; x++)
#define for_rowcol for_row for_col
#define for_colrow for_col for_row

#define for_blockrow for(int y = i*BLOCK_SIZE; y < (i+1) * BLOCK_SIZE ; y++)
#define for_blockcol for(int x = j*BLOCK_SIZE; x < (j+1) * BLOCK_SIZE ; x++)
#define for_blockrowcol for_blockrow for_blockcol
#define for_blocks for(z = 0; z < 3; z++) for_blockrowcol


#define BLOCK_SIZE 3
#define WIDTH 9
#define HEIGHT 9

#define MV_TOPLEFT "\033[H"

void print_board(void *b, void *v){
  int (*board)[WIDTH] = b;
  int (*verified)[WIDTH] = v;
  //    printf("\033[2J");

  //  for_col
  //  printf()
  for_row{
    if (((y) % 3)==0)
      printf("+=====+=====+=====+\n|");
    else
      printf("+-----+-----+-----+\n|");
    for_col{
      if (((x+1) % 3)==0 )
	printf("%i|", board[y][x]);
      else
	printf("%i:", board[y][x]);
    }
    
    
    if(y == HEIGHT-1)
      printf("\n+=====+=====+=====+\n");
    else
      printf("\n");
  }  
  
}



int check_rows(void *b){
  int (*board)[WIDTH] = b;
  int check[10];
  for_row{
    for(int i = 0; i < WIDTH+1; i++)
      check[i] = 0;
    for_col{
      if (check[board[y][x]] == 1 && board[y][x] > 0){
	printf("\nIn block check");
	printf("\nAmount of number: %i,",check[board[y][x]]+1);
	printf("\nNumber: %i,",board[y][x]);
	printf("\nLocation on board: y=%i,x=%i\n",y+1,x+1);
	return 1;
      }else
	check[board[y][x]]++;
    }
  }
  return 0;
}

int check_columns(void *b){
  int (*board)[WIDTH] = b;
  int check[10];
  for_col{
    for(int i = 0; i < WIDTH+1; i++)
      check[i] = 0;
    for_row{
      if (check[board[y][x]] == 1 && board[y][x] > 0){
	printf("\nIn column check");
	printf("\nAmount of number: %i,",check[board[y][x]]+1);
	printf("\nNumber: %i,",board[y][x]);
	printf("\nLocation on board: y=%i,x=%i\n",y+1,x+1);
	return 1;
      }else
	check[board[y][x]]++;
    }
  }
  return 0;
}

int check_blocks(void *b){
  int (*board)[WIDTH] = b;
  int check[10];

  for(int i = 0; i < BLOCK_SIZE; i++){    
    for(int j = 0; j < BLOCK_SIZE; j++){//inside block
      for(int c = 0; c < WIDTH+1; c++)
	  check[c] = 0;
      for_blockrow{//for row in block
	for_blockcol{//for column in block
	  if (check[board[y][x]] == 1 && board[y][x] > 0){
	    printf("\nIn block check");
	    printf("\nAmount of number: %i,",check[board[y][x]]+1);
	    printf("\nNumber: %i,",board[y][x]);
	    printf("\nLocation of number: y=%i,x=%i\n",y+1,x+1);
	    return 1;
	  }else
	    check[board[y][x]]++;	
	}
      }
    }
      printf("\nnumbers: |0|1|2|3|4|5|6|7|8|9|\ncount:   |");
    for(int i = 0; i < WIDTH+1; i++)
      printf("%i|", check[i]);
    printf("\n");
  }
  return 0;
}

int no_errors(void* b){
  int (*board)[WIDTH] = b;
  /*
    for each row
     if num appears twice
      return false, coordinate
    for each column
     if num appears twice
      return false, coordinate
    for each 3x3
     if num appears twice
      return false, coordinate
  */
  if (check_rows(board) == 0){printf("rows good\n");
    if (check_columns(board) == 0){printf("columns good\n");
      if (check_blocks(board) == 0){printf("blocks good\n");
	return 1;
      }
    }
  }
  return 0;
}

int main(){
  int board[9][9] ={
    {0,0,0,8,0,0,0,0,0},
    {4,0,0,0,1,5,0,3,0},
    {0,2,9,0,4,0,5,1,8},
    {0,4,0,0,0,0,1,2,0},
    {0,0,0,6,0,2,0,0,0},
    {0,3,2,0,0,0,0,9,0},
    {6,9,3,0,5,0,8,7,0},
    {0,5,0,4,8,0,0,0,1},
    {0,0,0,0,0,3,0,0,0}
  };

  int colerror[9][9] ={
    {4,0,0,8,0,0,0,0,0},
    {4,0,0,0,1,5,0,3,0},
    {0,2,9,0,4,0,5,1,8},
    {0,4,0,0,0,0,1,2,0},
    {0,0,0,6,0,2,0,0,0},
    {0,3,2,0,0,0,0,9,0},
    {6,9,3,0,5,0,8,7,0},
    {0,5,0,4,8,0,0,0,1},
    {0,0,0,0,0,3,0,0,0}
  };
  int rowerror[9][9] ={
    {8,0,0,8,0,0,0,0,0},
    {4,0,0,0,1,5,0,3,0},
    {0,2,9,0,4,0,5,1,8},
    {0,4,0,0,0,0,1,2,0},
    {0,0,0,6,0,2,0,0,0},
    {0,3,2,0,0,0,0,9,0},
    {6,9,3,0,5,0,8,7,0},
    {0,5,0,4,8,0,0,0,1},
    {0,0,0,0,0,3,0,0,0}
  };
  int blockerror[9][9] ={
    {0,0,0,8,0,0,0,0,0},
    {4,0,0,0,1,5,0,3,0},
    {0,2,9,0,4,0,5,1,8},
    {0,4,0,0,0,0,1,2,0},
    {0,0,0,6,0,2,0,0,0},
    {0,3,2,0,0,0,0,9,0},
    {6,9,3,0,5,0,8,7,0},
    {0,5,0,4,8,0,7,0,1},
    {0,0,0,0,0,3,0,0,7}
  };
  
  int check = no_errors(blockerror);
  if(check == 1)
    printf("\nthere are no errors on board\n");    
  else
    printf("\nthere is at least 1 error on the board\n");
  print_board(blockerror, blockerror);

}
