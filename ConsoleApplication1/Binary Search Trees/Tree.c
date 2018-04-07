//#include "list.h"
#include <string.h>
#include <stdlib.h>
#include "stack_queue.h"

#pragma warning (disable:4996)


void listInit(ListDescriptor* descr)
{
	descr->head = NULL;
}

int AddItem(ListDescriptor *descr)
{
	BinTreeNode *Node;
	//������ ����
	Node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	//���������
	if (!Node)
	{
		puts("Allocation Error!");
		return 0;
	}
	//�������� ��������� �� ��������
	Node->left = Node->right = NULL;
	//������ ������
	setInfo(&Node->data);
	//���� ������ ���� ������, �� ������ ��� �������
	if (!descr->head)
	{
		descr->head = Node;
		return 1;//��������� ��������� �����
	}

	//���� ������ ��� ����

	//������ ��������� ��� ������ � ������ ��� � ������(������) ������
	BinTreeNode *temp = descr->head;

	int check;//���������� ��� �������� ���������� ����������������� ���������
//	char fl = '0';

	while (1)
	{
		//���������� ����� �� ������� ������, �.�. ��� ������� - ������-����������
		check = strcmp(Node->data.Russian, temp->data.Russian);

		if (check > 0)//���� ����� � ���������� ������� ����� ���������, ��� ������
		{
			if (!temp->right)//���� ��������� ������ ������, �.�. ������� ������� ��� ���
			{
				temp->right = Node;//������ ����
				break;//��������� ����
			}
			else//����� ��������� ������ ������
			{
				temp = temp->right;
			}
		}
		else if (check < 0)//�� �� �����, ������ �����
		{
			if (!temp->left)
			{
				temp->left = Node;
				break;
			}
			else
			{
				temp = temp->left;
			}
		}
		else//���� ����� �������, �� ������ ����� ����
		{
			puts("That word already exists in database");
			break;
		}
	}

	return 1;
}

/*
������� ������:
������� *Node ��������� � ����� ������, ����� ����, ��������� ������ �������� ��������
����� �� ����� ������, ���� �� �������� �� NULL, ����� ���� �������� �������� �������������,
�� ����� �� ���������� �� ��������� ������� � ��������� ���������� ������.
��� ����������, ���� *Node ��������� �� ������ ����� ��������.
����� ��������� ��������� � ������ �������� � ��������� �� �� ����, ���� �� ���������
����������� ��������.
������ ����� ����� �������� ����� ������������ ���������� � ��������� ������ �������.
*/

void Preorder(BinTreeNode *Node)//���������� ������ �����
{
	if (Node)
	{
		showInfo(&Node->data);
		if (Node->left) Preorder(Node->left);
		if (Node->right) Preorder(Node->right);
	}
}

void Inorder(BinTreeNode *Node)//���������� ������ �����
{
	if (Node)
	{
		if (Node->left) Inorder(Node->left);
		showInfo(&Node->data);
		if (Node->right) Inorder(Node->right);
	}
}

void Postorder(BinTreeNode *Node)//���������� ������ �����
{
	if (Node)
	{
		if (Node->left) Postorder(Node->left);
		if (Node->right) Postorder(Node->right);
		showInfo(&Node->data);
	}
}

void ShowUsingRecursion(ListDescriptor descr, order type)
{//����� ���������, �� ����� �� ������
	if (!descr.head)
	{
		puts("Empty!");
	}
	else//�������� ������ ������
	{
		switch (type)
		{
		case INORDER:
		{
			Inorder(descr.head);
			break;
		}
		case PREORDER:
		{
			Preorder(descr.head);
			break;
		}
		case POSTORDER:
		{
			Postorder(descr.head);
			break;
		}
		}
	}
}


/*
	�������� ����� �����, ��� � � ����������� �������, �� ���������� �����.
	������� ����� ������ � ����.
�����, ���� ���� �� ��������, ������ ���������:
���� ������� �����, ������� � ����� ����, ������� ������������, ���� �� ����� ��������� ����� ������� ���� ������;
���� ���� ������ �������, ����� ��� � ����;
���������� ���� �������� �����;
��������� �����.
	����� �� ��������� NULL, � ������� ����� ����� ����� ������� ������� �������� ���������;
������ ���.
	���� ����� ������������, ���� �� ����� ��������� ����� ������ ���� ������.
	� ����� �� ������ ����� �������� ������ ����� ������� ������
*/

