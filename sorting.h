#ifndef __sorting_h_
#define __sorting_h_

#include <stdlib.h>
#include <stdio.h>

// Constant Definitions

/* Return/Error Codes */
#define OK               (  0 )  // No errors, everything as should be
#define ERROR            ( -1 ) // Generic error

// structures
/* struct Stack { 
    int top; 
    unsigned capacity; 
    int* array; 
}; 
  
// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct Stack* createStack(unsigned capacity) 
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*)malloc(stack->capacity * sizeof(int)); 
    return stack; 
}  */


/* Function Prototypes */
long *Load_File(char *Filename, int *Size);
int Save_File(char *Filename, long *Array, int Size);
int *genseq1(int Size); 
int genseq2(int Size);
void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
void Save_Seq1(char *Filename, int N);
void Save_Seq2(char *Filename, int N);
#endif  // __sorting_h_ 

