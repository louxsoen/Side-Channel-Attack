#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memset함수 
#include <math.h>
#include <time.h>
//여러번 사용할 변수 선언
#define _FOLD_ "C:\\Users\\wngjs\\Desktop\\AES_CPA자료\\"    // 경로 지정 -> \1개씩 더 붙여 + 마지막에 \\까지 해야됨  (\\빼면 바탕화면에 생김)
#define TraceFN "AES.traces"   //FN : FileName   // 폴더에 있는 파일의 끝에 파일형식지정자 붙이지마... 자동으로 붙여져서 사용됨...
#define AlignedTraceFN "AlignedAES.traces"

#define PlaintextFN "plaintext.txt"
#define CiphertextFN "ciphertext.txt"

#define Startpoint 22551 // 어디부터 어디까지 끊을꺼냐 -> 1라운드를 포함하는 포인트 확인해 
#define Endpoint 31050 // 범위가 73200 -> 9000으로 줄어듦

static unsigned char AES_Sbox[256] = { //static으로 하는 이유?
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
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
};

// Cov함수 : 파형은 float형태로 찍혀있음 -> float형 배열 / size: 배열의 크기
double Cov(float* x, float* y, int size) {
	double Sxy = 0, Sx = 0, Sy = 0;
	int i;
	for (i = 0; i < size; i++) {
		Sxy += x[i] * y[i];  //XY들의 합
		Sx += x[i];
		Sy += y[i];
	}
	// Cov 리턴
	// return Sxy / (double)size - (Sx / (double)size) * (Sy / (double)size); // (double)안 붙여도 되지 않나?
	return (Sxy - Sx * Sy / (double)size) / (double)size; // size나누는게 3번 들어가니까 한번에 묶어서 계산해라 (괄호 주의)
} // 여기는 왜 루트 안들어감?? -> 상관계수가 아니라 공분산!

// Var(X) = E(X^2) - E(X)^2 에 루트 (sqrt : 스퀘어 루트)
double Corr(float* x, float* y, int size) {
	double Sxy = 0, Sx = 0, Sy = 0, Sxx = 0, Syy = 0;
	int i;
	for (i = 0; i < size; i++) {
		Sxy += x[i] * y[i];  
		Sx += x[i];
		Sy += y[i];
		Sxx += x[i] * x[i]; //E(X^2)구하는 부분에 필요 
		Syy += y[i] * y[i];
	}
	// double VarX = Sxx / (double)size - Sx * Sx / (double)size / (double)size; 
	// double VarY = Syy / (double)size - Sy * Sy / (double)size / (double)size;
	// return ((Sxy - Sx * Sy / (double)size) / (double)size) / sqrt(VarX * VarY);
	// size로 나누는게 굉장히 많음 -> 소거 가능 
	return ((double)size * Sxy - Sx * Sy) / sqrt(((double)size * Sxx - Sx * Sx) * ((double)size * Syy - Sy * Sy)); 
} //(double)size를 곱하는건 무슨 의미가 있는게 아니라 식을 정리하다 보니까 저렇게 된거야!

