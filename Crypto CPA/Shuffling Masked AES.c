#include<stdio.h>
#include<stdlib.h>
#include <time.h>

unsigned char mask[10];
unsigned char MSbox[256];

unsigned char Sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

unsigned Rcon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

void RK_Update(unsigned char* out, unsigned char* in, int i)
{
	unsigned char tmp[4];

	tmp[0] = in[13]; tmp[1] = in[14]; tmp[2] = in[15]; tmp[3] = in[12];

	tmp[0] = Sbox[tmp[0]] ^ Rcon[i];
	tmp[1] = Sbox[tmp[1]];
	tmp[2] = Sbox[tmp[2]];
	tmp[3] = Sbox[tmp[3]];

	out[0] = in[0] ^ tmp[0]; out[1] = in[1] ^ tmp[1]; out[2] = in[2] ^ tmp[2]; out[3] = in[3] ^ tmp[3];
	out[4] = in[4] ^ out[0]; out[5] = in[5] ^ out[1]; out[6] = in[6] ^ out[2]; out[7] = in[7] ^ out[3];
	out[8] = in[8] ^ out[4]; out[9] = in[9] ^ out[5]; out[10] = in[10] ^ out[6]; out[11] = in[11] ^ out[7];
	out[12] = in[12] ^ out[8]; out[13] = in[13] ^ out[9]; out[14] = in[14] ^ out[10]; out[15] = in[15] ^ out[11];
}

void Mask_RK_Update(unsigned char* out, unsigned char* in, int i) 
{
	unsigned char tmp[4]; 

	tmp[0] = in[13] ^ mask[7];
	tmp[1] = in[14] ^ mask[8];
	tmp[2] = in[15] ^ mask[9];	
	tmp[3] = in[12] ^ mask[6];

	tmp[0] = MSbox[tmp[0]] ^ Rcon[i]; 
	tmp[1] = MSbox[tmp[1]];
	tmp[2] = MSbox[tmp[2]];
	tmp[3] = MSbox[tmp[3]];
	
	// 첫번째 블록 
	out[0] = in[0] ^ tmp[0] ^ mask[1]; 
	out[1] = in[1] ^ tmp[1] ^ mask[1];
	out[2] = in[2] ^ tmp[2] ^ mask[1];
	out[3] = in[3] ^ tmp[3] ^ mask[1];
	// 두번째 블록
	out[4] = in[4] ^ mask[0] ^ out[0] ^ mask[6];
	out[5] = in[5] ^ mask[0] ^ out[1] ^ mask[7];
	out[6] = in[6] ^ mask[0] ^ out[2] ^ mask[8];
	out[7] = in[7] ^ mask[0] ^ out[3] ^ mask[9];
	// 세번째 블록
	out[8] = in[8] ^ mask[0] ^ out[4] ^ mask[6];
	out[9] = in[9] ^ mask[0] ^ out[5] ^ mask[7];
	out[10] = in[10] ^ mask[0] ^ out[6] ^ mask[8];
	out[11] = in[11] ^ mask[0] ^ out[7] ^ mask[9];
	// 네번째 블록
	out[12] = in[12] ^ mask[6] ^ out[8] ^ mask[0];
	out[13] = in[13] ^ mask[7] ^ out[9] ^ mask[0];
	out[14] = in[14] ^ mask[8] ^ out[10] ^ mask[0];
	out[15] = in[15] ^ mask[9] ^ out[11] ^ mask[0];
}

