/*
 * writev.c
 * This program demonstrates vectored I/O. It uses the writev() function to
 * perform a write from multiple buffers into a file.
 * Copyright (c) 2013, 2014, 2020 Mr. Jin-Jwei Chen.  All rights reserved.
 */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>   /* memset() */
#include <sys/uio.h>  /* readv()/writev() */

#define  BUFSZ1  256  /* size of buffer 1 */
#define  BUFSZ2  512  /* size of buffer 2 */
#define  BUFSZ3  128  /* size of buffer 3 */

int main(int argc, char *argv[])
{
  char *fname;
  int  fd;
  ssize_t  bytes;
  struct   iovec  iov[3];  /* the I/O vector */
  char     buf1[BUFSZ1], buf2[BUFSZ2], buf3[BUFSZ3];
  size_t   i;

  /* Expect to get the file name from user */
  if (argc > 1)
    fname = argv[1];
  else
  {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    return(-1);
  }

  /* Open the output file. Create it if it does not exist. */
  fd = open(fname, O_WRONLY|O_CREAT|O_TRUNC, 0644);
  if (fd == -1)
  {
    fprintf(stderr, "open() failed, errno=%d\n", errno);
    return(-2);
  }

  /* Fill in the output buffers */
  for (i = 0; i < BUFSZ1; i++)
    buf1[i] = '1';
  for (i = 0; i < BUFSZ2; i++)
    buf2[i] = '2';
  for (i = 0; i < BUFSZ3; i++)
    buf3[i] = '3';

  /* Set up the I/O vector */
  iov[0].iov_base = buf1;
  iov[0].iov_len = BUFSZ1;
  iov[1].iov_base = buf2;
  iov[1].iov_len = BUFSZ2;
  iov[2].iov_base = buf3;
  iov[2].iov_len = BUFSZ3;

  /* Perform the vectored I/O */
  bytes = writev(fd, iov, 3);
  if (bytes == -1)
  {
    fprintf(stderr, "writev() failed, errno=%d\n", errno);
    close(fd);
    return(-3);
  }
  fprintf(stdout, "%ld bytes were written\n", bytes);

  /* Close the file */
  close(fd);
  return(0);
}

