//47 till infinity

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//notice me! the short * arr should get by with & so it can change propley, shit is broken  with out that
//סעיף ב' שבור כי לא מצליח לעדכן את המערך של האפשרויות אחרי ההורדה, אנסה שוב מחר

typedef struct _Array
{
	short *arr;
	unsigned short size;
} Array;

Array ***PossibleDigits(short sudokuBoard[][9]);
void sudokoPrintBoard(short board[][9]);
int OneStage(short board[][9], Array ***possibilities,int *x, int *y);
Array *checkParentBox(int row, int col, short arr[][9]);
void printLine();

int removeFromArr(short *arr,short size,int toRm){
	int index=-1;
	for (int i = 0; i < size; i++)
	{
		if(arr[i]==toRm){
			index=i;
		}
	}
	if(index!=-1){
		for (int j = index; j < size; j++)
		{
			arr[j]=arr[j+1];
			
		}

		arr = (short *)realloc(arr, (size - 1) * sizeof(int));
		printf("test %d")
	}else{
		return -1;
	}
	return size-1;
}

void removePossibilitiesFromSquare(int row, int col, int possToRmv, Array ***possibilities)
{
	for (int r = row - (row % 3); r < 3; r++)
	{
		for (int c = col - (col % 3); c < 3; c++)
		{
			possibilities[r][c]->size = removeFromArr(possibilities[r][c]->arr, possibilities[r][c]->size, possToRmv);
		}
	}
}

void removePossibilitiesFromCol(int col, int possToRmv, Array ***possibilities){	
		for (int r =0; r < 9; r++)
		{
			
			possibilities[r][col]->size= removeFromArr(possibilities[r][col]->arr, possibilities[r][col]->size, possToRmv);
		}
}

int OneStage(short board[][9], Array ***possibilities, int *x, int *y)
{
	printf("before test %d\n", possibilities[3][0]->size);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if(board[i][j]==-1){
				if(possibilities[i][j]->size==1){
					board[i][j] = possibilities[i][j]->arr[0];
					removePossibilitiesFromSquare(i, j, board[i][j], possibilities);
					// removePossibilitiesFromCol(j,board[i][j],possibilities);

				}
			}
		}
		
	}

	printf("after test %d\n", possibilities[3][0]->size);
		sudokoPrintBoard(board);
}

	//possibleDigits helper, basiclly runs on the whole checking logic
	Array *checkParentBox(int row, int col, short arr[][9])
{

		//note:everytime i change it to -1 its to mark the num in the temparr as unworthy to return
		//static init arr to filter the possible digits
		int temparr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		//to check how many digits are left in the temparr after filtering
		int sizeCounter = 0;
		//%3 logic takes the location and reset it to the 3x3 box it is in
		for (int k = row - (row % 3); k < 3; k++)
		{
			for (int t = col - (col % 3); t < 3; t++)
			{
				if (arr[k][t] == -1)
					continue;
				//test the current box of the tested location
				if (arr[k][t] == temparr[arr[k][t] - 1])
				{
					temparr[arr[k][t] - 1] = -1;
				}
			}
		}
		for (int k = 0; k < 9; k++)
		{
			//checks the row of the tested location
			if (arr[k][col] == temparr[arr[k][col] - 1])
			{
				temparr[arr[k][col] - 1] = -1;
			}
			for (int t = 0; t < 9; t++)
			{
				if (arr[k][t] == -1)
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

		Array *newShortArr = (Array *)malloc(sizeof(Array));
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
				if (sudokuBoard[i][j] != -1)
					continue;
				else{
				//get the array from the helper function
				Array *pointPossibleDig = checkParentBox(i, j, sudokuBoard);
				//put the array in the right spot 
				PossibleDigits[i][j] = pointPossibleDig;
				//just to check the possibledigits array is holding the right values
				for (int o = 0; o < PossibleDigits[i][j]->size;o++)
				{
					printf("[%d,%d] %d \n", i, j, PossibleDigits[i][j]->arr[o]);
				}
				
			}
			
	}
	
}


return PossibleDigits;
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

 

       Array*** possible_solutions;

 

       printf("Initial board\n");

       sudokoPrintBoard(board);

 

       printf("Press enter to start playing...\n");

       getchar();

       possible_solutions = PossibleDigits(board);
	   int x,y;

	   OneStage(board, possible_solutions,&x,&y);

	   //some other shit i am not responsible to

	   //    if (FillBoard(board, possible_solutions) == -1)

	   //          printf("User's selections led to duplications\n");

	   //    else

	   //    {

	   //          sudokoPrintBoard(board);

	   //          printf("Board filled successfully\n");

	   //    }

 

       // Don't forget to free memory!

}