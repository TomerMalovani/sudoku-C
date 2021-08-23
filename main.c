//47 till infinity
#include "main.h"

//TO DO LIST
//GET SHIT TO OTHER FILES,MAKE IT NICE LOOKING  []
//MEMORY ALLOCTAION TESTS                       []
//REMOVE USLESS PRINTF                          []
//ADD DEFINE VAR TO PRINT EXTRA STUFF LIKE STATS[]
//RE-THINK YOU LIFE DECISIONS THAT GOT YOU HERE []
//FINISH THE GOD DAMN THING                     []

void checkMemoryAlloc(Array *arr, char *msg)
{
	if(arr==NULL){
		printf("%s",msg);
		exit(0);
	}
}

int removeFromArr(Array *squarePoss, short size, int toRm)
{
	int index=-1;
	for (int i = 0; i < size; i++)
	{	
		if (squarePoss->arr[i] == toRm)	
			index=i;
	}
	if(index!=-1){

		for (int j = index; j < squarePoss->size; j++)
		{
			squarePoss->arr[j] = squarePoss->arr[j + 1];
		}
		int newSize = size > 0 ? squarePoss->size - 1 : 0;
		squarePoss->arr = (short *)realloc(squarePoss->arr, newSize * sizeof(short));
		squarePoss->size= newSize;
	}else{
		return -1;
	}
}

int removePossibilitiesFromSquare(int row, int col, int possToRmv, Array ***possibilities,short board[][9])
{
	int startRow = row - row % 3,
		startCol = col - col % 3;
	for (int k =  0; k < 3; k++)
	{

		for (int t = 0; t < 3; t++)
		{
			
			int r = k + startRow;
			int c = t + startCol;
			if(board[r][c] == possToRmv && (r!=row || c!=col)){
				printf("org [%d,%d] bad copy [%d,%d]\n",row,col,r,c); 
				return -1;
			}
			if ((possibilities[r][c]->size) > 0 && possibilities[r][c]->size < 9)
				removeFromArr(possibilities[r][c], possibilities[r][c]->size, possToRmv);
		}
	}
	return 0;
}

int removePossibilitiesFromCol(int row, int col, int possToRmv, Array ***possibilities, short board[][9])
{
	short *arr = possibilities[row][col]->arr;
	for (int k = 0; k < 9; k++)
	{
		if (board[k][col] == possToRmv && k != row){
			return -1;
		}
			//remove bad numbers from all items in row
			if (possibilities[k][col]->size != 0)
				removeFromArr(possibilities[k][col], possibilities[k][col]->size, possToRmv);
		for (int t = 0; t < 9; t++)
		{
			if (board[row][t] == possToRmv && t != col)
			{
				return -1;
			}
			//remove bad numbers from all items in col
			if (possibilities[k][t]->size != 0)
				 removeFromArr(possibilities[row][t], possibilities[row][t]->size, possToRmv);		
		}
	}
}

int OneStage(short board[][9], Array ***possibilities, int *x, int *y)
{
	// printf("before test %d\n", possibilities[6][0]->size);
	int minOptions = 9;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == -1 && possibilities[i][j]->size == 0){
				printf("bad copy [%d,%d]\n", i, j);
				return FINISH_FAILURE;
				
				}
		
				if (board[i][j] == -1)
				{
					if (possibilities[i][j]->size == 1)
					{
						board[i][j] = possibilities[i][j]->arr[0];
						if(removePossibilitiesFromSquare(i, j, board[i][j], possibilities,board)==-1){
							return FINISH_FAILURE;
						}
						if (removePossibilitiesFromCol(i, j, board[i][j], possibilities, board) == -1)
						{
							return FINISH_FAILURE;
						}
					}
				}
		}
	
		
		
	}
	for (int b = 0; b < 9; b++)
	{
		for (int k = 0; k < 9; k++)
		{
			if (possibilities[b][k]->size >= 1 && board[b][k]==-1)
			{
				if (possibilities[b][k]->size < minOptions)
				{
					minOptions = possibilities[b][k]->size;
					*x = b;
					*y = k;
					
				}
			}
		}
	}
	

	if(minOptions==9){
		return SUCCESS_FINISH;
	}else{
		return FINISH_NOT;
	}
}

	//possibleDigits helper, basiclly runs on the whole checking logic
