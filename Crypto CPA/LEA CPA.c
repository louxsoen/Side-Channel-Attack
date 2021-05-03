// LEA CPA 코드 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>

#define _FOLD_ "C:\\Users\\wngjs\\Desktop\\LEA_CPA\\"    
#define TraceFN "1trace.bin"  
#define Trace2FN "2trace.bin"  
#define Trace3FN "3trace.bin"  
#define Trace4FN "4trace.bin"  
#define Trace5FN "5trace.bin"  

#define HeaderFN "traces.npy"  

#define PlaintextFN "1textin.npy"
#define Plaintext2FN "2textin.npy"
#define Plaintext3FN "3textin.npy"
#define Plaintext4FN "4textin.npy"
#define Plaintext5FN "5textin.npy"

#define CiphertextFN "1textout.npy"
#define Ciphertext2FN "2textout.npy"
#define Ciphertext3FN "3textout.npy"
#define Ciphertext4FN "4textout.npy"
#define Ciphertext5FN "5textout.npy"


#define Startpoint 4800
#define Endpoint 4830
#define Startpoint2 0
#define Endpoint2 400

unsigned int RotationRight(unsigned int word, const unsigned int BitShift)
{	return (word >> BitShift) | (word << (32 - BitShift));	}
unsigned int RotationLeft(unsigned int word, const unsigned int BitShift)
{	return (word << BitShift) | (word >> (32 - BitShift));	}



void CPA() {
	unsigned char** plaintext = NULL, ** ciphertext = NULL; 
	float** trace;
	FILE* rfp, * wfp;
	char buf[256];
	int err, TraceLength, TraceNum, Tracenum, i, j, t;
	unsigned char c[6];

	int *temp,X[4], T; 
	unsigned char RK_23[4], RK_0[16], MK[16]; 

	int key, k, maxkey;
	unsigned char iv, hw_iv;

	double* Sx, * Sxx, * Sxy, * corrT;
	double Sy, Syy, max;

	double rank[256], tmp;
	int p, q, Max;

	int Delta[8] = { 0xc3efe9db ,0x44626b02 ,0x79e27c8a ,0x78df30ec ,0x715ea49e ,0xc785da0a ,0xe04ef22a ,0xe5c40957 };

	
#if 0
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, HeaderFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}

	fseek(rfp, 61, SEEK_SET);

	
	fgets(c, 4, rfp); 

	
	for (i = 0; i < 3; i++)
	{
		if (c[i] >= 'A' && c[i] <= 'F') c[i] = c[i] - 'A' + 10;
		else if (c[i] >= 'a' && c[i] <= 'z') c[i] = c[i] - 'a' + 10;
		else if (c[i] >= '0' && c[i] <= '9') c[i] -= '0';
	}
	TraceNum = c[0] * 10 * 10 + c[1] * 10 + c[2];  

	fseek(rfp, 3, SEEK_CUR); 

	
	fgets(c, 6, rfp);

	
	for (i = 0; i < 5; i++)
	{
		if (c[i] >= 'A' && c[i] <= 'F') c[i] = c[i] - 'A' + 10;
		else if (c[i] >= 'a' && c[i] <= 'z') c[i] = c[i] - 'a' + 10;
		else if (c[i] >= '0' && c[i] <= '9') c[i] -= '0';
	}
	TraceLength = c[0] * 10 * 10 * 10 * 10 + c[1] * 10 * 10 * 10 + c[2] * 10 * 10 + c[3] * 10 + c[4];
	fclose(rfp); 
#endif
	TraceLength = 6000;
	TraceNum = 50000;
	Tracenum = 10000;

	
