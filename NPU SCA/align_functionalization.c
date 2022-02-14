#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include <time.h>

double Cov(double* x, double* y, int size) {
   double Sxy = 0, Sx = 0, Sy = 0;
   int i;
   for (i = 0; i < size; i++) {
      Sxy += x[i] * y[i];
      Sx += x[i];
      Sy += y[i];
   }


   return (Sxy - Sx * Sy / (double)size) / (double)size;
}


double Corr(double* x, double* y, int size) {
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



void SubAligned(double* data1, double* data2, int windowsize, int stepsize, int  threshold, int TraceLength) {
   int i, j, size, maxcovpos, k;
   double* x, *y;
   double cov, maxcov;


   for (i = 0; i < (TraceLength - windowsize); i += stepsize) {


      maxcovpos = 0;
      maxcov = 0;


      for (j = -threshold; j < threshold; j++) {
         if (j < 0) {
            x = data1 + i;
            y = data2 + i - j;
            size = windowsize - abs(j);
         }
         else {
            x = data1 + i + j;
            y = data2 + i;
            size = windowsize - abs(j);
         }

         cov = Corr(x, y, size); //cov아님

         if (cov > maxcov) {
            maxcovpos = j;
            maxcov = cov;
         }
      }
      //printf("%f\n", maxcov);
      if (maxcovpos < 0) {
         for (k = i; k < (TraceLength + maxcovpos); k++) {
            data2[k] = data2[k - maxcovpos];

         }
      }
      else {
         for (k = (TraceLength - maxcovpos - 1); k >= i; k--) {
            data2[k + maxcovpos] = data2[k];
         }
      }
   }
   //printf("hi");
}
void Alignment(char *InputfilePath, char *InputfileFormat, char *OuputfilePath, char *OuputfileFormat, int TraceLength, int TraceNum, int windowsize, int stepsize, int threshold) {

   int i, err;
   char buf[256];
   char buf2[256];
   FILE* rfp, *wfp;
   unsigned short* data1, *data2;
   float *double_data1, *double_data2;
   char* TrcHeader;
   int flen;

   data1 = (unsigned short*)calloc(TraceLength, sizeof(unsigned short));
   data2 = (unsigned short*)calloc(TraceLength, sizeof(unsigned short));
   double_data1 = (double *)calloc(TraceLength, sizeof(double));
   double_data2 = (double *)calloc(TraceLength, sizeof(double));
   TrcHeader = (char*)calloc(357, sizeof(char));


   // 여기 까지 정렬 기준 데이터 읽기 
   sprintf_s(buf, 256 * sizeof(char)/*sizeof(buf)*/, "%s%s%05d.trc", InputfilePath, InputfileFormat, 0);
   if ((err = fopen_s(&rfp, buf, "rb"))) {
      printf("File Open Error1!!\n");
      exit(1);
   }
   fread(TrcHeader, sizeof(char), 357, rfp);
   fread(data1, sizeof(unsigned short), TraceLength, rfp);
   for (i = 0; i < TraceLength; i++) { // TraceNum아님
      double_data1[i] = (double)data1[i];
   }

   fclose(rfp);


   //정렬 시작
   for (i = 0; i < TraceNum; i++) {
      //다음 정렬 파형 읽어오기
      sprintf_s(buf, 256 * sizeof(char), "%s%s%05d.trc", InputfilePath, InputfileFormat, i);
      if ((err = fopen_s(&rfp, buf, "rb"))) {
         printf("File Open Error1!!\n");
         exit(1);
      }
      fseek(rfp, sizeof(char) * 357,SEEK_CUR);
      fread(data2, sizeof(unsigned short), TraceLength, rfp); // 정렬할 파형 읽기

      for (int j = 0; j < TraceLength; j++) {
         double_data2[j] = (double)data2[j];
      }
      SubAligned(double_data1, double_data2, windowsize, stepsize, threshold, TraceLength); // 정렬 하기

      for (int j = 0; j < TraceLength; j++) {
         data2[j] = (unsigned short)double_data2[j];
      }
                                                            // 정렬한 파형 적기 
      sprintf_s(buf2, 256 * sizeof(char), "%s%s%05d.trc", OuputfilePath, OuputfileFormat, i);
      if ((err = fopen_s(&wfp, buf2, "wb"))) {
         printf("File Open Error2!!\n");
         exit(1);
      }
      fwrite(TrcHeader, sizeof(char), 357, wfp); // TrcHear 적기 
      fwrite(data2, sizeof(unsigned short), TraceLength, wfp); // 정렬한 데이터 적기
      fclose(wfp);
      fclose(rfp);
   }

   free(data1);
   free(data2);

}
int main() {
   char InputfilePath[256] = "C:\\Users\\master\\Desktop\\mlp\\500MS_8118\\";
   char InputfileFormat[256] = "Z2--mlp500MS--";
   char OuputfilePath[256] = "C:\\Users\\master\\Desktop\\mlp\\500MS_8118\\align\\";
   char OuputfileFormat[256] = "Z2--mlp--align--";
   int TraceLength = 88002;
   int TraceNum = 8118;
   int windowsize = 500;
   int stepsize = 200;
   int threshold = 400;
   Alignment(InputfilePath, InputfileFormat, OuputfilePath, OuputfileFormat, TraceLength, TraceNum, windowsize, stepsize, threshold);

   return 0;
}
