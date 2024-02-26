/*******************************************************************************
 * ft2.c
 * author: Thierry Lecroq, University of Rouen Normandy, France
 */

#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

/*******************************************************************************
 * Fine tuned computation of the Boyer-Moore exact string matching algorithm
 * good-suffix table: quadratic version
 */

void ft2PreBmGs(char *x, int m, int *bmGs) {
  int f, g, i, j, k1;
  int e, h, k, k2, r;
  int sh;
  int mMinus1;
  char a;
  int mini;
 
  mMinus1 = m-1;
  g = mMinus1;
  a = x[mMinus1];
  /* looking for the start position of the first run of a */
  for (i = m - 2; i >= 0 && x[i] == a; --i);
  k1 = mMinus1-i;
  bmGs[mMinus1] = k1;
  for (j = m - 2, k=k1-1; j > i; --j, --k) {
    bmGs[j] = k;
  }
  for (j = 0; j <= i; ++j) {
    bmGs[j] = m;
  }
  j = 0;
  g = m;
  while (1) {
    /* looking for the end position of next run of a */
    for (--i; i >=0 && x[i] != a; --i);
    if (i < 0) { return; }
    r = i;
    /* looking for the start position of current run of a */
    for (; i >= 0 && x[i] == a; --i);
    if (i < 0) { /* the run of a's is at the beginning of x */
      mini = MIN(k1,r+1);
      for (; j <= mMinus1 - mini; ++j) {
        if (bmGs[j] > mMinus1-mini) {
          bmGs[j] = mMinus1 - mini+1;
        }
      }
      if (r+1 > k1) {
        if (bmGs[mMinus1-k1] > mMinus1-r) {
          bmGs[mMinus1-k1] = mMinus1-r;
        }   
      }   
      return;
    }
    /* otherwise the run of length r-i is internal */
    k2 = r - i;
    if (k2 < k1) {
      continue;
    }
    // k2 >= k1
    e = i+k1;
    if (k2 > k1) {
      if (bmGs[mMinus1-k1] > mMinus1-r) {
        bmGs[mMinus1-k1] = mMinus1-r;
      }
    }
    f = e;
    g = i;
    while (g >= 0 && x[g] == x[g + mMinus1 - f]) {
      --g;
    }
    if (g < 0) { /* suff[i] = i+1) */
      for (; j < mMinus1 - f; ++j) {
        if (bmGs[j] > mMinus1-f) {
          bmGs[j] = mMinus1 - f;
        }
      }
    }
    else {
      if (bmGs[mMinus1 - f+g] > mMinus1 - f) {
        bmGs[mMinus1 - f+g] = mMinus1 - f;
      }
    }
  }
}
