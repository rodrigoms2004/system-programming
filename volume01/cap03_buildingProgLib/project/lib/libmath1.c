#include<stdio.h>

#if WINDOWS
__declspec(dllexport) long int __cdecl  factorialRec(int n)
#else
long int factorialRec(int n)
#endif
{
    printf("The library function factorialRec() was called.\n");

    if (n>=1)
        return n*factorialRec(n-1);
    else
        return 1;   
}
