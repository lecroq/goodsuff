/*******************************************************************************
 * bf.c
 * author: Thierry Lecroq, University of Rouen Normandy, France
 */
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Brute force computation of the Boyer-Moore exact string matching algorithm
 * good-suffix table
 */

void bfPreBmGs(char *x, int m, int *bmGs) {
  int i, j, k, ell;
  int mMinus1,  mMinus2;
  char c;

  mMinus1 = m - 1;
  mMinus2 = mMinus1 - 1;
  for (i = mMinus1; i >= 0; --i) {
    ell = mMinus1 - i;
    for (j = mMinus2; j >= 0; --j) {
      for (k = 0; k < ell && j-k >= 0 && x[j-k] == x[mMinus1-k]; ++k);
      if (j-k < 0) {
        break;
      }
      if (k >= ell && x[j-k] != x[mMinus1-k]) {
        break;
      }
    }
    bmGs[i] = mMinus1-j;
  }
}
