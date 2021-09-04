#ifndef H
#define H
#include "main.h"
#endif // !H
BOARD *initBoard()
{
	BOARD *board = (BOARD *)malloc(sizeof(BOARD));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board->coors[i][j] = -1;
		}
	}
	return board;
}

SQLNODE *initSqrNode(int row, int col, SQLNODE *prev, SQLNODE *next)
{
	SQLNODE *sqr = (SQLNODE *)malloc(sizeof(SQLNODE));
	sqr->data = (SQRCOOR *)malloc(sizeof(SQRCOOR));
	sqr->next = next;
	sqr->prev = prev;
	sqr->data->col = col;
	sqr->data->row = row;
	return sqr;
}

SQRLIST *initSqrList()
{
	SQRLIST *emptySqrList = (SQRLIST *)malloc(sizeof(SQRLIST));
	emptySqrList->head = emptySqrList->tail = initSqrNode(0, 0, NULL, NULL);
	SQLNODE *curr = emptySqrList->head;
	emptySqrList->size = 1;

	for (int i = 0; i < 9; i++)
	{
		if (i != 0)
		{
			curr->next = initSqrNode(i, 0, curr, NULL);
			curr = curr->next;
		}
		for (int j = 0; j < 9; j++)
		{
			if (i != 0 || j != 0)
			{
				curr->next = initSqrNode(i, j, curr, NULL);
				curr = curr->next;
				emptySqrList->size += 1;
			}
		}
	}
	return emptySqrList;
}

SQLNODE *randomSqr_rec(int k, SQLNODE *root)
{
	if (k <= 0)
	{
		return root;
	}
	else
	{
		return randomSqr_rec(k - 1, root->next);
	}
}



SQRCOOR *setRandomSqr(SQRLIST *sqlst, SQLNODE *root)
{
	int k = 1 + rand() % (sqlst->size);
	SQLNODE *curr = sqlst->head;
	curr = randomSqr_rec(k, curr);

	if (curr == sqlst->head)
	{
		sqlst->head = curr->next;
	}
	if (curr == sqlst->tail)
	{
		sqlst->tail = curr->prev;
	}
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	sqlst->size -= 1;

	SQRCOOR *saver = curr->data;
	free(curr);
	return saver;
}

BOARD *createBoard()
{
	
	BOARD *board = initBoard();
	int vaildSqrCount = 1 + rand() % 20;
	SQRLIST *sqlst = initSqrList();
	SQLNODE *curr = sqlst->head;
	printf("amount of good sqr %d\n", vaildSqrCount);
	board->numOfValSqr = vaildSqrCount;
	board->PossibleDigits = PossibleDigits(board->coors);
	for (int i = 0; i < vaildSqrCount; i++)
	{

		SQRCOOR *pickedCoor = setRandomSqr(sqlst, curr);

		if (board->PossibleDigits[pickedCoor->row][pickedCoor->col]->size == 0)
		{
			printf("yap its 0 [%d.%d]\n", pickedCoor->row, pickedCoor->col);
		}
		int possArrindex = rand() % (board->PossibleDigits[pickedCoor->row][pickedCoor->col]->size);
		board->coors[pickedCoor->row][pickedCoor->col] = board->PossibleDigits[pickedCoor->row][pickedCoor->col]->arr[possArrindex];
		if (updatePossibilitiesViaCoor(board->PossibleDigits, board->coors, pickedCoor->row, pickedCoor->col) == -1)
		{
			printf("faild  [%d.%d]\n", pickedCoor->row, pickedCoor->col);
			// return NULL;
		}
	}
	sudokoPrintBoard(board->coors);
	// printBoardStats(board->coors, board->PossibleDigits);

	return board;
}