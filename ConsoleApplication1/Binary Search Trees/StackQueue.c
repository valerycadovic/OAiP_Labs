#include "stack_queue.h"


int AddToStack(Stack* Item, BinTreeNode* Node)//функция добавления элемента в вершишу стека: s.push();
{

	//создаём элемент
	listItem *temp = (listItem*)malloc(sizeof(listItem));
	if (!temp)
	{
		puts("Allocation Error!");
		return 0;
	}

	temp->Node = Node;//заполняем
	temp->next = Item->head;//ставим в вершину стека
	Item->head = temp;//делаем новой вершиной
}

BinTreeNode *pop(Stack* Item)// s.pop() - читаем вершину стека и удаляем её
{
	//создаём узел дерева
	BinTreeNode *temp;
	temp = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (!temp)
	{
		puts("Allocation Error");
		return NULL;
	}

	//указатель на удаляемый элемент
	listItem *TakeOff = Item->head;

	temp = Item->head->Node;//заполняем узел
	Item->head = Item->head->next;//смещаем вершину вниз
	free(TakeOff);//удаляем вершину

				  //возвращаем вершину
	return temp;
}


void freeList(listItem* item) //recursive delete
{
	if (item)
	{ //if an element exists
		freeList(item->next); //go deeper (to the stack bottom)
		free(item); //free elements from bottom to the top
	}
}

void ClearStack(Stack* item)
{
	freeList(item->head);
}

//-----------------------QUEUE-----------------------------------------//
/*
int Enqueue(Queue *Item, BinTreeNode *Node)
{
	listItem *temp = (listItem*)malloc(sizeof(listItem));
	if (!temp)
	{
		puts("Allocation error!");
		return 0;
	}

	if (!Item->head)//если нет головы, т.е. очередь пуста, то просто добавляем элемент
	{
		Item->head = (listItem*)malloc(sizeof(listItem));//выделяем память под голову
		if (!Item->head)
		{
			puts("error");
			return 0;
		}
		Item->tail = Item->head;//устанавливаем хвост на голову, т.к. сейчас они должны совпадать
		temp = Item->tail;//временный хвост также кидаем на добавленный элемент, чтобы после задать ему значение
	}
	else//если очередь уже не пуста, работаем со вспомогательным хвостом
	{
		temp = (listItem*)malloc(sizeof(listItem));//создаем за этим указателем элемент
		if (!temp)
		{
			puts("error tail");
			return 0;
		}

		Item->tail->next = temp;//указатель с прошлого элемета помещаем на вновь созданный
		Item->tail = temp;//и делаем его хвостом очереди
	}

	temp->Node = Node;
	Item->tail->next = NULL;
	return 1;
}

void ClearQueue(Queue *Item)
{
	listItem *temp = Item->head;
	while (Item->head != Item->tail)//пока голова не станет хвостом
	{
		Item->head = Item->head->next;//двигаемся
		free(temp->Node);
		free(temp);//удаляем
		temp = Item->head;//ставим следующий элемент на позицию удаления
	}

	if (Item->tail)
	{
		free(Item->tail);//очищаем последний элемент
	}
}

BinTreeNode *Dequeue(Queue *Item)
{
	BinTreeNode *temp;
	temp = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (!temp)
	{
		puts("Allocation Error");
		return NULL;
	}

	listItem *RemoveKebab = Item->head;
	temp = Item->head->Node;
	Item->head = Item->head->next;

	free(RemoveKebab);
	return temp;
}
*/