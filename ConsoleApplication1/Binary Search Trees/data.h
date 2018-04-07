#pragma once
#include <stdio.h>

#define STRSIZE 100

typedef struct
{
	char Russian[STRSIZE];
	char English[STRSIZE];
}book;

//��� ����������� ������� ������
typedef enum order
{
	PREORDER,
	INORDER,
	POSTORDER,
}order;

void setInfo(book*);
void showInfo(book*);
void FillStringCorrectly(char*);