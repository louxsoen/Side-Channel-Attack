// 실용 코드 (주석제거 + 단축 코드)
#include <stdio.h>

typedef unsigned int WORD; 

int Delta[8] = { 0xc3efe9db ,0x44626b02 ,0x79e27c8a ,0x78df30ec ,0x715ea49e ,0xc785da0a ,0xe04ef22a ,0xe5c40957 };

WORD RotationLeft(WORD word, const unsigned int BitShift) 
{
	return (word << BitShift) | (word >> (32 - BitShift));
}

WORD RotationRight(WORD word, const unsigned int BitShift)
{
	return (word >> BitShift) | (word << (32 - BitShift));
}

void Encryption(unsigned char* input, int* RK, unsigned char* output)
{	
	int X[4], temp;
	
	X[0] = (input[3] << 24) | (input[2] << 16) | (input[1] << 8) | input[0]; X[1] = (input[7] << 24) | (input[6] << 16) | (input[5] << 8) | input[4];
	X[2] = (input[11] << 24) | (input[10] << 16) | (input[9] << 8) | input[8]; X[3] = (input[15] << 24) | (input[14] << 16) | (input[13] << 8) | input[12];

	// 1라운드 
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[0]) + (X[1] ^ RK[1])), 9); X[1] = RotationRight(((X[1] ^ RK[2]) + (X[2] ^ RK[3])), 5); X[2] = RotationRight(((X[2] ^ RK[4]) + (X[3] ^ RK[5])), 3); X[3] = temp;
	// 2라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[6]) + (X[1] ^ RK[7])), 9); X[1] = RotationRight(((X[1] ^ RK[8]) + (X[2] ^ RK[9])), 5); X[2] = RotationRight(((X[2] ^ RK[10]) + (X[3] ^ RK[11])), 3); X[3] = temp;
	// 3라운드 
	temp = X[0];
	X[0] = RotationLeft(((X[0] ^ RK[12]) + (X[1] ^ RK[13])), 9); X[1] = RotationRight(((X[1] ^ RK[14]) + (X[2] ^ RK[15])), 5); X[2] = RotationRight(((X[2] ^ RK[16]) + (X[3] ^ RK[17])), 3); X[3] = temp;
	// 4라운드
	temp = X[0];
	X[0] = RotationLeft(((X[0] ^ RK[18]) + (X[1] ^ RK[19])), 9); X[1] = RotationRight(((X[1] ^ RK[20]) + (X[2] ^ RK[21])), 5); X[2] = RotationRight(((X[2] ^ RK[22]) + (X[3] ^ RK[23])), 3); X[3] = temp;
	// 5라운드 
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[24]) + (X[1] ^ RK[25])), 9); X[1] = RotationRight(((X[1] ^ RK[26]) + (X[2] ^ RK[27])), 5); X[2] = RotationRight(((X[2] ^ RK[28]) + (X[3] ^ RK[29])), 3); X[3] = temp;
	// 6라운드 
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[30]) + (X[1] ^ RK[31])), 9); X[1] = RotationRight(((X[1] ^ RK[32]) + (X[2] ^ RK[33])), 5); X[2] = RotationRight(((X[2] ^ RK[34]) + (X[3] ^ RK[35])), 3); X[3] = temp;
	// 7라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[36]) + (X[1] ^ RK[37])), 9); X[1] = RotationRight(((X[1] ^ RK[38]) + (X[2] ^ RK[39])), 5); X[2] = RotationRight(((X[2] ^ RK[40]) + (X[3] ^ RK[41])), 3); X[3] = temp;
	// 8라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[42]) + (X[1] ^ RK[43])), 9); X[1] = RotationRight(((X[1] ^ RK[44]) + (X[2] ^ RK[45])), 5); X[2] = RotationRight(((X[2] ^ RK[46]) + (X[3] ^ RK[47])), 3); X[3] = temp;
	// 9라운드
	temp = X[0];
	X[0] = RotationLeft(((X[0] ^ RK[48]) + (X[1] ^ RK[49])), 9); X[1] = RotationRight(((X[1] ^ RK[50]) + (X[2] ^ RK[51])), 5);  X[2] = RotationRight(((X[2] ^ RK[52]) + (X[3] ^ RK[53])), 3); X[3] = temp;
	// 10라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[54]) + (X[1] ^ RK[55])), 9); X[1] = RotationRight(((X[1] ^ RK[56]) + (X[2] ^ RK[57])), 5); X[2] = RotationRight(((X[2] ^ RK[58]) + (X[3] ^ RK[59])), 3); X[3] = temp;
	// 11라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[60]) + (X[1] ^ RK[61])), 9); X[1] = RotationRight(((X[1] ^ RK[62]) + (X[2] ^ RK[63])), 5); X[2] = RotationRight(((X[2] ^ RK[64]) + (X[3] ^ RK[65])), 3); X[3] = temp;
	// 12라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[66]) + (X[1] ^ RK[67])), 9); X[1] = RotationRight(((X[1] ^ RK[68]) + (X[2] ^ RK[69])), 5); X[2] = RotationRight(((X[2] ^ RK[70]) + (X[3] ^ RK[71])), 3); X[3] = temp;
	// 13라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[72]) + (X[1] ^ RK[73])), 9); X[1] = RotationRight(((X[1] ^ RK[74]) + (X[2] ^ RK[75])), 5); X[2] = RotationRight(((X[2] ^ RK[76]) + (X[3] ^ RK[77])), 3); X[3] = temp;
	// 14라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[78]) + (X[1] ^ RK[79])), 9); X[1] = RotationRight(((X[1] ^ RK[80]) + (X[2] ^ RK[81])), 5); X[2] = RotationRight(((X[2] ^ RK[82]) + (X[3] ^ RK[83])), 3); X[3] = temp;
	// 15라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[84]) + (X[1] ^ RK[85])), 9); X[1] = RotationRight(((X[1] ^ RK[86]) + (X[2] ^ RK[87])), 5); X[2] = RotationRight(((X[2] ^ RK[88]) + (X[3] ^ RK[89])), 3); X[3] = temp;
	// 16라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[90]) + (X[1] ^ RK[91])), 9); X[1] = RotationRight(((X[1] ^ RK[92]) + (X[2] ^ RK[93])), 5); X[2] = RotationRight(((X[2] ^ RK[94]) + (X[3] ^ RK[95])), 3); X[3] = temp;
	// 17라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[96]) + (X[1] ^ RK[97])), 9); X[1] = RotationRight(((X[1] ^ RK[98]) + (X[2] ^ RK[99])), 5); X[2] = RotationRight(((X[2] ^ RK[100]) + (X[3] ^ RK[101])), 3); X[3] = temp;
	// 18라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[102]) + (X[1] ^ RK[103])), 9); X[1] = RotationRight(((X[1] ^ RK[104]) + (X[2] ^ RK[105])), 5); X[2] = RotationRight(((X[2] ^ RK[106]) + (X[3] ^ RK[107])), 3); X[3] = temp;
	// 19라운드
	temp = X[0];
	X[0] = RotationLeft(((X[0] ^ RK[108]) + (X[1] ^ RK[109])), 9); X[1] = RotationRight(((X[1] ^ RK[110]) + (X[2] ^ RK[111])), 5); X[2] = RotationRight(((X[2] ^ RK[112]) + (X[3] ^ RK[113])), 3); X[3] = temp;
	// 20라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[114]) + (X[1] ^ RK[115])), 9); X[1] = RotationRight(((X[1] ^ RK[116]) + (X[2] ^ RK[117])), 5); X[2] = RotationRight(((X[2] ^ RK[118]) + (X[3] ^ RK[119])), 3); X[3] = temp;
	// 21라운드
	temp = X[0];
	X[0] = RotationLeft(((X[0] ^ RK[120]) + (X[1] ^ RK[121])), 9); X[1] = RotationRight(((X[1] ^ RK[122]) + (X[2] ^ RK[123])), 5); X[2] = RotationRight(((X[2] ^ RK[124]) + (X[3] ^ RK[125])), 3); X[3] = temp;
	// 22라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[126]) + (X[1] ^ RK[127])), 9); X[1] = RotationRight(((X[1] ^ RK[128]) + (X[2] ^ RK[129])), 5); X[2] = RotationRight(((X[2] ^ RK[130]) + (X[3] ^ RK[131])), 3); X[3] = temp;
	// 23라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[132]) + (X[1] ^ RK[133])), 9); X[1] = RotationRight(((X[1] ^ RK[134]) + (X[2] ^ RK[135])), 5); X[2] = RotationRight(((X[2] ^ RK[136]) + (X[3] ^ RK[137])), 3); X[3] = temp;
	// 24라운드
	temp = X[0]; X[0] = RotationLeft(((X[0] ^ RK[138]) + (X[1] ^ RK[139])), 9); X[1] = RotationRight(((X[1] ^ RK[140]) + (X[2] ^ RK[141])), 5); X[2] = RotationRight(((X[2] ^ RK[142]) + (X[3] ^ RK[143])), 3); X[3] = temp;

	output[0] = X[0] & 0xff; output[1] = (X[0] >> 8) & 0xff; output[2] = (X[0] >> 16) & 0xff; output[3] = (X[0] >> 24) & 0xff;
	output[4] = X[1] & 0xff; output[5] = (X[1] >> 8) & 0xff; output[6] = (X[1] >> 16) & 0xff; output[7] = (X[1] >> 24) & 0xff;
	output[8] = X[2] & 0xff; output[9] = (X[2] >> 8) & 0xff; output[10] = (X[2] >> 16) & 0xff; output[11] = (X[2] >> 24) & 0xff;
	output[12] = X[3] & 0xff; output[13] = (X[3] >> 8) & 0xff; output[14] = (X[3] >> 16) & 0xff; output[15] = (X[3] >> 24) & 0xff;
}


