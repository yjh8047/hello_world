
#include <stdio.h>

int num[999][999];	// ¶þÎ¬Êý×é

int input()
{
	int num = 0;
	int state = 0;
	while (true)
	{
		int c = 0;
		c = getchar();
		if (c >= '0' && c <= '9')
		{
			num *= 10;
			num += c - 0x30;
			state = 1;
		}
		else if (state == 1)
		{
			break;
		}
	}
	return num;
}

int main()
{
	int r[100];
	int t = input();

	for (int k = 0; k < t; ++k)
	{
		int m = input(), n = input(), x = input(), y = input();

		for (int j = 0; j < m; ++j)
		{
			for (int i = 0; i < n; ++i)
			{
				num[j][i] = input();
			}

			int pre = num[j][0];
			for (int i = 1; i < y; ++i)
			{
				num[j][0] += num[j][i];	// great
			}
			for (int i = 1; i <= n - y; ++i)
			{
				int temp = num[j][i];
				num[j][i] = num[j][i + y - 1];
				num[j][i] += num[j][i - 1] - pre;
				pre = temp;
			}
		}

		int max_v = 0;
		for (int i = 0; i <= n - y; ++i)
		{
			int v = num[0][i];
			for (int j = 1; j < x; ++j)
			{
				v += num[j][i];
			}
			if (max_v < v)
			{
				max_v = v;
			}

			for (int j = 1; j <= m - x; ++j)
			{
				v -= num[j - 1][i];
				v += num[j + x - 1][i];
				if (max_v < v)
				{
					max_v = v;
				}
			}
		}

		r[k] = max_v;
	}

	for (int k = 0; k < t; ++k)
	{
		printf("%d\n", r[k]);
	}
	return 0;
}
