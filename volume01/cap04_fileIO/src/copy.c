/*
 * copy.c
 * This program makes a copy of an existing file.
 * It demonstrates sequential read and sequential write of files.
 * Copyright (c) 2013, 2014, 2020 Mr. Jin-Jwei Chen.  All rights reserved.
 */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>  /* memset() */

#define BUFSZ   2048

int main(int argc, char *argv[])
{
    char *infname, *outfname;   /* names of input and output file */
    int infd, outfd;            /* input and output file descriptors */
    int ret = 0;                /* return code of this program */
    ssize_t bytes_rd, bytes_wr;     /* number of bytes read or written */
    size_t  count;
    int     done = 0;
    char    buf[BUFSZ];         /* input and output buffer */
    char    *bufadr;

    /* Expect to get the file names from user */
    if (argc > 2)
    {
        infname = argv[1];
        outfname = argv[2];
    }
    else
    {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return(-1);
    }

    /* Open the input file for read only. */
    infd = open(infname, O_RDONLY);
    if (infd == -1)
    {
        fprintf(stderr, "opening input file failed, errno=%d\n", errno);
        return(-2);
    }

    /* Open the output file for write only. Create it if it does not already
    * exist. Truncate the file (erase old contents) if it already exists.
    */
   outfd = open(outfname, O_WRONLY|O_CREAT|O_TRUNC, 0644);
   if (outfd == -1)
   {
        fprintf(stderr, "opening output file failed, errno=%d\n", errno);
        close(infd);
        return(-3);
   }

    /* Read from the input file and write to the output file. Loop until done. */
    while(!done)
    {
        /* Read the next chunk from the input file */
        bytes_rd = read(infd, buf, BUFSZ);
        if (bytes_rd == -1)
        {
            fprintf(stderr, "failed to read input file, errno=%d\n", errno);
            ret = (-4);
            break;
        }
        else if (bytes_rd == 0) /* End of file */
            break;

        /* Write the file contents we just read to the output file */
        count = bytes_rd;
        bufadr = buf;
        while (count > 0)
        {
            bytes_wr = write(outfd, bufadr, count);
            if (bytes_wr == -1)
            {
                fprintf(stderr, "failed to write output file, errno=%d\n", errno);
                ret = (-5);
                break;
            }
            count = count - bytes_wr;
            bufadr = bufadr + bytes_wr;
        }   /* inner while */
    }   /* outer while */

    /* Close the files */
    close(infd);
    close(outfd);
    return(ret);
}
