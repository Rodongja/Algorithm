#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <array>

using namespace std;

void swap(int* l, int* r)
{
	// �ڸ� ����
	int temp = *l;
	*l = *r;
	*r = temp;
}

int partition(array<int,9>& arr, int l, int r)
{
	// �Ǻ��� ���� �����ʿ�
	// �׷��� i�� j�� ++�� ����Ǿ� ����� ����
	int pivot = arr[r];
	int i = l - 1;

	// j����
	for (int j = l; j <= r - 1; j++)
	{
		// arr[j]�� �ǹ����� ������
		if (arr[j] <= pivot)
		{
			// i�� ������Ű�� j�� ����
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	// ��� �ڸ���ȯ�� ������ i+1�� �ǹ��� ����
	swap(&arr[i + 1], &arr[r]);

	// ���ο� �ǹ� ����
	return (i + 1);
}

void quickSort(array<int,9>& arr, int l, int r)
{
	// ���Ұ� ��Ƽ�ǿ� 2�� �̻��̸�
	if (l < r)
	{
		int p = partition(arr, l, r);

		// �ǹ��� ���� ���
		quickSort(arr, l, p - 1);
		// �ǹ��� ������ ���
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