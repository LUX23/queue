/*
* ����� ���� ��� ������� X � Y, ���������� ������������ �����.
* �� ������ ������� ������������ ����������� �� ������ x��y, ��������������. 
* ���� x�<�y, �� ����� (x�+�y) ���������� � ����� ������� X, ����� ����� (x���y) ���������� � ����� ������� Y. 
* ���������� �������������, ����� ���� �� �������� ���������� ������.
* ����������� ����� �����, ����� ������� ���� �� �������� ������ ������.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct QueueNode // ������� ������� 
{
	int info;
	QueueNode* next;
};

struct Queue // ������ � ����� �������
{
	QueueNode* Begin;
	QueueNode* End;
};

void init(Queue& Q) // ������������� �������
{ 
	Q.Begin = NULL; 
	Q.End = NULL; 
}

bool IsEmpty(Queue& Q) // ���������, �������� �� ������� ������
{
	return ((Q.Begin == NULL) && (Q.End == NULL));
}

void EnQueue(Queue& Q, int num) // �������� ������� � ������� 
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

int DeQueue(Queue& Q) // ������� ������� � ������� 
{

	if (IsEmpty(Q)) // �������� �� ������� �������� ������� �� ������ �������
		throw "������! ������� ������ �� ������ �������!";

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

int Front(Queue& Q) // �������� �������� ������� �������� ������� 
{
	if (IsEmpty(Q)) // �������� �� ������� �������� ������� �� ������ �������
		throw "������! ������� ������ �� ������ �������!";

	return (Q.Begin->info);
}

void Destroy(Queue& Q) // �������� �������
{
	while (!IsEmpty(Q))
		DeQueue(Q);
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");

	Queue X;
	Queue Y;

	init(X); // ������������� ������� X
	init(Y); // ������������� ������� Y

	// ������ �������� �� ������
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
		// ���������� 
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

	cout << "����� ����� = " << step << endl;

	system("PAUSE");
	return 0;
}