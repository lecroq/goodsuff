/*******************************************************************************
 * ft3.c
 * author: Thierry Lecroq, University of Rouen Normandy, France
 */
#include <stdio.h>
#include <stdlib.h>


/*******************************************************************************
 * Fine tuned computation of the Boyer-Moore exact string matching algorithm
 * good-suffix table: mixed version
 */

void ft3PreBmGs(char *x, int m, int *bmGs, int *suff) {
  int f, g, i, j, k;
  int sh;
  int mMinus1;
  char c;
 
  mMinus1 = m-1;
  g = mMinus1;
  c = x[mMinus1];
  /* looking for the end of the first run of c thus before suff[i] = 0 */
  for (i = m - 2; i >= 0 && x[i] == c; --i);
  k = mMinus1-i;
  bmGs[mMinus1] = k;
  for (j = m - 2, --k; j > i; --j, --k) {
    suff[j] = bmGs[j] = k;
  }
  for (j = 0; j <= i; ++j) {
    bmGs[j] = m;
  }
  j = 0;
  /* looking for the second run of c */
  for (--i; i >=0 && x[i] != c; --i);
  if (i < 0) {
    return;
  }
  f = i;
  g = i-1;
  while (g >= 0 && x[g] == x[g + mMinus1 - f]) {
    --g;
  }
  suff[i] = f - g;
  if (g < 0) { /* suff[i] == i+1) */
    for (; j < mMinus1 - i; ++j) {
      if (bmGs[j] > mMinus1-i) {
        bmGs[j] = mMinus1 - i;
      }
    }
    --i;
    goto laststep;
  }
  else {
   if (bmGs[mMinus1 - suff[i]] > mMinus1 - i) {
     bmGs[mMinus1 - suff[i]] = mMinus1 - i;
   }
  }
  
  /* after suff[i] = 0 and before suff[i] = i+1 */
  for (--i; i >= 0; --i) {
    if (x[i] != c) {
      continue;
    }
    if (i > g && suff[i + mMinus1 - f] != i - g) {
      if (suff[i + mMinus1 - f] < i-g) {
        suff[i] = suff[i + mMinus1 - f];
      }
      else {
        if (suff[i + mMinus1 - f] > i-g) {
          suff[i] = i-g;
          if (bmGs[mMinus1 - suff[i]] > mMinus1 - i) {
            bmGs[mMinus1 - suff[i]] = mMinus1 - i;
          }
        }
      }
    }
    else {
      if (i < g) {
        g = i-1;
      }
      f = i;
      while (g >= 0 && x[g] == x[g + mMinus1 - f]) {
        --g;
      }
      suff[i] = f - g;
      if (g < 0) { /* suff[i] == i+1 */
         for (; j < mMinus1 - i; ++j) {
           if (bmGs[j] > mMinus1-i) {
             bmGs[j] = mMinus1 - i;
           }
         }
         --i;
         break;
      }
      else {
        if (bmGs[mMinus1 - suff[i]] > mMinus1 - i) {
          bmGs[mMinus1 - suff[i]] = mMinus1 - i;
        }
      }
    }
  }
laststep:
  /* after suff[i] = i+1 */
  sh = mMinus1-f;
  for (; i >= 0; --i) {
    if (x[i] != c) {
      continue;
    }
    if (i+1 <= suff[i + sh]) {
      suff[i] = i+1;
      for (; j < mMinus1 - i; ++j) {
        if (bmGs[j] > mMinus1-i) {
          bmGs[j] = mMinus1 - i;
        }
      }
    }
    else {
      suff[i] = suff[i+sh];
    }
  }
}
