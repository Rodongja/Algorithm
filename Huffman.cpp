#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define MAX_CHAR 256
#define MAX_BIT 8

typedef unsigned int UINT;
typedef unsigned char UCHAR; // char는 문자 처리에 사용, unsigned char는 비트 연산 처리에 사용 

using namespace std;

typedef struct TagSymbolInfo
{
	UCHAR Symbol;
	int Frequency;
}SymbolInfo;

typedef struct TagHuffmanNode
{
	SymbolInfo Data;
	struct TagHuffmanNode* Left;
	struct TagHuffmanNode* Right;
}HuffmanNode;

typedef struct TagBitBuffer
{
	// 바이트(UCHAR) 단위의 벡터
	vector<UCHAR> Buffer;
	// 기록된 비트 수
	UINT Size;
}BitBuffer;

typedef struct TagHuffmanCode
{
	UCHAR Code[MAX_BIT];
	size_t Size;
}HuffmanCode;

// 우선 순위 비교 (최소 힙)
// 빈도수가 낮은 문자를 우선적으로 처리하기 위해 사용
struct Compare 
{
	bool operator()(HuffmanNode* a, HuffmanNode* b) 
	{
		// a의 빈도수가 b의 빈도수보다 크면 true 반환
		return a->Data.Frequency > b->Data.Frequency;
	}
};

HuffmanNode* Huffman_CreateNode(SymbolInfo NewData);
void Huffman_DestroyTree(HuffmanNode* Node);
void Huffman_AddBit(BitBuffer* Buffer, char value);
void Huffman_Encode(HuffmanNode** Tree, UCHAR* Source, BitBuffer* Encoded, HuffmanCode CodeTable[MAX_CHAR]);
void Huffman_Decode(HuffmanNode* Tree, BitBuffer* Encoded, UCHAR* Decoded);
void Huffman_BuildPrefixTree(HuffmanNode** Tree, SymbolInfo SymbolInfoTable[MAX_CHAR]);
void Huffman_BuildCodeTable(HuffmanNode* Tree, HuffmanCode CodeTable[MAX_CHAR], UCHAR Code[MAX_BIT], size_t Size);
void Huffman_PrintBinary(BitBuffer* Buffer);

// 노드 생성
HuffmanNode* Huffman_CreateNode(SymbolInfo NewData)
{
	HuffmanNode* NewNode = new HuffmanNode;
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;

	return NewNode;
}

// 트리 제거
void Huffman_DestroyTree(HuffmanNode* Node)
{
	if (Node == NULL)
		return;

	Huffman_DestroyTree(Node->Left);
	Huffman_DestroyTree(Node->Right);
	delete(Node);
}

// 비트 추가
void Huffman_AddBit(BitBuffer* Buffer, char Bit)
{
	// 비트 마스크 (1000 0000)
	UCHAR Mask = 0x80;

	// UCHAR는 바이트 단위이므로 비트 수가 8의 배수가 될 때마다 새로운 바이트 추가
	if (Buffer->Size % 8 == 0)
	{
		Buffer->Buffer.resize(Buffer->Size / 8 + 1);
		Buffer->Buffer[Buffer->Size / 8] = 0x00;
	}

	// Mask 값을 비트만큼 shift
	Mask >>= Buffer->Size % 8;

	// 비트 값 or 연산
	if(Bit == 1)
		Buffer->Buffer[Buffer->Size / 8] |= Mask;
	// 비트 값 and 연산
	else
		Buffer->Buffer[Buffer->Size / 8] &= ~Mask;

	// 비트 수 증가
	Buffer->Size++;
}

// 인코딩
void Huffman_Encode(HuffmanNode** Tree, UCHAR* Source, BitBuffer* Encoded, HuffmanCode CodeTable[MAX_CHAR])
{
	int i = 0, j = 0;

	// 빈도수 테이블 생성
	SymbolInfo SymbolInfoTable[MAX_CHAR];
	// 임시 코드 저장용 배열
	UCHAR Temporary[MAX_BIT];

	// 빈도수 초기화
	for (i = 0; i < MAX_CHAR; i++)
	{		
		SymbolInfoTable[i].Symbol = i;
		SymbolInfoTable[i].Frequency = 0;
	}

	i = 0;
	// 빈도수 계산
	while (Source[i] != '\0')
	{
		// 해당 문자의 빈도수 증가
		SymbolInfoTable[Source[i++]].Frequency++;
	}

	// 접두사 트리 생성
	Huffman_BuildPrefixTree(Tree, SymbolInfoTable);

	// 코드 테이블 생성
	Huffman_BuildCodeTable(*Tree, CodeTable, Temporary, 0);

	i = 0;
	// 실제 인코딩 수행
	while(Source[i] != '\0')
	{
		// 해당 문자의 비트 수
		size_t BitCount = CodeTable[Source[i]].Size;

		// 코드 테이블에서 비트 단위로 인코딩
		for (j = 0; j < BitCount; j++)
		{
			Huffman_AddBit(Encoded, CodeTable[Source[i]].Code[j]);
		}
		// 다음 문자로 이동
		i++;
	}
}