// 짧지만 과정 과정에서의 생각 중요 -> 할당된 메모리 영역을 넘지 않도록 
// data1 배열에 저장되어 있는 전력파형을 기준으로 data2 배열에 저장되어 있는 전력파형을 정렬 -> 파형 2개의 비교 
void SubAligned(float* data1, float* data2, int windowsize, int stepsize, int  threshold, int TraceLength) { //리턴은 data2에 들어감 
	int i, j, size, maxcovpos, k; // size : 비교하는 파형의 범위 / maxcovpos: cov가 최대일 때의 움직인 값
	float* x, * y; //비교할 부분의 시작위치
	double cov, maxcov; 

	// i가 TraceLength까지가면 메모리 범위를 넘어감 -> 파형전체를 사용하는 건 아니야, 끝쪽에는 분석에 의미 없는 파형이 있다고 가정해 -> 안전하게 windowsize를 빼
	for (i = 0; i < (TraceLength - windowsize); i += stepsize) { //stepsize만큼 뛰면서 정렬 맞춤

		//흔들때마다 정렬된 위치 기록해야함
		maxcovpos = 0;
		maxcov = 0;

		//windowsize만큼을 threshold 만큼 좌우로 흔들면서 Cov값 비교 
		for (j = -threshold; j < threshold; j++) { // 좌우로 흔들기 -> -threshold부터 +threshold까지 흔들기 

			// j의 부호에 따라서 나뉨 -> 두번째 파형을 왼쪽(음수)으로 옮기는지 오른쪽(양수)으로 옮기는지 (잘려나간 부분을 보면 이해됨)
			// 옮기는 작업은 귀찮으니까 사용하는 부분을 바꾸면 됨 -> 처음 시작부분이 남아있는 애는 놔두고 잘린 애의 인덱스 값을 바꾼다 -> 인덱스로 하는게 아니라 주소로 하는거여서 옮겨야함!
			if (j < 0) {
				x = data1 + i; // 기준 파형의 비교 시작부분 주소  -> int 값을 더함 -> 4byte주소 이동 -> float도 4byte -> 1포인트 이동
				y = data2 + i - j; // 비교 대상 파형의 시작부분 주소
				size = windowsize - abs(j); // size = windowsize + j(음수) -> windowsize보다 작아짐 -> 옮겼으니까 옮긴만큼이 잘림 -> 비교하는 부분이 적어짐 
			} // 절댓값씌우면 걍 - (양수)되잖아 -> 똑같은데 
			else {
				x = data1 + i + j;
				y = data2 + i;
				size = windowsize - abs(j); // size = windowsize - j(양수) -> windoswsize보다 작아짐
			}
		
			cov  = Cov(x, y, size); // size는 Cov를 구하기 위한 값이지 정렬할 때는 필요 없음
			// 최대값 Cov계산 해야함 
			if (cov > maxcov) {
				maxcovpos = j; //움직인 정도 저장
				maxcov = cov; // 가장큰 cov값 저장 -> 다음값과 계속 비교 
			}
		}
		// 이거 maxcovpos가 양/음에 상관없이 똑같은 부분이 뒤/앞에 생기네 -> 그래서 stepsize를 저렇게 잡는 건가? j만큼이 똑같은 값이 됨 -> 뒤쪽에서 나타나면 상관없는데 앞쪽에서 나타나면 동일한 파형이 2개 생기는데?
		// TraceLength까지 가니까 파형 맨 끝부분이 문제가 되겠네 or 파형 맨 앞부분 -> TraceLength까지 안가고 TraceLength-windowsize하니까 뒷부분은 정렬 필요 없다고 보니까 의미 없어짐 -> 앞부분은 그대로 유의미한데?
		// 좌/우로 흔드는게 겹치면서 상쇄되나?
		// 가장 적합한 정렬 정도를 구했으니 정렬시키자 
		// windowsize안에서만 움직이면 겹치니까 안되고 Trace 전체를 움직여야함 -> 왼쪽으로 움직이는건 데이터 보존 상관없음 / 오른쪽으로 움직일 때 데이터 보존해야함  
		if (maxcovpos < 0) { // 음수/양수 일 때 나눠야함 -> j가 음/양일 때 나누는 것과 같음 -> 왼쪽으로 옮길지, 오른쪽으로 옮길지
			for (k = i; k < (TraceLength + maxcovpos); k++) {//maxcovpos가 음수니까 + 연산자 사용
				data2[k] = data2[k - maxcovpos]; //음수니까 - 연산자  -> 범위를 벗어나는지 확인 TraceLength - 1까지 O.K
				// k로 해도 TraceLength 안 넘어감 -> maxcovpos가 음수여서 안넘어감 
			}
		}
		else { // 맨끝부터 이동해야지 값 보존 가능 -> 첫번째 파형은 가만히 놔두고 나머지 파형만 움직일 수 있음 -> 처음 파형은 안 짤림? -> 두번째 파형의 시작점이 첫번째 파형의 중간 부분과 시점이 일치하는거 아니야?
			for (k = (TraceLength - maxcovpos - 1); k >= i; k--) {
				data2[k + maxcovpos] = data2[k];
			}
		}
	}
}


