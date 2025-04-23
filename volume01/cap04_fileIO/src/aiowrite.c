/*
 * aiowrite.c
 * This program opens a file and writes a number of KBs to it using
 * asynchronous I/O.
 * $ cc -o aiowrite aiowrite.c -lrtkaio -lrt
 * Copyright (c) 2013, 2014, 2020 Mr. Jin-Jwei Chen.  All rights reserved.
 */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>  /* memset() */
#include <stdlib.h>  /* atoi() */
#include <aio.h>

#define  BUFSZ        (100*1024)
char     buf[BUFSZ];

int main(int argc, char *argv[])
{
  char *fname;
  int  fd;
  ssize_t  bytes;
  size_t   count;
  int      status;
  int      nkbs=20;
  struct aiocb  aiocb;
  size_t   i;

  /* Expect to get the file name from user */
  if (argc > 1)
    fname = argv[1];
  else
  {
    fprintf(stderr, "Usage: %s filename [KBs(1-100)]\n", argv[0]);
    return(-1);
  }
  if (argc > 2)
  {
    nkbs = atoi(argv[2]);
    if (nkbs <= 0 || nkbs > 100)
      nkbs = 1;
  }
  fprintf(stdout, "Writing %u KBs to file %s\n", nkbs, fname);

  /* Open a file for write only. */
  fd = open(fname, O_WRONLY|O_CREAT|O_TRUNC, 0644);
  if (fd == -1)
  {
    fprintf(stderr, "open() failed, errno=%d\n", errno);
    return(-2);
  }

  /* Initialize the entire buffer with letter 'A' */
  memset(buf, 65, BUFSZ);
  count = nkbs * 1024;

  /* Fill in the aio control block */
  memset((void *)&aiocb, 0, sizeof(aiocb));
  aiocb.aio_fildes = fd;
  aiocb.aio_buf = buf;
  aiocb.aio_nbytes = count;

  /* Write the amount specified to the file */
  status = aio_write(&aiocb);
  if (status == 0)
    fprintf(stdout, "The aio write request has been enqueued.\n");
  else if (status == -1)
  {
    fprintf(stderr, "aio_write() call failed, errno=%d\n", errno);
    close(fd);
    return(-3);
  }
    
  /* Do some other processing here. Otherwise, we wouldn't need async I/O. */

  /* Wait for the async I/O operation to complete */
  status = EINPROGRESS;
  while (status == EINPROGRESS)
    status = aio_error(&aiocb);
  fprintf(stdout, "The async I/O operation completed. aio_error returned %d\n",
    status);
  switch (status)
  {
    case 0:
      fprintf(stdout, "The async I/O operation completed successfully.\n");
    break;
    case ECANCELED:
      fprintf(stdout, "The async I/O operation was cancelled.\n");
    break;
    default:
      fprintf(stdout, "The async I/O operation encountered error %d\n", status);
    break;
  }

  /* Get the final return value of the async I/O call */
  bytes = aio_return(&aiocb);
  if (status == -1)
  {
    fprintf(stderr, "Async write operation failed, errno=%d\n", errno);
    close(fd);
    return(-4);
  }

  fprintf(stdout, "%ld bytes were written into the file.\n", bytes);

  /* Close the file */
  close(fd);
  return(0);
}

