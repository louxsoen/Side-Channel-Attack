#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	float total = -5;
	float a, b, c;

	srand((unsigned)time(NULL));

	for (int i = 0; i < 1000; i++)
	{
		// b,c 랜덤값 생성 
		b = (float)(rand() % 600 - 300) / 100;
		c = (float)(rand() % 600 - 300) / 100;
		
		a = total - (b + c);
		if (i % 3 == 0 && i != 0)  // 1개의 입력에 대해서 1줄 차지 -> 1000줄 
			printf("\n");
		printf("%.2f , %.2f , %.2f ,", a, b, c);
		//printf("%.2f , %.2f , %.2f = %.3f ", a, b, c, a + b + c);
		total += 0.01;
	}
}
