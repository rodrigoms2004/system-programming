/*
 * This program demonstrates calling functions in libraries of our own
 * via static or dynamic linking.
 * Authored by Mr. Jin-Jwei Chen
 * Copyright (c) 1991-2013 Mr. Jin-Jwei Chen. All rights reserved.
 */

#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int  ret;
  int  x = 22;
  char *mymsg = "Hello, there!";

  /* Pass in an integer and get back another */
  ret = tripleIt(x);
  printf("Triple of %d is %d.\n", x, ret);

  /* Pass in a string and get back an integer */
  ret = echoMsg(mymsg);
  printf("There are %d characters in the string '%s'.\n", ret, mymsg);

  return(0);
}

