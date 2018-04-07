#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "..\common\data.h"
#include "..\common\list.h"

#pragma warning(disable : 4996)
#pragma warning(disable : 4133)
#pragma warning(disable : 4013)

#define STRSIZE 100


void listInit(ListDescriptor *descr)
{
	descr->head = NULL;
}


int AddItem(ListDescriptor *descr)
{
	listItem *temp; //������ ��������� ���������, ����� �� �������� ��������� �� ������
	temp = descr->head; //�������� ��� � ������ �����
	listItem *head;//������ ��������� ��������� �� �������, ������� ����� ����� �������� � ����

	head = (listItem*)malloc(sizeof(listItem));//������ �������
	if (!head)
	{
		puts("Memory allocation error. The Item did not added");
		return 0;
	}


	if (!setInfo(&head->data))//���������
	{
		free(head);
		puts("Information did not introduced in correct way");
		return 0;
	}

	descr->head = head;//������������ ��������� �� ������ ����� �� ����� �������
	head->next = temp;//"����������" ����� ������ �� ������
	return 1;
}


void ShowList(ListDescriptor descr)
{
//	puts("Information");

	if (!descr.head)//���� ������ ����� - ����, �� ���� - ����.
	{
		puts("Empty!");
		return;
	}

	while (descr.head)//���� �� ��������� �� ����
	{
		showInfo(descr.head);//���������� ���������� �������� ��������
		descr.head = descr.head->next;//��������� �� �����
	}
}


int DeleteItem(ListDescriptor *descr)
{
	int RemoveKebab, Current = 0, k;

	printf("Enter number of element to remove: ");
	do
	{
		rewind(stdin);
		k = scanf("%d", &RemoveKebab);
	} while (!k || RemoveKebab < 0);

	listItem *cur = descr->head, *pre;
	//cur - ����� �������
	//pre - ����� "�������������" ��������� �������
	pre = NULL;

	while (Current < RemoveKebab && cur)//����
	{
		pre = cur; 
		cur = cur->next; //�������������
		Current++;
	}

	if (Current != RemoveKebab || !cur) 
	{
		puts("There is no element with this number. Try again");
		return 0;
	}

	if (!pre) //���� ����� ������� ��������
	{
		descr->head = cur->next;//������������� �
	}
	else//���� ���, �� � ��� �������� pre
	{
		pre->next = cur->next;//�������������
	}

	free(cur->data.model);
	free(cur);//� �������

	return 1;
}


int FindItem(ListDescriptor descr)
{

	if (!descr.head)//�������� �� �������
	{
		puts("Empty!");
		return 0;
	}

	char buffer[STRSIZE]; //������ ��� ������
	rewind(stdin);

	printf("Enter the Car Model for searching: ");
	FillStringCorrectly(buffer); //��������� ���, ����� ������ �� ����� ��������� ������. ������� ���������� � data.h

	listItem *temp;//��������� ���������
	temp = NULL;

	int min;

	while (descr.head)//���� �� ���������� �� ����
	{
		if (!strcmp(descr.head->data.model, buffer))//���� ������ ������ � �����������
		{
			if (!temp)//���� ��������� �������
			{
				temp = descr.head;//�������� ��������� ��������� �� ���� �������, ����� ��� �������
				min = descr.head->data.cost;//���������� ��� �������
			}
			else if (descr.head->data.cost < min)//���� �� ������t � ���� ������ ����������
			{
				min = descr.head->data.cost;//�� ���������� � ����
				temp = descr.head;//� ��� �������
			}
		}
		descr.head = descr.head->next;//���������
	}


	if (temp)//���� ���-������ �����
	{
		showInfo(&temp->data);//�� ����������
		return 1;
	}
	else
	{
		puts("Not Found");
		return 0;
	}

}


int SaveToFile(ListDescriptor descr)
{
	FILE *file;

	char k;

	puts("Select Item\n");
	puts("w - Create File to Fill");
	puts("r - Open File to Fill");

	do
	{				//�������� �����
		rewind(stdin);
		k = getchar();
	} while (k != 'w' && k != 'r');

	if (k == 'w')//������ ������
	{
		if (!(file = fopen("stacks.txt", "w+t")))
		{
			puts("File opening error");
			return 0;
		}
	}
	else//��� ��������
	{
		if (!(file = fopen("stacks.txt", "r+t")))
		{
			puts("File not found");
			return 0;
		}
	}

	while (descr.head)//�����, ���� �� ���������� ����
	{
		saveInfoToFile(file, &descr.head->data);
		descr.head = descr.head->next;//� ���������
	}

	if (fclose(file) == EOF)//��������� ����
	{
		puts("File closing error!");
		return 0;
	}

	return 1;
}


int GetFromFile(ListDescriptor *descr)
{
	FILE *file;

	//��������� ��� ������
	if (!(file = fopen("stacks.txt", "r")))
	{
		puts("File not found");
		return 0;
	}

	book item;//��������� ��� ������
	listItem *temp, *head;
	//temp - 
	//head - 

	while (readInfoFromFile(file, &item))//���� �� ����� �����, ������ �� ��������� ���������
	{
		temp = descr->head;//���������� ������� �� ������
		head = NULL;

		head = (listItem*)malloc(sizeof(listItem));//������� ������� ��� ������

		if (!head)
		{
			puts("Memory Allocation Error");
			return 0;
		}

		head->data = item;//���������� � ����
		descr->head = head;//������ �������
		head->next = temp;//��������� �� ��������� ���������
	}

	fclose(file);
	return 1;
}


void freeList(listItem* item) //recursive delete
{
	if (item)
	{ //if an element exists
		freeList(item->next); //go deeper (to the stack bottom)
		free(item); //free elements from bottom to the top
	}
}


void ClearAll(ListDescriptor *descr)
{
	freeList(descr->head); //pointer to stack top
}

/*
void DeleteAll(ListDescriptor *descr)
{
	listItem *cur;

	while (descr->head)
	{
		cur = descr->head;
		descr->head = cur->next;
		free(cur);
	}
//	descr->head = NULL;
}
*/