#include <iostream>
#include <stdio.h>
#include "half.hpp"

using half_float::half;
using namespace std;

union Half_float
{
	unsigned short i;
	half f;

	Half_float() { i = 0; };
	//Half_float(half x) { f = x; };
};

// Exp 추출 
int exp(Half_float x)
{
	x.i >> 10;
	int y = x.i & 0x1f;
	return y;
}

// Mantissa 추출 
int frac(Half_float x)
{
	int y = x.i & 0x3ff;
	return y;
}


int half_bit_return(short a, int loc) // Bit returned at location 
{
	int buf = a & 1 << loc;

	if (buf == 0) return 0;
	else
		return 1;
}

void half_bit_print(half a)
{
	void* b;
	b = &a;
	int i = 0;
	for (i = 15; i >= 0; i--)
	{
		int j = 0;
		printf("%d", half_bit_return(*((short*)b), i));
		j = 15 - i;
		switch (j) { case 0: case 5: printf(" "); }
	}
	printf("\n");
}

int main()
{
	Half_float b;
	b.f = 3.14;

	half_bit_print(b.f);
	int a = frac(b);
	cout << a << endl;

	int c = exp(b);
	cout << c << endl;
	

	return 0;
}

// ilogb / logb 
//
