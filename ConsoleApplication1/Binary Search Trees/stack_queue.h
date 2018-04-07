#pragma once
#include "list.h"

typedef struct
{
	BinTreeNode *Node;
	struct listItem *next;
}listItem;

typedef struct
{
	listItem* head;
}Stack;

typedef struct
{
	listItem *head;
	listItem *tail;
}Queue;

//for stack
int AddToStack(Stack* Item, BinTreeNode* Node);
BinTreeNode *pop(Stack* Item);
void freeList(listItem* item);
void ClearStack(Stack* item);
//for queue
/*
int Enqueue(Queue *Item, BinTreeNode *Node);
void ClearQueue(Queue *Item);
BinTreeNode *Dequeue(Queue *Item);*/