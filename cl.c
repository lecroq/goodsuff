/*******************************************************************************
 * cl.c
 * author: Thierry Lecroq, University of Rouen Normandy, France
 */
#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

/*******************************************************************************
 * Classical computation of the suff table
 */
void suffixes(char *x, int m, int *suff) {
  int f, g, i;
  int mMinus1;
 
  mMinus1 = m - 1;
  g = mMinus1;
  for (i = g - 1; i >= 0; --i) {
    if (i > g && suff[i + mMinus1 - f] != i - g) {
      suff[i] = MIN(i-g, suff[i + mMinus1 - f]);
    }
    else {
      if (i < g) {
        g = i;
      }
      f = i;
      while (g >= 0 && x[g] == x[g + mMinus1 - f]) {
        --g;
      }
      suff[i] = f - g;
    }
  }
}
 
/*******************************************************************************
 * Classical computation of the Boyer-Moore exact string matching algorithm
 * good-suffix table
 */
void clPreBmGs(char *x, int m, int *bmGs, int *suff) {
  int i, j;
  int mMinus1;
  int mMinus2;
 
  suffixes(x, m, suff);
 
  j = 0;
  mMinus1 = m - 1;
  mMinus2 = mMinus1 - 1;
  for (i = mMinus2; i >= 0; --i) {
    if (suff[i] == i + 1) {
      for (; j < mMinus1 - i; ++j) {
        bmGs[j] = mMinus1 - i;
      }
    }
  }
  for (; j < m; ++j) {
    bmGs[j] = m;
  }
  for (i = 0; i <= mMinus2; ++i) {
    bmGs[mMinus1 - suff[i]] = mMinus1 - i;
  }
}
