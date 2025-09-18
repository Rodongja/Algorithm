#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <array>

using namespace std;

void swap(int* l, int* r)
{
	// 자리 스왑
	int temp = *l;
	*l = *r;
	*r = temp;
}

int partition(array<int,9>& arr, int l, int r)
{
	// 피봇을 가장 오른쪽에
	// 그러면 i와 j가 ++로 연산되어 계산이 쉬움
	int pivot = arr[r];
	int i = l - 1;

	// j증가
	for (int j = l; j <= r - 1; j++)
	{
		// arr[j]가 피벗보다 작으면
		if (arr[j] <= pivot)
		{
			// i를 증가시키고 j와 스왑
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	// 모든 자리교환이 끝나면 i+1과 피벗을 스왑
	swap(&arr[i + 1], &arr[r]);

	// 새로운 피벗 리턴
	return (i + 1);
}

void quickSort(array<int,9>& arr, int l, int r)
{
	// 원소가 파티션에 2개 이상이면
	if (l < r)
	{
		int p = partition(arr, l, r);

		// 피벗의 왼쪽 계산
		quickSort(arr, l, p - 1);
		// 피벗의 오른쪽 계산
		quickSort(arr, p + 1, r);
	}
}

//int main() 
//{
//	array<int,9> arr = { 6,8,9,3,1,4,7, 2, 5 };
//	int Length = arr.size();
//
//	quickSort(arr, 0, Length-1);
//
//	for (int i = 0; i < Length ; i++)
//	{
//		cout << arr[i] << " ";
//	}
//
//	cout << endl;
//
//	return 0;
//}