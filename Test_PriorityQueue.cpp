#include "PriorityQueue.h"
#include <iostream>

using namespace std;

void PrintNode(PQNode* Node)
{
	cout << "작업명 : " << Node->Data << " (우선순위:" << Node->Priority << ")\n";
}

int main()
{
	PriorityQueue* PQ = PQ_Create(3);
	PQNode Popped;

	PQNode Nodes[7] =
	{
		{ 34, (const char*)"코딩"},
		{ 12, (const char*)"고객미팅" },
		{ 87, (const char*)"커피타기" },
		{ 45, (const char*)"문서작성" },
		{ 35, (const char*)"디버깅" },
		{ 66, (const char*)"이닦기" }
	};

	PQ_Enqueue(PQ, Nodes[0]);
	PQ_Enqueue(PQ, Nodes[1]);
	PQ_Enqueue(PQ, Nodes[2]);
	PQ_Enqueue(PQ, Nodes[3]);
	PQ_Enqueue(PQ, Nodes[4]);
	PQ_Enqueue(PQ, Nodes[5]);

	cout << "큐에 남아 있는 작업의 수 : " << PQ->UsedSize << "\n";

	while (!PQ_IsEmpty(PQ))
	{
		PQ_Dequeue(PQ, &Popped);
		PrintNode(&Popped);
	}

	return 0;
}