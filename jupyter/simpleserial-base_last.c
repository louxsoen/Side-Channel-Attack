/*
    This file is part of the ChipWhisperer Example Targets
    Copyright (C) 2012-2017 NewAE Technology Inc.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // memset함수 
#include <math.h>  // expf함수 
#include "simpleserial.h"

#define INPUT 3		// 입력층 노드 개수 
#define HIDDEN 6	// 첫번째 은닉층 노드 개수 
#define OUTPUT 2	// 출력층 노드 개수 

// 입,출력 데이터 

// 입력 데이터 
float X[INPUT] = { 0.0 };  // ※ Setting ※

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
// expf : float 입출력 exp 함수 -> 존재하지 않음  

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

//******************************************************************************************************//

uint8_t get_key(uint8_t* k)
{
	// Load key here
	return 0x00;
}

#if SS_VER == SS_VER_2_0
uint8_t get_pt(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t* pt)
#else
uint8_t get_pt(uint8_t* pt) // char형값 16개 -> [0~4] 4개만 사용
#endif

{
	/**********************************
	* Start user-specific code here. */
    float y; 
    // [ -N , N ] 범위 입력 만들기
    //float input[3] = { 0.1f, 2.1f };
    //char *pt_ = pt; ( -2.56 ~ 2.54 : 실패 )
    char *p;
    float temp;
    
#if 1
    // [ -N , N ] 범위 입력 만들기
    float input[3] = { 0.0 };
    
    for(int i = 0; i < 3; i++)
    {
        if( pt[i + 3] % 2 )
            X[i] = input[i] + ((int)pt[i]/ 100.0); // 0 ~ 2.55
        else 
            X[i] = input[i] - ((int)pt[i]/ 100.0); // -2.55 ~ 0
        
    }
#endif        
    X[0] = 2.1;
    
    
#if 0
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

    //WH[0][0] = 2.0; // 출력값 확인용 
    
    
	// 초기화 
	memset(WSX, 0, sizeof(WSX));
	memset(WSH, 0, sizeof(WSH));
#endif
    
    trigger_high();
    
    //y = sigmoid(input);
    
    //y = exp(X[0]);
    //y = tanh2(X[0]);
   
    

#if 0
	// 가중합 + 활성함수 
	for (i = 0; i < HIDDEN; i++) 
	{
		for (j = 0; j < INPUT; j++)  
		{
			WSX[i] += X[j] * WX[j][i];
		}
		//AFR[i] = sigmoid(WSX[i]);
		AFR[i] = tanh2(WSX[i]);
		//AFR[i] = relu(WSX[i]);
        
        if(i == 0 ) // 첫번째 노드의 활성함수 출력값 담기 
        {
            p = &temp;
            temp = tanh2(WSX[i]);
            pt[4] = p[0];
            pt[5] = p[1];
            pt[6] = p[2];
            pt[7] = p[3];
            
            temp = sigmoid(WSX[i]);
            pt[8] = p[0];
            pt[9] = p[1];
            pt[10] = p[2];
            pt[11] = p[3];
        }
	}
#endif
    
#if 0
	// 가중합 + softmax exp연산 
	for (i = 0; i < OUTPUT; i++)
	{
		for (j = 0; j < HIDDEN; j++) 
		{
			WSH[i] += AFR[j] * WH[j][i];
		}
		Y[i] = exp(WSH[i]); // 분자 
		sum += Y[i];
	}

	
	for (i = 0; i < OUTPUT; i++) 
	{
		Y[i] /= sum; 
	}

    
#endif
trigger_low();
	//16 hex bytes held in 'pt' were sent
	//from the computer. Store your response
	//back into 'pt', which will send 16 bytes
	//back to computer. Can ignore of course if
	//not needed
	
	
    
    // 입력값 3개를 더해서 활성함수 입력 만들기 

    p = X;
    //X[0] = X[0] + X[1] + X[2];
    pt[0] = p[0];
    pt[1] = p[1];
    pt[2] = p[2];
    pt[3] = p[3];
         
#if 0
    
    // 출력값 1개 -> softmax라서 나머지 1개 알 수 있음 
	p = Y;
    pt[12] = p[0];
    pt[13] = p[1];
    pt[14] = p[2];
    pt[15] = p[3];
    
#endif
	/* End user-specific code here. *
	********************************/
	simpleserial_put('r', 16, pt);
	return 0x00;
}

uint8_t reset(uint8_t* x)
{
	// Reset key here if needed
	return 0x00;
}


int main(void)
{
    platform_init();
	init_uart();	
	trigger_setup();
	
 	/* Uncomment this to get a HELLO message for debug */
	/*
	putch('h');
	putch('e');
	putch('l');
	putch('l');
	putch('o');
	putch('\n');
	*/
		
	simpleserial_init();		
	simpleserial_addcmd('p', 16, get_pt);
#if SS_VER != SS_VER_2_0
	simpleserial_addcmd('k', 16, get_key);
	simpleserial_addcmd('x', 0, reset);
#endif
	while(1)
		simpleserial_get();
}
