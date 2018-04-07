#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "..\common\data.h"
#include "..\common\list.h"

#pragma warning(disable : 4996)

int main(int argc, char* argv[])
{
	ListDescriptor list;
	char select;

	listInit(&list);


	do
	{
		system("cls");

		puts("1. Add item");
		puts("2. Show list");
		puts("3. Delete item");
		puts("4. Find item");
		puts("5. Save to file");
		puts("6. Get from file");
		puts("7. Delete All");
		puts("0. Exit");

		do//выбираем пункт
		{
			rewind(stdin);
			select = getchar();
		} while (select > '7' || select < '0');

		switch (select)
		{
		case '1':
		{
			puts("\tYou May Add.");
			if (AddItem(&list))
			{
				puts("\tSuccess!!");
			}
			break;
		}
		case '2':
		{
			puts("\tThe list:");
			ShowList(list);
			break;
		}
		case '3':
		{
			puts("\tYou May Delete.");
			if (DeleteItem(&list))
			{
				puts("\tSuccess!!");
			}
			break;
		}
		case '4':
		{
			puts("\tSearch");
			FindItem(list);
			break;
		}
		case '5':
		{
			puts("\tWrite Down.");
			if (SaveToFile(list))
			{
				puts("\tSuccess!!");
			}
			break;
		}
		case '6':
		{
			if (GetFromFile(&list))
			{
				puts("\tSuccess!!");
			}
			break;
		}
		case '7':
		{
			puts("\n\tDelete All List");
			ClearAll(&list);
			listInit(&list);
			puts("\tSuccess!");
			break;
		}
		case '0':
		{
			puts("\tPress any key to exit");
			ClearAll(&list);
			getch();
			return 0;
		}
		}
		puts("Press any key to back to menu");
		getch();

	} while (1);

}