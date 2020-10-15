//
// Created by freddie on 30.09.19.
//

#include <assert.h>
#include <ctype.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string.h>

#include "texts.h"
#include "stdfuncs_wrappers.h"


const char * mempbrk (
        const char *text,
        const char *splitters,
        size_t      len) {

    assert (text      != nullptr);
    assert (splitters != nullptr);

    if (len == 0) {
        return nullptr;
    }

    const char *const eom = text + len;

    register const char *spltPtr = nullptr;

    register int currChar     = 0,
                 currSplitter = 0;

    while (text < eom) {
        currChar = *text++;
        spltPtr  = splitters;

        while ((currSplitter = *spltPtr++))
            if (currChar == currSplitter)
                return (text - 1);
    }
    return (nullptr);
}



size_t fileSize (FILE *fp) {

    assert (fp != nullptr);

    long prev = ftell_wrapper (fp);
    fseek_wrapper (fp, 0L, SEEK_END);

    long size = ftell_wrapper (fp);
    fseek_wrapper (fp, prev, SEEK_SET);

    return (size_t)size;
}


size_t outputLine(
        Line   line,
        FILE  *outputFile) {
        return fwrite (
                line.beginning,
                sizeof (*line.beginning),
                line.length,
                outputFile);
}

size_t outputLines (
        const Line *lines,
        size_t      size,
        FILE       *outputFile) {

    assert (lines      != nullptr);
    assert (outputFile != nullptr);

    for (int i = 0; i < size; ++i) {
        outputLine(lines[i], outputFile);
        putc ('\n', outputFile);
        fflush(outputFile);
    }
}


size_t countNumberOfNonEmptyLines (
        const char *text,
        size_t      length,
        const char *splitters) {

    assert (text != nullptr);

    if (length == 0) {
        return 0;
    }

    size_t  number = 0;

    const char *prev = mempbrk (text, splitters, length);

    // if there are no splitters in the text
    // there is one non-empty line
    if (prev == nullptr) {
        return 1;
    }
    // here we count the non-empty line ending with *prev
    if (prev != text) {
        number++;
    }

    // count all the non-empty lines ending with a splitter
    // after the first one (one ending with *prev)
    const char * s = prev;
    while (true) {
        size_t sLength = length - (s - text + 1);
        s = mempbrk (s + 1, splitters, sLength);

        if (s == nullptr) {
            break;
        }

        if (s - prev > 1) {
            number++;
        }
        prev = s;
    }


    // if the last non-empty line doesn't end with splitter
    if ((prev - text) + 1 != length) {
        number++;
    }

    return number;
}



size_t splitTextIntoLines (
        const char *text,
        size_t      length,
        Line       *lines,
        const char *splitters) {
    assert (text  != nullptr);
    assert (lines != nullptr);

    if (length == 0) {
        return 0;
    }

    assert (text != nullptr);

    size_t  number = 0;

    const char *prev = mempbrk (text, splitters, length);

    // if there are no splitters in the text
    // there is one non-empty line
    if (prev == nullptr) {
        lines[number].beginning = text;
        lines[number].length    = length;
        return ++number;
    }
    // here we count the non-empty line ending with *prev
    if (prev != text) {
        lines[number].beginning = text;
        lines[number].length    = prev - text;
        ++number;
    }

    // count all the non-empty lines ending with a splitter
    // after the first one (one ending with *prev)
    const char * s = prev;
    while (true) {
        size_t sLength = length - (s - text + 1);
        s = mempbrk (s + 1, splitters, sLength);

        if (s == nullptr) {
            break;
        }

        if (s - prev > 1) {
            lines[number].beginning = prev + 1;
            lines[number].length    = s - prev - 1;
            number++;
        }
        prev = s;
    }

    // if the last non-empty line doesn't end with splitter
    size_t delta = (prev - text) + 1;
    if (delta != length) {
        lines[number].beginning = prev + 1;
        lines[number].length    = length - delta;
        number++;
    }

    return number;
}


int lexicographicalOrderComp (
        const char *lineA,
        const char *lineB,
        long        lineAFirstInd,
        long        lineBFirstInd,
        long        step,
        long        terminalAInd,
        long        terminalBInd) {

    assert (lineA != nullptr);
    assert (lineB != nullptr);

    long i = lineAFirstInd,
         j = lineBFirstInd;

    while (i != terminalAInd && j != terminalBInd) {

        bool isContinue = false;

        if (ispunct(lineA[i]) || lineA[i] == ' ') {
            i += step;
            isContinue = true;
        }

        if (ispunct(lineB[j]) || lineB[j] == ' ') {
            j += step;
            isContinue = true;
        }

        if (isContinue)
            continue;

        int upperA = toupper(lineA[i]);
        int upperB = toupper(lineB[j]);

        if (upperA == upperB) {
            i = i + step;
            j = j + step;
        }
        else {
            return  upperA - upperB;
        }
    }


    while (i != terminalAInd && (ispunct(lineA[i]) || lineA[i] == ' ')) {
            i += step;
    }

    while (j != terminalBInd && (ispunct(lineB[j]) || lineB[j] == ' ')) {
            j += step;
    }


    if (i == terminalAInd && j == terminalBInd) {
        return 0;
    }

    if (i == terminalAInd) {
        return -1;
    }

    return 1;
}

int compFromBegToEnd (
        const void *a,
        const void *b) {

    const char *lineA = ((Line *)a)->beginning;
    const char *lineB = ((Line *)b)->beginning;

    size_t lengthA = ((Line *)a)->length;
    size_t lengthB = ((Line *)b)->length;

    lexicographicalOrderComp (lineA, lineB, 0, 0, 1, lengthA, lengthB);
}

int compFromEndToBeg (const void *a,  const void *b) {
    const char *lineA = ((Line *)a)->beginning;
    const char *lineB = ((Line *)b)->beginning;

    size_t lengthA = ((Line *)a)->length;
    size_t lengthB = ((Line *)b)->length;

    return lexicographicalOrderComp (lineA, lineB, lengthA - 1, lengthB - 1, -1, -1, -1);
}