#include "LinkedQueue.h"

void LQ_CreateQueue(LinkedQueue** Queue)
{
    (*Queue) = (LinkedQueue*)malloc(sizeof(LinkedQueue));
    (*Queue)->Front = nullptr;
	(*Queue)->Rear = nullptr;
	(*Queue)->Count = 0;
}

void LQ_DestroyQueue(LinkedQueue* Queue)
{
    while (!LQ_IsEmpty(Queue))
    {
		Node* Popped = LQ_Dequeue(Queue);
		LQ_DestroyNode(Popped);
    }

	free(Queue);
}

Node* LQ_CreateNode(ElementType NewData)
{
	Node* NewNode = new Node;
	NewNode->Data = NewData;
	NewNode->NextNode = nullptr;

    return NewNode;
}

void LQ_DestroyNode(Node* _Node)
{
	delete _Node->Data;
	delete _Node;
}

void LQ_Enqueue(LinkedQueue* Queue, Node* NewNode)
{
	if (Queue->Front == NULL)
	{
		Queue->Front = NewNode;
		Queue->Rear = NewNode;
		Queue->Count++;
	}
	else
	{
		Queue->Rear->NextNode = NewNode;
		Queue->Rear = NewNode;
		Queue->Count++;
	}
}

Node* LQ_Dequeue(LinkedQueue* Queue)
{
	Node* Front = Queue->Front;

	if (Queue->Front->NextNode == NULL)
	{
		Queue->Front = NULL;
		Queue->Rear = NULL;
	}
	else
	{
		Queue->Front = Queue->Front->NextNode;
	}

	Queue->Count--;

	//Node*를 리턴했기 때문에 호출자가 메모리를 해제 해야함
	return Front;
}

int LQ_IsEmpty(LinkedQueue* Queue)
{

    return (Queue->Front == NULL);
}
