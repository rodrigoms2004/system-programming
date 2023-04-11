/*
 * Library functions - source file #2.
 * These functions demonstrate that one library function can call another
 * library function and a library function can take input arguments and
 * return a value.
 * Authored by Mr. Jin-Jwei Chen
 * Copyright (c) 1991-2013 Mr. Jin-Jwei Chen  All rights reserved.
 */

#include <stdio.h>
#include <string.h>

/*
 * Call another library function to echo the input message.
 * Return the length of the input message.
 */

#if WINDOWS
__declspec(dllexport) int __cdecl  echoMsg(char *msg)
#else
int echoMsg(char *msg)
#endif
{
  int echoMsg2(char *msg);

  printf("The library function echoMsg() was called.\n");
  return(echoMsg2(msg));
}

/*
 * Echo the input message and return its length.
 */

int echoMsg2(char *msg)
{
  int  len = 0;

  printf("The library function echoMsg2() was called.\n");
  if (msg != NULL) {
    len = strlen(msg);
    printf("*** Your message is: %s\n", msg);
  }
  return(len);
}