#if 1
	plaintext = (unsigned char**)calloc(TraceNum, sizeof(unsigned char*));

	for (i = 0; i < TraceNum; i++)
	{
		plaintext[i] = (unsigned char*)calloc(16, sizeof(unsigned char));
	}

	
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, PlaintextFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{	printf("File Open Error!!\n");	}

	fseek(rfp, 128, SEEK_SET); 

	
	for (i = 0; i < Tracenum; i++)
	{
		fread(plaintext[i], sizeof(unsigned char), 16, rfp);
	}
	fclose(rfp); 

	
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Plaintext2FN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}
	fseek(rfp, 128, SEEK_SET); 

	for (i = 0; i < Tracenum; i++)
	{
		fread(plaintext[i + 10000], sizeof(unsigned char), 16, rfp);
	}
	fclose(rfp); 

	
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Plaintext3FN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}
	fseek(rfp, 128, SEEK_SET);

	for (i = 0; i < Tracenum; i++)
	{
		fread(plaintext[i + 20000], sizeof(unsigned char), 16, rfp);
	}
	fclose(rfp); 


	
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Plaintext4FN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}
	fseek(rfp, 128, SEEK_SET);

	for (i = 0; i < Tracenum; i++)
	{
		fread(plaintext[i + 30000], sizeof(unsigned char), 16, rfp);
	}
	fclose(rfp); 


	
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Plaintext5FN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}
	fseek(rfp, 128, SEEK_SET);

	for (i = 0; i < Tracenum; i++)
	{
		fread(plaintext[i + 40000], sizeof(unsigned char), 16, rfp);
	}
	fclose(rfp); 
#endif
	
#if 0
	
	ciphertext = (unsigned char**)calloc(TraceNum, sizeof(unsigned char*));

	for (i = 0; i < TraceNum; i++)
	{
		ciphertext[i] = (unsigned char*)calloc(16, sizeof(unsigned char));
	}

	
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, CiphertextFN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}

	fseek(rfp, 128, SEEK_SET); 

	for (i = 0; i < Tracenum; i++)
	{
		fread(ciphertext[i], sizeof(unsigned char), 16, rfp); 
	}
	fclose(rfp); 

	
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Ciphertext2FN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}

	fseek(rfp, 128, SEEK_SET); 

	for (i = 0; i < Tracenum; i++)
	{
		fread(ciphertext[i+10000], sizeof(unsigned char), 16, rfp);
	}
	fclose(rfp); 
	
	
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Ciphertext3FN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}

	fseek(rfp, 128, SEEK_SET); 

	for (i = 0; i < Tracenum; i++)
	{
		fread(ciphertext[i + 20000], sizeof(unsigned char), 16, rfp);
	}
	fclose(rfp); 

	
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Ciphertext4FN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}

	fseek(rfp, 128, SEEK_SET); 

	for (i = 0; i < Tracenum; i++)
	{
		fread(ciphertext[i + 30000], sizeof(unsigned char), 16, rfp);
	}
	fclose(rfp); 

	
	sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Ciphertext5FN);
	if ((err = fopen_s(&rfp, buf, "rb")))
	{
		printf("File Open Error!!\n");
	}

	fseek(rfp, 128, SEEK_SET); 

	for (i = 0; i < Tracenum; i++)
	{
		fread(ciphertext[i + 40000], sizeof(unsigned char), 16, rfp);
	}
	fclose(rfp); 
