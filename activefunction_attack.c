#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>


#define _FOLD_ "C:\\Users\\master\\Desktop\\LEEJUHEON\\"
//#define TraceFN "ReLU_traces.npy"   
//#define TraceFN "Tanh_traces.npy"
#define TraceFN "Sigmoid_traces.npy"


//#define PlaintextFN "ReLU_textin.npy" 
//#define PlaintextFN "Tanh_textin.npy"
//#define PlaintextFN "Sigmoid_textin.npy"

//#define PlaintextFN "Tanh_textout.npy"  // textout에 입출력 다 넣었어 
//#define CipherextFN "Tanh_textout.npy"

#define PlaintextFN "Sigmoid_textout.npy"
#define CipherextFN "Sigmoid_textout.npy"


//#define CipherextFN "ReLU_textout.npy"
//#define CipherextFN "Tanh_textout.npy"
//#define CipherextFN "Sigmoid_textout.npy"


#define startpoint 0
#define endpoint 22000

#define start 26 // 입력 CPA 기준 tanh : 26 / sigmoid : 34 
//#define end 0  //필요 한가?
#define peak 15000

#define ClearTraceFN "Clear_ReLU_traces.npy" // Clear_Sigmod_traces.npy  / Clear_tanh_traces.npy -> 구할 필요없음 정확한 시점만 찾으면 됨 
#define TrashTraceFN "trash_traces.npy"	// 칩위스퍼 쓰레기 파형 


double Cov(float* x, float* y, int size) {
	double Sxy = 0, Sx = 0, Sy = 0;
	int i;
	for (i = 0; i < size; i++) {
		Sxy += x[i] * y[i];
		Sx += x[i];
		Sy += y[i];
	}


	return (Sxy - Sx * Sy / (double)size) / (double)size;
}


double Corr(float* x, float* y, int size)
{
	double Sxy = 0, Sx = 0, Sy = 0, Sxx = 0, Syy = 0;
	int i;
	for (i = 0; i < size; i++) {
		Sxy += x[i] * y[i];
		Sx += x[i];
		Sy += y[i];
		Sxx += x[i] * x[i];
		Syy += y[i] * y[i];
	}

	return ((double)size * Sxy - Sx * Sy) / sqrt(((double)size * Sxx - Sx * Sx) * ((double)size * Syy - Sy * Sy));
}


void SubAligned(float* data1, float* data2, int windowsize, int stepsize, int  threshold, int TraceLength)  // data
{
	int i, j, size, maxcovpos, k;
	float* x, *y;
	double cov, maxcov;


	for (i = 0; i < (TraceLength - windowsize); i += stepsize)
	{
		maxcovpos = 0;
		maxcov = 0;


		for (j = -threshold; j < threshold; j++)
		{
			if (j < 0)
			{
				x = data1 + i;
				y = data2 + i - j;
				size = windowsize - abs(j);
			}
			else
			{
				x = data1 + i + j;
				y = data2 + i;
				size = windowsize - abs(j);
			}

			cov = Cov(x, y, size);

			if (cov > maxcov)
			{
				maxcovpos = j;
				maxcov = cov;
			}
		}

		if (maxcovpos < 0)
		{
			for (k = i; k < (TraceLength + maxcovpos); k++) {
				data2[k] = data2[k - maxcovpos];

			}
		}
		else
		{
			for (k = (TraceLength - maxcovpos - 1); k >= i; k--) {
				data2[k + maxcovpos] = data2[k];
			}
		}
	}
}


