#include "GraphTraversal.h"
#include <iostream>

using namespace std;

void DFS(Vertex* V)
{
	Edge* E = nullptr;

	cout << V->Data << " ";

	V->Visited = Visited;

	E = V->AdjacencyList;

	while (E != nullptr)
	{
		if (E->Target != nullptr && E->Target->Visited == NotVisited)
			DFS(E->Target);
		E = E->Next;
	}
}

void BFS(Vertex* V, LinkedQueue* Queue)
{
	Edge* E = nullptr;

	cout << V->Data << " ";
	V->Visited = Visited;

	// 큐에 노드 삽입
	LQ_Enqueue(Queue, LQ_CreateNode(V));

	while (!LQ_IsEmpty(Queue))
	{
		Node* Popped = LQ_Dequeue(Queue);
		V = Popped->Data;
		E = V->AdjacencyList;

		while (E != nullptr)
		{
			V = E->Target;

			if (V != nullptr && V->Visited == NotVisited)
			{
				cout << V->Data << " ";
				V->Visited = Visited;
				LQ_Enqueue(Queue, LQ_CreateNode(V));
			}
			E = E->Next;
		}
	}
}
