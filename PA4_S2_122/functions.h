#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*
* Programmer: Konstantin Shvedov
* Class: CptS 122
* Programming Assignment: PA4
* Date: 02/10/2017
* Description: This is the header file where all the function prototypes are stored
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
typedef struct node
{
	char food[15];
	struct node *pNext;
} Node;

typedef struct data
{
	int customerNumber; // Unique identifier; starts at 1; after 24 hours should be reset to 1
	int serviceTime;
	struct Node *groceries;   // pointer to the list of groceies;
	int totalTime;     // totalTime = serviceTime + sum of serviceTimes of customers in line before this customer; units in minutes
} Data; // This memory needs to be allocated on the heap!

typedef struct queueNode
{
	Data *pData;    // The memory for Data will need to be allocated on the heap as well!

	struct queueNode *pNext;
} QueueNode;

typedef struct queue
{
	QueueNode *pHead;
	QueueNode *pTail;
} Queue;

void maincall(void);

void simulation(int mins, Queue **express, Queue **normal);

Node *random_groceries(int line);

void instFrontNode(Node **head, char cust[9][15], int pos);

Node *makegNode(char cust[9][15], int pos);

void delNode(Node **head);

int isgEmpty(Node *curr);

int grocerycount(Node *head);

QueueNode *makeNode(Data cust);

void printQueue(Queue *curr);

int isEmpty(Queue *curr);

void enqueue(Queue **que, Data cust);

void dequeue(Queue **que);

int randomtime(int line);

int numb_check(char data[50]);

//all functions bellow are simple color functions
void red(void);
void green(void);
void white(void);
void blue(void);
void pink(void);

#endif