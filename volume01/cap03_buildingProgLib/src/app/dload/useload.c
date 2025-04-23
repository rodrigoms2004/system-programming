/*
 * This program demonstrates how to dynamically load a shared library.
 * This same program works on all of these platforms: Windows XP,
 * Solaris 9, AIX 5.2, HP-UX 11.11, Linux 2.6.9 and Apple darwin 19.3 and on.
 * Use "cc -DWINDOWS" when you compile this program on Windows.
 * Authored by Jin-Jwei Chen.
 * Copyright (C) 2007, 2013 by Jin-Jwei Chen. All rights reserved.
 */
/*
 * HPUX : cc -DHPUX -Ae xx.c  (-Aa is ANSI mode, -Ae is ANSI plus "long long")
          `-Aa +e' or `-Ae'
   cc -DHPUX -Ae useload.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#if WINDOWS
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#if WINDOWS
#define  FUNCPTR   FARPROC
#define  SHLIBHDL  HMODULE
#else
typedef int (*FUNCPTR)();   /* define FUNCPTR as type of ptr-to-function */
#define  SHLIBHDL  void *
#endif

struct funcPtrEle {
    FUNCPTR *funcPtr;    /* pointer to (i.e. address of) the ptr-to-function */
    char    *funcName;   /* Name of the function */
};

typedef struct funcPtrEle FUNCPTRELE;

/* Declare the variables that will hold pointer to the functions. */
int (*FPechoMsg)();
int (*FPtripleIt)();

/* Set it up for symbol address lookup after loading the library.
 * First column gives address of the ptr-to-func variable. Second column
 * gives the name of the corresponding function.
 * The lookup will use the string value (the function name) in the second
 * column as input and fill in the pointer value in the first column.
 */
FUNCPTRELE funcPtrTbl[] = {
  /* FPechoMsg is a variable holding the ptr to the echoMsg() function */
  (FUNCPTR *)&FPechoMsg,   "echoMsg",
  (FUNCPTR *)&FPtripleIt,  "tripleIt",
  (FUNCPTR *)NULL,         (char *)NULL
};

SHLIBHDL load_shlib(char *libname, FUNCPTRELE *fptbl);

/*
 * Name of the shared library to load. Assuming most platforms use the .so
 * file name extension. Change the name accordingly to suit your system.
 */
#if WINDOWS
char SHLIBNAME[64] = "libtst1.dll";
#elif HPUX
char SHLIBNAME[64] = "libtst1.sl";
#else
char SHLIBNAME[64] = "libtst1.so";
#endif

/*
 * Start of main() function.
 */

int main(int argc, char **argv)
{
  int  ret;
  int  x = 22;
  char *mymsg = "Hello, there!";

  SHLIBHDL  hdl;

  /* Dynamically load the library and look up address of each function. */
  hdl = load_shlib(SHLIBNAME, funcPtrTbl);
  if (hdl == NULL) {
    fprintf(stderr, "Failed to load the library %s\n", SHLIBNAME);
    return(1);
  }

  /* Use the pointer-to-function to call each function. */

  /* Pass in an integer and get back another */
  ret = FPtripleIt(x);
  printf("Triple of %d is %d.\n", x, ret);

  /* Pass in a string and get back an integer */
  ret = FPechoMsg(mymsg);
  printf("There are %d characters in the string '%s'.\n", ret, mymsg);

  return(0);
}

/*
 * This function loads the shared library whose name specified by the
 * libname parameter. It then looks up the address of each function
 * whose name is specified by the second field of each element in the
 * array given in the fptbl parameter. The address obtained is returned
 * to the caller in the first field of each element in the array given
 * in the fptbl parameter.
 *
 * INPUT parameter: libname - name of the library to load
 * INPUT and OUTPUT parameter: fptbl - array of function pointers and
 *   function names.
 */

SHLIBHDL load_shlib(char *libname, FUNCPTRELE *fptbl)
{

    SHLIBHDL  hdl = NULL;

    if (libname == NULL || fptbl == NULL)
      return(NULL);

    /* Load the library */
#if WINDOWS
    hdl = LoadLibrary(libname);
#else
    hdl = dlopen(libname, RTLD_NOW | RTLD_GLOBAL);
#endif
    if (hdl == NULL) {
      fprintf(stderr, "Loading library %s failed.\n", libname);
#ifndef WINDOWS
      fprintf(stderr, "%s\n", dlerror());
#endif
      return(hdl);
    }

#ifndef WINDOWS
    /* Clear any existing error */
    dlerror();
#endif
    /* Look up symbols */
    while (fptbl->funcName != (char *)NULL)
    {
#if WINDOWS
      if ((*(fptbl->funcPtr) = GetProcAddress(hdl,
                               fptbl->funcName)) == (FARPROC)NULL)
      {
        fprintf(stderr, "Looking up symbol %s failed\n", fptbl->funcName);
        FreeLibrary(hdl);
        return (SHLIBHDL) NULL;
      }
#else
      if ((*(fptbl->funcPtr) = (FUNCPTR)dlsym(hdl, fptbl->funcName)) == NULL)
      {
        fprintf(stderr, "Looking up symbol %s failed\n", fptbl->funcName);
        dlclose(hdl);
        return (SHLIBHDL) NULL;
      }

#endif
      fptbl++;
    }
    return (hdl);
}