void KeyExpansion(unsigned char* MK, int* RK)
{
	int T[4];

	T[0] = (MK[3] << 24) | (MK[2] << 16) | (MK[1] << 8) | MK[0];
	T[1] = (MK[7] << 24) | (MK[6] << 16) | (MK[5] << 8) | MK[4];
	T[2] = (MK[11] << 24) | (MK[10] << 16) | (MK[9] << 8) | MK[8];
	T[3] = (MK[15] << 24) | (MK[14] << 16) | (MK[13] << 8) | MK[12];

	// 1라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[0], 0), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[0], 1), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[0], 2), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[0], 3), 11);
	RK[0] = T[0]; RK[1] = RK[3] = RK[5] = T[1]; RK[2] = T[2]; RK[4] = T[3];
	// 2라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[1], 1), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[1], 2), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[1], 3), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[1], 4), 11);
	RK[6] = T[0]; RK[7] = RK[9] = RK[11] = T[1]; RK[8] = T[2]; RK[10] = T[3];
	// 3라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[2], 2), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[2], 3), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[2], 4), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[2], 5), 11);
	RK[12] = T[0]; RK[13] = RK[15] = RK[17] = T[1]; RK[14] = T[2]; RK[16] = T[3];
	// 4라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[3], 3), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[3], 4), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[3], 5), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[3], 6), 11);
	RK[18] = T[0]; RK[19] = RK[21] = RK[23] = T[1]; RK[20] = T[2]; RK[22] = T[3];
	// 5라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[0], 4), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[0], 5), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[0], 6), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[0], 7), 11);
	RK[24] = T[0]; RK[25] = RK[27] = RK[29] = T[1]; RK[26] = T[2]; RK[28] = T[3];
	// 6라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[1], 5), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[1], 6), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[1], 7), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[1], 8), 11);
	RK[30] = T[0]; RK[31] = RK[33] = RK[35] = T[1]; RK[32] = T[2]; RK[34] = T[3];
	// 7라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[2], 6), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[2], 7), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[2], 8), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[2], 9), 11);
	RK[36] = T[0]; RK[37] = RK[39] = RK[41] = T[1]; RK[38] = T[2]; RK[40] = T[3];
	// 8라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[3], 7), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[3], 8), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[3], 9), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[3], 10), 11);
	RK[42] = T[0]; RK[43] = RK[45] = RK[47] = T[1]; RK[44] = T[2]; RK[46] = T[3];
	// 9라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[0], 8), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[0], 9), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[0], 10), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[0], 11), 11);
	RK[48] = T[0]; RK[49] = RK[51] = RK[53] = T[1]; RK[50] = T[2]; RK[52] = T[3];
	// 10라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[1], 9), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[1], 10), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[1], 11), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[1], 12), 11);
	RK[54] = T[0]; RK[55] = RK[57] = RK[59] = T[1]; RK[56] = T[2]; RK[58] = T[3];
	// 11라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[2], 10), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[2], 11), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[2], 12), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[2], 13), 11);
	RK[60] = T[0]; RK[61] = RK[63] = RK[65] = T[1]; RK[62] = T[2]; RK[64] = T[3];
	// 12라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[3], 11), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[3], 12), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[3], 13), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[3], 14), 11);
	RK[66] = T[0]; RK[67] = RK[69] = RK[71] = T[1]; RK[68] = T[2]; RK[70] = T[3];
	// 13라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[0], 12), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[0], 13), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[0], 14), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[0], 15), 11);
	RK[72] = T[0]; RK[73] = RK[75] = RK[77] = T[1]; RK[74] = T[2]; RK[76] = T[3];
	// 14라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[1], 13), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[1], 14), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[1], 15), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[1], 16), 11);
	RK[78] = T[0]; RK[79] = RK[81] = RK[83] = T[1]; RK[80] = T[2]; RK[82] = T[3];
	// 15라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[2], 14), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[2], 15), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[2], 16), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[2], 17), 11);
	RK[84] = T[0]; RK[85] = RK[87] = RK[89] = T[1]; RK[86] = T[2]; RK[88] = T[3];
	// 16라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[3], 15), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[3], 16), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[3], 17), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[3], 18), 11);
	RK[90] = T[0]; RK[91] = RK[93] = RK[95] = T[1]; RK[92] = T[2]; RK[94] = T[3];
	// 17라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[0], 16), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[0], 17), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[0], 18), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[0], 19), 11);
	RK[96] = T[0]; RK[97] = RK[99] = RK[101] = T[1]; RK[98] = T[2]; RK[100] = T[3];
	// 18라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[1], 17), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[1], 18), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[1], 19), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[1], 20), 11);
	RK[102] = T[0]; RK[103] = RK[105] = RK[107] = T[1]; RK[104] = T[2]; RK[106] = T[3];
	// 19라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[2], 18), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[2], 19), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[2], 20), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[2], 21), 11);
	RK[108] = T[0]; RK[109] = RK[111] = RK[113] = T[1]; RK[110] = T[2]; RK[112] = T[3];
	// 20라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[3], 19), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[3], 20), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[3], 21), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[3], 22), 11);
	RK[114] = T[0]; RK[115] = RK[117] = RK[119] = T[1]; RK[116] = T[2]; RK[118] = T[3];
	// 21라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[0], 20), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[0], 21), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[0], 22), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[0], 23), 11);
	RK[120] = T[0]; RK[121] = RK[123] = RK[125] = T[1]; RK[122] = T[2]; RK[124] = T[3];
	// 22라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[1], 21), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[1], 22), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[1], 23), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[1], 24), 11);
	RK[126] = T[0]; RK[127] = RK[129] = RK[131] = T[1]; RK[128] = T[2]; RK[130] = T[3];
	// 23라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[2], 22), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[2], 23), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[2], 24), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[2], 25), 11);
	RK[132] = T[0]; RK[133] = RK[135] = RK[137] = T[1]; RK[134] = T[2]; RK[136] = T[3];
	// 24라운드 라운드키 생성
	T[0] = RotationLeft(T[0] + RotationLeft(Delta[3], 23), 1); T[1] = RotationLeft(T[1] + RotationLeft(Delta[3], 24), 3); T[2] = RotationLeft(T[2] + RotationLeft(Delta[3], 25), 6); T[3] = RotationLeft(T[3] + RotationLeft(Delta[3], 26), 11);
	RK[138] = T[0]; RK[139] = RK[141] = RK[143] = T[1]; RK[140] = T[2]; RK[142] = T[3];
}

int main() {
	unsigned char input[16] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
	unsigned char  MK[16] = { 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4 ,0xc3, 0xd2, 0xe1, 0xf0 };
	unsigned char output[16] = { 0 };
	int RK[144] = { 0 };
	int i; 
	
	printf("PlainText : ");
	for (i = 0; i < 16; i++)
		printf("%02x ", input[i]);
	printf("\n");

	printf("MasterKey : ");
	for (i = 0; i < 16; i++)
		printf("%02x ", MK[i]);
	printf("\n");

	KeyExpansion(MK, RK);
	Encryption(input, RK, output);

	printf("CipherText : ");
	for (i = 0; i < 16; i++)
		printf("%02x ", output[i]);
	printf("\n");
}

