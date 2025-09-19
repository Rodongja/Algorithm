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
    // 각 링크드 리스트를 자유 저장소에서 제거하기
    int i = 0;
    for (i = 0; i < HT->TableSize; ++i)
    {
        List L = HT->Table[i];
        CHT_DestroyList(L);
    }
    // 해시 테이블을 자유 저장소에서 저게하기
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

    // 해당 주소가 비어 있는 경우
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
    // 주소를 해싱한다
    int Address = CHT_Hash(Key, Key.length(), HT->TableSize);

    // 해싱한 주소에 있는 링크드 리스트를 가져온다
    List TheList = HT->Table[Address];
    List Target = nullptr;
    if (TheList == nullptr)
    {
        return "";
    }

    // 값을 찾을 때까지 순차 탐색
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
