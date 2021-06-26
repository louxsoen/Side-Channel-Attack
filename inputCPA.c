#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>


#define _FOLD_ "C:\\Users\\master\\Desktop\\LEEJUHEON\\"
#define TraceFN "ReLU_traces.npy"   // Sigmod_traces.npy  / tanh_traces.npy

#define ClearTraceFN "Clear_ReLU_traces.npy" // Clear_Sigmod_traces.npy  / Clear_tanh_traces.npy -> 구할 필요없음 정확한 시점만 찾으면 됨 
#define TrashTraceFN "trash_traces.npy"	// 칩위스퍼 쓰레기 파형 

#define PlaintextFN "ReLU_textin.npy"
#define CipherextFN "ReLU_textout.npy"


#define startpoint 0
#define endpoint 5000 


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
	//unsigned char** plaintext = NULL;
	float** plaintext = NULL; // float 입력 
	float** data;
	char buf[256];
	int err, TraceLength, TraceNum, i, j, k;
	FILE* rfp, *wfp;
	unsigned char   iv, hw_iv;
	double* Sx, *Sxx, *Sxy, *corrT;
	double Sy, Syy, max;


	// 활성함수 파형 담기 
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, TraceFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}

	// 파형수집 정보 
	TraceLength = 5000;
	TraceNum = 200;

	data = (float**)calloc(TraceNum, sizeof(float*));

	for (i = 0; i < TraceNum; i++)
	{
		data[i] = (float*)calloc(TraceLength, sizeof(float));
	}

	fseek(rfp, 128, SEEK_SET);
	for (i = 0; i < TraceNum; i++)
	{
		fread(data[i], sizeof(float), TraceLength, rfp);
	}
	fclose(rfp);


	// plaintext에 4byte float만 담기 -> 이중 배열에 담을 필요 없음 
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, PlaintextFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}

	plaintext = (float*)calloc(TraceLength, sizeof(float));
	/*
	for (i = 0; i < TraceNum; i++)
	{
		plaintext[i] = (float*)calloc(1, sizeof(float));
	}
	*/

	fseek(rfp, 128, SEEK_SET);
	for (i = 0; i < TraceNum; i++)
	{
		fread(plaintext[i], sizeof(float), 1, rfp); // 
		fseek(rfp, 12, SEEK_SET);
		//fread(temp, sizeof(unsigned char), 12, rfp);
	}
	fclose(rfp);



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
	memset(Sxy, 0, sizeof(double) * TraceLength);


	for (j = 0; j < TraceNum; j++)
	{
		iv = plaintext[j]; // float형 변수 
		hw_iv = 0;


		for (k = 0; k < 8; k++)
		{
			hw_iv += ((iv >> k) & 1);
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
			max = fabs(corrT[k]);
		}
	}

	sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\input.corrtrace", _FOLD_);
	if ((err = fopen_s(&wfp, buf, "wb")))
	{
		printf("File Open Error!!\n");
	}
	fwrite(corrT, sizeof(double), TraceLength, wfp);
	fclose(wfp);
	printf(".");


	printf("input maxcorr : %lf \n", max);

	free(Sx);
	free(Sxx);
	free(Sxy);
	free(corrT);
	free(data);
	free(plaintext);
}

void OutputCPA()
{


}

int main()
{
	InputCPA();
}
