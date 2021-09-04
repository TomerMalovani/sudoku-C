 // Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004 12

#endif

#define H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define FINISH_NOT 0
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"

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
	 int numOfValSqr;
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


//==============================================================================
typedef struct WPLAYERNOD
{
	PLAYER *data;
	struct WPLAYERNOD *next;
	struct WPLAYERNOD *prev;
} WPLAYERNOD;

typedef struct WPLAYERLST
{
	WPLAYERNOD *head;
	WPLAYERNOD *tail;
	int size;
} WPLAYERLST;

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
typedef struct PlayerTreeNode
{
	APLAYERNOD *data;
	struct PlayerTreeNode *right;
	struct PlayerTreeNode *left;
} PLAYER_TREE_NODE;

typedef struct PlayerTree
{
	PLAYER_TREE_NODE * root;
	int size;
} PLAYER_TREE;

//-----------------------------------------------------------------------------

void checkMemoryAlloc(void *arr);
void freeTreeHelper(PLAYER_TREE_NODE *node);
void freeTree(PLAYER_TREE tr);

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

//============================================================================
void insertDataToActivePlayerEndDList(APLAYERLST *lst, PLAYER *data);
void insertNodeToEndDList(APLAYERLST *lst, APLAYERNOD *tail);
int isEmptyList(APLAYERLST *lst);
APLAYERNOD *createNewAPlayerListNode(PLAYER *data, APLAYERNOD *next, APLAYERNOD *prev);
APLAYERNOD **arrayFromList(APLAYERLST *root, int *size);

//-----------------------------------------------------------------------------
void merge(APLAYERNOD **Arr, int start, int mid, int end);
void mergeSortPlayers(APLAYERNOD **playerArr, int start, int end);

//------------------------------
void removeActivePlayerFromList(APLAYERNOD *curr, APLAYERLST *lst);
void gameFlowInOrder_rec(PLAYER_TREE_NODE *t, APLAYERLST *lst, APLAYERLST *winningPlayersList);
