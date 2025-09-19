#include "Chaining.h"
#include <iostream>

using namespace std;

HashTable* CHT_CreateHashTable(int TableSize)
{
    HashTable* HT = (HashTable*)malloc(sizeof(HashTable));
    HT->Table = (List*)malloc(sizeof(Node) * TableSize);

    memset(HT->Table, 0, sizeof(List) * TableSize);

    HT->TableSize = TableSize;

    return HT;
}

void CHT_DestroyHashTable(HashTable* HT)
{
    // �� ��ũ�� ����Ʈ�� ���� ����ҿ��� �����ϱ�
    int i = 0;
    for (i = 0; i < HT->TableSize; ++i)
    {
        List L = HT->Table[i];
        CHT_DestroyList(L);
    }
    // �ؽ� ���̺��� ���� ����ҿ��� �����ϱ�
    free(HT->Table);
    free(HT);
}

Node* CHT_CreateNode(KeyType Key, ValueType Value)
{ 
    Node* NewNode = new Node;
    NewNode->Key = Key;
    NewNode->Value = Value;
    NewNode->Next = nullptr;

    return NewNode;
}

void CHT_DestroyNode(Node* TheNode)
{
    free(TheNode);
}

void CHT_DestroyList(List L)
{
    if (L == nullptr)
    {
        return;
    }

    if (L->Next != nullptr)
    {
        CHT_DestroyList(L->Next);
    }
    CHT_DestroyNode(L);
}

void CHT_Set(HashTable* HT, KeyType Key, ValueType Value)
{
    int Address = CHT_Hash(Key, Key.length(), HT->TableSize);
    Node* NewNode = CHT_CreateNode(Key, Value);

    // �ش� �ּҰ� ��� �ִ� ���
    if (HT->Table[Address] == nullptr)
    {
        HT->Table[Address] = NewNode;
    }
    else
    {
        List L = HT->Table[Address];
        NewNode->Next = L;
        HT->Table[Address] = NewNode;

        cout << "Collision occured : Key(" << Key << "), Address(" << Address << ")\n";
    }
}

ValueType CHT_Get(HashTable* HT, KeyType Key)
{
    // �ּҸ� �ؽ��Ѵ�
    int Address = CHT_Hash(Key, Key.length(), HT->TableSize);

    // �ؽ��� �ּҿ� �ִ� ��ũ�� ����Ʈ�� �����´�
    List TheList = HT->Table[Address];
    List Target = nullptr;
    if (TheList == nullptr)
    {
        return "";
    }

    // ���� ã�� ������ ���� Ž��
    while (TheList != nullptr)
    {
        if (TheList->Key == Key)
        {
            return TheList->Value;
        }

        TheList = TheList->Next;
    }
    return "";
}

int CHT_Hash(KeyType Key, int KeyLength, int TableSize)
{
    int i = 0;
    int HashValue = 0;

    for (i = 0; i < KeyLength; ++i)
    {
        HashValue = (HashValue << 3) + Key[i];
    }

    HashValue = HashValue % TableSize;

    return HashValue;
}
