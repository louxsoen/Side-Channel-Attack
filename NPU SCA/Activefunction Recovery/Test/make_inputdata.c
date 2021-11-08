// 모든 가중치 1.0인 상황
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



// 랜덤화된 가중치에 따른 입력 생성 
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
    float total = -5;
    float a, b, c;


	srand((unsigned)time(NULL));
    
    // Setting된 가중치 
    {
        WX[0][0] = -2.464;
        WX[0][1] = -4.633;
        WX[0][2] = -0.948;
        WX[0][3] = -4.241;
        WX[0][4] = 0.847;
        WX[0][5] = 1.477;
        WX[1][0] = -3.501;
        WX[1][1] = 1.613;
        WX[1][2] = 1.073;
        WX[1][3] = 0.331;
        WX[1][4] = 4.349;
        WX[1][5] = 4.728;
        WX[2][0] = 3.537;
        WX[2][1] = 0.215;
        WX[2][2] = -3.727;
        WX[2][3] = -0.018;
        WX[2][4] = -3.035;
        WX[2][5] = -4.727;


        WH[0][0] = 3.746;
        WH[0][1] = -4.071;
        WH[1][0] = 4.049;
        WH[1][1] = -1.419;
        WH[2][0] = 3.681;
        WH[2][1] = 2.544;
        WH[3][0] = -1.990;
        WH[3][1] = -4.119;
        WH[4][0] = 4.102;
        WH[4][1] = -2.527;
        WH[5][0] = 1.181;
        WH[5][1] = -3.696;
    }
    for (int i = 0; i < 1000; i++)
    {
        // b,c 랜덤값 생성 -3 ~ 3
        b = (float)(rand() % 600 - 300) / 100;
        c = (float)(rand() % 600 - 300) / 100;

        a = (total - (b * WX[1][0] + c * WX[2][0])) / WX[0][0];

        if (i % 3 == 0 && i != 0)
            printf("\n");
        printf("%.3f , %.3f , %.3f ,", a, b, c);
        //printf("%.3f , %.3f , %.3f = %.3f \n", a, b, c, a * WX[0][0] + b * WX[1][0] + c * WX[2][0]);
        total += 0.01;
    }
	return 0;
}
