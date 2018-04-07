#pragma warning(disable : 4996)
#pragma warning(disable : 4133)
#pragma warning(disable : 4013)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\common\data.h"
#include "..\common\list.h"

#define STRSIZE 100

void listInit(ListDescriptor *descr)
{
	descr->head = NULL;
	descr->tail = NULL;
}

void ClearAll(ListDescriptor *descr)
{
	listItem *temp = descr->head;
	while (descr->head != descr->tail)//���� ������ �� ������ �������
	{
		descr->head = descr->head->next;//���������
		free(temp);//�������
		temp = descr->head;//������ ��������� ������� �� ������� ��������
	}

	if (descr->tail)
	{
		free(descr->tail);//������� ��������� �������
	}
}

int AddItem(ListDescriptor *descr)
{
	listItem *tail = NULL;//��������������� ��������� �����-���������
 
	if (!descr->head)//���� ��� ������, �.�. ������� �����, �� ������ ��������� �������
	{
		descr->head = (listItem*)malloc(sizeof(listItem));//�������� ������ ��� ������
		if (!descr->head)
		{
			puts("error");
			return 0;
		}
		descr->tail = descr->head;//������������� ����� �� ������, �.�. ������ ��� ������ ���������
		tail = descr->tail;//��������� ����� ����� ������ �� ����������� �������, ����� ����� ������ ��� ��������
	}
	else//���� ������� ��� �� �����, �������� �� ��������������� �������
	{
		tail = (listItem*)malloc(sizeof(listItem));//������� �� ���� ���������� �������
		if (!tail)
		{
			puts("error tail");
			return 0;
		}

		descr->tail->next = tail;//��������� � �������� ������� �������� �� ����� ���������
		descr->tail = tail;//� ������ ��� ������� �������
	}

	if (!setInfo(&tail->data))//���������
	{
		free(tail);
		return 0;
	}

	descr->tail->next = NULL;//�������� ��������� ���������� ��������
	return 1;
} 

void ShowList(ListDescriptor descr)
{
	if (!descr.head)//�������� �� �������
	{
		puts("Empty!");
		return;
	}

	while (descr.head)//���� �� ���������� �� ����� �������
	{
		showInfo(descr.head);//����������
		descr.head = descr.head->next;//���������
	}
}

int FindItem(ListDescriptor descr)
{
	if (!descr.head)//�������� �� �������
	{
		puts("Empty!");
		return 0;
	}

	char buffer[STRSIZE];//������ ��� ������
	listItem *temp = NULL;//��������� ��������� ��� ������
	int min;
	rewind(stdin);

	puts("Enter model for searching");
	FillStringCorrectly(buffer);//��������� ���, ����� ������ �� ����� ��������� ������. ������� ���������� � data.h

	while (descr.head)//���� �� �����
	{
		if (!strcmp(descr.head->data.model, buffer))//���������� ������ � ���������
		{
			if (!temp)//���� ������ � ��������� ������� �������
			{
				temp = descr.head;//���������� ���� �������, ������ �� ���� ��������� ���������
				min = descr.head->data.cost;//���������� ��� ��������
			}
			else if (descr.head->data.cost < min)//���� �� �������, ������� �� ��� ��������
			{
				min = descr.head->data.cost;//���� ��� ������, �� ����������
				temp = descr.head;//� ���������� �������
			}
				
		}
		descr.head = descr.head->next;//��������� ������
	}

	if (temp)//���� ���-������ �����
	{
		showInfo(&temp->data);//����������
		return 1;
	}
	else
	{
		puts("Not Found");
		return 0;
	}

	
}

int DeleteItem(ListDescriptor *descr)
{
	int RemoveKebab, Current = 0, k;//����������: ������ ��������, ��� ������, ��� �������� �����

	printf("Enter number of element to remove: ");
	do
	{
		rewind(stdin);
		k = scanf("%d", &RemoveKebab);
	} while (!k || RemoveKebab < 0);

	listItem *cur = descr->head, *pre = NULL;//���������: ��� �������� � ��� ���������� ����������� ��������, ����� "������������" ���������

	while (Current < RemoveKebab && cur)//����, ���� �� ����� ��� �� ��������� �� �����
	{
		pre = cur;//������� ���������� ����������
		cur = cur->next;//���������
		Current++;
	}

	if (!cur || Current != RemoveKebab)//���� �� �����
	{
		puts("There is no element with this number. Try again");
		return 0;
	}

	if (!pre)//���� ��������� �� ���������� ������, ������ �� ������� �������� �������
	{
		descr->head = cur->next;//������ ������� ���������
	}
	else//���� �� ������
	{
		pre->next = cur->next;//"�������������" ���������
	}

	if (!cur->next)//���� ������������ �� ����, �.�. ������� ���������
	{
		descr->tail = pre;//���������� ������� ������ �������
	}

	free(cur->data.model);
	free(cur);//�������
	return 1;
}

int SaveToFile(ListDescriptor descr)
{
	FILE *file;
	char k;

	//�������� �����
	puts("Select Item\n");
	puts("w - Create File to Fill");
	puts("r - Open File to Fill");

	do
	{
		rewind(stdin);
		k = getchar();
	} while (k != 'w' && k != 'r');

	//��������� ����
	if (k == 'w')
	{
		if (!(file = fopen("queues.txt", "w+t")))
		{
			puts("File opening error");
			return 0;
		}
	}
	else
	{
		if (!(file = fopen("queues.txt", "r+t")))
		{
			puts("File not found");
			return 0;
		}
	}

	while (descr.head)//���� �� �����
	{
		saveInfoToFile(file, &descr.head->data);//����� � ����
		descr.head = descr.head->next;//���������
	}

	//��������� ����
	if (fclose(file) == EOF)
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
	if (!(file = fopen("queue.txt", "r")))
	{
		puts("File not found");
		return 0;
	}

	book item;//���������, � ������� ������ � �����, ����� �������� � �������
	listItem *tail;//��������������� �����-���������

	while (readInfoFromFile(file, &item))//������, ���� �� ����� �����(��. �-��� readInfoFromFile � data.c)
	{
		tail = NULL;//��������

		//��� ��� � AddItem, ������ ������ � �����, � �� � ����������
		if (!descr->head)//���� ����� �������
		{
			descr->head = (listItem*)malloc(sizeof(listItem));//������� ������ ������� �� �������� ���������
			if (!descr->head)
			{
				puts("error");
				return 0;
			}
			descr->tail = descr->head;//������ ��� � �������
			tail = descr->tail;//����������
		}
		else//���� � ������� ���-�� ��� ����
		{
			tail = (listItem*)malloc(sizeof(listItem));//������ ������� �� ��������������� ���������
			if (!tail)
			{
				puts("tail");
				return 0;
			}
			descr->tail->next = tail;//������������ ��� � �������
			descr->tail = tail;//������ ����������� �������
		}

		tail->data = item;//���������
		descr->tail->next = NULL;//��������
	}

	//���� ���������
	fclose(file);
	return 1;
}