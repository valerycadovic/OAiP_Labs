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
	listItem *temp; //создаём временный указатель, чтобы не потерять указатель на голову
	temp = descr->head; //посылаем его в голову стека
	listItem *head;//создаём временный указатель на элемент, который нужно будет добавить в стек

	head = (listItem*)malloc(sizeof(listItem));//создаём элемент
	if (!head)
	{
		puts("Memory allocation error. The Item did not added");
		return 0;
	}


	if (!setInfo(&head->data))//заполняем
	{
		free(head);
		puts("Information did not introduced in correct way");
		return 0;
	}

	descr->head = head;//перекидываем указатель на голову стека на новый элемент
	head->next = temp;//"насаживаем" новую голову на старую
	return 1;
}


void ShowList(ListDescriptor descr)
{
//	puts("Information");

	if (!descr.head)//если голова стека - нуль, то стек - пуст.
	{
		puts("Empty!");
		return;
	}

	while (descr.head)//пока не наткнемся на нуль
	{
		showInfo(descr.head);//показываем информацию текущего элемента
		descr.head = descr.head->next;//двигаемся по стеку
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
	//cur - чтобы удалять
	//pre - чтобы "перепрыгивать" удаляемый элемент
	pre = NULL;

	while (Current < RemoveKebab && cur)//ищем
	{
		pre = cur; 
		cur = cur->next; //передвигаемся
		Current++;
	}

	if (Current != RemoveKebab || !cur) 
	{
		puts("There is no element with this number. Try again");
		return 0;
	}

	if (!pre) //если нужно удалить верхушку
	{
		descr->head = cur->next;//перепрыгиваем её
	}
	else//если нет, то в ход вступает pre
	{
		pre->next = cur->next;//перепрыгиваем
	}

	free(cur->data.model);
	free(cur);//и удаляем

	return 1;
}


int FindItem(ListDescriptor descr)
{

	if (!descr.head)//Проверка на пустоту
	{
		puts("Empty!");
		return 0;
	}

	char buffer[STRSIZE]; //строка для поиска
	rewind(stdin);

	printf("Enter the Car Model for searching: ");
	FillStringCorrectly(buffer); //заполняем так, чтобы строка не могла оказаться пустой. Функция определена в data.h

	listItem *temp;//временный указатель
	temp = NULL;

	int min;

	while (descr.head)//пока не наткнулись на нуль
	{
		if (!strcmp(descr.head->data.model, buffer))//если запрос совпал с результатом
		{
			if (!temp)//если встречаем впервые
			{
				temp = descr.head;//посылаем временный указатель на этот элемент, чтобы его помнить
				min = descr.head->data.cost;//запоминаем как минимум
			}
			else if (descr.head->data.cost < min)//если не впервыt и цена меньше предыдущей
			{
				min = descr.head->data.cost;//то запоминаем и цену
				temp = descr.head;//и сам элемент
			}
		}
		descr.head = descr.head->next;//двигаемся
	}


	if (temp)//если что-нибудь нашли
	{
		showInfo(&temp->data);//то показываем
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
	{				//выбираем режим
		rewind(stdin);
		k = getchar();
	} while (k != 'w' && k != 'r');

	if (k == 'w')//запись заново
	{
		if (!(file = fopen("stacks.txt", "w+t")))
		{
			puts("File opening error");
			return 0;
		}
	}
	else//или дозапись
	{
		if (!(file = fopen("stacks.txt", "r+t")))
		{
			puts("File not found");
			return 0;
		}
	}

	while (descr.head)//пишем, пока не закончился стек
	{
		saveInfoToFile(file, &descr.head->data);
		descr.head = descr.head->next;//и двигаемся
	}

	if (fclose(file) == EOF)//закрываем файл
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
	if (!(file = fopen("stacks.txt", "r")))
	{
		puts("File not found");
		return 0;
	}

	book item;//структура для чтения
	listItem *temp, *head;
	//temp - 
	//head - 

	while (readInfoFromFile(file, &item))//пока не конец файла, читаем во временную структуру
	{
		temp = descr->head;//направляем читалку на голову
		head = NULL;

		head = (listItem*)malloc(sizeof(listItem));//создаем элемент для записи

		if (!head)
		{
			puts("Memory Allocation Error");
			return 0;
		}

		head->data = item;//записываем в него
		descr->head = head;//делаем головой
		head->next = temp;//соединяем со следующим элементом
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