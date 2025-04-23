/*
 * aioread.c
 * This program opens a file and reads a couple of blocks from it using
 * asynchronous I/O. The user can specify a starting offset to read from.
 * $ cc -o aioread aioread.c -lrtkaio -lrt
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

#define  BUFSZ        (1024)

int main(int argc, char *argv[])
{
  char *fname;
  int  fd;
  ssize_t  bytes;
  size_t   count;
  int      status;
  int      offset=0;
  struct aiocb  aiocb;
  char     buf[BUFSZ+1];

  /* Expect to get the file name from user */
  if (argc > 1)
    fname = argv[1];
  else
  {
    fprintf(stderr, "Usage: %s filename [offset]\n", argv[0]);
    return(-1);
  }
  if (argc > 2)
  {
    offset = atoi(argv[2]);
    if (offset < 0)
      offset = 0;
  }

  /* Open a file for read only. */
  fd = open(fname, O_RDONLY);
  if (fd == -1)
  {
    fprintf(stderr, "open() failed, errno=%d\n", errno);
    return(-2);
  }

  /* Clear the entire buffer */
  memset(buf, 0, BUFSZ);
  count =  BUFSZ;

  /* Fill in the aio control block */
  memset((void *)&aiocb, 0, sizeof(aiocb));
  aiocb.aio_fildes = fd;
  aiocb.aio_buf = buf;
  aiocb.aio_nbytes = count;
  if (offset > 0)
    aiocb.aio_offset = offset;

  /* Read the amount specified from the file */
  status = aio_read(&aiocb);
  if (status == 0)
    fprintf(stdout, "The aio read request has been enqueued.\n");
  else if (status == -1)
  {
    fprintf(stderr, "aio_read() call failed, errno=%d\n", errno);
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
    fprintf(stderr, "Async read operation failed, errno=%d\n", errno);
    close(fd);
    return(-4);
  }
  buf[BUFSZ] = '\0';
  fprintf(stdout, "%ld bytes were read from the file.\n", bytes);
  fprintf(stdout, "%s\n", buf);

  /* Close the file */
  close(fd);
  return(0);
}