//����� � ������ � ������� �����
int ShowUsingStack(ListDescriptor descr)
{
	//�������� �� �������
	if (!descr.head)
	{
		puts("Empty!");
		return;
	}

	//������ ����
	Stack stack;
	stack.head = NULL;

	//���������� � ���� ������ ������
	if (!AddToStack(&stack, descr.head))
	{//���� ��������� ������ � ��������� ������ ��� ������� �����
		return 0;
	}

	BinTreeNode *temp;//��������� ��� ������

	while (stack.head)//���� ���� �� ����
	{
		temp = pop(&stack);//���� ������� �����
		if (!temp)
		{
			puts("error");
			if (stack.head)//���� �� ���������� ������ ��� ������� ����� � ��� ���� ���� �� ����,
			{
				ClearStack(&stack);// ����� ���������� �����, ���������� ��� ����
			}
			return 0;
		}
		//���� ��������� �� ���� 
		while (temp)
		{
			if (temp->right)//���� ���� ������ �������
			{
				if (!AddToStack(&stack, temp->right))//��������� ��� � ����
				{
					if (stack.head)
					{
						ClearStack(&stack);
					}
					return 0;
				}
			}
			showInfo(&temp->data);//���������� ����������
			temp = temp->left;//��������� �����
		}
	}
	return 1;
}


//�������� ��������
int DeleteItem(ListDescriptor* descr)
{
	//���������, �� ����� �� ������
	if (!descr->head)
	{
		puts("Empty!");
		return 0;
	}

	puts("What word do you want to remove?");

	char buffer[STRSIZE];
	//�� ����� ������� ������ ������
	FillStringCorrectly(buffer);

	BinTreeNode *temp = descr->head;//��������� ��� ������ � ��������
	BinTreeNode *parent = NULL;//��������� �� ��������
	int check;
	char side;//�����������

	//����� ��������
	while (temp)
	{
		//��������� �����
		check = strcmp(buffer, temp->data.Russian);

		if (!check)
		{//���� �����, ��������� ����
			break;
		}
		else
		{
			parent = temp;//������ ������� ���� ���������
			if (check > 0)
			{
				side = 'R';//���������, ���� ���������
				temp = temp->right;//������
			}
			else
			{
				side = 'L';
				temp = temp->left;//�����
			}
		}
	}
	
	//���� �� �����, ���������� ������
	if (!temp)
	{
		puts("Not Found");
		return 0;
	}

	/*------------------------------------------------------------------------------------------
		����� �������� ��������� ��������� �������� �������:
	1. ���� �������� ������
	2. ���� ����� ������ ������� �������
	3. ���� ����� ������ ������ �������
	4. ���� ����� ����� ��������
		��� ���� ���������� ������������� ����������� ����, ��� ���� ����� ���� ������ ������
	------------------------------------------------------------------------------------------*/

	//1. ���� �������� ������, ���� �� ����� ��������
	if (!temp->left && !temp->right)
	{
		free(temp);//������ ������� ����
		//���������, �� ��� �� �� ������ ������
		if (!parent)
		{//���� ���, �� �������� ��������� �� ������, ������������ � ������� ������
			descr->head = NULL;
			return 1;
		}

		if (side == 'L')//���� ������� ��� ����� �� ��������, �������� ��� ����� ���������
		{
			parent->left = NULL;
		}
		else
		{
			parent->right = NULL;//����� - ������
		}

		return 1;
	}

	//2. ���� ����� ������� �������
	if (!temp->left)
	{
		if (!parent)//���� ������
		{
			descr->head = temp->right;//������� ���������� ������
			free(temp);//������� ����
			return 1;
		}

		if (side == 'L')//���� � �������� ���� - �����
		{
			parent->left = temp->right;//������ ��� ������� ������� ����� �������� ��������
		}
		else
		{
			parent->right = temp->right;//����� - ������
		}

		free(temp);//�������
		return 1;
	}

	//3. ���� ������� ������ ����� �������
	if (!temp->right)
	{
		//���� �� ������
		if (!parent)
		{
			descr->head = temp->left;//��� ������ ������� ������ ��������
			free(temp);//������� ����
			return 1;
		}

		if (side == 'L')//���� ��������� ���� - ����� ������� ��������
		{
			parent->left = temp->left;//������ ������� ���� �������� �������� (�������������)
		}
		else
		{
			parent->right = temp->left;//���� ������, �� ��� ����� ������ �����
		}

		free(temp);//�������
		return 1;
	}


	//4. ���� ���� ����� ���� ��������, �� ��� ���� ������� �� �����.
	//	  ���������� ���� �������� ��� �������� �� ���������� (����� �����) �������� ��� ������� ��������,
	//    � ������� ����, ��� �����������

	BinTreeNode *RemoveKebab = temp;// ���� ��������� ������� �� ��������� ����
	parent = temp;
	temp = temp->right;//������� � ������ ��������

	side = 'R';//������, ��� ��������� �������� ���� ��������� ������
	while (temp->left)
	{//������� ���� ��� ������
		side = 'L';
		parent = temp;
		temp = temp->left;
	}

	//������� ������ ��������
	strcpy(RemoveKebab->data.English, temp->data.English);
	strcpy(RemoveKebab->data.Russian, temp->data.Russian);

	//����� ����� ������� ����, �� �������� ����������

	//���� �� �� ����� ��������
	if (!temp->left && !temp->right)
	{
		free(temp);//�������
		//�������� ������������ ���������
		if (side == 'L')
		{
			parent->left = NULL;
		}
		else
		{
			parent->right = NULL;
		}
	}
	else//���� �� ����� ���� �� ������ �������
	{
		//������� ������� ������� �������� � ����������� �� ������� �������
		if (side == 'L')
		{
			parent->left = temp->right;
		}
		else
		{
			parent->right = temp->right;
		}

		free(temp);//�������
	}
	

	return 1;
}

