#include <stdio.h>
#include <stdlib.h>
#include "..\common\data.h"
#include "..\common\list.h"

#pragma warning (disable:4996)

#define STRSIZE 100

void FillStringCorrectly(char* str)
{
	while (1)
	{
		rewind(stdin);
		gets(str);
		if (str[0]) break;
	}
}

int setInfo(book *data)
{
	rewind(stdin);
	printf("Enter Car Model's name: ");

	data->model = (char*)malloc(STRSIZE);
	if (!(data->model))
	{
		puts("Memory Allocation Errorr: the string for the model did not created");
		return 0;
	}

	FillStringCorrectly(data->model);


	printf("Enter Car's cost: ");
	while (!scanf("%d", &data->cost))
	{
		rewind(stdin);
		printf("It might be an integer number!");
	}


	puts("\n1. Press \"t\" to introduce the type of the body");
	puts("2. Press \"e\" to specify the volume of the engine");

	do
	{
		rewind(stdin);
		data->type = getchar();
	} while (data->type != 'e' && data->type != 't');
	rewind(stdin);

	if (data->type == 't')
	{
		printf("Enter the type of the body: ");
		FillStringCorrectly(data->choose.body);
	}
	else
	{
		printf("Enter the volume of the engine: ");
		while (!scanf("%d", &data->choose.engine))
		{
			rewind(stdin);
			puts("It might be an integer number!");
		}
		rewind(stdin);
	}

	return 1;
}

void showInfo(book* data)
{

	printf("Car Model: %s\n", data->model);
	printf("Car Cost: %d\n", data->cost);

	if (data->type == 't')
	{
		printf("Type of Body: %s\n", data->choose.body);
	}
	else
	{
		printf("Volume of Engine: %d\n", data->choose.engine);
	}
}

void saveInfoToFile(FILE *file, book *data)
{
	fprintf(file, "%s %d %c ", data->model, data->cost, data->type);

	if (data->type == 't')
	{
		fprintf(file, "%s ", data->choose.body);
	}
	else
	{
		fprintf(file, "%d ", data->choose.engine);
	}
}

int readInfoFromFile(FILE *file, book *data)
{

	data->model = (char*)malloc(STRSIZE);
	if (!(data->model))
	{
		puts("Memory Allocation Error");
		return 0;
	}

	if (!fscanf(file, "%s", data->model) || feof(file))
	{
		puts("Model Scaning Error!");
		return 0;
	}

	if (!fscanf(file, "%d", &data->cost))
	{
		puts("Cost Scaning Error!");
		return 0;
	}

	/*	if (!fscanf(file, "%c", &data->type))
	{
	puts("Type Scaning Error!");
	return 0;
	}

	*/

	fgetc(file);


	/*	if (data->type == 't')
	{
	if (!fscanf(file, "%s", &data->choose.body))
	{
	puts("Body Scaning Error!");
	return 0;
	}
	}
	else
	{
	if (!*/fscanf(file, "%d", &data->choose.engine);//)
	/*	{
	puts("Engine Scaning Error!");
	return 0;
	}
	}*/

	return 1;
}