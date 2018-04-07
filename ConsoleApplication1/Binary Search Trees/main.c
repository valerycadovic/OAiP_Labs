#include <conio.h>
#include "list.h"

#pragma warning (disable:4996)

//void Getch();

int main()
{
	ListDescriptor list;
	char select;

	listInit(&list);

	do
	{
		system("cls");

		puts("1. Add Node");
		puts("2. Show Tree Using Recursion");
		puts("3. Delete Node");
		puts("4. Show Tree Using Stack");
		puts("5. Delete Tree");
		puts("6. Level Order Print");
		puts("0. Exit");

		do
		{
			rewind(stdin);
			select = getchar();
		} while (select > '5' || select < '0');

		system("cls");

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
			puts("\tSelect type\n1. Inorder\n2. Preorder\n3. Postorder");
			do
			{
				rewind(stdin);
				select = getchar();
			} while (select > '3' || select < '1');

			switch (select)
			{
			case '1':
			{
				ShowUsingRecursion(list, INORDER);
				break;
			}
			case '2':
			{
				ShowUsingRecursion(list, PREORDER);
				break;
			}
			case '3':
			{
				ShowUsingRecursion(list, POSTORDER);
				break;
			}
			}
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
			puts("\tShow Using Stack");
			ShowUsingStack(list);
			break;
		}
		case '5':
		{
			puts("\n\tDelete Tree");
			ClearAll(&list);
			listInit(&list);
			puts("\tSuccess!");
			break;
		}
		case '6':
		{
			puts("Level Order Print");
			Demonstrate(list);
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
		puts("\nPress any key to back to menu");
		getch();
//		Getch();
	} while (1);
}

/*
void Getch()
{
	char k;
	do
	{
		rewind(stdin);
		k = getchar();
		if (k > 40 || k < 37) break;
	} while (1);
}
*/