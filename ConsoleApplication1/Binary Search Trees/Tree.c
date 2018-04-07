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
	//создаём узел
	Node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	//проверяем
	if (!Node)
	{
		puts("Allocation Error!");
		return 0;
	}
	//зануляем указатели на потомков
	Node->left = Node->right = NULL;
	//вводим данные
	setInfo(&Node->data);
	//если данный узел первый, то делаем его головой
	if (!descr->head)
	{
		descr->head = Node;
		return 1;//программа выполнена верно
	}

	//если корень уже есть

	//создаём указатель для обхода и ставим его в голову(корень) дерева
	BinTreeNode *temp = descr->head;

	int check;//переменная для хранения результата лексографического сравнения
//	char fl = '0';

	while (1)
	{
		//сравнивать будем по русским словам, т.к. наш словарь - русско-английский
		check = strcmp(Node->data.Russian, temp->data.Russian);

		if (check > 0)//если слово в алфовитном порядке после корневого, идём вправо
		{
			if (!temp->right)//если указатель вправо занулён, т.е. правого потомка ещё нет
			{
				temp->right = Node;//создаём узел
				break;//завершаем цикл
			}
			else//иначе двигаемся дальше вправо
			{
				temp = temp->right;
			}
		}
		else if (check < 0)//то же самое, только влево
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
		else//если слова совпали, не создаём новый узел
		{
			puts("That word already exists in database");
			break;
		}
	}

	return 1;
}

/*
Принцип работы:
Вначале *Node находится в корне дерева, после чего, опускаясь вглубь рекурсии движется
влево от корня дерева, пока не наткнётся на NULL, после чего рекурсия начинает сворачиваться,
но сразу же натыкается на следующее условие и вынуждена углубиться вправо.
Так происходит, пока *Node полностью не пройдёт левое поддрево.
Далее указатель переходит в правое поддрево и повторяет те же шаги, поки не достигнет
наибольшего элемента.
Только после этого рекурсия может окончательно свернуться и завершить работу функции.
*/

void Preorder(BinTreeNode *Node)//используем прямой обход
{
	if (Node)
	{
		showInfo(&Node->data);
		if (Node->left) Preorder(Node->left);
		if (Node->right) Preorder(Node->right);
	}
}

void Inorder(BinTreeNode *Node)//используем прямой обход
{
	if (Node)
	{
		if (Node->left) Inorder(Node->left);
		showInfo(&Node->data);
		if (Node->right) Inorder(Node->right);
	}
}

void Postorder(BinTreeNode *Node)//используем прямой обход
{
	if (Node)
	{
		if (Node->left) Postorder(Node->left);
		if (Node->right) Postorder(Node->right);
		showInfo(&Node->data);
	}
}

