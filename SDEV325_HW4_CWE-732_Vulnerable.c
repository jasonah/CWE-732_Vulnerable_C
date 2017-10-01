/* 
 * JASON HOWARTH
 * SDEV325 6380
 * HOMEWORK 4 - VULNERABLE to CWE-732: Incorrect Permission Assignment for Critical Resource
 * 02 JULY 2017
 * SDEV325_HW4_CWE-732_Vulnerable.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    
    //CONSTANTS
    #define OUTFILE "SSN.txt"
    
    //VARIABLE DEFINITIONS
    char ssnArray[12] = {0};
    char userInput[12]; 
    int arraySize = sizeof(ssnArray);
    char cwd[1024];
  
    //REQUEST USER INPUT
    printf("Enter a 9-digit Social Security Number with dashes: ");
    scanf("%s", &userInput);

    // COPY userInput USING strlcpy FUNCTION INTO bufferArray  
    strlcpy(ssnArray, userInput, arraySize);
    
    //CWE-732 VULNERABILITY - Incorrect permissions.
    //umask(0) sets permissions allowing anyone to read/write the created file.
    umask(0);
    
    //OUTPUT FILE SSN.txt with ssnArray
    FILE *out;//POINTER TO FILE
    out = fopen(OUTFILE, "w");//CREATE AN EMPTY FILE
    if (out) {
        fprintf(out, "%s\n",ssnArray);//PRINT ssnArray TO FILE
        fclose(out);
    }
    
    //GET CURRENT WORKING DIRECTORY
    getcwd(cwd, sizeof(cwd));
    //TELL USER WHERE FILE HAS BEEN SAVED
    printf("\nYour Social Security Number %s has been saved to:\n %s/%s\n",ssnArray,cwd,OUTFILE);
    
    return (EXIT_SUCCESS);
}