// 디코딩
void Huffman_Decode(HuffmanNode* Tree, BitBuffer* Encoded, UCHAR* Decoded)
{
	int i;
	int Index = 0;
	// 현재 노드를 루트로 초기화
	HuffmanNode* Current = Tree;

	// 인코딩된 비트 수만큼 반복
	for (i = 0; i <= Encoded->Size; i++)
	{
		// 비트 마스크
		UCHAR Mask = 0x80; // 1000 0000

		// 리프 노드에 도달한 경우
		if (Current->Left == NULL && Current->Right == NULL)
		{
			// 문자를 디코딩 배열에 저장
			Decoded[Index++] = Current->Data.Symbol;
			// 다시 루트 노드로 이동
			Current = Tree;
		}

		// 비트 마스크를 i % 8만큼 오른쪽으로 시프트
		Mask >>= i % 8;

		// 비트 값에 따라 왼쪽 또는 오른쪽 자식 노드로 이동
		if ((Encoded->Buffer[i / 8] & Mask) != Mask)
			Current = Current->Left;
		else
			Current = Current->Right;
	}
	// 문자열 종료 문자 추가
	Decoded[Index] = '\0';
}

// 접두사 트리 생성
void Huffman_BuildPrefixTree(HuffmanNode** Tree, SymbolInfo SymbolInfoTable[MAX_CHAR])
{
	// 1.저장되는 자료형 2. 내부 컨테이너 3. 우선순위 비교 함수
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // 1. 빈도 > 0인 문자로 노드 생성 후 우선순위 큐에 삽입
    for (int i = 0; i < MAX_CHAR; i++)
    {
		// 빈도수가 0보다 큰 경우에만 노드 생성
        if (SymbolInfoTable[i].Frequency > 0)
        {
			// 노드 생성
            HuffmanNode* node = Huffman_CreateNode(SymbolInfoTable[i]);
			// 우선순위 큐에 삽입
            pq.push(node);
        }
    }

    // 2. 최소 힙에서 두 개 노드를 꺼내 새로운 부모 노드로 합치기
    while (pq.size() > 1)
    {
		// 두 개의 최소 빈도 노드 추출
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

		// 두 노드를 합친 새로운 부모 노드 생성
        SymbolInfo combinedData = {0, left->Data.Frequency + right->Data.Frequency};
		// 부모 노드 생성
        HuffmanNode* parent = Huffman_CreateNode(combinedData);
		// 자식 노드 연결
        parent->Left = left;
        parent->Right = right;
		// 부모 노드를 우선순위 큐에 삽입
        pq.push(parent);
    }

	// 3. 최종 트리의 루트 노드 설정
    *Tree = pq.top();
}

// 코드 테이블 생성
void Huffman_BuildCodeTable(HuffmanNode* Tree, HuffmanCode CodeTable[MAX_CHAR], UCHAR Code[MAX_BIT], size_t Size)
{
	// 노드가 NULL인 경우 반환
	if (Tree == NULL)
		return;

	// 왼쪽 자식 노드로 이동
	if (Tree->Left != NULL)
	{
		Code[Size] = 0;
		Huffman_BuildCodeTable(Tree->Left, CodeTable, Code, Size + 1);
	}

	// 오른쪽 자식 노드로 이동
	if (Tree->Right != NULL)
	{
		Code[Size] = 1;
		Huffman_BuildCodeTable(Tree->Right, CodeTable, Code, Size + 1);
	}

	// 리프 노드에 도달한 경우 코드 테이블에 코드 저장
	if (Tree->Left == NULL && Tree->Right == NULL)
	{
		int i;

		// 코드 테이블에 코드 복사
		for (i = 0; i < Size; i++)
		{
			CodeTable[Tree->Data.Symbol].Code[i] = Code[i];
		}
		// 코드 크기 저장
		CodeTable[Tree->Data.Symbol].Size = Size;
	}
}

// 비트 버퍼 출력
void Huffman_PrintBinary(BitBuffer* Buffer)
{
	int i;
	// 비트 단위로 출력
	for (i = 0; i < Buffer->Size; i++)
	{
		UCHAR Mask = 0x80; // 1000 0000
		Mask >>= i % 8;

		// 비트 값 출력
		cout << ((Buffer->Buffer[i / 8] & Mask) == Mask);
	}
}

int main()
{
    string Source = "This Is Algorithms.";
    string Decoded = "";

    HuffmanNode* Tree = NULL;

    // Initialize the BitBuffer properly
    BitBuffer Encoded;
    Encoded.Size = 0;
    Encoded.Buffer = vector<UCHAR>();

    HuffmanCode CodeTable[MAX_CHAR];

    memset(&CodeTable, 0, sizeof(HuffmanCode) * MAX_CHAR);

    // Convert std::string to UCHAR* for compatibility
    UCHAR* SourceUCHAR = (UCHAR*)Source.c_str();

    Huffman_Encode(&Tree, SourceUCHAR, &Encoded, CodeTable);
	
	cout << "Original Size: " << (Source.size() + 2 + 10) * sizeof(char) * 8 << " Encoded Size:" << Encoded.Size << endl;

	Decoded.resize(Source.length() + 1);
	Huffman_Decode(Tree, &Encoded, (UCHAR*)Decoded.data());
	
	cout << "Original : " << Source << endl;
	cout << "Encoded : ";

	Huffman_PrintBinary(&Encoded);

	cout << endl;

	cout << "Decoded : " << Decoded << endl;

	Huffman_DestroyTree(Tree);

	return 0;
}
