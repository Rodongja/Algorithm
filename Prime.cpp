#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// �����佺�׳׽��� ü
int Eratosthenes(int n)
{
	int primeCount = 0;
	// 0���� n���� true�� �ʱ�ȭ
	vector<bool> vec(n + 1, true);

	// 0�� 1 ����
	vec[0] = false;
	vec[1] = false;

	for (int i = 2; i <= sqrt(n); i++)
	{
		// �̹� false�� ���
		if (!vec[i])
			continue;

		// i�� ���� �Ҽ���� i*i���� i�� ������� false ó�� (�ߺ��Ǵ� ���� ����)
		for (int j = i * i ; j <= n; j+= i)
			vec[j] = false;
	}

	// count ����
	for (int i = 2; i <= n; i++)
	{
		if (vec[i])
			primeCount++;
	}

	return primeCount;
}

//int main()
//{
//	int n;
//	cin >> n;
//
//	cout << Eratosthenes(n);
//
//	return 0;
//}

//// ���Ʈ ����
//bool isPrime(int n)
//{
//	if (n < 2)
//	{
//		return false;
//	}
//
//	int limit = static_cast<int>(sqrt(n));
//
//	for (int i = 2; i <= limit; i++)
//	{
//		if (n % i == 0)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//int primeCount(int n)
//{
//	int count = 0;
//	for (int i = 0; i < n; i++)
//	{
//		if (isPrime(i))
//		{
//			count++;
//		}
//	}
//	return count;
//}
//
//using namespace std;
//
//int main()
//{
//	int n;
//	cin >> n;
//
//	int ans = primeCount(n);
//	cout << ans;
//
//	return 0;
//}