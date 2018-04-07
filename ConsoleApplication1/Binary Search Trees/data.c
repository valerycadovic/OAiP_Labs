#include <stdio.h>
#include "list.h"

#pragma warning (disable:4996)

void FillStringCorrectly(char* str)
{
	do
	{
		rewind(stdin);
		gets(str);
		if (str[0]) break;
	} while (1);
}

void setInfo(book* data)
{
	
	printf("Russian Word: ");
	FillStringCorrectly(data->Russian);

	printf("English translation: ");
	FillStringCorrectly(data->English);

}

void showInfo(book* data)
{
	puts("\nNode contains\n");
	printf("Russian: %s\nEnglish: %s", data->Russian, data->English);
}