void Mask_RK_Update2(unsigned char* out, unsigned char* in) 
{
	unsigned char tmp[4];

	tmp[0] = in[13] ^ mask[7];
	tmp[1] = in[14] ^ mask[8];
	tmp[2] = in[15] ^ mask[9];
	tmp[3] = in[12] ^ mask[6];

	tmp[0] = MSbox[tmp[0]] ^ Rcon[9];
	tmp[1] = MSbox[tmp[1]];
	tmp[2] = MSbox[tmp[2]];
	tmp[3] = MSbox[tmp[3]];

	// 첫번째 블록
	out[0] = in[0] ^ tmp[0];
	out[1] = in[1] ^ tmp[1];
	out[2] = in[2] ^ tmp[2];
	out[3] = in[3] ^ tmp[3];
	// 두번째 블록
	out[4] = in[4] ^ out[0]; 
	out[5] = in[5] ^ out[1]; 
	out[6] = in[6] ^ out[2];
	out[7] = in[7] ^ out[3];
	// 세번째 블록
	out[8] = in[8] ^ mask[6] ^ out[4];
	out[9] = in[9] ^ mask[7] ^ out[5];
	out[10] = in[10] ^ mask[8] ^ out[6];
	out[11] = in[11] ^ mask[9] ^ out[7];
	// 네번째 블록
	out[12] = in[12] ^ mask[6] ^ out[8];
	out[13] = in[13] ^ mask[7] ^ out[9];
	out[14] = in[14] ^ mask[8] ^ out[10];
	out[15] = in[15] ^ mask[9] ^ out[11];

	// 마스크 옳바르게 바꾸기 
	out[0] = out[0] ^ mask[6] ^ mask[0];
	out[1] = out[1] ^ mask[7] ^ mask[0];
	out[2] = out[2] ^ mask[8] ^ mask[0];
	out[3] = out[3] ^ mask[9] ^ mask[0];

	out[8] = out[8] ^ mask[0];
	out[9] = out[9] ^ mask[0];
	out[10] = out[10] ^ mask[0];
	out[11] = out[11] ^ mask[0];
}


void KeyExpansion(unsigned char* MK, unsigned char* RK)
{
	int i;

	for (i = 0; i < 16; i++)
		RK[i] = MK[i];

	for (i = 0; i < 10; i++) {

		RK_Update(RK + 16, RK, i);
		RK += 16;
	}
}

void Mask_KeyExpansion(unsigned char* MK, unsigned char* RK) 
{
	int i, j;

	for (i = 0; i < 16; i += 4)
	{
		RK[i] = MK[i] ^ mask[6] ^ mask[0];	
		RK[i + 1] = MK[i + 1] ^ mask[7] ^ mask[0];
		RK[i + 2] = MK[i + 2] ^ mask[8] ^ mask[0];
		RK[i + 3] = MK[i + 3] ^ mask[9] ^ mask[0];
	}

	for (i = 0; i < 9; i++) 
	{ 
		Mask_RK_Update(RK + 16, RK, i);  
		RK += 16;
	}

	Mask_RK_Update2(RK + 16, RK); 
}


void KeyAddition(unsigned char* input, unsigned char* RK)
{
	int i;

	for (i = 0; i < 16; i++)
		input[i] ^= RK[i];
}

void Random_KeyAddition(unsigned char* input, unsigned char* RK)
{
	int i;

}

void Random_KeyAddition2(unsigned char* input, unsigned char* RK) // 마지막 라운드 KeyAddition
{
	int i;

}

void Subbyte(unsigned char* input)
{
	int i;

	for (i = 0; i < 16; i++)
		input[i] = Sbox[input[i]];
}

void Mask_Subbyte(unsigned char* input) 
{
	int i;

	for (i = 0; i < 16; i++)
		input[i] = MSbox[input[i]]; 
}

void Random_Mask_Subbyte(unsigned char* input)
{
	int i;
}


void ShiftRow(unsigned char* input) 
{
	unsigned char tmp; 

	tmp = input[5]; input[5] = input[9]; input[9] = input[13]; input[13] = input[1]; input[1] = tmp;
	
	tmp = input[10]; input[10] = input[2]; input[2] = tmp; 
	tmp = input[14]; input[14] = input[6]; input[6] = tmp; 

	tmp = input[11]; input[11] = input[7]; input[7] = input[3]; input[3] = input[15]; input[15] = tmp;
}


unsigned char MUL2(unsigned char a) 
{
	if (a & 0x80) 
		return (a << 1) ^ 0x1b;
	else
		return a << 1; 
}

unsigned char MUL3(unsigned char a) 
{
	return MUL2(a) ^ a;
}

void Submix(unsigned char* in) 
{
	unsigned char tmp[4]; 

	tmp[0] = MUL2(in[0]) ^ MUL3(in[1]) ^ in[2] ^ in[3]; 
	tmp[1] = in[0] ^ MUL2(in[1]) ^ MUL3(in[2]) ^ in[3];
	tmp[2] = in[0] ^ in[1] ^ MUL2(in[2]) ^ MUL3(in[3]);
	tmp[3] = MUL3(in[0]) ^ in[1] ^ in[2] ^ MUL2(in[3]); 

	in[0] = tmp[0]; in[1] = tmp[1]; in[2] = tmp[2]; in[3] = tmp[3];
}