#endif
	
	{
		
		trace = (float**)calloc(TraceNum, sizeof(float*));

		for (i = 0; i < TraceNum; i++)
		{
			trace[i] = (float*)calloc(TraceLength, sizeof(float));
		}

		
		sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, TraceFN);
		if ((err = fopen_s(&rfp, buf, "rb")))
		{
			printf("File Open Error!!\n");
		}

		for (i = 0; i < Tracenum; i++)
		{
			fread(trace[i], sizeof(float), TraceLength, rfp);
		}
		fclose(rfp); 

		
		sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Trace2FN);
		if ((err = fopen_s(&rfp, buf, "rb")))
		{
			printf("File Open Error!!\n");
		}

		for (i = 0; i < Tracenum; i++)
		{
			fread(trace[i + 10000], sizeof(float), TraceLength, rfp);
		}
		fclose(rfp); 

		
		sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Trace3FN);
		if ((err = fopen_s(&rfp, buf, "rb")))
		{
			printf("File Open Error!!\n");
		}

		for (i = 0; i < Tracenum; i++)
		{
			fread(trace[i + 20000], sizeof(float), TraceLength, rfp);
		}
		fclose(rfp); 

		
		sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Trace4FN);
		if ((err = fopen_s(&rfp, buf, "rb")))
		{
			printf("File Open Error!!\n");
		}

		for (i = 0; i < Tracenum; i++)
		{
			fread(trace[i + 30000], sizeof(float), TraceLength, rfp);
		}
		fclose(rfp); 

		
		sprintf_s(buf, 256 * sizeof(char), "%s%s", _FOLD_, Trace5FN);
		if ((err = fopen_s(&rfp, buf, "rb")))
		{
			printf("File Open Error!!\n");
		}

		for (i = 0; i < Tracenum; i++)
		{
			fread(trace[i + 40000], sizeof(float), TraceLength, rfp);
		}
		fclose(rfp); 
	}

	
	Sx = (double*)calloc(TraceLength, sizeof(double));
	Sxx = (double*)calloc(TraceLength, sizeof(double));
	Sxy = (double*)calloc(TraceLength, sizeof(double));
	corrT = (double*)calloc(TraceLength, sizeof(double));

	for (i = 0; i < TraceNum; i++)
	{
		for (j = 0; j < TraceLength; j++)
		{
			Sx[j] += trace[i][j];
			Sxx[j] += trace[i][j] * trace[i][j];
		}
	}

	
#if 0
	
	Sy = 0;
	Syy = 0;
	memset(Sxy, 0, sizeof(double) * TraceLength);

	for (j = 0; j < TraceNum; j++)
	{	
		iv = (ciphertext[j][0]<<24)| (ciphertext[j][1] << 16) | (ciphertext[j][2] << 8) | ciphertext[j][3]; 
		
		hw_iv = 0;

		
		for (k = 0; k < 32; k++) 
		{
			hw_iv += ((iv >> k) & 1);
		}

		Sy += hw_iv;
		Syy += hw_iv * hw_iv;

		for (k = 0; k < TraceLength; k++)	
		{
			Sxy[k] += hw_iv * trace[j][k];
		}
	}

	for (k = 0; k < TraceLength; k++)
	{
		corrT[k] = ((double)TraceNum* Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));
	}

	sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\Cipher_trace", _FOLD_);
	if ((err = fopen_s(&wfp, buf, "wb")))
	{
		printf("File Open Error!!\n");
	}
	fwrite(corrT, sizeof(double), TraceLength, wfp);
	fclose(wfp);
#endif
	
#if 0
	
	Sy = 0;
	Syy = 0;
	memset(Sxy, 0, sizeof(double)* TraceLength);

	for (j = 0; j < TraceNum; j++)
	{
		iv = (plaintext[j][0] << 24) | (plaintext[j][1] << 16) | (plaintext[j][2] << 8) | plaintext[j][3]; 
		
		hw_iv = 0;

		
		for (k = 0; k < 32; k++)
		{
			hw_iv += ((iv >> k) & 1);
		}

		Sy += hw_iv;
		Syy += hw_iv * hw_iv;

		for (k = 0; k < TraceLength; k++)
		{
			Sxy[k] += hw_iv * trace[j][k];
		}
	}

	for (k = 0; k < TraceLength; k++)
	{
		corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));
	}

	sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\Plain_trace", _FOLD_);
	if ((err = fopen_s(&wfp, buf, "wb")))
	{
		printf("File Open Error!!\n");
	}
	fwrite(corrT, sizeof(double), TraceLength, wfp);
	fclose(wfp);
#endif
	
