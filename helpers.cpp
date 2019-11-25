//
// Created by freddie on 30.09.19.
//

#include <assert.h>
#include <ctype.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string.h>

#include "helpers.h"



int fileSize (FILE *fp) {

    assert (fp != NULL);

    int prev=ftell (fp);
    fseek (fp, 0L, SEEK_END);

    int sz=ftell (fp);
    fseek (fp, prev, SEEK_SET);

    return sz;
}


int outputLines (const Line *lines, int size, FILE *outputFile) {

    assert (lines != NULL);
    assert (outputFile != NULL);
    assert (isfinite(size));

    for (int i = 0; i < size; ++i) {
        fwrite (lines[i].beginning, sizeof (char), lines[i].length, outputFile);
        putc ('\n', outputFile);
    }


}


int countNumberOfLines (const char *text, unsigned int length) {
    assert (text != NULL);
    assert (isfinite (length));
    assert (length > 0);

    int number = 1;
    int l = length;
    for (char *s = (char *)memchr (text, '\n', length);
         s && (l = length - (s - text) - 1) > 0;
         s = (char *)memchr (s + 1, '\n', l)) {
        number++;
    }

    return number;
}



int splitTextIntoLines (char *text, unsigned int length, Line *lines) {
    assert (text != NULL);
    assert (lines != NULL);
    assert (isfinite(length));
    assert (length > 0);

    int i = 0;
    while (i < length && text[i]  == '\n') {
        i++;
    }

    if (i >= length)
        return 0;

    lines[0].beginning = text + i;
    lines[0].length = length - i;


    int n = 1;
    for (char *s = (char *)memchr (lines[0].beginning, '\n', lines[0].length);
         s;
         s = (char *)memchr (s + 1, '\n', lines[n++].length)) {

        lines[n - 1].length = s - lines[n - 1].beginning;


        while ((lines[n].length = length - (s - text) - 1) > 0 &&
               *(s + 1) == '\n') {
            s++;
        }

        if (lines[n].length <= 0) {
            break;
        }

        lines[n].beginning = s + 1;
    }

    return n;
}


int lexicographicalOrderComp (const char *lineA, const char *lineB,
                              int lineAFirstInd, int lineBFirstInd,
                              int step, int terminalAInd, int terminalBInd) {

    assert (lineA != NULL);
    assert (lineB != NULL);

    int i = lineAFirstInd,
        j = lineBFirstInd;

    while (i != terminalAInd && j != terminalBInd) {

        bool isContinue = false;

        if (ispunct(lineA[i]) || lineA[i] == ' ') {
            i = i + step;
            isContinue = true;
        }

        if (ispunct(lineB[j]) || lineB[j] == ' ') {
            j = j + step;
            isContinue = true;
        }

        if (isContinue == true)
            continue;

        char upperA = toupper(lineA[i]);
        char upperB = toupper(lineB[j]);

        if (upperA == upperB) {
            i = i + step;
            j = j + step;
        }
        else {
            return  upperA - upperB;
        }
    }

    if (i == terminalAInd && j == terminalBInd) {
        return 0;
    }

    if (i == terminalAInd) {
        return -1;
    }

    return 1;
}

int compFromBegToEnd (const void *a,  const void *b) {
    const char *lineA = ((Line *)a)->beginning;
    const char *lineB = ((Line *)b)->beginning;

    int lengthA = ((Line *)a)->length;
    int lengthB = ((Line *)b)->length;

    lexicographicalOrderComp (lineA, lineB, 0, 0, 1, lengthA, lengthB);
}

int compFromEndToBeg (const void *a,  const void *b) {
    const char *lineA = ((Line *)a)->beginning;
    const char *lineB = ((Line *)b)->beginning;

    int lengthA = ((Line *)a)->length;
    int lengthB = ((Line *)b)->length;

    return lexicographicalOrderComp (lineA, lineB, lengthA - 1, lengthB - 1, -1, -1, -1);
}