//��������
void Descent(BinTreeNode* Node)
{//������� ���������� �� ��������� ������
	if (Node->left)
	{
		Descent(Node->left);
	}
	if (Node->right)
	{
		Descent(Node->right);
	}

	free(Node);
}

void ClearAll(ListDescriptor *descr)
{
	if (descr->head)//���� ������ �� �����
	{
		Descent(descr->head);
	}
}

/*
int Demonstrate(ListDescriptor descr)
{
	if (!descr.head)
	{
		puts("Empty!");
		return 0;
	}

	Queue queue;
	queue.tail = queue.head = NULL;
	char LeftFlag = '0', RightFlag = '0';
	BinTreeNode* temp;
	BinTreeNode* gap;

	gap = (BinTreeNode*)malloc(sizeof(BinTreeNode));

	if (!gap)
	{
		puts("Did not Allocated");
		return 0;
	}

	strcpy(gap->data.English, "(x)");
	strcpy(gap->data.Russian, "(x)");

	if (!Enqueue(&queue, descr.head))
	{
		return 0;
	}

	while (queue.head)
	{
		temp = Dequeue(&queue);
		if (!temp)
		{
			if (!queue.head)
			{
				ClearQueue(&queue);
			}
			return 0;
		}

		showInfo(&temp->data);

		if (temp == gap) continue;

		if (temp->left)
		{
			if (!Enqueue(&queue, temp->left))
			{
//				LeftFlag = '0';
				if (!queue.head)
				{
					ClearQueue(&queue);
				}
				return 0;
			}
		}
		else //if(LeftFlag == '0')
		{
			LeftFlag = '1';
			if (!Enqueue(&queue, gap))
			{
				if (!queue.head)
				{
					ClearQueue(&queue);
				}
				return 0;
			}
		}

		if (temp->right)
		{
//			RightFlag = '0';
			if (!Enqueue(&queue, temp->right))
			{
				if (!queue.head)
				{
					ClearQueue(&queue);
				}
				return 0;
			}
		}
		else //if(RightFlag == '0')
		{
//			RightFlag = '1';
			if (!Enqueue(&queue, gap))
			{
				if (!queue.head)
				{
					ClearQueue(&queue);
				}
				return 0;
			}
		}
	}
} 
*/

void DrawInConsole(BinTreeNode *Node, int level)
{
	if (Node)
	{
		DrawInConsole(Node->left, level + 1);
		for (int i = 0; i < level; i++) printf("\t");
		printf("%s - %s\n", Node->data.Russian, Node->data.English);
		//	showInfo(&Node->data);
		DrawInConsole(Node->right, level + 1);
	}
}

void Demonstrate(ListDescriptor descr)
{
	DrawInConsole(descr.head, 0);
}