#if 0
	
	for (i = 0; i < 4; i++) 
	{ 
		max = maxkey = 0; 

		for (key = 0; key < 256; key++) 
		{
			tmp = 0;
			Sy = 0;
			Syy = 0;
			memset(Sxy, 0, sizeof(double) * TraceLength);

			for (j = 0; j < TraceNum; j++)
			{
				X[0] = (ciphertext[j][0] << 24) | (ciphertext[j][1] << 16) | (ciphertext[j][2] << 8) | ciphertext[j][3];
				X[3] = (ciphertext[j][12] << 24) | (ciphertext[j][13] << 16) | (ciphertext[j][14] << 8) | ciphertext[j][15];

				iv = (RotationRight(X[0], 9) - (X[3] ^ key)) & 0xff; 
				hw_iv = 0;

				
				for (k = 0; k < 8; k++)
				{
					hw_iv += ((iv >> k) & 1);
				}

				Sy += hw_iv;
				Syy += hw_iv * hw_iv;

				for (k = Startpoint; k < Endpoint; k++)
				{
					Sxy[k] += hw_iv * trace[j][k];
				}
			}

			for (k = Startpoint; k < Endpoint; k++) 
			{
				corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));

				if (fabs(corrT[k]) > max) 
				{
					maxkey = key;
					max = fabs(corrT[k]);
				}

				
				if (fabs(corrT[k]) > tmp)
					tmp = fabs(corrT[k]);
			}

			sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\RK_23[0] %02dth_block_%02x.corrtrace", _FOLD_, i, key); 
			if ((err = fopen_s(&wfp, buf, "wb")))
			{
				printf("File Open Error!!\n");
			}
			fwrite(corrT, sizeof(double), TraceLength, wfp); 
			fclose(wfp);
			printf(".");
			
			rank[key] = tmp; 
		}
		printf("RK_23[0] %02dth_block: maxkey(%02x), maxcorr(%f)\n", i, maxkey, max); 
		RK_23[i] = maxkey;

		
		
		for (p = 0; p < 255; p++)
		{
			Max = p;
			for (q = p + 1; q < 256; q++)
			{
				if (rank[Max] < rank[q])
				{
					Max = q;
				}
			}
			printf("%d등 RK_23[0] = %02x : %f \n", p + 1, Max, rank[Max]); 
			tmp = rank[Max];
			rank[Max] = rank[p];
			rank[p] = tmp;
		}
	}
#endif
	

	
	
#if 0
	
	T = (RK_23[3] << 24) | (RK_23[2] << 16) | (RK_23[1] << 8) | RK_23[0];

	for (i = 23; i >= 1; i--) 
	{
		T = RotationRight(T, 1) - RotationLeft(Delta[i % 4], i);
	}
	
	
	RK_0[0] = T & 0xff;
	RK_0[1] = (T >> 8) & 0xff;
	RK_0[2] = (T >> 16) & 0xff;
	RK_0[3] = (T >> 24) & 0xff;
#endif
	/*
	for (i = 0; i < 4; i++) {
		printf("%02x ", RK_0[i]);
	}
	printf("\n");
	return;

	*/

	RK_0[0] = 0xd4;
	RK_0[1] = 0x0f;
	RK_0[2] = 0x3a;
	RK_0[3] = 0x00;
	RK_0[4] = 0x10;
#if 0	
			max = maxkey = 0;

			for (key = 0; key < 256; key++)
			{
				tmp = 0;
				Sy = 0;
				Syy = 0;
				memset(Sxy, 0, sizeof(double) * TraceLength);

				for (j = 0; j < TraceNum; j++)
				{
					iv = (plaintext[j][3] ^ RK_0[0]) + (plaintext[j][7] ^ key);
					
					hw_iv = 0;

					for (k = 0; k < 8; k++)
					{
						hw_iv += ((iv >> k) & 1);
					}

					Sy += hw_iv;
					Syy += hw_iv * hw_iv;

					for (k = Startpoint2; k < Endpoint2; k++)
					{
						Sxy[k] += hw_iv * trace[j][k];
					}
				}

				for (k = Startpoint2; k < Endpoint2; k++) 
				{
					corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));

					if (fabs(corrT[k]) > max) 
					{
						maxkey = key;
						max = fabs(corrT[k]);
					}

					
					if (fabs(corrT[k]) > tmp)
						tmp = fabs(corrT[k]);
				}

				sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\RK_0[1] %02dth_block_%02x.corrtrace", _FOLD_, i, key);
				if ((err = fopen_s(&wfp, buf, "wb")))
				{
					printf("File Open Error!!\n");
				}
				fwrite(corrT, sizeof(double), TraceLength, wfp);
				fclose(wfp);
				printf(".");
				
				rank[key] = tmp; 
			}
			printf("RK_0[1] %02dth_block: maxkey(%02x), maxcorr(%f)\n", 0, maxkey, max);
			
			RK_0[4] = maxkey;
			
			
			for (p = 0; p < 255; p++)
			{
				Max = p;
				for (q = p + 1; q < 256; q++)
				{
					if (rank[Max] < rank[q])
					{
						Max = q;
					}
				}
				printf("%d등 RK_0[1] = %02x : %f \n", p + 1, Max, rank[Max]);
				tmp = rank[Max];
				rank[Max] = rank[p];
				rank[p] = tmp;
				
			}