void ShowUsingRecursion(ListDescriptor descr, order type)
{//Здесь проверяем, не пусто ли дерево
	if (!descr.head)
	{
		puts("Empty!");
	}
	else//выбираем способ обхода
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
	Алгоритм точно такой, как и в рекурсивной функции, но реализован иначе.
	Вначале кладём корень в стек.
Затем, пока стек не опустеет, делаем следующее:
берём вершину стека, заходим в новый цикл, который продолжается, пока не будет достигнут самый меньший лист дерева;
Если есть правый потомок, кладём его в стек;
Показываем ключ текущего корня;
Двигаемся влево.
	Когда мы достигнем NULL, в вершине стека будет самый большой элемент текущего поддерева;
Читаем его.
	Цикл будет продолжаться, пока не будет достигнут самый правый лист дерева.
	В итоге на экране будет получено дерево после прямого обхода
*/

//обход и печать с помощью стека
int ShowUsingStack(ListDescriptor descr)
{
	//проверка на пустоту
	if (!descr.head)
	{
		puts("Empty!");
		return;
	}

	//создаём стек
	Stack stack;
	stack.head = NULL;

	//отправляем в стек корень дерева
	if (!AddToStack(&stack, descr.head))
	{//если произошла ошибка в выделении памяти под элемент стека
		return 0;
	}

	BinTreeNode *temp;//указатель для обхода

	while (stack.head)//пока стек не пуст
	{
		temp = pop(&stack);//берём вершину стека
		if (!temp)
		{
			puts("error");
			if (stack.head)//если не выделилась память под вершину стека и при этом стек не пуст,
			{
				ClearStack(&stack);// нужно освободить памят, выделенную под стек
			}
			return 0;
		}
		//пока указатель не пуст 
		while (temp)
		{
			if (temp->right)//если есть правый потомок
			{
				if (!AddToStack(&stack, temp->right))//вставляем его в стек
				{
					if (stack.head)
					{
						ClearStack(&stack);
					}
					return 0;
				}
			}
			showInfo(&temp->data);//показываем информацию
			temp = temp->left;//двигаемся влево
		}
	}
	return 1;
}


//удаление элемента
int DeleteItem(ListDescriptor* descr)
{
	//Проверяем, не пусто ли дерево
	if (!descr->head)
	{
		puts("Empty!");
		return 0;
	}

	puts("What word do you want to remove?");

	char buffer[STRSIZE];
	//не можем послать пустую строку
	FillStringCorrectly(buffer);

	BinTreeNode *temp = descr->head;//указатель для обхода и удаления
	BinTreeNode *parent = NULL;//указатель на родителя
	int check;
	char side;//направление

	//поиск элемента
	while (temp)
	{
		//сравнение строк
		check = strcmp(buffer, temp->data.Russian);

		if (!check)
		{//если нашли, завершаем цикл
			break;
		}
		else
		{
			parent = temp;//делаем текущий узел родителем
			if (check > 0)
			{
				side = 'R';//указываем, куда двигаемся
				temp = temp->right;//вправо
			}
			else
			{
				side = 'L';
				temp = temp->left;//влево
			}
		}
	}
	
	//если не нашли, возвращаем ошибку
	if (!temp)
	{
		puts("Not Found");
		return 0;
	}

	/*------------------------------------------------------------------------------------------
		Далее возможны несколько вариантов развития событий:
	1. Узел является листом
	2. Узел имеет только правого потомка
	3. Узел имеет только левого потомка
	4. Узел имеет обоих потомков
		При этом необходимо рассматривать возможность того, что узем может быть корнем дерева
	------------------------------------------------------------------------------------------*/

	//1. Узел является листом, если не имеет потомков
	if (!temp->left && !temp->right)
	{
		free(temp);//просто удаляем узел
		//проверяем, не был ли он корнем дерева
		if (!parent)
		{//если был, то зануляем указатель на корень, сигнализируя о пустоте дерева
			descr->head = NULL;
			return 1;
		}

		if (side == 'L')//если элемент был слева от родителя, зануляем его левый указатель
		{
			parent->left = NULL;
		}
		else
		{
			parent->right = NULL;//иначе - правый
		}

		return 1;
	}

	//2. Узел имеет правого потомка
	if (!temp->left)
	{
		if (!parent)//если корень
		{
			descr->head = temp->right;//потомок становится корнем
			free(temp);//удаляем узел
			return 1;
		}

		if (side == 'L')//если у родителя узел - левый
		{
			parent->left = temp->right;//делаем его правого потомка левым потомком родителя
		}
		else
		{
			parent->right = temp->right;//иначе - правым
		}

		free(temp);//удаляем
		return 1;
	}

	//3. Если имеется только левый потомок
	if (!temp->right)
	{
		//если он корень
		if (!parent)
		{
			descr->head = temp->left;//его левого потомка делаем головным
			free(temp);//удаляем узел
			return 1;
		}

		if (side == 'L')//если удаляемый узел - левый потомок родителя
		{
			parent->left = temp->left;//делаем потомка узла потомком родителя (перепрыгиваем)
		}
		else
		{
			parent->right = temp->left;//если правый, то все равно делаем левым
		}

		free(temp);//удаляем
		return 1;
	}


	//4. Если узел имеет двух потомков, то сам узел удалять не нужно.
	//	  Необходимо лишь заменить его значение на наименьшее (самое левое) значение его правого поддрева,
	//    и удалить узел, его содержавший

	BinTreeNode *RemoveKebab = temp;// этот указатель оставим на удаляемом узле
	parent = temp;
	temp = temp->right;//перейдём в правое поддрево

	side = 'R';//укажем, что последнее движение было совершено вправо
	while (temp->left)
	{//находим узел для замены
		side = 'L';
		parent = temp;
		temp = temp->left;
	}

	//заносим нужное значение
	strcpy(RemoveKebab->data.English, temp->data.English);
	strcpy(RemoveKebab->data.Russian, temp->data.Russian);

	//далее будем удалять узел, из которого копировали

	//если он не имеет потомков
	if (!temp->left && !temp->right)
	{
		free(temp);//удаляем
		//зануляем родительский указатель
		if (side == 'L')
		{
			parent->left = NULL;
		}
		else
		{
			parent->right = NULL;
		}
	}
	else//если же имеет хотя бы одного потомка
	{
		//правого потомка передаём родителю в зависимости от стороны прихода
		if (side == 'L')
		{
			parent->left = temp->right;
		}
		else
		{
			parent->right = temp->right;
		}

		free(temp);//удаляем
	}
	

	return 1;
}

//удаление
void Descent(BinTreeNode* Node)
{//очистка происходит по обратному обходу
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
	if (descr->head)//если дерево не пусто
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
