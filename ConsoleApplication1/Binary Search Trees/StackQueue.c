#include "stack_queue.h"


int AddToStack(Stack* Item, BinTreeNode* Node)//������� ���������� �������� � ������� �����: s.push();
{

	//������ �������
	listItem *temp = (listItem*)malloc(sizeof(listItem));
	if (!temp)
	{
		puts("Allocation Error!");
		return 0;
	}

	temp->Node = Node;//���������
	temp->next = Item->head;//������ � ������� �����
	Item->head = temp;//������ ����� ��������
}

BinTreeNode *pop(Stack* Item)// s.pop() - ������ ������� ����� � ������� �
{
	//������ ���� ������
	BinTreeNode *temp;
	temp = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (!temp)
	{
		puts("Allocation Error");
		return NULL;
	}

	//��������� �� ��������� �������
	listItem *TakeOff = Item->head;

	temp = Item->head->Node;//��������� ����
	Item->head = Item->head->next;//������� ������� ����
	free(TakeOff);//������� �������

				  //���������� �������
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

	if (!Item->head)//���� ��� ������, �.�. ������� �����, �� ������ ��������� �������
	{
		Item->head = (listItem*)malloc(sizeof(listItem));//�������� ������ ��� ������
		if (!Item->head)
		{
			puts("error");
			return 0;
		}
		Item->tail = Item->head;//������������� ����� �� ������, �.�. ������ ��� ������ ���������
		temp = Item->tail;//��������� ����� ����� ������ �� ����������� �������, ����� ����� ������ ��� ��������
	}
	else//���� ������� ��� �� �����, �������� �� ��������������� �������
	{
		temp = (listItem*)malloc(sizeof(listItem));//������� �� ���� ���������� �������
		if (!temp)
		{
			puts("error tail");
			return 0;
		}

		Item->tail->next = temp;//��������� � �������� ������� �������� �� ����� ���������
		Item->tail = temp;//� ������ ��� ������� �������
	}

	temp->Node = Node;
	Item->tail->next = NULL;
	return 1;
}

void ClearQueue(Queue *Item)
{
	listItem *temp = Item->head;
	while (Item->head != Item->tail)//���� ������ �� ������ �������
	{
		Item->head = Item->head->next;//���������
		free(temp->Node);
		free(temp);//�������
		temp = Item->head;//������ ��������� ������� �� ������� ��������
	}

	if (Item->tail)
	{
		free(Item->tail);//������� ��������� �������
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