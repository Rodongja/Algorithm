#include "PriorityQueue.h"
#include <iostream>

using namespace std;

void PrintNode(PQNode* Node)
{
	cout << "�۾��� : " << Node->Data << " (�켱����:" << Node->Priority << ")\n";
}

int main()
{
	PriorityQueue* PQ = PQ_Create(3);
	PQNode Popped;

	PQNode Nodes[7] =
	{
		{ 34, (const char*)"�ڵ�"},
		{ 12, (const char*)"������" },
		{ 87, (const char*)"Ŀ��Ÿ��" },
		{ 45, (const char*)"�����ۼ�" },
		{ 35, (const char*)"�����" },
		{ 66, (const char*)"�̴۱�" }
	};

	PQ_Enqueue(PQ, Nodes[0]);
	PQ_Enqueue(PQ, Nodes[1]);
	PQ_Enqueue(PQ, Nodes[2]);
	PQ_Enqueue(PQ, Nodes[3]);
	PQ_Enqueue(PQ, Nodes[4]);
	PQ_Enqueue(PQ, Nodes[5]);

	cout << "ť�� ���� �ִ� �۾��� �� : " << PQ->UsedSize << "\n";

	while (!PQ_IsEmpty(PQ))
	{
		PQ_Dequeue(PQ, &Popped);
		PrintNode(&Popped);
	}

	return 0;
}