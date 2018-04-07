#pragma once

#include "..\common\data.h"

typedef struct
{
	book data;
	struct listItem *next;
}listItem;

#ifdef LIST_QUEUE
typedef struct
{
	listItem * head;
	listItem * tail;
} ListDescriptor;
#else
typedef struct
{
	listItem * head;
} ListDescriptor;
#endif // LIST_QUEUE


//Прототипы

void listInit(ListDescriptor *descr);
int AddItem(ListDescriptor *descr);
void ShowList(ListDescriptor descr);
int FindItem(ListDescriptor descr);
int DeleteItem(ListDescriptor *descr);
int SaveToFile(ListDescriptor descr);
int GetFromFile(ListDescriptor *descr);
void ClearAll(ListDescriptor *descr);