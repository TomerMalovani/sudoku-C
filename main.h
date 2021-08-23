#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define FINISH_NOT 0
#define SUCCESS_FINISH 1
#define FINISH_FAILURE -1

typedef struct _Array
{
	short *arr;
	unsigned short size;
} Array;

Array ***PossibleDigits(short sudokuBoard[][9]);
void sudokoPrintBoard(short board[][9]);
int OneStage(short board[][9], Array ***possibilities, int *x, int *y);
Array *checkParentBox(int row, int col, short arr[][9]);
void printLine();