//정렬 함수
// AES.traces에 2000개의 파형이 있음 -> 이 파형들은 정렬 안 되어있음 -> 첫번째 파형을 기준으로 1999개의 파형을 맞춤
// 2000개의 정렬된 파형을 만들고 새로운 trace파일을 만들겠다 -> 크기. 구조 모두 같은데 정렬 유무차이 
// 구간을 잡는다 == 윈도우를 잡는다 / 쓰레쉬홀드(threshold)값 만큼 흔들면서 Cov값이 높은곳에 놓기 : 반복 
// 73200개의 포인트인데 이거를 한번에 흔들어서 맞추지는 못해 -> 흔들린 기준이 달라 -> 중간중간 파형이 흔들려 있음
void Alignment() {
	int windowsize = 500; // 부분 정렬을 맞추고 싶은 파형의 길이 (파형 포인트의 수)
	int stepsize = 450; // 정렬을 끝낸 후에 몇 포인트씩 이동 후 다시 정렬을 맞출 것인지 결정 -> windowsize보다 약간 작게 -> 조금씩 겹쳐서 맞출수 있게 
	int threshold = 100;// 좌우로 얼마나 흔들면서 Cov값을 계산해서 최대값일 때 이동할 포인트수를 계산 -> 파형을 보면서 결정 -> 값이 너무 크면 많은 시간소요
	char buf[256]; // 파일의 정보를 담고 넘길 때 필요한 버퍼
	int err, TraceLength, TraceNum,i; //에러확인 변수(가독성을 위한 것이지 반드시 필요하지는 않음), Trace의 길이와 개수, for문 제어변수
	FILE* rfp, * wfp; // 파일 포인터 

	// 데이터 읽어오기 
	// 파일의 사이즈 : 570Mbyte -> 파형이 너무 커서 10GB씩 되는 경우 있음 -> 메모리에서 한번에 작업 못함 -> 파형을 그때그때 읽어야함 
	// 통째로 열어서 처음 4byte 2번 읽어서 길이, 개수 측정 -> 파형을 1개씩 읽어서 특정 메모리 영역을 올려놓고 두번째 파형부터 메모리에 1개씩 올려가며 정렬 맞춘 후 저장
	float* data1, * data2;  //첫번째 파형, 두번째 파형이후 
	
	// 읽을 파일 
	sprintf_s(buf, 256 * sizeof(char)/*sizeof(buf)*/, "%s%s", _FOLD_, TraceFN);//파형 파일open -> 해당 경로에 대한 문자열이 buf에 들어옴 / 왜 sizeof(buf)하면 되는데 구지 저렇게함?
	if ((err = fopen_s(&rfp, buf, "rb"))) { // 경로를 포함한 파일명이 있는 buf를 파일포인터를 이용해 readbinary형태로 연다 
		printf("File Open Error1!!\n");	
		// return ; : 오류 어디서 나는지 check 용도
	}
	
	// 정렬 맞춘 파형을 쓸 파일
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, AlignedTraceFN);
	if ((err = fopen_s(&wfp, buf, "wb"))) { 
		printf("File Open Error2!!\n");
	}

	// 파일 형식 파악
	fread(&TraceLength, sizeof(int), 1, rfp);  // 트레이스 길이 읽기 
	fwrite(&TraceLength, sizeof(int), 1, wfp);// 정렬 맞춘 파일도 형식 같음 
	fread(&TraceNum, sizeof(int), 1, rfp);   // 트레이스 개수 읽기 (순차적 읽기)
	fwrite(&TraceNum, sizeof(int), 1, wfp);

	//data와 data1에 대한 포인터만 있지 메모리 할당 안됨 
	data1 = (float*)calloc(TraceLength, sizeof(float)); // data1에 TraceLength개의 float형 메모리 동적 할당
	data2 = (float*)calloc(TraceLength, sizeof(float));// calloc: 메모리를 할당하면서 0으로 채움
	 
	// 파형 읽기 
	fread(data1, sizeof(float), TraceLength, rfp); // 첫번째 파형 읽기 
	fwrite(data1, sizeof(float), TraceLength, wfp); // 첫번째 파형은 정렬된 파형에도 그대로 복사 

	//두번째 파형부터 첫번째 파형에 맞춰 정렬한 것을 저장
	for (i = 1; i < TraceNum; i++) {
		fread(data2, sizeof(float), TraceLength, rfp); // 두번째 파형 읽기
		SubAligned(data1, data2, windowsize, stepsize, threshold, TraceLength);  // data1파형 기준으로 data2파형을 정렬하는 함수  -> 정보 넘겨줘 
		fwrite(data2, sizeof(float), TraceLength, wfp);  //정렬된 data2을 업데이트 
	}
	fclose(rfp);
	fclose(wfp);

	free(data1); //동적 메모리 해지 
	free(data2);
}	