void Alignment()
{
	int windowsize = 500;
	int stepsize = 450;
	int threshold = 100;
	char buf[256];
	int err, TraceLength, TraceNum, i;
	FILE* rfp, *wfp;
	float* data1, *data2; // data1: 함수 파형 | data2: 쓰레기 파형 



	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, TraceFN);	// 함수 파형 
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error1!!\n");
	}

	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, TrashTraceFN); // 쓰레기 파형
	if ((err = fopen_s(&wfp, buf, "wb")))
	{
		printf("File Open Error2!!\n");
	}

	TraceLength = 0;
	TraceNum = 0;
	/*
	fread(&TraceLength, sizeof(int), 1, rfp);
	fwrite(&TraceLength, sizeof(int), 1, wfp);
	fread(&TraceNum, sizeof(int), 1, rfp);
	fwrite(&TraceNum, sizeof(int), 1, wfp);
	*/

	// fseek(rfp, 61, SEEK_SET);
	// fseek(wfp, 61, SEEK_SET);

	fseek(rfp, 128, SEEK_SET);
	fseek(wfp, 128, SEEK_SET);

	data1 = (float*)calloc(TraceLength, sizeof(float));
	data2 = (float*)calloc(TraceLength, sizeof(float));

	fread(data1, sizeof(float), TraceLength, rfp); 	fwrite(data1, sizeof(float), TraceLength, wfp);
	for (i = 1; i < TraceNum; i++)
	{
		fread(data2, sizeof(float), TraceLength, rfp);
		SubAligned(data1, data2, windowsize, stepsize, threshold, TraceLength);
		fwrite(data2, sizeof(float), TraceLength, wfp);
	}
	fclose(rfp);
	fclose(wfp);

	free(data1);
	free(data2);
}


void InputCPA()
{
	unsigned char** plaintext = NULL;
	//float* plaintext = NULL; // float 입력 
	double** data; // float -> double
	char buf[256];
	int err, TraceLength, TraceNum, i, j, k;
	FILE* rfp, *wfp;
	unsigned char hw_iv;
	int iv, maxpoint;
	double* Sx, *Sxx, *Sxy, *corrT;
	double Sy, Syy, max;
	int temp = 0;


	// 활성함수 파형 담기 
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, TraceFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error1!!\n");
	}

	// 파형수집 정보
	TraceLength = 22000;
	TraceNum = 5000;

	data = (double**)calloc(TraceNum, sizeof(double*));

	for (i = 0; i < TraceNum; i++)
	{
		data[i] = (double*)calloc(TraceLength, sizeof(double));
	}

	fseek(rfp, 128, SEEK_SET);
	for (i = 0; i < TraceNum; i++)
	{
		fread(data[i], sizeof(double), TraceLength, rfp);
	}
	fclose(rfp);

	/*
	printf("%lf ", data[0][0]);
	printf("%lf ", data[0][1]);
	printf("%lf ", data[0][2]);
	printf("%lf ", data[0][3]);
	printf("%lf ", data[0][4]);
	printf("%lf ", data[0][5]);
	*/


	// plaintext에 4byte만 담기
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, PlaintextFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error2!!\n");
	}

	plaintext = (unsigned char**)calloc(TraceNum, sizeof(unsigned char*));

	for (i = 0; i < TraceNum; i++)
	{
		plaintext[i] = (unsigned char*)calloc(4, sizeof(unsigned char));
	}

	fseek(rfp, 128, SEEK_SET);
	for (i = 0; i < TraceNum; i++)
	{
		fread(plaintext[i], sizeof(unsigned char), 4, rfp);
		//fseek(rfp, 11, SEEK_SET);
		fread(&temp, sizeof(unsigned char), 12, rfp);
	}
	fclose(rfp);

#if 0
	printf("%x ", plaintext[0][0]);
	printf("%x ", plaintext[0][1]);
	printf("%x ", plaintext[0][2]);
	printf("%x ", plaintext[0][3]);
	printf("%x ", plaintext[1][0]);
	printf("%x ", plaintext[1][1]);
	printf("%x ", plaintext[2][0]);
