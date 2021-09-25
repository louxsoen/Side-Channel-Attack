// 랜덤 가중치 생성 
#define INPUT 3		// 입력층 노드 개수 
#define HIDDEN 6	// 첫번째 은닉층 노드 개수 
#define OUTPUT 2	// 출력층 노드 개수 

float WX[INPUT][HIDDEN]; // 입력층 - 은닉층(1) 가중치(Weight)  // 왜 INPUT + 1인가?
float WH[HIDDEN][OUTPUT]; // 은닉층(1) - 출력층 가중치(Weight)	


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
	int i, j;

	srand((unsigned)time(NULL));

	for (i = 0; i < INPUT; i++)
	{
		for (j = 0; j < HIDDEN; j++)
		{
			printf("WX[%d][%d] = %.3f \n", i, j, (float)(rand() % 10000 - 5000) / 1000);  // 가중치 범위 : -5 ~ 5 
		}
	}

	printf("\n\n");

	for (i = 0; i < HIDDEN; i++)
	{
		for (j = 0; j < OUTPUT; j++)
		{
			printf("WH[%d][%d] = %.3f \n", i, j, (float)(rand() % 10000 - 5000) / 1000);  // 가중치 범위 : -5 ~ 5 
		}
	}

	return 0;
}
