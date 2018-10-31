#include "functions.h"
/*
* Programmer: Konstantin Shvedov
* Class: CptS 122
* Programming Assignment: PA4
* Date: 02/10/2017
* Description: This is where all the function are programmed
*/

/*
Function: void maincall(void)
Date Created : 01 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : calls the functions that make the program run the simulation and asks the user for amount of time to run
Input parameters : none
Returns : none
Precondition : Call function
Postconditions : None
*/
void maincall(void)
{
	srand(time(NULL));
	white();
	Queue *express = (Queue*)malloc(sizeof(Queue));
	Queue *normal = (Queue*)malloc(sizeof(Queue));

	express->pHead = NULL;
	express->pTail = NULL;
	normal->pHead = NULL;
	normal->pTail = NULL;
	char  sel[50];
	int choice;
	double time = 0;
	printf("Please choose number of minutes to run simulator for: ");
	gets(sel);
	while (numb_check(sel) == -1 || numb_check(sel) < 1)
	{
		printf("Invalid Input, please try again: ");
		gets(sel);
	}
	choice = atoi(sel);
	system("cls");

	clock_t before = clock();
	//Node *head = (Node*)malloc(sizeof(Node));
	//head = random_groceries(1);
	
	if (express != NULL && normal != NULL)
	{
		simulation(choice, &express, &normal);
	}
	time = (clock() - before) / 1000.00;
	white();
	printf("Simulation Complete In: %.2f seconds\n\n", time);
}

