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
	while (descr->head != descr->tail)//пока голова не станет хвостом
	{
		descr->head = descr->head->next;//двигаемся
		free(temp);//удаляем
		temp = descr->head;//ставим следующий элемент на позицию удаления
	}

	if (descr->tail)
	{
		free(descr->tail);//очищаем последний элемент
	}
}

int AddItem(ListDescriptor *descr)
{
	listItem *tail = NULL;//вспомагательный временный хвост-указатель
 
	if (!descr->head)//если нет головы, т.е. очередь пуста, то просто добавляем элемент
	{
		descr->head = (listItem*)malloc(sizeof(listItem));//выделяем память под голову
		if (!descr->head)
		{
			puts("error");
			return 0;
		}
		descr->tail = descr->head;//устанавливаем хвост на голову, т.к. сейчас они должны совпадать
		tail = descr->tail;//временный хвост также кидаем на добавленный элемент, чтобы после задать ему значение
	}
	else//если очередь уже не пуста, работаем со вспомогательным хвостом
	{
		tail = (listItem*)malloc(sizeof(listItem));//создаем за этим указателем элемент
		if (!tail)
		{
			puts("error tail");
			return 0;
		}

		descr->tail->next = tail;//указатель с прошлого элемета помещаем на вновь созданный
		descr->tail = tail;//и делаем его хвостом очереди
	}

	if (!setInfo(&tail->data))//заполняем
	{
		free(tail);
		return 0;
	}

	descr->tail->next = NULL;//зануляем указатель последнего элемента
	return 1;
} 

void ShowList(ListDescriptor descr)
{
	if (!descr.head)//Проверка на пустоту
	{
		puts("Empty!");
		return;
	}

	while (descr.head)//пока не натыкаемся на конец очереди
	{
		showInfo(descr.head);//показываем
		descr.head = descr.head->next;//двигаемся
	}
}

int FindItem(ListDescriptor descr)
{
	if (!descr.head)//Проверка на пустоту
	{
		puts("Empty!");
		return 0;
	}

	char buffer[STRSIZE];//строка для поиска
	listItem *temp = NULL;//временный указатель для поиска
	int min;
	rewind(stdin);

	puts("Enter model for searching");
	FillStringCorrectly(buffer);//заполняем так, чтобы строка не могла оказаться пустой. Функция определена в data.h

	while (descr.head)//пока не конец
	{
		if (!strcmp(descr.head->data.model, buffer))//сравниваем запрос и результат
		{
			if (!temp)//если запрос и результат совпали впервые
			{
				temp = descr.head;//запоминаем этот элемент, послав на него временный указатель
				min = descr.head->data.cost;//запоминаем его значение
			}
			else if (descr.head->data.cost < min)//если не впервые, смотрим на его значение
			{
				min = descr.head->data.cost;//если оно меньше, то запоминаем
				temp = descr.head;//и запоминаем позицию
			}
				
		}
		descr.head = descr.head->next;//двигаемся вперед
	}

	if (temp)//если что-нибудь нашли
	{
		showInfo(&temp->data);//показываем
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
	int RemoveKebab, Current = 0, k;//переменные: номера элемента, для поиска, для проверки ввода

	printf("Enter number of element to remove: ");
	do
	{
		rewind(stdin);
		k = scanf("%d", &RemoveKebab);
	} while (!k || RemoveKebab < 0);

	listItem *cur = descr->head, *pre = NULL;//указатели: для удаления и для сохранения предыдущего элемента, чтобы "перепрыгнуть" удаляемый

	while (Current < RemoveKebab && cur)//ищем, пока не найдём или не наткнемся на конец
	{
		pre = cur;//текущая становится предыдущей
		cur = cur->next;//двигаемся
		Current++;
	}

	if (!cur || Current != RemoveKebab)//если не нашли
	{
		puts("There is no element with this number. Try again");
		return 0;
	}

	if (!pre)//если указатель на предыдущий занулён, значит мы удаляем головной элемент
	{
		descr->head = cur->next;//делаем головой следующий
	}
	else//если не занулён
	{
		pre->next = cur->next;//"перепрыгиваем" удаляемый
	}

	if (!cur->next)//если перепрыгнули на нуль, т.е. удаляем последний
	{
		descr->tail = pre;//предыдущий элемент делаем хвостом
	}

	free(cur->data.model);
	free(cur);//удаляем
	return 1;
}

int SaveToFile(ListDescriptor descr)
{
	FILE *file;
	char k;

	//выбираем режим
	puts("Select Item\n");
	puts("w - Create File to Fill");
	puts("r - Open File to Fill");

	do
	{
		rewind(stdin);
		k = getchar();
	} while (k != 'w' && k != 'r');

	//открываем файл
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

	while (descr.head)//если не конец
	{
		saveInfoToFile(file, &descr.head->data);//пишем в файл
		descr.head = descr.head->next;//двигаемся
	}

	//закрываем файл
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
	if (!(file = fopen("queue.txt", "r")))
	{
		puts("File not found");
		return 0;
	}

	book item;//структура, в которую читаем с файла, чтобы добавить в очередь
	listItem *tail;//вспомогательный хвост-указатель

	while (readInfoFromFile(file, &item))//читаем, пока не конец файла(см. ф-цию readInfoFromFile в data.c)
	{
		tail = NULL;//зануляем

		//все как в AddItem, только читаем с файла, а не с клавиатуры
		if (!descr->head)//если пишем впервые
		{
			descr->head = (listItem*)malloc(sizeof(listItem));//создаем первый элемент на головном указателе
			if (!descr->head)
			{
				puts("error");
				return 0;
			}
			descr->tail = descr->head;//делаем его и хвостом
			tail = descr->tail;//запоминаем
		}
		else//если в очереди что-то уже есть
		{
			tail = (listItem*)malloc(sizeof(listItem));//создаём элемент на вспомогательном указателе
			if (!tail)
			{
				puts("tail");
				return 0;
			}
			descr->tail->next = tail;//присоединяем его к очереди
			descr->tail = tail;//делаем полноценным хвостом
		}

		tail->data = item;//заполняем
		descr->tail->next = NULL;//зануляем
	}

	//файл закрываем
	fclose(file);
	return 1;
}