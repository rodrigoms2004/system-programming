/*
 * Library functions - source file #1.
 * Authored by Mr. Jin-Jwei Chen
 * Copyright (c) 1991-2013 Mr. Jin-Jwei Chen  All rights reserved.
 */

#include <stdio.h>

/*
 * Compute and return the triple of the input integer value.
 */

#if WINDOWS
__declspec(dllexport) int __cdecl  tripleIt(int x)
#else
int tripleIt(int x)
#endif
{
  printf("The library function tripleIt() was called.\n");
  return (3*x);
}

