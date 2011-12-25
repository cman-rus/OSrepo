#include<stdio.h>
volatile int a[1024][1024];
volatile int b[1024][1024];
volatile int c[1024][1024];
int main()
{
	for (int x = 0; x < 1024; ++x)
	{
		for (int y = 0; y < 1024; ++y)
		{
			for (int i = 0; i < 1024; ++i)
			{
				c[x][y] += a[x][i] * b[i][y];
			}
		}
	}

	return 0;

}
