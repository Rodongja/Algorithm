#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// 에라토스테네스의 체
int Eratosthenes(int n)
{
	int primeCount = 0;
	// 0부터 n까지 true로 초기화
	vector<bool> vec(n + 1, true);

	// 0과 1 제외
	vec[0] = false;
	vec[1] = false;

	for (int i = 2; i <= sqrt(n); i++)
	{
		// 이미 false인 경우
		if (!vec[i])
			continue;

		// i가 아직 소수라면 i*i부터 i의 배수들을 false 처리 (중복되는 연산 제거)
		for (int j = i * i ; j <= n; j+= i)
			vec[j] = false;
	}

	// count 세기
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

//// 브루트 포스
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