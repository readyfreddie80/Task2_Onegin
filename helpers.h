//
// Created by freddie on 28.09.19.
//

#ifndef TASK2_ONEGIN_HELPERS_H
#define TASK2_ONEGIN_HELPERS_H

struct Line {
    char *beginning;
    unsigned int length;
};

/*!
    Gets the size of a text file in bytes
    \param[in] fp pointer on FILE
    \return Size of file in bytes
 */
int fileSize (FILE *fp);

/*!
    Puts lines from an array of Line into file one by one
    \param[in] fp pointer on FILE
    \return Size of file in bytes
 */
int outputLines (const Line *lines, int size, FILE *outputFile);


/*!
    Counts number of lines in the text
    \param[in] text original text
    \param[in] length length of the text
    \return Number of lines
 */
int countNumberOfLines (const char *text, unsigned int length);

/*!
    Splits text into lines skipping empty lines
    \param[in] text original text
    \param[in] length length of the text
    \param[out] array of lines
    \return Number of lines
 */
int splitTextIntoLines (char *text, unsigned int length, Line *lines);

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
int lexicographicalOrderComp (const char *lineA, const char *lineB,
                              int lineAFirstInd, int lineBFirstInd,
                              int step, int terminalAInd, int terminalBInd);

int compFromBegToEnd (const void *a,  const void *b);

int compFromEndToBeg (const void *a,  const void *b);

#endif //TASK2_ONEGIN_HELPERS_H
