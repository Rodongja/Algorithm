#include "MST.h"
#include <iostream>

using namespace std;

void Prim(Graph* G, Vertex* StartVertex, Graph* MST)
{
	int i = 0;
	PQNode StartNode = { 0,StartVertex };
	PriorityQueue* PQ = PQ_Create(10);

	Vertex* CurrentVertex = nullptr;
	Edge* CurrentEdge = nullptr;

	int* Weights = new int[G->VertexCount];
	Vertex** MSTVertices = new Vertex* [G->VertexCount];
	Vertex** Fringes = new Vertex* [G->VertexCount];
	Vertex** Precedences = new Vertex* [G->VertexCount];

	CurrentVertex = G->Vertices;
	while (CurrentVertex != nullptr)
	{
		Vertex* NewVertex = CreateVertex(CurrentVertex->Data);
		AddVertex(MST, NewVertex);

		Fringes[i] = nullptr;
		Precedences[i] = nullptr;
		MSTVertices[i] = NewVertex;
		Weights[i] = MAX_WEIGHT;
		CurrentVertex = CurrentVertex->Next;
		++i;
	}

	PQ_Enqueue(PQ, StartNode);
	Weights[StartVertex->Index] = 0;
	while (!PQ_IsEmpty(PQ))
	{
		PQNode Popped;

		PQ_Dequeue(PQ, &Popped);
		CurrentVertex = (Vertex*)Popped.Data;

		Fringes[CurrentVertex->Index] = CurrentVertex;

		CurrentEdge = CurrentVertex->AdjacencyList;

		while (CurrentEdge != nullptr)
		{
			Vertex* TargetVertex = CurrentEdge->Target;

			if (Fringes[TargetVertex->Index] == nullptr && CurrentEdge->Weight < Weights[TargetVertex->Index])
			{
				PQNode NewNode = { CurrentEdge->Weight, TargetVertex };
				PQ_Enqueue(PQ,NewNode );

				Precedences[TargetVertex->Index] = CurrentEdge->From;
				Weights[TargetVertex->Index] = CurrentEdge->Weight;
			}
			CurrentEdge = CurrentEdge->Next;
		}
	}

	for (i = 0; i < G->VertexCount; ++i)
	{
		int FromIndex, ToIndex;

		if (Precedences[i] == nullptr)
		{
			continue;
		}
		FromIndex = Precedences[i]->Index;
		ToIndex = i;

		AddEdge(MSTVertices[FromIndex], CreateEdge(MSTVertices[FromIndex], MSTVertices[ToIndex], Weights[i]));
		AddEdge(MSTVertices[ToIndex], CreateEdge(MSTVertices[ToIndex], MSTVertices[FromIndex], Weights[i]));
	}

	delete[] Fringes;
	delete[] Precedences;
	delete[] MSTVertices;
	delete[] Weights;

	PQ_Destroy(PQ);
}

void Kruskal(Graph* G, Graph* MST)
{
	int i;
	Vertex* CurrentVertex = nullptr;
	Vertex** MSTVertices = new Vertex * [G->VertexCount];
	DisjointSet** VertexSet = new DisjointSet * [G->VertexCount]; 
	int maxEdges = G->VertexCount * G->VertexCount;
	PriorityQueue* PQ = PQ_Create(maxEdges);
	
	i = 0;
	CurrentVertex = G->Vertices;
	while (CurrentVertex != nullptr)
	{
		Edge* CurrentEdge;

		VertexSet[i] = DS_MakeSet(CurrentVertex);
		MSTVertices[i] = CreateVertex(CurrentVertex->Data);
		AddVertex(MST, MSTVertices[i]);

		CurrentEdge = CurrentVertex->AdjacencyList;
		while (CurrentEdge != nullptr)
		{
			PQNode NewNode = { CurrentEdge->Weight,CurrentEdge };
			PQ_Enqueue(PQ, NewNode);

			CurrentEdge = CurrentEdge->Next;
		}
		CurrentVertex = CurrentVertex->Next;
		++i;
	}

	while (!PQ_IsEmpty(PQ))
	{
		Edge* CurrentEdge;
		int FromIndex;
		int ToIndex;
		PQNode Popped;

		PQ_Dequeue(PQ, &Popped);
		CurrentEdge = (Edge*)Popped.Data;

		cout << CurrentEdge->From->Data << " - " << CurrentEdge->Target->Data << " : " << CurrentEdge->Weight << "\n";

		FromIndex = CurrentEdge->From->Index;
		ToIndex = CurrentEdge->Target->Index;

		if (DS_FindSet(VertexSet[FromIndex]) != DS_FindSet(VertexSet[ToIndex]))
		{
			AddEdge(MSTVertices[FromIndex], CreateEdge(MSTVertices[FromIndex], MSTVertices[ToIndex], CurrentEdge->Weight));

			AddEdge(MSTVertices[ToIndex], CreateEdge(MSTVertices[ToIndex], MSTVertices[FromIndex], CurrentEdge->Weight));

			DS_UnionSet(VertexSet[FromIndex], VertexSet[ToIndex]);
		}
	}

	for (i = 0; i < G->VertexCount; ++i)
	{
		DS_DestroySet(VertexSet[i]);
	}
	delete[] VertexSet;
	delete[] MSTVertices;
}
 