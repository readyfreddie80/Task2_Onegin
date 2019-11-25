#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string.h>

#include "helpers.h"


int main () {

    char *iputFileName = "/home/freddie/CLionProjects/Task2_Onegin/Text/hamlet.txt";
    FILE *inputFile = fopen (iputFileName, "r");
    assert (inputFile != NULL);

    int inputFileLength = fileSize (inputFile);

    char *originalText = (char *)calloc (inputFileLength + 1, sizeof (char));
    assert (originalText != NULL);
    originalText[inputFileLength] = '\0';


    if (fread (originalText, sizeof (char), inputFileLength, inputFile) != inputFileLength) {
        if (feof (inputFile)) {
            printf ("Premature end of file: %s", iputFileName);
        }
        else
            printf ("File %s read ERROR.", iputFileName);

        exit (1);
    }

    fclose (inputFile);


    int numberOfLines = countNumberOfLines (originalText, inputFileLength);

    if (numberOfLines < 1) {
        printf ("ERROR: number of lines in file is %d", numberOfLines);
        exit (1);
    }

    Line *lines = (Line *)calloc(numberOfLines, sizeof (Line));

    int numberOfNonEmptyLines = splitTextIntoLines (originalText, inputFileLength, lines);

    if (numberOfNonEmptyLines < 1) {
        printf ("ERROR: number of non-empty lines in file is %d", numberOfNonEmptyLines);
        exit(1);
    }


    char *outputFileName = "/home/freddie/CLionProjects/Task2_Onegin/hamletResult.txt";
    FILE *outputFile = fopen (outputFileName, "w");
    assert (outputFile != NULL);

    qsort (lines, numberOfNonEmptyLines, sizeof (Line), compFromBegToEnd);

    fputs ("ALPHABETIC DICTIONARY\n", outputFile);

    outputLines (lines, numberOfNonEmptyLines, outputFile);

    qsort (lines, numberOfNonEmptyLines, sizeof (Line), compFromEndToBeg);

    fputs ("\nRHYMES DICTIONARY\n", outputFile);

    outputLines (lines, numberOfNonEmptyLines, outputFile);

    fputs ("ORIGINAL\n", outputFile);

    fwrite (originalText, sizeof (char), inputFileLength, outputFile);

    fputc ('\n', outputFile);

    fclose (outputFile);


    free (originalText);
    free (lines);

    return 0;
}




