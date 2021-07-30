#include <stdio.h>


int main()
{
	unsigned char pt[16] = { 0x00, 0x11,0x22,0x33 ,0x44 ,0x55 ,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff };
	char *p = pt; // 포인터의 자료만 바꾸기 > 값을 참조할 때 unsinged를 무시하고 참조

	char pt_[16];
	for (int i = 0; i<16; i++)
	{
		pt_[i] = pt[i];
	}

	printf("<< unsigned char -> int 출력 >> \n");
	for (int i = 0; i < 16; i++)
	{
		printf("%d ", pt[i]);
	}
	printf("\n\n");


	printf("<< char -> int 출력 >> \n");
	for (int i = 0; i < 16; i++)
	{
		printf("%d ", p[i]);
	}
	printf("\n\n");


	printf("<< char -> int 출력 >> \n");
	for (int i = 0; i < 16; i++)
	{
		printf("%d ", pt_[i] / 50);
	}
	printf("\n\n");

	return 0;
}

// -10 ~ 10 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
	int i;

	srand((unsigned)time(NULL));


	for (i = 0; i < 1000; i++)
	{
		printf("%.3f ,",  (float)(rand() % 20000 - 10000) / 1000);  // 가중치 범위 : -10 ~ 10 
		if (i % 10 == 0 && i != 0)
			printf("\n");
	}
	
}
