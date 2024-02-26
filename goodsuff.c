/*******************************************************************************
 * goodsuff.c
 * author: Thierry Lecroq, University of Rouen Normandy, France
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "goodsuff.h"

#define XSIZE 1050         /* pattern length */
#define NBTIMES 10000      /* number of runs of the methods */
#define NBALPHABET 4       /* number of alphabets */
#define MAXPATLENGTH 1024  /* pattern length */



/*******************************************************************************
 * check
 */
void check(char* pattern, int *x, int *y, int m) {
  int i;

  for (i = 0; i < m; ++i) {
    if (x[i] != y[i]) {
      printf("ERROR i = %d, m = %d, pattern = %s\n", i, m, pattern);
      return;
    }
  }
  /* printf("GOOD\n");*/
}


/*******************************************************************************
 * Main
 */
int main() {
  int i, j, k, m;
  int alphabet;
  int *bfbmGs;
  int *clsuff, *clbmGs;
  int *ft1suff, *ft1bmGs;
  int *ft2bmGs;
  int *ft3suff, *ft3bmGs;
  int alphabetTable[NBALPHABET];
  char *pattern;
clock_t
  initialTime, /* initial time in micro-seconds */
  finalTime;   /* final time in micro-seconds */
float
  cpubfTime,
  cpuclTime,
  cpuft1Time,
  cpuft2Time,
  cpuft3Time;
    /* total time in seconds */ 


  bfbmGs = (int *)malloc(XSIZE*sizeof(int));
  if (bfbmGs == NULL) exit(1);
  clsuff = (int *)malloc(XSIZE*sizeof(int));
  if (clsuff == NULL) exit(1);
  clbmGs = (int *)malloc(XSIZE*sizeof(int));
  if (clbmGs == NULL) exit(1);
  ft1suff = (int *)malloc(XSIZE*sizeof(int));
  if (ft1suff == NULL) exit(1);
  ft1bmGs = (int *)malloc(XSIZE*sizeof(int));
  if (ft1bmGs == NULL) exit(1);
  ft2bmGs = (int *)malloc(XSIZE*sizeof(int));
  if (ft2bmGs == NULL) exit(1);
  ft3suff = (int *)malloc(XSIZE*sizeof(int));
  if (ft3suff == NULL) exit(1);
  ft3bmGs = (int *)malloc(XSIZE*sizeof(int));
  if (ft3bmGs == NULL) exit(1);
  pattern = (char *)malloc(XSIZE*sizeof(char));
  if (pattern == NULL) exit(1);

  alphabetTable[0] = 2;
  alphabetTable[1] = 4;
  alphabetTable[2] = 20;
  alphabetTable[3] = 70;

  srand(time(0)%36000);

  for (k = 0; k < NBALPHABET; ++k) {
    alphabet = alphabetTable[k];
    printf("alphabet = %d\n", alphabet);
    for (m = 2; m <= MAXPATLENGTH; m *= 2) {

      cpubfTime = cpuclTime = cpuft1Time = cpuft2Time = cpuft3Time = 0;
      for (i=0; i<NBTIMES; ++i) {
        for (j=0; j < m; ++j) pattern[j]=(rand()%alphabet)+' ';


        initialTime = clock ();
        bfPreBmGs(pattern, m, bfbmGs);
        finalTime = clock ();
        cpubfTime += ((finalTime - initialTime) * 1e-6);

        initialTime = clock ();
        clPreBmGs(pattern, m, clbmGs, clsuff);
        finalTime = clock ();
        cpuclTime += ((finalTime - initialTime) * 1e-6);

        initialTime = clock ();
        ft1PreBmGs(pattern, m, ft1bmGs, ft1suff);
        finalTime = clock ();
        cpuft1Time += ((finalTime - initialTime) * 1e-6);

        initialTime = clock ();
        ft2PreBmGs(pattern, m, ft2bmGs);
        finalTime = clock ();
        cpuft2Time += ((finalTime - initialTime) * 1e-6);

        initialTime = clock ();
        ft3PreBmGs(pattern, m, ft3bmGs, ft3suff);
        finalTime = clock ();
        cpuft3Time += ((finalTime - initialTime) * 1e-6);
        check(pattern, bfbmGs, clbmGs, m);
        check(pattern, bfbmGs, ft1bmGs, m);
        check(pattern, bfbmGs, ft2bmGs, m);
        check(pattern, bfbmGs, ft3bmGs, m);
      }
      printf("%d & %f & %f & %f & %f & %f\n", m, cpubfTime, cpuclTime, cpuft1Time, cpuft2Time, cpuft3Time);

    }
  }
}
