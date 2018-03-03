#include <stdio.h>
#include <bitset>
#include <atomic>
#include <thread>

typedef unsigned int uint;
typedef unsigned long long uint64;

const int BASE_N = 1000000;
const int SQRT_N = 1000;
const int PRIME_N = 78497;
const int MAX_T = 10000;
const int THREAD_N = 8;

std::bitset<BASE_N> is_prime;
uint primes[PRIME_N];

uint64 inputs[MAX_T];
uint outputs[MAX_T];
int count;
std::atomic_int cur_idx;

template <bool n_32, typename T1, typename T2>
inline bool calc(T1& p, T2& n, uint& i)
{
	if (!(n & 1))
	{
		p = 3;
		do
		{
			n >>= 1;
		} while (!(n & 1));
	}

	while (true)
	{
		if (!n_32 && n <= 0xffe20000)
		{
			return false;
		}
		if (n_32 && n < BASE_N && is_prime[(uint)n])
		{
			p = T1(p * (n + 1) % 1000000007);
			return true;
		}
		if (!(n % primes[i]))
		{
			p *= primes[i] + 1;
			do
			{
				n /= primes[i];
			} while (!(n % primes[i]));
		}
		if ((T2)primes[i] * primes[i] > n)
		{
			if (n != 1)
			{
				p = T1(p * (n + 1) % 1000000007);
			}
			return true;
		}
		++i;
	}
}

inline uint compute(uint64 n)
{
	uint p = 1, i = 0;
	if (n < 0x6c000000)
	{
		uint n2 = (uint)n;
		calc<true>(p, n2, i);
		return p;
	}

	if (n > 0xffe20000)
	{
		if (calc<false>(p, n, i))
		{
			return p;
		}
	}

	uint64 p2 = p;
	uint n2 = (uint)n;
	calc<true>(p2, n2, i);
	return (uint)p2;
}

void thread_loop()
{
	while (true)
	{
		int idx = cur_idx.fetch_add(1);
		if (idx >= count)
		{
			break;
		}
		outputs[idx] = compute(inputs[idx]);
	}
}

int main()
{
	is_prime.set();
	is_prime[1] = false;
	for (int i = 3; i < SQRT_N; i += 2)
	{
		if (is_prime[i])
		{
			for (int num = i * i; num < BASE_N; num += (i << 1))
			{
				is_prime[num] = false;
			}
		}
	}

	int idx = 0;
	for (int i = 3; i < BASE_N; i += 2)
	{
		if (is_prime[i])
		{
			primes[idx++] = i;
		}
	}

	scanf("%d", &count);
	for (int i = 0; i < count; ++i)
	{
		scanf("%lld", &inputs[i]);
	}

	cur_idx = 0;
	std::thread threads[THREAD_N];
	for (int i = 0; i < THREAD_N; ++i)
	{
		threads[i] = std::thread(thread_loop);
	}
	for (int i = 0; i < THREAD_N; ++i)
	{
		threads[i].join();
	}

	for (int i = 0; i < count; ++i)
	{
		printf("%d\n", outputs[i]);
	}
	return 0;
}
}
