#pragma once
#include <stdio.h>
#define STRSIZE 100

typedef union
{
	char body[STRSIZE];
	int engine;
}sort;

typedef struct
{
	int cost;
	char* model;
	char type;
	sort choose;
}book;

int setInfo(book *data);
void showInfo(book *data);
void saveInfoToFile(FILE *file, book *data);
int readInfoFromFile(FILE *file, book *data);

void FillStringCorrectly(char* str);

