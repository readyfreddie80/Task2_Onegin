//
// Created by freddie on 28.09.19.
//

#ifndef TASK2_ONEGIN_HELPERS_H
#define TASK2_ONEGIN_HELPERS_H

#include <stdlib.h>
#include <fstream>

struct Line {
    const char   *beginning; /// pointer to the beginning of the line
    size_t        length;    /// length of the line without any terminating symbols
};

/*!
    Returns a pointer to the first occurrence in text of length len
    of any of the characters that are part of splitter,
    or a null pointer if there are no matches.

    \param[in] text      pointer to the beginning of the string to be scanned
    \param[in] splitters string containing the characters to match
    \param[in] len       length of text
    \return A pointer to the first occurrence in text of length len of any of the characters
    that are part of splitters, or a null pointer if none of the characters of splitters
    is found in text.
    */
const char * mempbrk (
        const char *text,
        const char *splitters,
        size_t      len);


/*!
    Gets the size of a text file in bytes
    \param[in] fp pointer on FILE
    \return Size of file in bytes
 */
size_t fileSize (FILE *fp);

/*!
    Puts line of struct Line into the file
    \param[in] line
    \param[in] fp    pointer to FILE
    \return Size of file in bytes
 */
size_t outputLine(
        Line   line,
        FILE  *outputFile);

/*!
    Puts lines from an array of Line into file one by one
    \param[in] lines array of lines to put
    \param[in] size  size of array
    \param[in] fp    pointer on FILE
    \return Size of file in bytes
 */
size_t outputLines (
        const Line *lines,
        size_t      size,
        FILE       *outputFile);


/*!
    Counts number of lines in the text
    \param[in] text original text
    \param[in] length length of the text
    \return Number of lines
 */
size_t countNumberOfNonEmptyLines (
        const char *text,
        size_t      length,
        const char *splitters);

/*!
    Splits text into lines skipping empty lines
    \param[in]  text original text
    \param[in]  length length of the text
    \param[out] array of lines
    \return Number of lines
 */
size_t splitTextIntoLines (
        const char *text,
        size_t      length,
        Line       *lines,
        const char *splitters);

/*!
    Compares two lines
    \param[in] lineA first line
    \param[in] lineB second line
    \param[in] lineAFirstInd first index of comparison in the first line
    \param[in] lineBFirstInd first index of comparison in the second line
    \param[in] step step
    \param[in] terminalAInd
    \param[in] terminalBInd
 */
int lexicographicalOrderComp (
        const char *lineA,
        const char *lineB,
        long        lineAFirstInd,
        long        lineBFirstInd,
        long        step,
        long        terminalAInd,
        long        terminalBInd);

int compFromBegToEnd (
        const void *a,
        const void *b);

int compFromEndToBeg (
        const void *a,
        const void *b);

#endif //TASK2_ONEGIN_HELPERS_H
