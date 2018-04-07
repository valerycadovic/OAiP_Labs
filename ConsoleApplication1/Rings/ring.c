#pragma warning(disable : 4996)
#pragma warning(disable : 4133)
#pragma warning(disable : 4013)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\common\data.h"
#include "..\common\list.h"


void listInit(ListDescriptor *descr)
{
	descr->head = NULL;
}

int AddItem(ListDescriptor *descr)
{
	listItem *temp, *enter;
	temp = descr->head;
	if (!descr->head)//если добавляем впервые
	{
		descr->head = (listItem*)malloc(sizeof(listItem));
		if (!descr->head)
		{
			return 0;
		}
		//указываем на самого себя
		descr->head->next = descr->head;
		descr->head->prev = descr->head;
		enter = descr->head;//заносим для вывода
	}
	else
	{
		enter = (listItem*)malloc(sizeof(listItem));
		if (!enter)
		{
			return 0;
		}

		//добавление
		temp = descr->head->next;
		descr->head->next = enter;
		enter->prev = descr->head;
		enter->next = temp;
		temp->prev = enter;
		descr->head = enter;
	}

	//вывод
	if (!setInfo(&enter->data))
	{
		free(enter->data.model);
		free(enter);
		return 0;
	}

	return 1;
}

void ShowList(ListDescriptor descr)
{
	if (!descr.head)
	{
		puts("Empty");
		return;
	}

	char check;
	listItem *temp;
	temp = descr.head;

	puts("Select how to show:\n1 - As a stack\n2 - As a queue");
	do
	{
		rewind(stdin);
		check = getchar();
	} while (check != '1' && check != '2');

	switch (check)
	{
	case '1':
	{
		while (1)
		{//как стек
			showInfo(temp);
			temp = temp->prev;
			if (temp == descr.head) break;
		}
		break;
	}
	case '2':
	{
		while (1)
		{//как очередь
			temp = temp->next;
			showInfo(temp);
			if (temp == descr.head) break;
		}
		break;
	}
	}
}

int FindItem(ListDescriptor descr)
{
	if (!descr.head)//если пусто, дальше не идём для экономии времени и памяти
	{
		puts("Empty!");
		return 0;
	}

	char buffer[STRSIZE];
	char flag = '0';
	listItem *temp = descr.head;

	rewind(stdin);

	puts("Enter model for searching");
	FillStringCorrectly(buffer);//заполняем так, чтобы строка не могла оказаться пустой. Функция определена в data.h

	while (1)
	{
		temp = temp->next;
		if (!strcmp(temp->data.model, buffer))
		{
			showInfo(&temp->data);
			flag = '1';
		}
		if (temp == descr.head) break;
	}

	if (flag == '0')
	{
		puts("Not Found");
		return 0;
	}

	return 1;
}

int DeleteItem(ListDescriptor *descr)
{
	int RemoveKebab, Current = 0, k;
	listItem *cur = descr->head, *temp;

	if (!descr->head)
	{
		puts("empty!!");
		return 0;
	}


	printf("Enter number of element to remove: ");
	do
	{
		rewind(stdin);
		k = scanf("%d", &RemoveKebab);
	} while (!k || RemoveKebab < 0);

	if (descr->head->next == descr->head)
	{
		if (RemoveKebab > 0)
		{
			puts("There is no element with this number. Try again!");
			return 0;
		}
		else
		{
			descr->head = NULL;
			free(cur->data.model);
			free(cur);
			return 1;
		}
	}
	if (!RemoveKebab)
	{
		descr->head = cur->prev;
	}
	else
	{
		cur = cur->next;
		Current++;
	}

	while (Current < RemoveKebab && cur != descr->head)
	{
		cur = cur->next;
		Current++;
	}

	if (cur == descr->head || Current!=RemoveKebab)
	{
		puts("There is no element with this number. Try again!");
		return 0;
	}

	temp = cur;
	cur = cur->prev;
	cur->next = temp->next;
	cur = temp->next;
	cur->prev = temp->prev;

	free(temp->data.model);
	free(temp);

	return 1;
}

int SaveToFile(ListDescriptor descr)
{
	FILE *file;
	char mode;

	if (!descr.head)
	{
		puts("There is nothing to write");
		return 0;
	}

	listItem *temp = descr.head;

	puts("Select Mode");
	puts("w - Create File to Fill");
	puts("a - Open File to Add at the End");

	do
	{
		rewind(stdin);
		mode = getchar();
	} while (mode != 'w' && mode != 'a');

	if (mode == 'a')
	{
		if (!(file = fopen("rings.txt", "w+t")))
		{
			puts("File opening error");
			return 0;
		}
	}
	else
	{
		if (!(file = fopen("rings.txt", "a+t")))
		{
			puts("File opening error");
			return 0;
		}
	}


	while (1)
	{
		temp = temp->next;
		saveInfoToFile(file, &temp->data);
		if (temp == descr.head) break;
	}
	
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

	//открываем для чтения
	if (!(file = fopen("rings.txt", "r")))
	{
		puts("File not found");
		return 0;
	}

	book item;
	listItem *temp, *enter;

	while (readInfoFromFile(file, &item))
	{
		temp = descr->head;
		if (!descr->head)
		{
			descr->head = (listItem*)malloc(sizeof(listItem));
			if (!descr->head)
			{
				return 0;
			}

			descr->head->next = descr->head;
			descr->head->prev = descr->head;
			enter = descr->head;
		}
		else
		{
			enter = (listItem*)malloc(sizeof(listItem));
			if (!enter)
			{
				return 0;
			}

			temp = descr->head->next;
			descr->head->next = enter;
			enter->prev = descr->head;
			enter->next = temp;
			temp->prev = enter;
			descr->head = enter;
		}
		enter->data = item;
	}

	fclose(file);
	return 1;
}

void ClearAll(ListDescriptor *descr)
{
	if (!descr->head) return;

	listItem *temp = descr->head;
	listItem *Finish = descr->head->prev;

	while (descr->head != Finish)
	{
		descr->head = descr->head->next;
		free(temp->data.model);
		free(temp);
		temp = descr->head;
	}

	free(temp->data.model);
	free(temp);
}