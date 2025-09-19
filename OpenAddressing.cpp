#include "OpenAddressing.h"
#include <iostream>

using namespace std;

HashTable* OAHT_CreateHashTable(int TableSize)
{
    HashTable* HT = new HashTable;
    HT->Table = new ElementType[TableSize];
    HT->TableSize = TableSize;
    HT->OccupiedCount = 0;

    for (int i = 0; i < TableSize; ++i)
    {
        HT->Table[i].Status = EMPTY;
    }

    return HT;
}

void OAHT_DestroyHashTable(HashTable* HT)
{
    // 각 링크드 리스트를 자유 저장소에서 제거하기
    int i = 0;
    for (i = 0; i < HT->TableSize; ++i)
    {
        OAHT_ClearElement(&HT->Table[i]);
    }

    // 해시 테이블을 자유 저장소에서 제거하기
    delete[] HT->Table;
    HT->Table = nullptr;
    delete HT;
}

void OAHT_ClearElement(ElementType* Element)
{
    if (Element->Status == EMPTY)
        return;

    Element->Key.clear();
    Element->Value.clear();
}

void OAHT_Set(HashTable** HT, KeyType Key, ValueType Value)
{
    int KeyLen, Address, StepSize;
    double Usage;

    Usage = (double)(*HT)->OccupiedCount / (*HT)->TableSize;

    if (Usage > 0.5)
    {
        OAHT_Rehash(HT);
    }

    KeyLen = Key.length();
    Address = OAHT_Hash(Key, KeyLen, (*HT)->TableSize);
    StepSize = OAHT_Hash2(Key, KeyLen, (*HT)->TableSize);

    while ((*HT)->Table[Address].Status != EMPTY && (*HT)->Table[Address].Key != Key)
    {
        cout << "Collision occured! : Key(" << Key << "), Address(" << Address << "), StepSize(" << StepSize << ")\n";

        Address = (Address + StepSize) % (*HT)->TableSize;
    }

    (*HT)->Table[Address].Key = Key;
    (*HT)->Table[Address].Value = Value;
    (*HT)->Table[Address].Status = OCCUPIED;
    (*HT)->OccupiedCount++;

    cout << "Key(" << Key << ") entered at address(" << Address << ")\n";
}

ValueType OAHT_Get(HashTable* HT, KeyType Key)
{
    int KeyLen = Key.size();

    int Address = OAHT_Hash(Key, KeyLen, HT->TableSize);
    int StepSize = OAHT_Hash2(Key, KeyLen, HT->TableSize);

    while (HT->Table[Address].Status != EMPTY && HT->Table[Address].Key != Key)
    {
        Address = (Address + StepSize) % HT->TableSize;
    }

    return HT->Table[Address].Value;
}

int OAHT_Hash(KeyType Key, int KeyLength, int TableSize)
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

int OAHT_Hash2(KeyType Key, int KeyLength, int TableSize)
{
    int i = 0;
    int HashValue = 0;
    
    for (i = 0; i < KeyLength; ++i)
    {
        HashValue = (HashValue << 2) + Key[i];
    }

    HashValue = HashValue % (TableSize - 3);
    
    return HashValue + 1;
}

void OAHT_Rehash(HashTable** HT)
{
    if (!HT || !(*HT) || !(*HT)->Table) return;

    int oldSize = (*HT)->TableSize;

    ElementType* OldTable = (*HT)->Table;

    // 새 해시테이블 생성
    HashTable* NewHT = OAHT_CreateHashTable((*HT)->TableSize * 2);

    cout << "\nRefreshed. New table size is : " << NewHT->TableSize << "\n\n";

    // 이전의 해시 테이블에 있던 데이터를 새 해시 테이블로 옮긴다
    for (int i = 0; i < (*HT)->TableSize; ++i)
    {
        if (OldTable[i].Status == OCCUPIED)
        {
            OAHT_Set(&NewHT, OldTable[i].Key, OldTable[i].Value);
        }
    }

    // 이전의 해시 테이블 소멸
    OAHT_DestroyHashTable((*HT));

    // HT 포인터에는 새 해시 테이블의 주소를 대입한다
    (*HT) = NewHT;
}