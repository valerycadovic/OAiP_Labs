#pragma once

#include "data.h"

typedef struct
{
	book data;
	struct BinTreeNode *right;
	struct BinTreeNode *left;
}BinTreeNode;

typedef struct
{
	BinTreeNode *head;
}ListDescriptor;

void listInit(ListDescriptor*);
int AddItem(ListDescriptor*);
int DeleteItem(ListDescriptor*);
void ShowUsingRecursion(ListDescriptor, order);
int ShowUsingStack(ListDescriptor);
void ClearAll(ListDescriptor*);
void Demonstrate(ListDescriptor);