/*
Function: void simulation(int mins, Queue **express, Queue **normal)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : function that makes the whole simulation run
Input parameters : int mins, Queue **express, Queue **normal
Returns : none
Precondition : Call function
Postconditions : None
*/
void simulation(int mins, Queue **express, Queue **normal)
{
	//general variables
	int expl = 0, eL = -1 , norml = 0, nL = -1, i = 0;
	//variables for customer creation
	int timeTE = 0, timeTN = 0, customerNum = 0, gLeftExp = 0, gLeftNormal = 0, custInExp = 0, custInNorm = 0;
	Data *custDataExp = (Data*)malloc(sizeof(Data));
	Data *custDataNorm = (Data*)malloc(sizeof(Data));
	Node *gHead = (Node*)malloc(sizeof(Node));
	QueueNode *temp = (QueueNode*)malloc(sizeof(QueueNode));
	expl = randomtime(1);
	norml = randomtime(2);
	for (int time = 0; time < mins + 1; time++)
	{
		/**********************************************************/
		//Adding customers
		//and
		//Info about cutomer by min, if new one arrives, prints out there info
		/**********************************************************/
		if ((time % 1440) == 0) customerNum = 0;
		eL++;
		nL++;
		//printf("TIME: %d, Arrival: %d, Wait: %d\n", time, expl, eL);
		if (expl == eL)
		{
			customerNum++;
			/**********************************************************/
			//arrived cutomer info
				green();
				printf("NEW ARRIVAL");
				blue();
				printf(" EXPRESS LANE\n");
				green();
				printf("Customer %d has arrived in", customerNum);
				blue();
				printf(" Express Lane");
				green();
				printf(" at %d minutes\n\n", time);
				white();
			/**********************************************************/
			custDataExp->customerNumber = customerNum;
			gHead = random_groceries(1);
			custDataExp->groceries = gHead;
			custDataExp->serviceTime = grocerycount(custDataExp->groceries);
			timeTE = custDataExp->serviceTime;
			if (isEmpty(*express) == 0)
			{
				timeTE = custDataExp->serviceTime;
				temp = (*express)->pHead;
				while (temp != NULL)
				{
					timeTE += temp->pData->serviceTime;
					temp = temp->pNext;
				}
			}
			custDataExp->totalTime = timeTE;
			enqueue(express, *custDataExp);
			expl = randomtime(1);
			eL = 0;
		}
		//printf("TIME: %d, Arrival: %d, Wait: %d\n", time, norml, nL);
		if (norml == nL)
		{
			customerNum++;
			/**********************************************************/
			//arrived cutomer info
				green();
				printf("NEW ARRIVAL");
				pink();
				printf(" NORMAL LANE\n");
				green();
				printf("Customer %d has arrived in", customerNum);
				pink();
				printf(" Normal Lane");
				green();
				printf(" at %d minutes\n\n", time);
				white();
			/**********************************************************/
			custDataNorm->customerNumber = customerNum;
			gHead = random_groceries(2);
			custDataNorm->groceries = gHead;
			custDataNorm->serviceTime = grocerycount(custDataNorm->groceries);
			timeTN = custDataNorm->serviceTime;
			if (isEmpty(*normal) == 0)
			{
				timeTN = custDataNorm->serviceTime;
				temp = (*normal)->pHead;
				while (temp != NULL)
				{
					timeTN += temp->pData->serviceTime;
					temp = temp->pNext;
				}
			}
			custDataNorm->totalTime = timeTN;
			enqueue(normal, *custDataNorm);
			norml = randomtime(2);
			nL = 0;
		}
		/**********************************************************/
		//Customer out info if they leave
		/**********************************************************/
		if (gLeftExp == 1)
		{
			red();
			printf("CUSTOMER CHECKING OUT");
			blue();
			printf(" EXPRESS LANE\n");
			red();
			printf("Customer %d is checking out of", (*express)->pHead->pData->customerNumber);
			blue();
			printf(" Express Lane");
			red();
			printf(" with waiting time %d minutes\n\n", (*express)->pHead->pData->totalTime);
			white();
			dequeue(express);
			custInExp = 0;
		}
		if (gLeftNormal == 1)
		{
			red();
			printf("CUSTOMER CHECKING OUT");
			pink();
			printf(" NORMAL LANE\n");
			red();
			printf("Customer %d is checking out of", (*normal)->pHead->pData->customerNumber);
			pink();
			printf(" Normal Lane");
			red();
			printf(" with waiting time %d minutes\n\n", (*normal)->pHead->pData->totalTime);
			white();
			dequeue(normal);
			custInNorm = 0;
		}
		gLeftExp--;
		gLeftNormal--;
		//printf("EMPTY? express: %d, normal: %d\n\n", isEmpty(*express), isEmpty(*normal));
		if (custInExp == 0 && isEmpty(*express) == 0)
		{
			temp = (*express)->pHead;
			gLeftExp = temp->pData->serviceTime;
			custInExp = 1;
		}
		if (custInNorm == 0 && isEmpty(*normal) == 0)
		{
			temp = (*normal)->pHead;
			gLeftNormal = temp->pData->serviceTime;
			custInNorm = 1;
		}
		/**********************************************************/
		//10 min info print out
		/**********************************************************/
		if ((time % 10) == 0 && time != 0)
		{
			printf("\nTIME: %d mins\n", time);
			printf("***********************************************************************************\n");
			blue();
			printf("EXPRESS LANE\n");
			white();
			if (isEmpty(*express))
			{
				printf("Express Lane Is Empty\n");
			}
			else
			{
				temp = (*express)->pHead;
				i = 0;
				while (temp != NULL)
				{
					i++;
					printf("Position: %d, Customer: %d, Groceries: %d, Approximate total time in que: %d\n", i, temp->pData->customerNumber, temp->pData->serviceTime, temp->pData->totalTime);
					temp = temp->pNext;
				}
			}
			printf("***********************************************************************************");
			pink();
			printf("\nNORMAL LANE\n");
			white();
			if (isEmpty(*normal))
			{
				printf("Normal Lane is Empty\n");
			}
			else
			{
				temp = (*normal)->pHead;
				i = 0;
				while (temp != NULL)
				{
					i++;
					printf("Position: %d, Customer: %d, Groceries: %d, Approximate total time in que: %d\n", i, temp->pData->customerNumber, temp->pData->serviceTime, temp->pData->totalTime);
					temp = temp->pNext;
				}
			}
			white();
			printf("***********************************************************************************\n");
		}
		/**********************************************************/
	}
	red();
	//printQueue(*express);
	printf("SIMULATION ENDED\n");
}

