//47 till infinity
#include "main.h"
#include "board_funcs.c"

// #include "board_funcs.c"
//TO DO LIST
//GET SHIT TO OTHER FILES,MAKE IT NICE LOOKING  []
//MEMORY ALLOCTAION TESTS                       []
//REMOVE USLESS PRINTF                          []
//ADD DEFINE VAR TO PRINT EXTRA STUFF LIKE STATS[]
//RE-THINK YOU LIFE DECISIONS THAT GOT YOU HERE []
//FINISH THE GOD DAMN THING                     []

void checkMemoryAlloc(void *ptr)
{
	if(ptr==NULL){
		puts("Memory Error\n");
		exit(1);
	}
}

int removeFromArr(Array *squarePoss, short size, int toRm)
{
	int index=-1;
	for (int i = 0; i < size; i++)
		if (squarePoss->arr[i] == toRm){	
			index=i;
			break;
	}
	if(index!=-1){
		for (int j = index; j < squarePoss->size; j++)
		{
			squarePoss->arr[j] = squarePoss->arr[j + 1];
		}
		// int newSize = size > 0 ? squarePoss->size - 1 : 0;
		int newSize = squarePoss->size - 1 ;
		squarePoss->arr = (short *)realloc(squarePoss->arr, newSize * sizeof(short));
		squarePoss->size= newSize;
	}else{
		return -1;
	}
}

int removePossibilitiesFromSquare(int row, int col, int possToRmv, Array ***possibilities,short board[][9])
{
	for (int k =  0; k < 3; k++)
	{
		for (int t = 0; t < 3; t++)
		{
			int startRow = row - row % 3,
				startCol = col - col % 3;
			int r = k + startRow;
			int c = t + startCol;
			if(board[r][c] == possToRmv && (r!=row || c!=col)){
				printf("org [%d,%d] bad copy [%d,%d]\n",row,col,r,c); 
				return -1;
			}
			if ((possibilities[r][c]->size) > 0)
				removeFromArr(possibilities[r][c], possibilities[r][c]->size, possToRmv);
		}
	}
	return 0;
}

int removePossibilitiesFromCol(int row, int col, int possToRmv, Array ***possibilities, short board[][9])
{
	for (int k = 0; k < 9; k++)
	{
		if (board[k][col] == possToRmv && k != row){
			return -1;
		}
			//remove bad numbers from all items in row
			if (possibilities[k][col]->size != 0)
				removeFromArr(possibilities[k][col], possibilities[k][col]->size, possToRmv);
		
	}
	for (int t = 0; t < 9; t++)
	{
		if (board[row][t] == possToRmv && t != col)
		{
			return -1;
		}
		//remove bad numbers from all items in col
		if (possibilities[row][t]->size != 0)
			removeFromArr(possibilities[row][t], possibilities[row][t]->size, possToRmv);
	}
	return 0;
}

int OneStage(short board[][9], Array ***possibilities, int *x, int *y)
{
	
	int minOptions = 9;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == -1 && possibilities[i][j]->size == 0){
				printf("dead spot [%d,%d]\n", i, j);
				return FINISH_FAILURE;
				}
		
				if (board[i][j] == -1)
				{
				
					if (possibilities[i][j]->size == 1)
					{
						board[i][j] = possibilities[i][j]->arr[0];
						updatePossibilitiesViaCoor(possibilities,board,i,j);
						break;
					}
				}
		}
	
	}
	for (int b = 0; b < 9; b++)
		for (int k = 0; k < 9; k++)
			if (possibilities[b][k]->size >= 1 && board[b][k]==-1)
				if (possibilities[b][k]->size < minOptions)
				{
					minOptions = possibilities[b][k]->size;
					*x = b;
					*y = k;	
				}

	if (minOptions == 9)
		return SUCCESS_FINISH;
	else
		return FINISH_NOT;
}

	//possibleDigits helper, basiclly runs on the whole checking logic