void MixColums(unsigned char* input)  
{
	Submix(input);
	Submix(input + 4); 
	Submix(input + 8); 
	Submix(input + 12);
}

void Random_MixColums(unsigned char* input) // 굉장히 더럽게 바꿔야 할거같은데..
{

}


void Remask(unsigned char* input)
{
	for (int i = 0; i < 16; i += 4)
	{
		input[i] = input[i] ^ (mask[1] ^ mask[2]);
		input[i+1] = input[i+1] ^ (mask[1] ^ mask[3]);
		input[i+2] = input[i+2] ^ (mask[1] ^ mask[4]);
		input[i+3] = input[i+3] ^ (mask[1] ^ mask[5]);
	}
}


void ENC(unsigned char* in, unsigned char* RK, unsigned char* out)
{
	int i;
	unsigned char temp[16];

	for (i = 0; i < 16; i++)
	{
		temp[i] = in[i];
	}

	for (i = 0; i < 9; i++)
	{
		KeyAddition(temp, RK);
		Subbyte(temp);
		ShiftRow(temp);
		MixColums(temp);
		RK += 16;
	}

	KeyAddition(temp, RK);
	Subbyte(temp);
	ShiftRow(temp);
	RK += 16;
	KeyAddition(temp, RK);

	for (i = 0; i < 16; i++)
	{
		out[i] = temp[i];
	}
}

void Mask_ENC(unsigned char* in, unsigned char* RK, unsigned char* out)
{
	int i;
	unsigned char temp[16];

	// 평문 마스킹 //
	for (i = 0; i < 16; i += 4)
	{
		temp[i] = in[i] ^ mask[6];
		temp[i + 1] = in[i + 1] ^ mask[7];
		temp[i + 2] = in[i + 2] ^ mask[8];
		temp[i + 3] = in[i + 3] ^ mask[9];
	}

	for (i = 0; i < 9; i++)
	{
		KeyAddition(temp, RK);
		Mask_Subbyte(temp);
		ShiftRow(temp);
		Remask(temp);
		MixColums(temp);
		RK += 16;
	}

	// 10라운드
	KeyAddition(temp, RK);
	Mask_Subbyte(temp);
	ShiftRow(temp);
	RK += 16;
	KeyAddition(temp, RK);

	for (i = 0; i < 16; i++)
	{
		out[i] = temp[i];
	}
}

void Random_Mask_ENC2(unsigned char* in, unsigned char* RK, unsigned char* out) 
{
	int i;
	unsigned char temp[16];

	for (i = 0; i < 16; i += 4)
	{
		temp[i] = in[i] ^ mask[6];
		temp[i + 1] = in[i + 1] ^ mask[7];
		temp[i + 2] = in[i + 2] ^ mask[8];
		temp[i + 3] = in[i + 3] ^ mask[9];
	}	

	// 1라운드 
	Random_KeyAddition(temp, RK); // 랜덤 + 더미
	Random_Mask_Subbyte(temp); // // 랜덤 + 더미
	Remask(temp); // 너도?
	Random_MixColums(temp); // 열 랜덤pick + 행 랜덤 -> 아닌디... 
	ShiftRow(temp); // 너는 랜덤하게 안하네? 공격지점 밖인가 보네?
	RK += 16;

	// 2~8라운드 
	for (i = 0; i < 7; i++) 
	{ 
		KeyAddition(temp, RK);
		Mask_Subbyte(temp);
		ShiftRow(temp);
		Remask(temp);
		MixColums(temp);
		RK += 16;
	}

	// 9라운드
	KeyAddition(temp, RK);
	Mask_Subbyte(temp);
	ShiftRow(temp);
	Remask(temp);
	Random_MixColums(temp);
	RK += 16;

	// 10라운드 
	Random_KeyAddition(temp, RK);
	Random_Mask_Subbyte(temp);
	// 원래 ShiftRow자리 
	RK += 16;  // RK를 증가시키는거지 temp를 증가시키는게 아님... 
	Random_KeyAddition2(temp, RK);
	ShiftRow(temp);


	for (i = 0; i < 16; i++) 
	{
		out[i] = temp[i]; 
	}
}