// 평문정보만 가지고 분석 코드 구현 
// 분석 도구 : 정렬된 파형, 평문 파일
// 분석방법: 정렬된 파형의 S-box출력 부분을 평문 파일을 이용하여 조사한다 -> 
void CPA() {
	unsigned char** plaintext = NULL; // 평문정보를 담을 이중 포인터 (2000*16) -> 2000개의 Trace 대한 16byte의 평문을 2000*16 크기의 배열에 저장 
	float** data; // 정렬된 파형을 한번에 로딩 -> 이중 포인터인 이유: 데이터의 크기가 500MB 밖에 안됨, 한 번에 메모리에 올려서 처리가능 
	char buf[256];
	int err, TraceLength, TraceNum, i, j, key, k, maxkey;
	FILE* rfp, * wfp;
	unsigned char temp[34], x, y, iv, hw_iv; // hw_iv는 어차피 0~8까지 밖에 저장 안 할꺼야  / temp그냥 char로 하라는데?? -> 빌드에서 제외하면 등장
	// unsigned char나 char나 담을 수 있는 범위는(1byte = 8bit) 같음 -> 양수범위를 누가 더 많이 담느냐에 차이가 있을뿐 -> 양수인 1byte의 값을 모두 담으려면 char로는 불가능 

	// 키추측마다 상관계수를 계산 할 텐데 -> corrT: 상관계수 값을 저장할 배열(correlation Trace) / Sxy: 공분산을 저장할 배열 
	double* Sx, * Sxx, * Sxy, * corrT; // 실제 소비전력 파형쪽은 배열을 이용-> 각 포인트에 대해서 각자 더해야함 -> 배열로 저장 -> 각 열의 합을 저장
	double Sy, Syy, max; // 키추측한 해밍웨이트는 그냥 값으로 -> 하나의 값을 그냥 더하면 됨 -> 배열 필요없음   
	// 배열과 값으로 하는 것의 차이?

	// 정렬된 파형 파일 열기
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, AlignedTraceFN);
	if ((err = fopen_s(&rfp, buf, "rb"))) { // fopen과 다르게 파일의 주소는 &rfp에 저장하고 open의 성공여부를 리턴한다 
		printf("File Open Error!!\n");
	}

	// 파일 형식 정보 얻기 
	fread(&TraceLength, sizeof(int), 1, rfp);
	fread(&TraceNum, sizeof(int), 1, rfp);

	
	// 데이터를 메모리에 올리기 위해 동적 할당 
	data = (float**)calloc(TraceNum, sizeof(float*));  // 2000개의 trace를 가르킬 2000개의 float 포인터 선언
	                           // 생성되는 배열: float형 포인터
	for (i = 0; i < TraceNum; i++) {
		data[i] = (float*)calloc(TraceLength, sizeof(float)); // 정렬된 파형을 담을 배열 선언
	}

	// 정렬된 파형 로딩
	for (i = 0; i < TraceNum; i++) {
		fread(data[i], sizeof(float), TraceLength, rfp); // 선언한 배열에 rfp로부터 파형을 읽어 온다 
	}         // 73200개의 포인트가 있는데 1개의 포인트의 size가 float

	fclose(rfp); // 다 읽어 왔으니 닫어 

	// 평문 파일 로딩 -> 평문이 저장된 형태를 보고 배열에 담아야함 -> 아스키형태(글자)로 저장되어 있음 -> 숫자로 변환해서 저장
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, PlaintextFN);
	if ((err = fopen_s(&rfp, buf, "r"))) { // plaintext파일을 열때 이진형태가(rb)가 아니라 텍스트형태(rt)로 열어야함 -> 개행문자 처리 때문에?? / text파일이여서 텍스트 형태로 저장되어 있어서 rt로 열어야하는건지? 왜 이진파일로는 못 열음?
		printf("File Open Error!!\n");
	}

	// plaintext 포인터들 할당
	plaintext = (unsigned char**)calloc(TraceNum, sizeof(unsigned char*)); // 평문으로부터 파형이 나왔으니까 데이터 구조 같음 -> 같은 형태로 동적 할당

	for (i = 0; i < TraceNum; i++) {
		plaintext[i] = (unsigned char*)calloc(16, sizeof(unsigned char)); // 1개의 plaintext는 16byte로 구성됨 -> plaintext 배열 할당
	}

	// txt형태의 평문 가져오기 
	// 문자와 값의 차이 존재 
	// 아스키코드 문자 1개는 1byte로 매핑됨: [문자] = 0x□□ (□=4bit) -> 한줄에 32글자: 32byte -> 16진수에서는 2글자가 1byte임 -> Hex파일로 열면 2줄을 차지함 -> 0D0A: 개행문자 -> 평문 한줄을 읽으려면 34byte씩 읽으면됨
	for (i = 0; i < TraceNum; i++) {
		fgets(temp, 34, rfp); // rfp로 부터 34byte씩 읽어서 temp배열에 저장  // 34를 35로 바꿔야할거 같은디 (교재 p430) -> 개행문자는 빼고 받으려고 34인가? -> 그럼 33을 해야하는디 -> 최대로 받는거여서 개행문자 만나면 끝나니까 작지만 않으면 됨-> txt로된 개행문자를 인식함?
		// 개행 문자를 제외한 32byte 크기의 문자를 2byte씩 묶어서 16byte를 plaintext에 넣기  
		// ftell(rfp); // 파일 위치 지시자가 어디에 위치하는지 확인 
		for (j = 0; j < 16; j++) { //16byte만들기 
			x = temp[2 * j]; // 아스키 코드로 받음   // i -> j 
			y = temp[2 * j + 1]; //34까지 읽어도 어차피 31까지밖에 처리를 안함 -> 0~31 : 32개의 byte만 처리

			// 아스키코드를 16진수 숫자로 변형
			if (x >= 'A' && x <= 'F') // 16진수니까 '0'~'9'와'A'~'F' 'a'~'f' 로 표현됨 
				x = x - 'A' + 10; // 아스키코드 'A'를 16진수 A로 변환 -> 'A'~'F'범위니까 대문자 'A'값(65)만큼빼서 0으로 만들고 16진수 A값인 10을 더해줘서 맞춰준다
			else if (x >= 'a' && x <= 'f')   
				x = x - 'a' + 10;
			else if (x >= '0' && x <= '9')
				x -= '0'; 
			// y도 마찬가지로
			if (y >= 'A' && y <= 'F') y = y - 'A' + 10; 
			else if (y >= 'a' && y <= 'z') y = y - 'a' + 10;
			else if (y >= '0' && y <= '9') y -= '0';
			
			// printf("%s %x", x, x); exit(0); // printf와 %x로 하면 원하는 값이 나오지만 %s로 x,y 출력하면 이상한 값 나올꺼야 -> 아스키앞쪽에 있는 값들 나옴 -> %s로 하면 x가 int라고 출력이 안되는데?

			plaintext[i][j] = x * 16 + y;// i번째 text에 j번째 바이트에 넣기 -> 두자리인데 x가 첫번째 자리니까 16곱해서 첫자리에 넣고 y를 두번째 자리에 넣기
		}                               // 0x00~0xFF 가능 -> 0xFF = 16*F + F -> 16진수니까 앞자리는 16^1의 자리수 
	}
	fclose(rfp); //평문 파일 닫기

	// 키마다 추측한 해밍웨이트와 전력파형 사이에 상관계수 계산 -> 그때 그때 한 포인트씩 읽어서 x에 넣고, 추측한 값을 y에 넣어서 비교 -> 너무 시간 오래걸려 -> 배열에 넣기 
	// x와 y의 데이터형을 분리해서 작성 -> y(키추측)는 값으로 x(소비전력)는 배열로 -> 배열로 할 것들 동적으로 할당 
	// TraceNum만큼의 Trace들을 동시에 순서대로 한 포인트씩 거치면서 해밍웨이트를 계산 
	Sx = (double*)calloc(TraceLength, sizeof(double));  // 배열로 하는 이유: 
	Sxx = (double*)calloc(TraceLength, sizeof(double));
	Sxy = (double*)calloc(TraceLength, sizeof(double)); // 파형을 float이고 상관계수는 double형이네?
	corrT = (double*)calloc(TraceLength, sizeof(double));
	
	
	// x는 키추측(y)과 상관 없는 부분이므로 독립적으로 연산 가능 -> 정렬된 파형으로 사전 계산
	for (i = 0; i < TraceNum; i++) {//행
		for (j = Startpoint  /*0*/ ; j < Endpoint /*TraceLength*/; j++) { // 열 열끼리의 합을 구함 
			Sx[j] += data[i][j]; // i번째 Trace의 j번째 포인트 값 -> 각 포인트의 값을 저장  -> 그 포인트의 값의 1의 개수는 전력소비량 -> 근데 이 파형이 전력소비 파형
			Sxx[j] += data[i][j] * data[i][j]; // 왜 더함? 각각을 비교해야 하는거 아니야? -> 정확한 값을 찾는게 아니라 상관계수를 찾는 중 -> 정확한 값이면 좋겠지만 같은 흐름인지 파악하여 정확한 값을 유추중 
		}                                      // 상관계수를 더해서 구하는 이유?(통계시간에..)
	}// 행과 열의 값 이해 Hard-> 같은 열끼리의 값을 합해놔야 하는거 아니야? -> 열값이 밖에 있고 행값이 안에 있어야하는거 아니야? -> 같은 의미야!
	
	/*
	// By 이주헌  -> 똑같음 -> 값을 훓는 방식이 다를뿐 더해진 결과는 같음 
	for (i = Startpoint; i < Endpoint; i++) { //열
		for (j = 0; j < TraceNum; j++) { //행
			Sx[i] += data[j][i];
			Sxx[i] += data[j][i] * data[j][i];  // 이 방식이 더 나한테는 직관적
		}
	} // 열을 고정해놓고 행쪽으로 훓기 vs. 행을 고정해놓고 열을 옮겨가며 훓기
	*/

	//AES의 마스터 키와 평문은 128bit -> 16byte -> 1byte 크기의 블록이 16개 있음 -> 이렇게 구하면 16번의 작업을 다 해야지 전체 마스터키를 구할 수 있음? -> 그래서 i가 0~15까지 가는거네...
	for (i = 0; i < 16; i++) { // i는 몇번째 블록인지 -> 몇번째 블록과 그에 대한 키인지 -> 16개의 키가 모여서 마스터키를 만듦
		max = 0; // 상관계수 최대값
		maxkey = 0; // 최대일 때의 key값 

		// 키추측
		for (key = 0; key < 256; key++) {// 각 블록은 1byte이므로 2^4 *2^4 = 2^8 = 256 -> 256개의 키가 가능 -> 1블록에서만 256가지의 키가 가능 

			Sy = 0;
			Syy = 0;
			memset(Sxy, 0, sizeof(double) * TraceLength); // double배열을 0으로 초기화시킴 -> +=연산 할려고 

			// 키추측마다의 중간값(iv: intermediate value) 계산 (1byte) -> 키추측마다의 S-box 출력값 -> 키추측마다 예측하는 파형 -> S-box를 거친 중간값의 해밍웨이트 -> 1의 개수 카운팅
			for (j = 0; j < TraceNum; j++) { // TraceNum: 평문의 개수 
				iv = AES_Sbox[plaintext[j][i] ^ key];//AES의 S-box필요 -> j번째 평문의 i번째 byte와 추측한 key의 Xor연산을 S-box에 넣기 -> S-box출력을 iv로 받기
				hw_iv = 0; // iv와 마찬가지로 unsigned char형 -> 해밍웨이트와 전력소비 파형의 값이 같지는 않지만 둘의 값의 추이가 어떤지를 비교하는거야 -> 같은 부분에서 증가하는지 않하는자
				// 이렇게하면 평문과 마스터키의 첫번째 8bit(1byte, 1개의 state)에 대한 헤밍웨이트만 계산? -> 평문의 전체 S-box출력의 헤밍웨이트가 아니라 평문 일부의 헤밍웨이트를 구하는거야?

				for (k = 0; k < 8; k++) { // 키에 해당하는 S-box출력값의 해밍웨이트 계산 
					hw_iv += ((iv >> k) & 1); // 1의 개수 카운팅 -> k=0 1개도 밀지않고 1과 연산하니까 최하위 1bit나옴 -> k=1 1bit밀고 1과 &하니까 최하위 2번째 비트값이 나옴
				} // unsigned char형의 첫 bit와 1과 Xor연산 -> 1의 자료형이 무엇이길래 비트연산을 저렇게함? -> 10진수의 1임 -> 8bit모두 연산되는데 &와 0때문에 마지막 비트만 추출 가능 
				// 1(2^0) = 0000 0001으로 됨 -> 2(2^1) = 0000 0010: 뒤에서 2번째 비트와 연산 가능 -> 4byte니까 앞에 0이 더 붙어있기는 한건지?
				Sy += hw_iv; // 상관계수 계산하려면 다 더해야함 -> 키추측에서의 헤밍웨이트 
				Syy += hw_iv * hw_iv; // 첫번째 파형에 대한 헤밍웨이트 -> 가로가 모두 공유 -> 가로로 더해야함 -> corrT구하는 거보면 열내에서의 합인데?

				for (k = Startpoint /*0*/ ; k < Endpoint /*TraceLength*/; k++) { // 여기도 왜 열끼리 더해? 열을 기준으로 행끼리 더해야지..
					Sxy[k] += (float)hw_iv * data[j][k];  // 키추측에서의 해밍웨이트와 실제 파형간의 곱셈 -> 파형의 헤밍웨이트도 구해야하는거 아니야? bit추출해서?
				} // S-box의 출력값의 1의 개수에 따라 전력소비 -> 파형이 전력소비를 나타냄 -> 파형 그대로 계산하면 그게 헤밍웨이트로 구한 값과 같은거야!
				// 같은 행은 같은 헤밍웨이트를 공유하므로 열을 옮겨가며 가로로 훓는 중 
				

				/* for (k = 0; k < TraceNum; k++) { // 근데 j가 행이네? -> 밖에서 해야하는데 hw_iv때문에 못함 -> 안에서 이중for문 해야함? -> hw_iv그냥 쫙 더해진 값인데? for밖으로 나와도 상관없지않나?
					Sxy[j] += hw_iv * data[k][j];
					} */
			}
			
			// 모든 포인트 상관계수 파형 계산해서 저장 -> 최대인 곳은 계속 체크하면서 -> 연산량 많아 -> 필요한 부분만 계산 가능 -> startpoint / endpoing
			for (k = Startpoint /*0*/; k < Endpoint /*TraceLength*/; k++) { // TraceNum == size
 				corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));
				// 처음부터 끝이아니라 startpoing부터 endpoint까지해서 나누는 값이 달라지나 했는데 TraceNum으로 나누네  
				if (fabs(corrT[k]) > max) { // 상관계수의 최대값 찾기 -> 상관계수의 절대값으로 해야함 -> 역으로 비례하는 경우 -> 전력파형이 음수인 경우 있음??
					maxkey = key;
					max = fabs(corrT[k]); //fabs: double형 일 때 사용하는 절댓값 함수 
				}
			}

			// 첫번째 블록에서 키를 바꿔가며(00~FF) 모든 포인트를 다 조사 -> 블록을 바꾼후 다시 모든 포인트 조사 
			// 상관계수 계산하면서 상관계수 파형 만들고 그 파형에서 어디가 최대치인지 확인 -> 상관계수 파형 저장
			sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\%02dth_block_%02x.corrtrace", _FOLD_, i, key);//corrtrace폴더에 몇번째(0~16) 블록에 어떤 키의 corrtrace값인지 기록
			if ((err = fopen_s(&wfp, buf, "wb"))) {
				printf("File Open Error5!!\n");
			}
			fwrite(corrT, sizeof(double), TraceLength, wfp); // wfp에 corrT(상관계수) 넣기 
			fclose(wfp);
			printf("."); //키 추측마다 왜 죽는지 확인 + 프로그램 돌아가는지 확인 
		}	
		//최대인 곳 출력 
		printf("%02dth_block: maxkey(%02x), maxcorr(%lf)\n", i, maxkey, max); //f와 lf의 출력이 달라?? -> 똑같어~	-> double형식을 출력하는 것을 명시
	}
	free(Sx);
	free(Sxx);
	free(Sxy);
	free(corrT);
	free(data);
	free(plaintext);
}

int main() {
	//float X[10] = { 1,2,3,5,6,4,6,7,6,5};
	//float Y[10] = { 2,3,6,3,5,4,2,1,5,8 };
	//printf("Covariance : %lf, Correlation Coefficient : %lf \n", Cov(X, Y, 10), Corr(X, Y, 10));

	//정렬하고 CPA해야하는거 아니야? -> 맞아 -> 정렬은 한 번만 돌리면 됨 
	// Alignment();
	CPA();
} 