Array *checkParentBox(int row, int col, short arr[][9])
{
	Array *newShortArr = (Array *)malloc(sizeof(Array));
	checkMemoryAlloc(newShortArr, "momery alloc faild,line 121\n");

	//note:everytime i change it to -1 its to mark the num in the temparr as unworthy to return
	//static init arr to filter the possible digits
	int temparr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	//to check how many digits are left in the temparr after filtering
	unsigned short sizeCounter = 0;
	//%3 logic takes the location and reset it to the 3x3 box it is in
	int startRow = row - row % 3,
		startCol = col - col % 3;

	for (int k = 0; k < 3; k++)
		for (int t = 0; t < 3; t++){
			int r=k + startRow;
			int c = t + startCol;
			if (arr[r][c] == -1)
				continue;
			//test the current box of the tested location
			if (arr[r][c] == temparr[arr[r][c] - 1])
			{
				temparr[arr[r][c] - 1] = -1;
	}}
		for (int j = 0; j< 9; j++)
		{
			//checks the row of the tested location

			if (arr[j][col] == temparr[arr[j][col] - 1])
			{

				temparr[arr[j][col] - 1] = -1;
			}
			for (int t = 0; t < 9; t++)
			{

				if (arr[j][t] == -1)
					continue;
				//test the current colum of the tested locatio
				if (arr[row][t] == temparr[arr[row][t] - 1])
				{
					temparr[arr[row][t] - 1] = -1;
				}
			}
		}
		//to save the size of the current possibledigit array for the malloc
		for (int i = 0; i < 9; i++)
		{
			if (temparr[i] != -1)
			{
				sizeCounter++;
			}
		}
		

				newShortArr->size = sizeCounter;

				//note line 57
				newShortArr->arr = (short *)malloc(sizeof(short) * sizeCounter);
			
				int insertCounter = 0;
				for (int i = 0; i < 9; i++)
				{

					if (temparr[i] != -1)
					{
						//insert to the arr the worthy digits
						(newShortArr->arr)[insertCounter] = temparr[i];
						insertCounter++;
					}
		}
		return newShortArr;
	}
	//print bunch of - for the board print
	void printLine()
	{
		printf("\n");
		for (int i = 0; i < 33; i++)
		{
			printf("-");
		}
	}

	void sudokoPrintBoard(short board[][9])
	{
		//counter to keep track when to print the divders
		int slashCounter = 0, lineCounter = 0;
		printf(" :");
		for (int i = 0; i < 9; i++)
		{
			printf(" %*d", 2, i);
			if (slashCounter == 2)
			{
				printf(":");
				slashCounter = 0;
			}
			else
			{
				slashCounter++;
			}
		}
		printLine();
		printf("\n");
		for (int i = 0; i < 9; i++)
		{
			printf("%d:", i);

			for (int j = 0; j < 9; j++)
			{
				printf(" %*d", 2, board[i][j]);
				if (slashCounter == 2)
				{
					printf(":");
					slashCounter = 0;
				}
				else
				{
					slashCounter++;
				}
			}
			if (lineCounter == 2)
			{
				printLine();
				lineCounter = 0;
			}
			else
			{
				lineCounter++;
			}
			printf("\n");
		}
	}

	Array ***PossibleDigits(short sudokuBoard[][9])
	{
		Array ***PossibleDigits = (Array ***)malloc(sizeof(Array **) * 9);
		for (int i = 0; i < 9; i++)
		{
			

			PossibleDigits[i] = (Array **)malloc(sizeof(Array *) * 9);

			for (int j = 0; j < 9; j++)
			{
				if (sudokuBoard[i][j] != -1){
					PossibleDigits[i][j]= (Array *)malloc(sizeof(Array));
					PossibleDigits[i][j]->size = 0;
					continue;
				}
				else
					PossibleDigits[i][j] = checkParentBox(i, j, sudokuBoard);
	}
}
return PossibleDigits;
}

void printBoardStats(short board[][9], Array ***PossibleDigits)
{
	printf("test stats:\n");
	for (int i = 0; i < 9; i++)

		for (int j = 0; j < 9; j++)
		{
			printf("pos numer [%d,%d]:\n",i,j);
			printf("size:%d\n",PossibleDigits[i][j]->size);
			printf("possible input:");
			for (int o = 0; o < PossibleDigits[i][j]->size; o++)
			{
				printf("%d,",PossibleDigits[i][j]->arr[o]);
			}
			printf("\n");
		}
}

void showPossibilities(Array ***possibilities,int x,int y){
	printf("options for [%d,%d] are:\n",x,y);
	for (int i = 0; i < possibilities[x][y]->size ; i++)
	{

		printf("%d)%d\n", i,possibilities[x][y]->arr[i]);
	}
	printf("pick one\n");
	
}

int FillBoard(short board[][9], Array ***possibilities)
{
	int x,y;
	int pickIndex;
	int res = OneStage(board,possibilities,&x,&y);
	while(res == FINISH_NOT){
		showPossibilities(possibilities, x, y);
		scanf("%d", &pickIndex);
		board[x][y] = possibilities[x][y]->arr[pickIndex];
		if (removePossibilitiesFromSquare(x, y, board[x][y], possibilities, board) == -1)
		{
			return FINISH_FAILURE;
		}
		if (removePossibilitiesFromCol(x, y, board[x][y], possibilities, board) == -1)
		{
			return FINISH_FAILURE;
		}
		res = OneStage(board, possibilities, &x, &y);
		sudokoPrintBoard(board);
	}
	return res;
}

void main()
{
       short board[9][9] =

       { 5,-1, 4,-1, 7,-1,-1, 1,-1,

        6,-1, 2, 1,-1,-1, 3,-1,-1,

        1,-1, 8,-1, 4,-1,-1, 6,-1,

       -1, 5,-1,-1, 6,-1,-1, 2,-1,

       -1, 2,-1, 8,-1, 3,-1,-1,-1,

       -1,-1,-1,-1,-1, 4,-1, 5, 6,

       -1, 6, 1, 5, 3, 7, 2, 8, 4,

       -1, 8, 7,-1, 1, 9,-1, 3,-1,

       -1,-1,-1, 2, 8,-1,-1,-1, 9 };
	   //end should be 9

 

       Array*** possible_solutions;

 

       printf("Initial board\n");

       sudokoPrintBoard(board);

 

       printf("Press enter to start playing...\n");

       getchar();

	   possible_solutions = PossibleDigits(board);
	 
	//    printBoardStats(board, possible_solutions);
		//   printBoardStats(board, possible_solutions);

		  //some other shit i am not responsible to

		     if (FillBoard(board, possible_solutions) == -1){
				   printf("User's selections led to duplications\n");
}
// printBoardStats(board, possible_solutions);

//    else

//    {

//          sudokoPrintBoard(board);

//          printf("Board filled successfully\n");

//    }

// Don't forget to free memory!

}