#endif
			
			for (t = -1; t < 1; t++) {
				for (i = 0; i < 4; i++)
				{
					max = maxkey = 0;

					for (key = 0; key < 256; key++)
					{
						tmp = 0;
						Sy = 0;
						Syy = 0;
						memset(Sxy, 0, sizeof(double) * TraceLength);

						for (j = 0; j < TraceNum; j++)
						{
							if (t < 0)iv = (plaintext[j][3 - i] ^ RK_0[i]) + (plaintext[j][7 - i] ^ key); 
							else iv = (plaintext[j][7 - i + t * 4] ^ key) + (plaintext[j][11 - i + t * 4] ^ RK_0[i + 4]); 
							hw_iv = 0;

							for (k = 0; k < 8; k++)
							{
								hw_iv += ((iv >> k) & 1);
							}

							Sy += hw_iv;
							Syy += hw_iv * hw_iv;

							for (k = Startpoint2; k < Endpoint2; k++)
							{
								Sxy[k] += hw_iv * trace[j][k];
							}
						}

						for (k = Startpoint2; k < Endpoint2; k++)
						{
							corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));

							if (fabs(corrT[k]) > max)
							{
								maxkey = key;
								max = fabs(corrT[k]);
							}

							
							if (fabs(corrT[k]) > tmp)
								tmp = fabs(corrT[k]);
						}

						sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\RK_0[1] %02dth_block_%02x.corrtrace", _FOLD_, i, key); 
						if ((err = fopen_s(&wfp, buf, "wb")))
						{
							printf("File Open Error!!\n");
						}
						fwrite(corrT, sizeof(double), TraceLength, wfp);
						fclose(wfp);
						printf(".");

						rank[key] = tmp; 
					}
					printf("RK_0[1] %02dth_block: maxkey(%02x), maxcorr(%f)\n", i, maxkey, max);  

					RK_0[i + 4 + (t + 1) * 4] = maxkey; 

					
					for (p = 0; p < 255; p++)
					{
						Max = p;
						for (q = p + 1; q < 256; q++)
						{
							if (rank[Max] < rank[q])
							{
								Max = q;
							}
						}
						printf("%d등 RK_0[1]_%d = %02x : %f \n", p + 1, i, Max, rank[Max]); 
						tmp = rank[Max];
						rank[Max] = rank[p];
						rank[p] = tmp;

					}
				}
			}
			return;
	
	
	
	T = (RK_0[3] << 24) | (RK_0[2] << 16) | (RK_0[1] << 8) | RK_0[0];
	T = RotationRight(T, 1) - RotationLeft(Delta[0], 0);
	MK[0] = T & 0xff; MK[1] = (T >> 8) & 0xff; MK[2] = (T >> 16) & 0xff; MK[3] = (T >> 24) & 0xff;

	T = (RK_0[7] << 24) & 0xff | (RK_0[6] << 16) & 0xff | (RK_0[5] << 8) & 0xff | RK_0[4];
	T = RotationRight(T, 3) - RotationLeft(Delta[0], 1);
	MK[4] = T & 0xff; MK[5] = (T >> 8) & 0xff; MK[6] = (T >> 16) & 0xff; MK[7] = (T >> 24) & 0xff;

	T = (RK_0[11] << 24) & 0xff | (RK_0[10] << 16) & 0xff | (RK_0[9] << 8) & 0xff | RK_0[8];
	T = RotationRight(T, 6) - RotationLeft(Delta[0], 2);
	MK[8] = T & 0xff; MK[9] = (T >> 8) & 0xff; MK[10] = (T >> 16) & 0xff; MK[11] = (T >> 24) & 0xff;

	T = (RK_0[15] << 24) & 0xff | (RK_0[14] << 16) & 0xff | (RK_0[13] << 8) & 0xff | RK_0[12];
	T = RotationRight(T, 11) - RotationLeft(Delta[0], 3);
	MK[12] = T & 0xff; MK[13] = (T >> 8) & 0xff; MK[14] = (T >> 16) & 0xff; MK[15] = (T >> 24) & 0xff;
	
	printf("MasterKey: ");
	for (i = 0; i < 16; i++)
	{
		printf("%x ", MK[i]);
	}
	printf("\n");


	free(Sx);
	free(Sxx);
	free(Sxy);
	free(corrT);
	free(trace);
	free(plaintext);
}

