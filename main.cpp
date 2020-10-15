#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string.h>

#include "texts.h"
#include "stdfuncs_wrappers.h"
#include "project_defines.h"


#ifndef TESTS
int main (int  argc, char *argv[]) {

    if (argc != 3) {
        FPRINTF_ERROR_AND_EXIT(
                "Paths of source file and result file must be given as arguments."
                "\nUsage: %s [source path] [result path]",
                argv[0]);
    }

    const char *inputFileName = argv[1];

    FILE *inputFile = fopen_wrapper (inputFileName, "rb");
    EXIT_IF_ERROR_OCCURRED();

    size_t inputFileLength = fileSize (inputFile);

    char *originalText = (char *)calloc_wrapper(
            inputFileLength + 1,
            sizeof(*originalText));
    EXIT_IF_ERROR_OCCURRED();

    originalText[inputFileLength] = '\0';
    if (fread (originalText, sizeof (*originalText), inputFileLength, inputFile) != inputFileLength) {
        if (feof (inputFile)) {
            FPRINTF_ERROR_AND_EXIT (
                    "Premature end of file: %s",
                    inputFileName);
        }
        else {
            FPRINTF_ERROR_AND_EXIT (
                    "File %s read ERROR.",
                    inputFileName);
        }
    }

    fclose_wrapper (inputFile);

    const char * splitters = "\n\r";
    size_t numberOfNonEmptyLines = countNumberOfNonEmptyLines(
            originalText,
            inputFileLength,
            splitters);

    if (numberOfNonEmptyLines < 1) {
        FPRINTF_ERROR_AND_EXIT (
                "Number of non-empty lines in file can't be %zu",
                numberOfNonEmptyLines);
    }

    Line *lines = (Line *)calloc_wrapper(
            numberOfNonEmptyLines,
            sizeof (*lines));
    EXIT_IF_ERROR_OCCURRED();

    splitTextIntoLines(
            originalText,
            inputFileLength,
            lines,
            splitters);

    const char *outputFileName = argv[2];
    FILE *outputFile = fopen_wrapper (outputFileName, "w");

    qsort (
            lines,
            numberOfNonEmptyLines,
            sizeof (*lines),
            compFromBegToEnd);

    fputs ("ALPHABETIC DICTIONARY\n", outputFile);

    outputLines (
            lines,
            numberOfNonEmptyLines,
            outputFile);

    qsort (
            lines,
            numberOfNonEmptyLines,
            sizeof (*lines),
            compFromEndToBeg);

    fputs ("\nRHYMES DICTIONARY\n", outputFile);

    outputLines (
            lines,
            numberOfNonEmptyLines,
            outputFile);

    fputs ("\nORIGINAL\n", outputFile);

    fwrite (
            originalText,
            sizeof (*originalText),
            inputFileLength,
            outputFile);

    fputc ('\n', outputFile);

    fclose_wrapper (outputFile);

    free (originalText);
    free (lines);

    return 0;
}


#endif

