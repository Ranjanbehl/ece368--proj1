#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sorting.h"

long *Load_File(char *Filename, int *Size)
{
    FILE *input;
    long *numArray = NULL;
    int i;
    input = fopen(Filename, "r");
    if (input == NULL){
        exit(0);
    }
    //read the first line of the file as the size to use for malloc
    fscanf(input, "%i", Size);
    //allocate memory for  the array to hold all the numbers
    numArray = (long *)malloc(*Size * sizeof(long));
    for (i = 0; i < *Size; i++)
    {
        //read line by line
        fscanf(input, "%ld", &numArray[i]);
    }
    fclose(input);
    return numArray;
}

int Save_File(char *Filename, long *Array, int Size)
{
    FILE *output;
    int i,cnt = 0;
    output = fopen(Filename,"w");
    if (output == NULL)
    {
        return false;
    }
    fprintf(output,"%d\n",Size);
    //write to output file
    for (i = 0; i < Size; i++){
        fprintf(output,"%ld\n",Array[i]);
        cnt++;
    }
    // free allocated memeory
    free(Array);
    fclose(output);
    return (cnt);
}

int *genseq1(int Size) //The number seq is correct
{
    int *Array = NULL;
    //  Finding all of the gap values
    int seq1[Size]; // This isnt the best way as its inefficent so maybe linked list?
    seq1[0] = 1;
    int p2 = 0;
    int p3 = 0;
    int cnt = 0;
    int i = 1;
    int j = 0;
    while(seq1[i - 1] < Size)//for (i = 1; i < Size - 2; i++) // I am dumb as a rock seq1[0] already has a value smh
    {
        if (seq1[p2] * 2 == seq1[i - 1])
        {
            p2 += 1;
        }
        if (seq1[p3] * 3 == seq1[i - 1])
        {
            p3 += 1;
        }
        int u2 = seq1[p2] * 2;
        int u3 = seq1[p3] * 3;
        if (u2 < u3)
        {
            p2 += 1;
            seq1[i] = u2;
            cnt++;
        }
        else
        {
            p3 += 1;
            seq1[i] = u3;
            cnt++;
        }
    i++;
    }
    Array = (int *)malloc((cnt + 1) * sizeof(int)); // put the value of cnt at the Array[0] to fix the problem
    Array[0] = cnt;
    while(j < cnt) 
    {
        Array[j + 1] = seq1[j];
       // printf("\nThe seq values are: %d",Array[j]);
        j++;
    }
    return Array;
}

/* int *gensq2(int Size) // This works correctly but is slower...
{
    int *Array1 = NULL;
    int seq2[Size];
    seq2[0] = Size / 1.3;
    int i = 0;
    int j;
    int cnt = 0;
    while (seq2[i] > 0)
    {
        if (seq2[i] == 9 || seq2[i] == 10)
        {
            seq2[i] = 11;
        }
        seq2[i + 1] = (seq2[i]) / 1.3;
        i++;
        cnt++;
    }
    Array1 = (int *)malloc((cnt  + 1) * sizeof(int));
    for (j = 0; j < (cnt + 1); j++)
    {
        Array1[j] = seq2[j];
    }
    return Array1;
}  */

int genseq2(int Size){
    int gap = Size / 1.3;//(Size * 10) / 13;
        if (gap == 9 || gap == 10)
        {
            gap = 11;
        }
         else if (gap < 1) 
        {
            gap = 1;
        } 
    return gap;
}

void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
    *N_Comp = 0;
    *N_Move = 0;
    int k,i,j = 0,cnt = 0,gap = 0;
    int *seq1Array = NULL;
    seq1Array = genseq1(Size);
    cnt = seq1Array[0];
    //printf("\nThe seq size is %d", cnt);
    for (k = cnt; k > 0; k--)
    {
        gap = seq1Array[k];
        for (i = gap; i < Size; i++)
        {
            long temp = Array[i];
            *N_Move = *N_Move + 1;
            j = i;
            while ((j >= gap) && (Array[j - gap] > temp))
            {
                Array[j] = Array[j - gap];
                j -= gap;
                *N_Move = *N_Move + 1;
                *N_Comp = *N_Comp + 1;
            }
            Array[j] = temp;
            *N_Move = *N_Move + 1;
        }
    }
    free(seq1Array);
}
 
/* void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
    *N_Comp = 0;
    *N_Move = 0;
    int *seqArray1 = NULL;
    seqArray1 = gensq2(Size);
    int cnt = 0;
    while (seqArray1[cnt] > 0)
    {
     //printf("\nthe seq val is %d", seqArray1[cnt]);
        cnt++;
    }
    printf("\nThe seq size is %d", cnt);
    int i = 0,j;
    long temp;
    bool swapped = true;
    while (seqArray1[i] > 0 || swapped == true)
    {
        i++;
        swapped = false;

        for (j = 0; j < Size - seqArray1[j]; j++)
        {
            if (Array[j] > Array[j + seqArray1[j]])
            {
                *N_Comp = *N_Comp + 1;
                temp = Array[j];
                Array[j] = Array[j + seqArray1[j]];
                Array[j + seqArray1[j]] = temp;
                swapped = true;
                *N_Move = *N_Move + 3;
            }
        }
    }
    free(seqArray1);
} 
 */
 void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move)// fix this the first interger is not showing up
{
    int i, j, gap;
    bool swapped = true;
    double temp;
    *N_Comp = 0;
    *N_Move = 0;
    gap = Size;
    while (gap > 1 || swapped == true)
    {
        gap = genseq2(gap); // getting the next gap value
        swapped = false;
        for (i = 0, j = gap; j < Size; i++, j++)
        {
            if (Array[i] > Array[j])
            {
                *N_Comp = *N_Comp + 1;
                temp = Array[i];
                Array[i] = Array[j];
                Array[j] = temp;
                swapped = true;
                *N_Move = *N_Move + 3;
            }
        }
    }
}

void Save_Seq1(char *Filename, int N)
{

    int *seqArray = NULL;
    seqArray = genseq1(N);
    FILE *output;
    output = fopen(Filename, "w");
    if (output == NULL)
    {
        exit(0);
    }
    int i;
    for (i = 0; i < N + 1; i++)
    {
        fprintf(output, "%d\n", seqArray[i + 1]);
    }
    free(seqArray);
    fclose(output);
}

 void Save_Seq2(char *Filename, int N) 
{
    int i = 0, j;
    int gap =  N;
    int arr[N];
    FILE *output;
    output = fopen(Filename, "w");
    if (output == NULL)
    {
        exit(0);
    }
    while(gap > 0)
    {
       gap = genseq2(gap);
       arr[i] = gap;
       i++;
    }
    for (j = i; j > 0; j--)
    {
        fprintf(output, "%d\n", arr[j]);
    }
    
    fclose(output);
}