int main() 
{
	CPA();
}

/* 어렵게 하기 전 코드 
	for (i = 0; i < 4; i++)
	{
		max = maxkey = 0;

		for (key = 0; key < 256; key++)
		{
			Sy = 0;
			Syy = 0;
			memset(Sxy, 0, sizeof(double) * TraceLength);

			for (j = 0; j < TraceNum; j++)
			{
				if (!t)iv = (plaintext[j][i] ^ RK_0[i]) + (plaintext[j][i + 4] ^ key);
				hw_iv = 0;

				for (k = 0; k < 8; k++)
				{
					hw_iv += ((iv >> k) & 1);
				}

				Sy += hw_iv;
				Syy += hw_iv * hw_iv;

				for (k = 0; k < TraceLength; k++)
				{
					Sxy[k] += hw_iv * data[j][k];
				}
			}

			for (k = 0; k < TraceLength; k++) {
				corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));

				if (fabs(corrT[k]) > max) {
					maxkey = key;
					max = fabs(corrT[k]);
				}
			}

			sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\RK_0[1] %02dth_block_%02x.corrtrace", _FOLD_, i, key);
			if ((err = fopen_s(&wfp, buf, "wb")))
			{
				printf("File Open Error!!\n");
			}
			fwrite(corrT, sizeof(double), TraceLength, wfp);
			fclose(wfp);
			printf(".");
		}
		printf("RK_0[1] %02dth_block: maxkey(%02x), maxcorr(%f)\n", i, maxkey, max);
		RK_0[i + 4] = maxkey;
		*/


/*
for (i = 0; i < 3; i++)
	{
		c[i] = temp[i];

		if (c[i] >= 'A' && c[i] <= 'F') c[i] = c[i] - 'A' + 10;
		else if (c[i] >= 'a' && c[i] <= 'z') c[i] = c[i] - 'a' + 10;
		else if (c[i] >= '0' && c[i] <= '9') c[i] -= '0';
	}



	for (i = 0; i < 5; i++)
	{
		c[i] = temp[i];

		if (c[i] >= 'A' && c[i] <= 'F') c[i] = c[i] - 'A' + 10;
		else if (c[i] >= 'a' && c[i] <= 'z') c[i] = c[i] - 'a' + 10;
		else if (c[i] >= '0' && c[i] <= '9') c[i] -= '0';
	}
	TraceLength = c[0] * 10 * 10 * 10 * 10 + c[1] * 10 * 10 * 10 + c[2] * 10 * 10 + c[3] * 10 + c[4];
*/