Array *checkParentBox(int row, int col, short arr[][9])
{
	Array *newShortArr = (Array *)malloc(sizeof(Array));
	checkMemoryAlloc(newShortArr);

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
				if (board[i][j] == -1)
					printf(" %*c", 2, ' ');
				else
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

int updatePossibilitiesViaCoor(Array ***possibilities,short board[][9],int x,int y){
	if (removePossibilitiesFromSquare(x, y, board[x][y], possibilities, board) == -1)
	{
		return FINISH_FAILURE;
	}
	else if (removePossibilitiesFromCol(x, y, board[x][y], possibilities, board) == -1)
	{
		return FINISH_FAILURE;
	}
	else{
		return 0;
	}
}

int FillBoard(short board[][9], Array ***possibilities)
{
	int x,y;
	int pickIndex;
	bool inputFlag = false;
	int res = OneStage(board,possibilities,&x,&y);
	while(res == FINISH_NOT){
		while (!inputFlag)
		{
			showPossibilities(possibilities, x, y);
			scanf("%d", &pickIndex);
			if (pickIndex < 0 || pickIndex > possibilities[x][y]->size)
				printf( "UNVAILD INPUT\n");
			else
				inputFlag = true;
		}
		board[x][y] = possibilities[x][y]->arr[pickIndex];
		inputFlag = false;
		updatePossibilitiesViaCoor(possibilities,board,x,y);
		res = OneStage(board, possibilities, &x, &y);
		sudokoPrintBoard(board);
	}
	return res;
}

APLAYERLST *initPlayerList(int playerAmount)
{
	APLAYERLST *newPlayerList = (APLAYERLST *)malloc(sizeof(APLAYERLST));
	newPlayerList->head = newPlayerList->tail = NULL;
	newPlayerList->size = playerAmount;
}
bool isEmptyWDList(WPLAYERLST *lst)
{

	return (lst->head == NULL && lst->tail == NULL);
}


int isEmptyList(APLAYERLST *lst)
{
	if (lst->head == NULL)
		return 1;
	else
		return 0;
}

void insertNodeToEndDList(APLAYERLST *lst, APLAYERNOD *tail)
{
	if (isEmptyList(lst)==1)
	{
		tail->next = tail->prev = NULL;
		lst->head = lst->tail = tail;
	}
	else
	{

		tail->prev = lst->tail;
		tail->next = NULL;
		lst->tail->next = tail;
		lst->tail = tail;
	}
}



APLAYERNOD *createNewAPlayerListNode(PLAYER * data, APLAYERNOD *next, APLAYERNOD *prev)
{
	APLAYERNOD *res;
	res = (APLAYERNOD *)malloc(sizeof(APLAYERNOD));
	res->data = data;
	res->next = next;
	res->prev = prev;
	return res;
}


void insertDataToActivePlayerEndDList(APLAYERLST *lst, PLAYER *data)
{
	APLAYERNOD *newTail;
	newTail = createNewAPlayerListNode(data, NULL, NULL);
	insertNodeToEndDList(lst, newTail);
}

APLAYERLST *getPlayers()
{
	char line[100];
	int playerAmount;
	printf("how many players are we talking about?");
	scanf("%d", &playerAmount);
	printf("press enter when ready to name the players\n");
	getchar();
	APLAYERLST *newPlayerList = initPlayerList(playerAmount);
	for (int i = 0; i < playerAmount; i++)
	{
		printf("name of player %d?\n", i + 1);
		gets(line);
		PLAYER *newPlayer = (PLAYER *)malloc(sizeof(PLAYER));
		newPlayer->name = strdup(line);
		newPlayer->board = createBoard();
		insertDataToActivePlayerEndDList(newPlayerList, newPlayer);
		}
		return newPlayerList;
	}


	void freeTreeHelper(PLAYER_TREE_NODE *node)
	{
		if (node != NULL)
		{
			freeTreeHelper(node->left);
			freeTreeHelper(node->right);
			free(node);
		}
	}
	void freeTree(PLAYER_TREE tr)
	{
		freeTreeHelper(tr.root);
	}
	void checkMemory(void *ptr)
	{
		if (ptr == NULL)
		{
			puts("Memory Error\n");
			exit(1);
		}
	}

	void merge(APLAYERNOD ** Arr, int start, int mid, int end)
	{
		static int count=0;
		APLAYERNOD **temp = (APLAYERNOD **)malloc(sizeof(APLAYERNOD *)*(end-start+1));
		int i = start, j = mid + 1, k = 0;
		while (i <= mid && j <= end)
		{
			if (Arr[i]->data->board->numOfValSqr <= Arr[j]->data->board->numOfValSqr)
			{
				if (Arr[j]->data->board->numOfValSqr == Arr[i]->data->board->numOfValSqr){
					//lexi sort !! right now only dectet first letter  
					if(strcmp(Arr[i]->data->name, Arr[j]->data->name) <= 0){
						temp[k] = Arr[i];
						k += 1;
						i += 1;
					}else{
						temp[k] = Arr[j];
						k += 1;
						j += 1;
					}
				}else{
					temp[k] = Arr[i];
					k += 1;
					i += 1;
				}	
			}
			else
			{
				temp[k] = Arr[j];
				k += 1;
				j += 1;
			}
		}
		while (i <= mid)
		{
			temp[k] = Arr[i];
			k += 1;
			i += 1;
		}
		while (j <= end)
		{
			temp[k] = Arr[j];
			k += 1;
			j += 1;
		}
		for (i = start; i <= end; i ++)
		{
			Arr[i] = temp[i-start];
		}
		free(temp);
	}

void mergeSortPlayers(APLAYERNOD **playerArr, int start, int end)
		{
			if (start == end)
				return;
			else
			{
				int mid = (start + end) / 2;
				mergeSortPlayers(playerArr, start, mid);
				mergeSortPlayers(playerArr, mid +1, end);
				merge(playerArr, start, mid, end);
			}
		}

		APLAYERNOD **arrayFromList(APLAYERLST * root,int*size)
		{
			int len = root->size;
			APLAYERNOD *curr = root->head;
			APLAYERNOD **playerArr = (APLAYERNOD **)malloc(sizeof(APLAYERNOD *) * len);
			for (int i = 0; i < len; i++)
			{
				playerArr[i] = curr;
				curr = curr->next;
			}
			

			mergeSortPlayers(playerArr, 0, len-1);
			int newSize =len;
			if (!(log2f(len + 1) == ceil(log2f(len + 1)))) //if its not the perfect size
			{
				newSize = (int)pow(2, ceil(log2f(len + 1))) - 1;
			}
				if (newSize > len)
				{
					// printf("new size %d\n", newSize);

					playerArr = (APLAYERNOD **)realloc(playerArr, sizeof(APLAYERNOD *) * newSize);

					for (int i = len; i < newSize; i++)
					{
						playerArr[i] = NULL;
					}
					*size = newSize;
				}
				else
					*size = len;

				return playerArr;
			}


		void removeActivePlayerFromList(APLAYERNOD *curr, APLAYERLST *lst)
		{
			APLAYERNOD *saver;
			saver = lst->head;
			if (lst->head == NULL){
				lst->head = lst->tail = NULL;}
			else if (lst->head == curr && lst->tail == curr)
			{
				free(lst->head);
				free(lst->tail);
				free(lst);
				return;
			}
			else if (lst->head == curr)
			{
				lst->head = curr->next;
				lst->head->prev = NULL;
			}
			else if (lst->tail == curr) 
			{
				lst->tail = lst->tail->prev;
				lst->tail->next = NULL;
			}
			else
			{
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
			}
			lst->size =lst->size-1;
			free(curr);
			return;
		}

		void gameFlowInOrder_rec(PLAYER_TREE_NODE *t, APLAYERLST *lst, APLAYERLST *winningPlayersList)
		{	

			if (t == NULL || lst->size == 0){ 
				return;
				}
			gameFlowInOrder_rec(t->left, lst, winningPlayersList);
			if (t->data != NULL)
			{
				printf("%s! its your turn!! \n",t->data->data->name);
				int step = FillBoard(t->data->data->board->coors, t->data->data->board->PossibleDigits);

				if (step == FINISH_FAILURE)
				{
					printf( "Sorry but %s just lost and out!\n" , t->data->data->name);
					removeActivePlayerFromList(t->data, lst);
					t->data=NULL;
				}
				else if(step == SUCCESS_FINISH){
					printf( "congrats %s! you won!\n", t->data->data->name);
					removeActivePlayerFromList(t->data, lst);
					insertNodeToEndDList(winningPlayersList, t->data);
					winningPlayersList->size = winningPlayersList->size + 1;
				}
				}
					gameFlowInOrder_rec(t->right, lst, winningPlayersList);
		}

		void freeList(APLAYERLST *lst)
		{
			APLAYERNOD *current;
			current = lst->head;
			while (current != NULL)
			{
				APLAYERNOD * next = current->next;
				free(current->prev);
				free(current->next);
				free(current->data);
				free(current);
				current = next;
			}
			lst->head = NULL;
			lst->tail = NULL;
		}

		PLAYER_TREE BuildTreeFromArray(APLAYERNOD **arr, int size)
		{
			PLAYER_TREE resTree;
			PLAYER_TREE left;
			PLAYER_TREE right;
			int halfSize;
			resTree.root = (PLAYER_TREE_NODE *)malloc(sizeof(PLAYER_TREE_NODE));
			checkMemoryAlloc(resTree.root);
			if (size == 1)
			{
				resTree.root->data = arr[0];
				resTree.root->left = NULL;
				resTree.root->right = NULL;
			}
			else
			{ 
				halfSize = size / 2;
				resTree.root->data = arr[halfSize];
				if (arr[halfSize / 2] != NULL)
				{ 
					left = BuildTreeFromArray(arr, halfSize);
					resTree.root->left = left.root;
				}
				else
				{
					resTree.root->left = NULL;
				}
				if (arr[halfSize + (halfSize / 2) + 1] != NULL)
				{ 
					right = BuildTreeFromArray(arr + halfSize + 1, halfSize);
					resTree.root->right = right.root;
				}
				else
				{
					resTree.root->right = NULL;
				}
			}
			return resTree;
		}
		void printForReal(PLAYER_TREE_NODE * curr)
		{
			if(curr== NULL){
				printf("\nNULL\n");
				return;}
			else{
				printf("<-\n");
				printForReal(curr->left);
				printf("\ncurr %s\n",curr->data != NULL ? curr->data->data->name : "NULL");
				printf("->\n");
					printForReal(curr->right);
			}
		}

			void main()
		{
			srand(time(NULL));
			APLAYERLST *activePlayersList = getPlayers();
			APLAYERLST *winningPlayersList = (APLAYERLST *)malloc(sizeof(APLAYERLST));
			winningPlayersList->head = winningPlayersList->tail= NULL;
			winningPlayersList->size = 0;
			int arrSize;
			APLAYERNOD **ActivePlayersPtrArr = arrayFromList(activePlayersList, &arrSize);
			PLAYER_TREE ActivePlayerTree = BuildTreeFromArray(ActivePlayersPtrArr, arrSize);
			gameFlowInOrder_rec(ActivePlayerTree.root, activePlayersList, winningPlayersList);
			if (winningPlayersList->size>0){
				printf("winners list!\n");
				APLAYERNOD *curr = winningPlayersList->head;

				for (int i = 0; i < winningPlayersList->size; i++)
				{
					printf("name: %s\n", curr->data->name);
					printf("%s's board\n", curr->data->name);
					sudokoPrintBoard(curr->data->board->coors);
					curr = curr->next;
			}
			}else{
				printf( "NO ONE WON,THATS A SHAME.." );
			}
			//    getchar();
			freeTree(ActivePlayerTree);
			free(activePlayersList);
			free(winningPlayersList);
			free(ActivePlayersPtrArr);
			// Don't forget to free memory!
		}