/****************************************************************************************************************************/
/****************************************************Grocery functions*******************************************************/
/****************************************************************************************************************************/
/*
Function: Node *random_groceries(int line)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : randomizes the groceies into a singly linked lists
Input parameters : int line
Returns : pointer to frist node
Precondition : Call function
Postconditions : None
*/
Node *random_groceries(int line)
{
	int i = 0, j = 0, k = 0, c = 0, f = 0, *shuf;
	i = randomtime(line);
	Node *first = (Node*)malloc(sizeof(Node));
	Node *head = (Node*)malloc(sizeof(Node));
	first = head = NULL;

	char groceries[9][15];
	strcpy(groceries[0], "cereal");
	strcpy(groceries[1], "milk");
	strcpy(groceries[2], "beef");
	strcpy(groceries[3], "eggs");
	strcpy(groceries[4], "coconut milk");
	strcpy(groceries[5], "redbull");
	strcpy(groceries[6], "oyster sauce");
	strcpy(groceries[7], "olive oil");
	strcpy(groceries[8], "chili");

	//printf("Time: %d\n", i);
	shuf = (int*)calloc(i, sizeof(int));
	for (int d = 0; d < i; d++)
	{
		shuf[d] = 0;
	}
	first = head;
	j = 1;

	while (j <= i)
	{
		//printf("Number %d, Items: %d\n", j, i);
		c = 1;
		while (c == 1)
		{
			k = random(i);
			if (shuf[k - 1] == 0)
			{
				shuf[k - 1] = j;
				//printf("shuf [%d] = %d\n", k - 1, j);
				c = 0;
			}
			else
			{
				k++;
				while (k <= i)
				{
					if (shuf[k - 1] == 0)
					{
						shuf[k - 1] = j;
						c = 0;
						k = i;
					}
					else if (k == i)
					{
						k = 0;
					}
					k++;
				}
			}
		}
		j++;
	}
	j = 0;
	while (j < i)
	{
		instFrontNode(&head, groceries, shuf[j]);
		//printf("done %d, %s, %s\n", j, groceries[shuf[j]], head->food);
		j++;
	}
	return head;
}

/*
Function: void instFrontNode(Node **head, char cust[9][15], int pos)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : inserts node at front of list
Input parameters : Node **head, char cust[9][15], int pos
Returns : none
Precondition : Call function
Postconditions : None
*/
void instFrontNode(Node **head, char cust[9][15], int pos)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	//printf("%s\n", cust[pos]);
	newNode = makegNode(cust, pos);
	//printf("Food in node insert function: %s\n", newNode->food);
	if (isgEmpty(*head) == 1)
	{
		newNode->pNext = NULL;
	}
	else
	{
		newNode->pNext = *head;
	}
	(*head) = newNode;
}

/*
Function: Node *makegNode(char cust[9][15], int pos)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : makes node with grocery item
Input parameters : char cust[9][15], int pos
Returns : pointer to node
Precondition : Call function
Postconditions : None
*/
Node *makegNode(char cust[9][15], int pos)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	//printf("Food: %s\n", cust[pos]);
	strcpy(newNode->food, cust[pos]);
	//printf("Food in node: %s\n", newNode->food);
	newNode->pNext = NULL;
	return newNode;
}

/*
Function: void delNode(Node **head)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : deletes node
Input parameters : Node **head
Returns : None
Precondition : Call function
Postconditions : None
*/
void delNode(Node **head)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode = *head;
	*head = (*head)->pNext;
	free(newNode);
}

/*
Function: int isgEmpty(Node *curr)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : checks if node is empty = NULL
Input parameters : Node *curr
Returns : int
Precondition : Call function
Postconditions : None
*/
int isgEmpty(Node *curr)
{
	if (curr == NULL)
	{
		return 1;
	}
	else return 0;
}

/*
Function: int grocerycount(Node *head)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : counts amount of groceries in singly linked list and returns the value
Input parameters : Node *head
Returns : int
Precondition : Call function
Postconditions : None
*/
int grocerycount(Node *head)
{
	Node *temp = (Node*)malloc(sizeof(Node));
	temp = head;
	int i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->pNext;
	}
	return i;
}
/****************************************************************************************************************************/
/****************************************************Queue Functions********************************************************/
/****************************************************************************************************************************/

/*
Function: QueueNode *makeNode(Data cust)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : makes a node for the que, one node, one customer
Input parameters : Data cust
Returns : pointer to QueueNode
Precondition : Call function
Postconditions : None
*/
QueueNode *makeNode(Data cust)
{
	QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
	Data *data = (Data*)malloc(sizeof(Data));
	if (newNode != NULL)
	{
		data->customerNumber = cust.customerNumber;
		data->serviceTime = cust.serviceTime;
		data->groceries = cust.groceries;
		data->totalTime = cust.totalTime;
		newNode->pNext = NULL;
		newNode->pData = data;
	}
	return newNode;
}

