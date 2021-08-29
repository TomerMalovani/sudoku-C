
#define H

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

typedef struct SqrCoor
{
	short row;
	short col;
} SQRCOOR;

// -------------------------------------------------------------

typedef struct SQLnode
{
	SQRCOOR *data;
	struct SQLnode *next;
	struct SQLnode *prev;
} SQLNODE;

typedef struct SQList
{
	SQLNODE *head;
	SQLNODE *tail;
	int size;
} SQRLIST;

// -------------------------------------------------------------

typedef struct board
{
	 short   coors[9][9];
	 Array ***PossibleDigits;
} BOARD;

typedef struct Player
{
	char * name;
	BOARD * board;
} PLAYER;

//-----------------------------------------------------------------------------
typedef struct APLAYERNOD
{
	PLAYER *data;
	struct APLAYERNOD *next;
	struct APLAYERNOD *prev;
} APLAYERNOD;

typedef struct APLAYERLST
{
	APLAYERNOD *head;
	APLAYERNOD *tail;
	int size;
} APLAYERLST;


//-----------------------------------------------------------------------------
typedef struct DPLAYERNOD
{
	PLAYER * data;
	struct DPLAYERNOD *next;
	struct DPLAYERNOD *prev;
} DPLAYERNOD;

typedef struct DPLAYERLST
{
	DPLAYERNOD *head;
	DPLAYERNOD *tail;
	int size;
} DPLAYERLST;

//-----------------------------------------------------------------------------
void checkMemoryAlloc(Array *arr, char *msg);

Array ***PossibleDigits(short sudokuBoard[][9]);
int OneStage(short board[][9], Array ***possibilities, int *x, int *y);
int FillBoard(short board[][9], Array ***possibilities);
Array *checkParentBox(int row, int col, short arr[][9]);
//-----------------------------------------------------------------------------

int removeFromArr(Array *squarePoss, short size, int toRm);
int removePossibilitiesFromSquare(int row, int col, int possToRmv, Array ***possibilities, short board[][9]);
int updatePossibilitiesViaCoor(Array ***possibilities, short board[][9], int x, int y);
//-----------------------------------------------------------------------------

void sudokoPrintBoard(short board[][9]);
void printBoardStats(short board[][9], Array ***PossibleDigits);
void printLine();
void showPossibilities(Array ***possibilities, int x, int y);
//-----------------------------------------------------------------------------

SQLNODE *initSqrNode(int row, int col, SQLNODE *prev, SQLNODE *next);
SQRLIST *initSqrList();
SQLNODE *randomSqr_rec();
void printSqr_rec(SQLNODE * root);
SQRCOOR *setRandomSqr(SQRLIST * sqlst, SQLNODE * root);
BOARD *createBoard();
BOARD *initBoard();
//-----------------------------------------------------------------------------

APLAYERLST *getPlayers();
