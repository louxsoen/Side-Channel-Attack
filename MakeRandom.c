#include <stdio.h>


int main()
{
	unsigned char pt[16] = { 0x00, 0x11,0x22,0x33 ,0x44 ,0x55 ,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff };
	char *p = pt; // 포인터의 자료만 바꾸기 > 값을 참조할 때 unsinged를 무시하고 참조


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
	printf("\n");




	return 0;
}
