/*
* Пусть даны две очереди X и Y, содержащие вещественные числа.
* Из каждой очереди одновременно извлекается по одному x и y, соответственно. 
* Если x < y, то число (x + y) помещается в конец очереди X, иначе число (x – y) помещается в конец очереди Y. 
* Вычисления заканчиваются, когда одна из очередей становится пустой.
* Подсчитайте число шагов, через которое одна из очередей станет пустой.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct QueueNode // элемент очереди 
{
	int info;
	QueueNode* next;
};

struct Queue // начало и конец очереди
{
	QueueNode* Begin;
	QueueNode* End;
};

void init(Queue& Q) // инициализация очереди
{ 
	Q.Begin = NULL; 
	Q.End = NULL; 
}

bool IsEmpty(Queue& Q) // проверить, является ли очередь пустой
{
	return ((Q.Begin == NULL) && (Q.End == NULL));
}

void EnQueue(Queue& Q, int num) // добавить элемент в очередь 
{
	QueueNode* p; 
	p = new QueueNode;

	p->info = num; 
	p->next = NULL; 

	if (Q.Begin == NULL)
		Q.Begin = p;

	else 
		Q.End->next = p; 

	Q.End = p; 
}

int DeQueue(Queue& Q) // удалить элемент в очереди 
{

	if (IsEmpty(Q)) // проверка на попытку получить элемент из пустой очереди
		throw "Ошибка! Попытка чтения из пустой очереди!";

	int val;
	QueueNode* p; 

	p = Q.Begin;
	val = Q.Begin->info;
	Q.Begin = p->next;

	if (Q.Begin == NULL)
		Q.End = NULL;

	delete p;

	return(val);
}

int Front(Queue& Q) // получить значение первого элемента очереди 
{
	if (IsEmpty(Q)) // проверка на попытку получить элемент из пустой очереди
		throw "Ошибка! Попытка чтения из пустой очереди!";

	return (Q.Begin->info);
}

void Destroy(Queue& Q) // удаление очереди
{
	while (!IsEmpty(Q))
		DeQueue(Q);
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");

	Queue X;
	Queue Y;

	init(X); // инициализация очереди X
	init(Y); // инициализация очереди Y

	// чтение очередей из файлов
	float x, y;
	fstream file;

	file.open("X.txt");
	while (file >> x)
		EnQueue(X, x);
	file.close();

	file.open("Y.txt");
	while (file >> y)
		EnQueue(Y, y);
	file.close();

	int step = 0;
	try
	{
		// вычисление 
		while (!IsEmpty(X) && !IsEmpty(Y))
		{
			if (Front(X) < Front(Y))
				EnQueue(X, (DeQueue(X) + DeQueue(Y)));

			else 
				EnQueue(Y, (DeQueue(X) - DeQueue(Y)));

			step++;
		}

		Destroy(X);
		Destroy(Y);
	}

	catch (const char* ErrMSG)
	{
		cout << ErrMSG;
		exit(EXIT_FAILURE);
	}

	cout << "Число шагов = " << step << endl;

	system("PAUSE");
	return 0;
}