void Random_Mask_ENC(unsigned char* in, unsigned char* RK, unsigned char* out)
{
	int i, j, order[16], size, tmp;
	unsigned char temp[16];

	for (i = 0; i < 16; i += 4)
	{
		temp[i] = in[i] ^ mask[6];
		temp[i + 1] = in[i + 1] ^ mask[7];
		temp[i + 2] = in[i + 2] ^ mask[8];
		temp[i + 3] = in[i + 3] ^ mask[9];
	}

	for (i = 0; i < 6; i++)
	{
		// pick (4~8)
		size = rand() % 5 + 4;
		//order = ReOrder[i];
		for (j = 0; j < size; j++) order[j] = j;
		for (j = size; j < 8; j++) order[j] = 0xff;

		// random permutation 
		for (j = size - 1; j >= 1; j--)
		{
			//t0 = rand() % (j + 1);
			//tmp = order[t0];
			//order[t0] = order[j];
			order[j] = tmp;
		}
	}

	// 1라운드 


}

int main() {
	unsigned char in[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
	// 0x4A ,0x19 ,0x24 ,0x22 ,0xE1 ,0xCA ,0xF5 ,0xE3 ,0xE0 ,0x63 ,0x9D ,0x8A ,0xA4 ,0x36 ,0x98 ,0x12
	unsigned char MK[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x12,0x34,0x56,0x78,0x9a,0xbc,0xde,0xf0 };
	// 0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10
	unsigned char out[16] = { 0x00, };
	unsigned char RK[176] = { 0x00 };
	int i;

	// 난수 생성 // 
	srand((unsigned)time(0));
	mask[0] = rand(); // M
	mask[1] = rand(); // M'  
	mask[2] = rand(); // M1
	mask[3] = rand(); // M2
	mask[4] = rand(); // M3
	mask[5] = rand(); // M4

	// 마스킹 S-box 연산 //   
	for (i = 0; i < 256; i++)
		MSbox[i ^ mask[0]] = Sbox[i] ^ mask[1]; 

	// M1'~ M4' 생성 //  
	mask[6] = MUL2(mask[2]) ^ MUL3(mask[3]) ^ mask[4] ^ mask[5];
	mask[7] = mask[2] ^ MUL2(mask[3]) ^ MUL3(mask[4]) ^ mask[5];
	mask[8] = mask[2] ^ mask[3] ^ MUL2(mask[4]) ^ MUL3(mask[5]);
	mask[9] = MUL3(mask[2]) ^ mask[3] ^ mask[4] ^ MUL2(mask[5]); 


	printf("Master Key: ");
	for (i = 0; i < 16; i++)
		printf("%02x ", MK[i]);
	printf("\n");


	printf("\n< Normal AES Encrytion > \n"); 
	KeyExpansion(MK, RK);
	ENC(in, RK, out);

	printf("Plaintext: ");
	for (i = 0; i < 16; i++)
		printf("%02x ", in[i]);
	printf("\n");

	printf("Ciphertext: ");
	for (i = 0; i < 16; i++)
		printf("%02x ", out[i]);
	printf("\n");


	printf("\n< Masked AES Encrytion > \n");
	Mask_KeyExpansion(MK, RK); 
	Mask_ENC(in, RK, out);

	printf("Plaintext: ");
	for (i = 0; i < 16; i++)
		printf("%02x ", in[i]);
	printf("\n");

	printf("Ciphertext: ");
	for (i = 0; i < 16; i++)
		printf("%02x ", out[i]);
	printf("\n");
	return 0;

	printf("\n< Random & Masked AES Encrytion > \n");
	Mask_KeyExpansion(MK, RK);
	Random_Mask_ENC(in, RK, out);

	printf("Plaintext: ");
	for (i = 0; i < 16; i++)
		printf("%02x ", in[i]);
	printf("\n");

	printf("Ciphertext: ");
	for (i = 0; i < 16; i++)
		printf("%02x ", out[i]);
	printf("\n");
	
	return 0;
}

