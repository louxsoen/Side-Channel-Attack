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
#include <math.h>  // exp함수 

#include "simpleserial.h"

// Sigmoid 함수
float sigmoid(float h)
{

	return (1 / (1 + exp(-h))); 

}

 

// double tanh(double x); 쌍곡선 tangent 함수 -s> float 형으로 구현 

// tanh 함수
float tanh2(float h)

{

        return (2 / (1 + exp(-2 * h)) - 1);

}

 

// ReLU 함수
float ReLU(float h)

{

	return (h > 0 ? h : 0);

}

 

// Softmax 
float softmax(float h, float *H,int n) // H : w*x 계산한 배열 

{

	float sum=0;

	for (int i = 0; i < n; i++)

	{

		sum += exp(H[i]);

	}

	return (h / sum);

}

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
    // 시행착오
    //float *input = pt;
    // float input = ((int)pt[0] << 24) | ((int)pt[1] << 16)|((int)pt[2] << 8)|(int)(pt[3]); // 형변환 해서 넣어야해 (floatx(x) int(o))
    float y; 
    
    // [ -N , N ] 범위 숫자 만들기
    float input = 0.0;
    
    input = input + ((int)pt[0])/100.0; // 0 ~ 2.55 
    
    //input = input - ((int)pt[0])/100.0; // -2.55 ~ 0
    
	trigger_high();
    //y = tanh2(input);
    //y = ReLU(input);
    //y = sigmoid(input);
    /*
     for(int i=0;i<10;i++)
     {
         y = tanh2(input);
         //y = sigmoid(input);
         //y = ReLU(input);
     }*/
    
    
    
    
	//16 hex bytes held in 'pt' were sent
	//from the computer. Store your response
	//back into 'pt', which will send 16 bytes
	//back to computer. Can ignore of course if
	//not needed
	
	trigger_low();
    
    // pt를 업데이트 ( 자동으로 거꾸로 담음 )
    char *p;
	p = &input; 
    // pt[0] =(y) & 0xff;   // float 에 & 연산자 불가능 
    pt[0] = p[0];
    pt[1] = p[1];
    pt[2] = p[2];
    pt[3] = p[3];
    
    // 범위 내의 입력인지 확인하기 위해서 textout 파일에 쓰기 
    p = &y;
    pt[4] = p[0];
    pt[5] = p[1];
    pt[6] = p[2];
    pt[7] = p[3];
    
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
