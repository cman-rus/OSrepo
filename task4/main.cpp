#include<stdio.h>

const int size = 10;
const int sT = 4;

volatile int a[1<<size][1<<size];
volatile int b[1<<size][1<<size];
volatile int c[1<<size][1<<size];

int R()
{
	for (int x = 0; x < 1<<size; ++x)
	{
		for (int y = 0; y < 1<<size; ++y)
		{
			for (int i = 0; i < 1<<size; ++i)
			{
				c[x][y] += a[x][i] * b[i][y];
			}
		}
	}

	return 0;

}

int T()
{
	int cou = ((1<<size) - 1)/(1<<sT)+1;
	for (int x = 0; x < cou; ++x)
        {
                for (int y = 0; y < cou; ++y)
                {
			for(int i1=0; i1<cou; ++i1)
			{
				for(int i=0; i< 1<<sT; ++i)
				{
					for(int j=0; j< 1<<sT; ++j)
                        		{
						int x1 = x * (1<<sT) + i;
						int y1 = y * (1<<sT) + j;
						for (int i2 = 0; i2 < 1<<sT; ++i2)
                        			{
                                			c[x1][y1] += a[x1][i1*(1<<sT)+i2] * b[i1*(1<<sT)+i2][y1];
                       				}
                        		} 
				}
			}
                }
        }

	return 0;
}

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		R();
	}
	else
	{
		T();
	}
	return 0;
}