/*

	for (i = 0; i < 4; i++) 
	{ 
		max = maxkey = 0; 

		for (key = 0; key < 256; key++) 
		{
			tmp = 0;
			Sy = 0;
			Syy = 0;
			memset(Sxy, 0, sizeof(double) * TraceLength);

			for (j = 0; j < TraceNum; j++)
			{
				iv = ciphertext[j][i] - (key ^ ciphertext[j][i + 12]);
				hw_iv = 0;

				
				for (k = 0; k < 8; k++)
				{
					hw_iv += ((iv >> k) & 1);
				}

				Sy += hw_iv;
				Syy += hw_iv * hw_iv;

				for (k = 0; k < TraceLength; k++)
				{
					Sxy[k] += hw_iv * trace[j][k];
				}
			}

			for (k = 0; k < TraceLength; k++)
			{
				corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));

				if (fabs(corrT[k]) > max)
				{
					maxkey = key;
					max = fabs(corrT[k]);
				}

				
				if (corrT[k] > tmp)
					tmp = corrT[k];
			}

			sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\RK_23[0] %02dth_block_%02x.corrtrace", _FOLD_, i, key);
			if ((err = fopen_s(&wfp, buf, "wb")))
			{
				printf("File Open Error!!\n");
			}
			fwrite(corrT, sizeof(double), TraceLength, wfp);
			fclose(wfp);
			printf(".");

			rank[key] = tmp; 
		}
		printf("RK_23[0] %02dth_block: maxkey(%02x), maxcorr(%f)\n", i, maxkey, max);
		RK_23[i] = maxkey;


		
		for (p = 0; p < 255; p++)
		{
			Max = p;
			for (q = p + 1; q < 256; q++)
			{
				if (rank[Max] < rank[q])
				{
					Max = q;
				}
			}
			printf("%d등 RK_23[0] = %02x : %f \n", p + 1, Max, rank[Max]);
			tmp = rank[Max];
			rank[Max] = rank[p];
			rank[p] = tmp;
		}

	}

*/


/*
	
	RK_0[0] = 0xd4;
	RK_0[1] = 0x0f;
	RK_0[2] = 0x3a;
	RK_0[3] = 0x00;

	for (t = 0; t < 9; t += 4) 
	{
		for (i = 0; i < 4; i++)
		{
			max = maxkey = 0;

			for (key = 0; key < 256; key++)
			{
				tmp = 0;
				Sy = 0;
				Syy = 0;
				memset(Sxy, 0, sizeof(double) * TraceLength);

				for (j = 0; j < TraceNum; j++)
				{
					if (!t)iv = (plaintext[j][i] ^ RK_0[i]) + (plaintext[j][i + 4] ^ key);
					else iv = (plaintext[j][i + t] ^ key) + (plaintext[j][i + 4 + t] ^ RK_0[i + 4]); 
					hw_iv = 0;

					for (k = 0; k < 8; k++)
					{
						hw_iv += ((iv >> k) & 1);
					}

					Sy += hw_iv;
					Syy += hw_iv * hw_iv;

					for (k = 0; k < TraceLength; k++)
					{
						Sxy[k] += hw_iv * trace[j][k];
					}
				}

				for (k = 0; k < TraceLength; k++)
				{
					corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));

					if (fabs(corrT[k]) > max)
					{
						maxkey = key;
						max = fabs(corrT[k]);
					}

					
					if (fabs(corrT[k]) > tmp)
						tmp = fabs(corrT[k]);
				}

				if (!t)sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\RK_0[1] %02dth_block_%02x.corrtrace", _FOLD_, i, key);
				else sprintf_s(buf, 256 * sizeof(char), "%scorrtrace\\RK_0[%d] %02dth_block_%02x.corrtrace", _FOLD_, t / 2, i, key);
				if ((err = fopen_s(&wfp, buf, "wb")))
				{
					printf("File Open Error!!\n");
				}
				fwrite(corrT, sizeof(double), TraceLength, wfp);
				fclose(wfp);
				printf(".");

				rank[key] = tmp; 
			}
			if (!t)printf("RK_0[1] %02dth_block: maxkey(%02x), maxcorr(%f)\n", i, maxkey, max);
			else printf("RK_0[%d] %02dth_block: maxkey(%02x), maxcorr(%f)\n", t / 2, i, maxkey, max);

			if (!t)RK_0[i + 4] = maxkey;
			else RK_0[i + 4 + t] = maxkey; 

			
			for (p = 0; p < 255; p++)
			{
				Max = p;
				for (q = p + 1; q < 256; q++)
				{
					if (rank[Max] < rank[q])
					{
						Max = q;
					}
				}
				printf("%d등 RK_0[1] = %02x : %f \n", p + 1, Max, rank[Max]);
				tmp = rank[Max];
				rank[Max] = rank[p];
				rank[p] = tmp;

			}
		}
		return;
	}

*/
