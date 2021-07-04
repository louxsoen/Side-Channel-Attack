//*********************************************************//
// 	   MLP : 입력(X) : 3 / 은닉(H1) : 6  / 출력(Y) : 2	   //
//*********************************************************//

// 가중합 연산과 활성함수 연산 분리_Ver

#include <stdio.h>
#include <math.h>

#define INPUT 3		// 입력층 노드 개수 
#define HIDDEN 6	// 첫번째 은닉층 노드 개수 
#define OUTPUT 2	// 출력층 노드 개수 

// 입,출력 데이터 
float X[INPUT] = { 1.0 };  // ※ Setting ※
float Y[OUTPUT];

// Weight ( ※ Setting ※ )
float WX[INPUT][HIDDEN]; // 입력층 - 은닉층(1) 가중치(Weight)  // 왜 INPUT + 1인가?
float WH[HIDDEN][OUTPUT]; // 은닉층(1) - 출력층 가중치(Weight)	

						  // Weight Sum
float WSX[HIDDEN]; // 입력값으로 계산한 은닉층(1)에 들어갈 가중합
float WSH[OUTPUT]; // 은닉층(1)의 출력값으로 계산한 출력층에 들어갈 가중합 

				   // Activefunction Result
float AFR[HIDDEN];



// Active Function Implement
// expf : float 입출력 exp 함수 

// Sigmoid 
float sigmoid(float h)
{
	return (1 / (1 + exp((-1)*h)));
}

// tanhf : float 입출력 Tanh함수 
float tanh2(float h)
{
	return (2 / (1 + exp(-2 * h)) - 1);

}

// ReLU 
float relu(float h)
{
	return (h > 0 ? h : 0);
}

// Softmax 
float softmax(float h, float *H, int n) // H : w*x 계산한 배열  |  n : H 배열의 사이즈 
{
	float sum = 0;

	for (int i = 0; i < n; i++)
	{
		sum += exp(H[i]);
	}

	return (h / sum);

}


int main()
{
	//*********************************************************//
	// 				 순전파 (Forward Propagation)	           //
	//*********************************************************//

	int i, j;
	float sum = 0;

	// Weight 설정 
	for (i = 0; i < INPUT; i++)
	{
		for (j = 0; j < HIDDEN; j++)
		{
			WX[i][j] = 1.0;
		}
	}

	for (i = 0; i < HIDDEN; i++)
	{
		for (j = 0; j < OUTPUT; j++)
		{
			WH[i][j] = 1.0;
		}
	}


	// 초기화 
	memset(WSX, 0, sizeof(WSX));
	memset(WSH, 0, sizeof(WSH));


	//*********************************************************//
	// 				      입력층 - 은닉층             	       //
	//*********************************************************//
	// 가중합
	for (i = 0; i < HIDDEN; i++)
	{
		for (j = 0; j < INPUT; j++)  // 왜 +1?
		{
			WSX[i] += X[j] * WX[j][i];
		}
	}



	// 출력
#if 1
	printf("<< Weight Sum1(WSX) >> \n");
	for (i = 0; i < INPUT; i++)
	{
		printf("%d : %f \n", i + 1, WSX[i]);
	}
	printf("\n");
#endif


	// 가중합 입력에 대한 활성함수 결과값 
	for (i = 0; i < HIDDEN; i++)
	{
		//AFR[i] = tanh2(WSX[i]);
		AFR[i] = sigmoid(WSX[i]);
	}

	// 출력
#if 1
	printf("<< Active Function 1(AFR) >> \n");
	for (i = 0; i < HIDDEN; i++)
	{
		printf("%d : %f \n", i + 1, AFR[i]);
	}
	printf("\n");
#endif

	//*********************************************************//
	// 				      은닉층 - 출력층             	       //
	//*********************************************************//
	// 가중합 
	for (i = 0; i < OUTPUT; i++)
	{
		for (j = 0; j < HIDDEN; j++)  // 왜 +1?
		{
			WSH[i] += AFR[j] * WH[j][i];
		}
	}

	// 출력
#if 1

	printf("<< Weight Sum 2(WSH) >> \n");
	for (i = 0; i < OUTPUT; i++)
	{
		printf("%d : %f \n", i + 1, WSH[i]);
	}
	printf("\n");
#endif


	// Softmax함수를 이용한 출력값  -> 함수로 어캐 바꾸지 
	for (i = 0; i < OUTPUT; i++)
	{
		Y[i] = exp(WSH[i]); // 분자 
		sum += Y[i];
	}

	for (i = 0; i < OUTPUT; i++)
	{
		Y[i] /= sum;
	}

	// 출력 
#if 1
	printf("<< Result (Y) >> \n");
	for (i = 0; i < OUTPUT; i++)
	{
		printf("%d : %f \n", i + 1, Y[i]);
	}
	printf("\n");
#endif

	return 0;
}