/*
Function: void printQueue(Queue *curr)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : prints out the queue recursively
Input parameters : Queue *curr
Returns : None
Precondition : Call function
Postconditions : None
*/
void printQueue(Queue *curr)
{
	if (curr->pHead->pNext == NULL)
	{
		printf("Customer Number: %d\n Service Time: %d\n Total Time: %d\n\n", curr->pHead->pData->customerNumber, grocerycount(curr->pHead->pData->groceries), curr->pHead->pData->totalTime);
		red();
		printf("End of List");
		white();
		return;
	}
	else
	{
		printf("Customer Number: %d\n Service Time: %d\n Total Time: %d\n\n", curr->pHead->pData->customerNumber, grocerycount(curr->pHead->pData->groceries), curr->pHead->pData->totalTime);
		curr->pHead = curr->pHead->pNext;
		printQueue(curr);
	}
}

/*
Function: int isEmpty(Queue *curr)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : checks if Queue is empty
Input parameters : Queue *curr
Returns : int
Precondition : Call function
Postconditions : None
*/
int isEmpty(Queue *curr)
{
	if (curr->pHead == NULL)
	{
		return 1;
	}
	else return 0;
}

/*
Function: void enqueue(Queue **que, Data cust)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : enqueue node at end of queue
Input parameters : Queue **que, Data cust
Returns : None
Precondition : Call function
Postconditions : None
*/
void enqueue(Queue **que, Data cust)
{
	QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
	newNode = makeNode(cust);
	if (isEmpty(*que) == 1)
	{
		(*que)->pHead = newNode;
	}
	else
	{
		(*que)->pTail->pNext = newNode;
	}
	(*que)->pTail = newNode;
	newNode->pNext = NULL;
}

/*
Function: void enqueue(Queue **que)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : deques from front of list
Input parameters : Queue **que
Returns : None
Precondition : Call function
Postconditions : None
*/
void dequeue(Queue **que)
{
	if (!isEmpty(*que))
	{
		QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
		newNode = (*que)->pHead;
		(*que)->pHead = newNode->pNext;
		free(newNode);
	}
}

/*
Function: int randomtime(int line)
Date Created : 03 / 10 / 2017
Date Last Modified : 05 / 10 / 2017
Description : makes random numbers of 1-5 or 3-8 depending if its express line or normal line respectively
Input parameters : int line
Returns : int
Precondition : Call function
Postconditions : None
*/
int randomtime(int line)
{
	int i;
	i = (rand() % 5) + 1;
	if (line == 1)
	{
		return i;
	}
	else return i + 3;
}

/*
Function: int random(int n)
Date Created : 22 / 09 / 2017
Date Last Modified : 05 / 10 / 2017
Description : makes random numbers from 1 to n
Input parameters : int n
Returns : int
Precondition : Call function
Postconditions : None
*/
int random(int n)
{
	return (rand() % n) + 1;
}

/*
Function: int numb_check(char data[50])
Date Created : 22/09/2017
Date Last Modified : 22/09/2017
Description : checks if its a number
Input parameters : char data[50]
Returns : -1 if not int and the actual value if true
Precondition : Call function
Postconditions : None
*/
int numb_check(char data[50])
{
	if (data[0] == 0)
	{
		return 0;
	}
	else if (atoi(data) == 0)
	{
		printf("Invalid Input, supposed to be a number value\n");
		return -1;
	}
	else
	{
		return atoi(data);
	}
}

/****************************************************************************************************************************/
/****************************************************Colour Functions********************************************************/
/****************************************************************************************************************************/
/*
Function: void red(void)
Date Created : 05/04/2017
Date Last Modified : 02/10/2017
Description : changes text color to red
Input parameters : NONE
Returns : NONE
Precondition : Call function
Postconditions : None
*/
void red(void)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
}

/*
Function: void green(void)
Date Created : 05/04/2017
Date Last Modified : 02/10/2017
Description : changes text color to green
Input parameters : NONE
Returns : NONE
Precondition : Call function
Postconditions : None
*/
void green(void)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
}

/*
Function: void white(void)
Date Created : 05/04/2017
Date Last Modified : 02/10/2017
Description : changes text color to white
Input parameters : NONE
Returns : NONE
Precondition : Call function
Postconditions : None
*/
void white(void)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
}

/*
Function: void blue(void)
Date Created : 05/04/2017
Date Last Modified : 02/10/2017
Description : changes text color to blue
Input parameters : NONE
Returns : NONE
Precondition : Call function
Postconditions : None
*/
void blue(void)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9);
}

/*
Function: void pink(void)
Date Created : 05/04/2017
Date Last Modified : 02/10/2017
Description : changes text color to pink
Input parameters : NONE
Returns : NONE
Precondition : Call function
Postconditions : None
*/
void pink(void)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 13);
}
/****************************************************************************************************************************/