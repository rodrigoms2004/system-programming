/*
    Before run 
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/eseye/system-programming/volume01/cap03_buildingProgLib/project/lib
*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <dlfcn.h>

typedef int (*FUNCPTR)(); // define FUNCPTC as type of ptr-to-function
#define SHLIBHDL void *


struct funcPtrEle {
    FUNCPTR *funcPtr;   // pointer to (i.e. address of) the ptr-to-function
    char    *funcName;  // name of the function
};

typedef struct funcPtrEle FUNCPTRELE;

// declare the variables that will hold pointer to the functions
long int (*FPfactorialRec)();

/*
    Set it up for symbol address lookup after loading the library.
    First column gives address of the ptr-to-func variable. Second column
    gives the name of the corresponding function.
    The lookup will use the strng value (the function name) in the second
    column as input and fill in the pointer value in the first column.
*/

FUNCPTRELE funcPtrTbl[] = {
    // FPfactorialRec is a variable holsing the ptr to the factorialRec() function
    (FUNCPTR *)&FPfactorialRec, "factorialRec",
    (FUNCPTR *)NULL, (char *)NULL
};


SHLIBHDL load_shlib(char *libname, FUNCPTRELE *fptbl);

/*
    Name of the shared library to load. Assuming most platformas use the .so
    file name extension. Change the name accordingly to duit your system.
*/
char SHLIBNAME[64] = "libmath1.so";

// Start main() function

int main(int argc, char **argv) {
    int n;
    SHLIBHDL hdl;

    // Dynamically load the library and look up address of each function.
    hdl = load_shlib(SHLIBNAME, funcPtrTbl);
    if (hdl == NULL) {
        fprintf(stderr, "Failed to load the library %s\n", SHLIBNAME);
        return 1;
    }

    // Use the pointer-to-function to call each function.
    // Pass in an integer and get back another
    
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    printf("Factorial of %d = %ld", n, FPfactorialRec(n));
    return 0;
}

SHLIBHDL load_shlib(char *libname, FUNCPTRELE *fptbl) {
    SHLIBHDL hdl = NULL;

    if (libname == NULL || fptbl == NULL)
        return NULL;

    // load the library

    hdl = dlopen(libname, RTLD_NOW | RTLD_GLOBAL);

    if (hdl == NULL) {
        fprintf(stderr, "Loading library %s failed.\n", libname);
        return hdl;
    }

    // Look up symbols 
    while (fptbl->funcName != (char *)NULL) {
        if ( (*(fptbl->funcPtr) = (FUNCPTR)dlsym(hdl, fptbl->funcName)) == NULL ) {
            fprintf(stderr, "Looking up symbol %s failed\n", funcPtrTbl->funcName);
            dlclose(hdl);
            return (SHLIBHDL) NULL;
        }

        fptbl++;
    } 
    return hdl;
}