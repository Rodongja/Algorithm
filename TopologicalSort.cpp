#include "TopologicalSort.h"
#include <iostream>

using namespace std;

void TopologicalSort(Vertex* V, Node** List)
{
	while (V != nullptr && V->Visited == NotVisited)
	{
		TS_DFS(V, List);
		V = V->Next;
	}
}

void TS_DFS(Vertex* V, Node** List)
{
	Node* NewHead = nullptr;
	Edge* E = nullptr;

	V->Visited = Visited;

	E = V->AdjacencyList;

	while (E != nullptr)
	{
		if (E->Target != nullptr && E->Target->Visited == NotVisited)
		{
			TS_DFS(E->Target, List);
		}
		E = E->Next;
	}

	cout << V->Data << "\n";

	NewHead = SLL_CreateNode(V);
	SLL_InsertNewHead(List, NewHead);
}
