
#pragma comment(linker, "/ALIGN:0x200")
#pragma comment(linker, "/SECTION:.text,REW")
#pragma comment(linker, "/MERGE:.data=.text")
#pragma comment(linker, "/MERGE:.rdata=.text") 
#pragma comment(linker, "/STACK:64")
#pragma optimize("gsy", on)

#include <stdio.h>

const int NUM_SIZE = 101;

int input(char* num)
{
	int state = 0;
	int low_idx = NUM_SIZE;
	while (low_idx > 0)
	{
		int c = getchar();
		if (c >= '0' && c <= '9')
		{
			num[--low_idx] = c;
			state = 1;
		}
		else if (state == 1)
		{
			break;
		}
	}
	return low_idx;
}

void output(const char* num, int len)
{
	for (int i = len - 1; i >= 0; --i)
	{
		putchar(num[i] + '0');
	}
	putchar('\n');
}

int sub(const char* n1, int i1, const char* n2, int i2, char* diff)
{
	int i;
	bool borrow = false;
	for (i = 0; i1 < NUM_SIZE; ++i1, ++i2, ++i)
	{
		diff[i] = n1[i1] + 10;
		if (borrow)
		{
			--diff[i];
		}
		diff[i] -= i2 < NUM_SIZE ? n2[i2] : '0';
		borrow = diff[i] < 10;
		if (!borrow)
		{
			diff[i] -= 10;
		}
	}
	while (i > 0 && !diff[--i]);
	return i + 1;
}

int sub2(const char* n1, int i1, const char* n2, int len2, char* diff)
{
	int i, i2 = 0;
	bool borrow = false;
	for (i = 0; i1 < NUM_SIZE; ++i1, ++i2, ++i)
	{
		diff[i] = n1[i1] + 10;
		if (borrow)
		{
			--diff[i];
		}
		diff[i] -= i2 < len2 ? n2[i2] + '0' : '0';
		borrow = diff[i] < 10;
		if (!borrow)
		{
			diff[i] -= 10;
		}
	}
	while (i > 0 && !diff[--i]);
	return i + 1;
}

int div_by_2(char* num, int len)
{
	bool rem = false;
	for (int i = len - 1; i >= 0; --i)
	{
		if (rem)
		{
			num[i] += 10;
		}
		rem = num[i] & 1;
		num[i] >>= 1;
	}
	if (len == 1)
	{
		return 1;
	}
	return num[len - 1] ? len : len - 1;
}

// Ö÷Èë¿Ú

int main()
{
	char num1[NUM_SIZE], num2[NUM_SIZE];
	char kl[NUM_SIZE], na[NUM_SIZE];
	for (int i = 0; i < 10; ++i)
	{
		int low_idx1 = input(num1);
		int low_idx2 = input(num2);

		int na_len = sub(num1, low_idx1, num2, low_idx2, na);
		na_len = div_by_2(na, na_len);
		int kl_len = sub2(num1, low_idx1, na, na_len, kl);

		output(kl, kl_len);
		output(na, na_len);
	}
	return 0;
}