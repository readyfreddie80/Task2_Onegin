//
// Created by freddie on 28.09.19.
//

#ifndef TASK2_ONEGIN_HELPERS_H
#define TASK2_ONEGIN_HELPERS_H

#include <ctype.h>


int fileSize (FILE *fp) {

    assert (fp != NULL);

    int prev=ftell(fp);
    fseek (fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek (fp, prev, SEEK_SET);

    return sz;
}


struct Line {
    char *beginning;
    unsigned int length;
};


int countNumberOfLines (const char *text, unsigned int length) {
    assert (text != NULL);
    assert (isfinite(length));
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



int splitTextIntoLines(char *text, unsigned int length, Line *lines) {
    assert (text != NULL);
    assert (lines != NULL);
    assert (isfinite(length));
    assert (length > 0);

    int i = 0;
    while(i < length && text[i]  == '\n') {
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


int comp (const void *a,  const void *b) {
    const char *lineA = ((Line *)a)->beginning;
    const char *lineB = ((Line *)b)->beginning;

    int lengthA = ((Line *)a)->length;
    int lengthB = ((Line *)b)->length;

    char upperA = 'A', upperB = 'A';
    bool isContinue = false;
    int i = 0, j = 0;
    while(i != lengthA && j != lengthB) {

        isContinue = false;

        if (ispunct(lineA[i]) || lineA[i] == ' ') {
            i++;
            isContinue = true;
        }

        if (ispunct(lineB[j]) || lineB[j] == ' ') {
            j++;
            isContinue = true;
        }

        if (isContinue == true)
            continue;

        upperA = toupper(lineA[i]);
        upperB = toupper(lineB[j]);

        if (upperA == upperB) {
            i++;
            j++;
        }
        else {
            return  upperA - upperB;
        }
    }

    if (i == lengthA && j == lengthB) {
        return 0;
    }

    if (i == lengthA) {
        return -1;
    }

    return 1;

}

int comp2 (const void *a,  const void *b) {
    const char *lineA = ((Line *)a)->beginning;
    const char *lineB = ((Line *)b)->beginning;

    int lengthA = ((Line *)a)->length;
    int lengthB = ((Line *)b)->length;

    char upperA = 'A', upperB = 'A';
    bool isContinue = false;
    int i = lengthA - 1, j = lengthB - 1;
    while (i != -1 && j != -1) {

        isContinue = false;

        if (ispunct(lineA[i]) || lineA[i] == ' ') {
            i--;
            isContinue = true;
        }

        if (ispunct(lineB[j]) || lineB[j] == ' ') {
            j--;
            isContinue = true;
        }

        if (isContinue == true)
            continue;

        upperA = toupper(lineA[i]);
        upperB = toupper(lineB[j]);

        if (upperA == upperB) {
            i--;
            j--;
        }
        else {
            return  upperA - upperB;
        }
    }

    if (i == -1 && j == -1) {
        return 0;
    }

    if (i == -1) {
        return -1;
    }

    return 1;

}







#endif //TASK2_ONEGIN_HELPERS_H
