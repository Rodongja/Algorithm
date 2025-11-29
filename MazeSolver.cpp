#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define MAX_BUFFER 1024
#define INIT_VALUE -1

#define START 'S'	// 시작점
#define GOAL 'G'	// 도착점
#define WAY ' '		// 길
#define WALL '#'	// 벽
#define MARKED '+'	// 탈출구로 향하는 길 표식

enum DIRECTION {NORTH, SOUTH, EAST, WEST};
enum RESULT {FAIL,SUCCEED};

using namespace std;

typedef struct tagPosition
{
	int x;
	int y;
} Position;

typedef struct tagMazeInfo
{
	int ColumnSize; // 너비
	int RowSize;    // 높이

	vector<vector<char>> Data; // 미로 데이터
}MazeInfo;

int Solve(MazeInfo* Maze);
int MoveTo(MazeInfo* Maze, Position* Current, int Direction);
int GetNextStep(MazeInfo* Maze, Position* Current, int Direction, Position* Next);
int GetMaze(MazeInfo* Maze);

int Solve(MazeInfo* Maze)
{
	int i = 0;
	int j = 0;
	int StartFound = FAIL;
	int Result = FAIL;

	Position Start;

	for (i = 0; i < Maze->RowSize; i++)
	{
		for(j=0; j<Maze->ColumnSize; j++)
		{
			if (Maze->Data[i][j] == START)
			{
				Start.x = j;
				Start.y = i;
				StartFound = SUCCEED;
				break;
			}
		}
	}

	if (StartFound == FAIL)
	{
		return FAIL;
	}

	if (MoveTo(Maze, &Start, NORTH))
		Result = SUCCEED;
	else if (MoveTo(Maze, &Start, SOUTH))
		Result = SUCCEED;
	else if (MoveTo(Maze, &Start, EAST))
		Result = SUCCEED;
	else if (MoveTo(Maze, &Start, WEST))
		Result = SUCCEED;

	Maze->Data[Start.y][Start.x] = START;
	
	return Result;
}

int MoveTo(MazeInfo* Maze, Position* Current, int Direction)
{
	int i = 0;
	int Dirs[] = { NORTH, SOUTH, EAST, WEST };

	Position Next;

	if (Maze->Data[Current->y][Current->x] == GOAL)
	{
		return SUCCEED;
	}

	if (Maze->Data[Current->y][Current->x] == MARKED)
	{
		return FAIL;
	}

	Maze->Data[Current->y][Current->x] = MARKED;


	for (i = 0; i < 4; i++)
	{
		if (GetNextStep(Maze, Current, Dirs[i], &Next) == FAIL)
		{
			continue;
		}

		if (MoveTo(Maze, &Next, NORTH) == SUCCEED)
			return SUCCEED;
	}

	Maze->Data[Current->y][Current->x] = WAY;

	return FAIL;
}

int GetNextStep(MazeInfo* Maze, Position* Current, int Direction, Position* Next)  
{  
    switch(Direction)  
    {  
    case NORTH:  
        Next->x = Current->x;  
        Next->y = Current->y - 1;  

        if(Next->y == -1)  
            return FAIL;  
        break;  
    case SOUTH:  
        Next->x = Current->x;  
        Next->y = Current->y + 1;  
        if(Next->y == Maze->RowSize)  
            return FAIL;  
        break;  
    case EAST:  
        Next->x = Current->x + 1;  
        Next->y = Current->y;  
        if(Next->x == Maze->ColumnSize)  
            return FAIL;  
        break;  
    case WEST:  
        Next->x = Current->x - 1;  
        Next->y = Current->y;  
        if(Next->x == -1)  
            return FAIL;  
        break;  
    default:  
        return FAIL;  
    }  

    if (Maze->Data[Next->y][Next->x] == WALL)  
        return FAIL;  

    if (Maze->Data[Next->y][Next->x] == MARKED)  
        return FAIL;  

    return SUCCEED;  
}

int GetMaze(MazeInfo* Maze)
{
	string FilePath;
	cout << "Enter maze file path : " << endl;
	getline(cin, FilePath);

	ifstream fp(FilePath);
	if(!fp.is_open())
	{
		cout << "Cannot open file: " << FilePath << endl;
		return FAIL;
	}

	vector<string> Lines;
	string LineText;

	while(getline(fp,LineText))
	{
		Lines.push_back(LineText);
	}
	fp.close();

	if (Lines.empty())
	{
		cout << "Maze file is empty." << endl;
		return FAIL;
	}

	int RowSize = Lines.size();
	int ColumnSize = Lines[0].size();

	for(const auto& Line : Lines)
	{
		if(Line.size() != ColumnSize)
		{
			cout << "Maze data is not valid." << endl;
			return FAIL;
		}
	}

	Maze->RowSize = RowSize;
	Maze->ColumnSize = ColumnSize;
	Maze->Data.resize(RowSize);

	for(int i = 0; i < RowSize; i++)
	{
		Maze->Data[i].resize(ColumnSize);
		for(int j = 0; j < ColumnSize; j++)
		{
			Maze->Data[i][j] = Lines[i][j];
		}
	}

	return SUCCEED;
}

int main()
{
	int i = 0;
	int j = 0;

	MazeInfo Maze;

	// 미로 정보 로드
	if (GetMaze(&Maze) == FAIL)
	{
		cout << "Failed to load maze." << endl;
		return 0;
	}

	// 미로 탈출 시도
	if (Solve(&Maze) == FAIL)
	{
		cout << "No solution found." << endl; // 탈출구를 찾지 못함
		return 0;
	}

	// 탈출구로 향하는 길 출력
	for (i = 0; i < Maze.RowSize; i++)
	{
		for(j=0; j< Maze.ColumnSize; j++)
		{
			cout << Maze.Data[i][j];
		}
		cout << endl;
	}

	return 0;
}