#endif

	Sx = (double*)calloc(TraceLength, sizeof(double));
	Sxx = (double*)calloc(TraceLength, sizeof(double));
	Sxy = (double*)calloc(TraceLength, sizeof(double));
	corrT = (double*)calloc(TraceLength, sizeof(double));


	for (i = startpoint; i < endpoint; i++)
	{
		for (j = 0; j < TraceNum; j++)
		{
			Sx[i] += data[j][i];
			Sxx[i] += data[j][i] * data[j][i];
		}
	}



	// float 입력에 대한 CPA
	Sy = 0;
	Syy = 0;
	max = 0;
	memset(Sxy, 0, sizeof(double) * TraceLength);


	for (j = 0; j < TraceNum; j++)
	{
		//iv = plaintext[j][0]; // float형 변수 
		iv = (plaintext[j][0] << 24 | plaintext[j][1] << 16 | plaintext[j][2] << 8 | plaintext[j][3]);

		hw_iv = 0;


		for (k = 0; k < 32; k++) // 32bit
		{
			hw_iv += ((iv >> k) & 1);
			//printf("%d \n", hw_iv);
		}

		Sy += hw_iv;
		Syy += hw_iv * hw_iv;

		for (k = startpoint; k < endpoint; k++)
		{
			Sxy[k] += hw_iv * data[j][k];
		}
	}

	for (k = startpoint; k < endpoint; k++)
	{
		corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));

		if (fabs(corrT[k]) > max)
		{
			maxpoint = k;
			max = fabs(corrT[k]);
		}
	}

	sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\input.corrtrace", _FOLD_);
	if ((err = fopen_s(&wfp, buf, "wb")))
	{
		printf("File Open Error3!!\n");
	}
	fwrite(corrT, sizeof(double), TraceLength, wfp);
	fclose(wfp);
	//printf(".");


	printf("input maxcorr : %lf at %dpoint \n", max, maxpoint + 1); // Matlab 1부터 시작하는거 반영 

	free(Sx);
	free(Sxx);
	free(Sxy);
	free(corrT);
	free(data);
	free(plaintext);
}

void OutputCPA()
{
	unsigned char** ciphertext = NULL;
	//float* plaintext = NULL; // float 입력 
	double** data; // float -> double
	char buf[256];
	int err, TraceLength, TraceNum, i, j, k;
	FILE* rfp, *wfp;
	unsigned char hw_iv;
	int iv, maxpoint;
	double* Sx, *Sxx, *Sxy, *corrT;
	double Sy, Syy, max;
	int temp = 0;


	// 활성함수 파형 담기 
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, TraceFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error1!!\n");
	}

	// 파형수집 정보
	TraceLength = 22000;
	TraceNum = 5000;

	data = (double**)calloc(TraceNum, sizeof(double*));

	for (i = 0; i < TraceNum; i++)
	{
		data[i] = (double*)calloc(TraceLength, sizeof(double));
	}

	fseek(rfp, 128, SEEK_SET);
	for (i = 0; i < TraceNum; i++)
	{
		fread(data[i], sizeof(double), TraceLength, rfp);
	}
	fclose(rfp);

	/*
	printf("%lf ", data[0][0]);
	printf("%lf ", data[0][1]);
	printf("%lf ", data[0][2]);
	printf("%lf ", data[0][3]);
	printf("%lf ", data[0][4]);
	printf("%lf ", data[0][5]);
	*/


	// plaintext에 4byte만 담기
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, CipherextFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error2!!\n");
	}

	ciphertext = (unsigned char**)calloc(TraceNum, sizeof(unsigned char*));

	for (i = 0; i < TraceNum; i++)
	{
		ciphertext[i] = (unsigned char*)calloc(4, sizeof(unsigned char));
	}

	fseek(rfp, 128, SEEK_SET);
	for (i = 0; i < TraceNum; i++)
	{
		fread(&temp, sizeof(unsigned char), 4, rfp);
		fread(ciphertext[i], sizeof(unsigned char), 4, rfp);
		fread(&temp, sizeof(unsigned char), 8, rfp);
	}
	fclose(rfp);

#if 0
	printf("%x ", plaintext[0][0]);
	printf("%x ", plaintext[0][1]);
	printf("%x ", plaintext[0][2]);
	printf("%x ", plaintext[0][3]);
	printf("%x ", plaintext[1][0]);
	printf("%x ", plaintext[1][1]);
	printf("%x ", plaintext[2][0]);
#endif

	Sx = (double*)calloc(TraceLength, sizeof(double));
	Sxx = (double*)calloc(TraceLength, sizeof(double));
	Sxy = (double*)calloc(TraceLength, sizeof(double));
	corrT = (double*)calloc(TraceLength, sizeof(double));


	for (i = startpoint; i < endpoint; i++)
	{
		for (j = 0; j < TraceNum; j++)
		{
			Sx[i] += data[j][i];
			Sxx[i] += data[j][i] * data[j][i];
		}
	}



	// float 입력에 대한 CPA
	Sy = 0;
	Syy = 0;
	max = 0;
	memset(Sxy, 0, sizeof(double) * TraceLength);


	for (j = 0; j < TraceNum; j++)
	{
		//iv = plaintext[j][0]; // float형 변수 
		iv = (ciphertext[j][0] << 24 | ciphertext[j][1] << 16 | ciphertext[j][2] << 8 | ciphertext[j][3]);

		hw_iv = 0;


		for (k = 0; k < 32; k++) // 32bit
		{
			hw_iv += ((iv >> k) & 1);
			//printf("%d \n", hw_iv);
		}

		Sy += hw_iv;
		Syy += hw_iv * hw_iv;

		for (k = startpoint; k < endpoint; k++)
		{
			Sxy[k] += hw_iv * data[j][k];
		}
	}

	for (k = startpoint; k < endpoint; k++)
	{
		corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));

		if (fabs(corrT[k]) > max)
		{
			maxpoint = k;
			max = fabs(corrT[k]);
		}
	}

	sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\output.corrtrace", _FOLD_);
	if ((err = fopen_s(&wfp, buf, "wb")))
	{
		printf("File Open Error3!!\n");
	}
	fwrite(corrT, sizeof(double), TraceLength, wfp);
	fclose(wfp);
	//printf(".");


	printf("output maxcorr : %lf at %dpoint \n", max, maxpoint + 1); // Matlab 1부터 시작하는거 반영 

	free(Sx);
	free(Sxx);
	free(Sxy);
	free(corrT);
	free(data);
	free(ciphertext);
}


void timedelay()
{

	float * plaintext = NULL;
	double** data; // float -> double
	char buf[256];
	int err, TraceLength, TraceNum, i, j, k;
	FILE* rfp, *wfp;

	unsigned char hw_iv;
	int iv, maxpoint;
	double* Sx, *Sxx, *Sxy, *corrT;
	double Sy, Syy, max;
	int temp = 0;

	int timedelay, end;


	// 활성함수 파형 담기 
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, TraceFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error1!!\n");
	}

	// 파형수집 정보
	TraceLength = 22000;
	TraceNum = 1000;

	data = (double**)calloc(TraceNum, sizeof(double*));

	for (i = 0; i < TraceNum; i++)
	{
		data[i] = (double*)calloc(TraceLength, sizeof(double));
	}

	fseek(rfp, 128, SEEK_SET);
	for (i = 0; i < TraceNum; i++)
	{
		fread(data[i], sizeof(double), TraceLength, rfp);
	}
	fclose(rfp);

	
	// float형 input값 추출
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, PlaintextFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error2!!\n");
	}

	plaintext = (float *)calloc(TraceNum, sizeof(float));

	fseek(rfp, 128, SEEK_SET);
	for (i = 0; i < TraceNum; i++)
	{
		fread(plaintext + i, sizeof(float), 1, rfp);
		fread(&temp, sizeof(float), 3, rfp);
	}
	fclose(rfp);

	/* Matlab이랑 똑같이 나옴 
	for (int i = 0; i < 100; i++)
		printf("%f \n", plaintext[i]);
	*/

	/* Matlab 그래프와 똑같음
	for (int i = 0; i <1 ;i++)
		for(int j=0;j< 1000;j++)
		printf("%f \n", data[i][j]);
	*/


	// 반복문 
	for (i = 0; i < TraceNum; i++) 
	{
		// 초기화 부분 

		for (j = peak; j < TraceLength; j++)
		{
			if (fabs(data[i][j]) > 0.36)
			{
				end = j;
				break;
			}
		}
		timedelay = end - start;
		//printf("input : %f  %d point \n", plaintext[i], timedelay - (2202-start));  //point 찍을 때 쓰레기 파형 고려하면 될겠네 
		printf("%d\n", timedelay - (2202 - start));
	}
	printf("\n\n");
	for (int i = 0; i < TraceNum; i++)
		printf("%f \n", plaintext[i]);

	free(data);
}


int main()
{
	//InputCPA();
	//OutputCPA();
	timedelay();
}
