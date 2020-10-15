//
// Created by freddie on 13.10.20.
//

#include <stdlib.h>
#include <cstring>
#include "project_defines.h"

#include "texts.h"

#ifdef TESTS

#define FPRINTF_ERROR(...) fprintf(stderr, __VA_ARGS__);

#define CAT(x, y) x##y

#define UNIT_TESTS(func)                     \
    FPRINTF_ERROR("\nStart testing " #func "...\n"); \
    CAT(func, UnitTests)();                  \
    FPRINTF_ERROR("\n" #func " tested\n");                \

void mempbrkTest (const char *text,
                  const char *splitters) {
    size_t  len = strlen(text);
    const char *realAnswer = strpbrk(text, splitters);
    const char *result = mempbrk(text, splitters, len);

    if (result != realAnswer) {
        FPRINTF_ERROR(
                "\nFor text=\"%s\" of len = %zu and splitters = \"%s\" gives WRONG return: ",
                text,
                len,
                splitters);

        if (result != nullptr) {
            FPRINTF_ERROR(
                    "pointer to %c with index %ld",
                    *result,
                    result - text);
        } else {
            FPRINTF_ERROR ("nullptr")
        }

        FPRINTF_ERROR("\nMust be: ")

        if (realAnswer != nullptr) {
            FPRINTF_ERROR(
                    "pointer to %c with index %ld",
                    *realAnswer,
                    realAnswer - text);
        } else {
            FPRINTF_ERROR("nullptr");
        }
    }
}
void mempbrkUnitTests () {

    const char *splitters = "_&";

    mempbrkTest("0123&56_", splitters);
    mempbrkTest("", splitters);
    mempbrkTest("_", splitters);
    mempbrkTest("01234&", splitters);
    mempbrkTest("0123", splitters);

}


void countNumberOfNonEmptyLinesTest (
        const char *text,
        const char *splitters,
        size_t      realAnswer
        ) {

    size_t  length = strlen(text);
    size_t result = countNumberOfNonEmptyLines(text, length, splitters);

    if (result != realAnswer) {
        FPRINTF_ERROR(
                "\nFor text=\"%s\" of len = %zu and splitters = \"%s\" gives WRONG return: %zu"
                "\nMust be: %zu",
                text,
                length,
                splitters,
                result,
                realAnswer);
    }
}

void countNumberOfNonEmptyLinesUnitTests() {
    const char *splitters = "_|";
    countNumberOfNonEmptyLinesTest("|", splitters, 0);
    countNumberOfNonEmptyLinesTest("", splitters, 0);
    countNumberOfNonEmptyLinesTest("_|aaa|aaa|", splitters, 2);
    countNumberOfNonEmptyLinesTest("aaaa", splitters, 1);
    countNumberOfNonEmptyLinesTest("a|_a|_aaaa", splitters, 3);
    countNumberOfNonEmptyLinesTest("a|a|a|", splitters, 3);
    countNumberOfNonEmptyLinesTest("a|a|a", splitters, 3);
    countNumberOfNonEmptyLinesTest("|a|a|a", splitters, 3);
    countNumberOfNonEmptyLinesTest("|a|a|a|", splitters, 3);
    countNumberOfNonEmptyLinesTest("a", splitters, 1);
    countNumberOfNonEmptyLinesTest("||||||", splitters, 0);
    countNumberOfNonEmptyLinesTest("a|", splitters, 1);
    countNumberOfNonEmptyLinesTest("a|||", splitters, 1);
    countNumberOfNonEmptyLinesTest("|a", splitters, 1);
    countNumberOfNonEmptyLinesTest("|||a", splitters, 1);

}


void splitTextIntoLinesTest (
        const char *text,
        const char *splitters,
        const Line *answLines){

    size_t length = strlen(text);

    size_t numberOfNonEmptyLines = countNumberOfNonEmptyLines(
            text,
            length,
            splitters);

    Line *lines = (Line *)calloc(numberOfNonEmptyLines, sizeof (*lines));

    size_t res = splitTextIntoLines(text, length, lines, splitters);

    bool error = false;
    if (res != numberOfNonEmptyLines) {
        error = true;
    } else {
        for (int i = 0; i < res; ++i) {
            if (lines[i].beginning != answLines[i].beginning
                || lines[i].length != answLines[i].length) {
                error = true;
            }
        }
    }

    if (error) {
        FPRINTF_ERROR(
        "\nFor text=\"%s\" of len = %zu and splitters = \"%s\" WRONG result:"
        "\nReturn:%zu Expected: %zu",
        text,
        length,
        splitters,
        res,
        numberOfNonEmptyLines);

        for (int i = 0; i < res; ++i) {

            FPRINTF_ERROR ("\n%d: ", i);

            outputLine(lines[i], stderr);

            FPRINTF_ERROR (" len: %zu Expected: ", lines[i].length);

            outputLine(answLines[i], stderr);
            FPRINTF_ERROR (" len: %zu \n", answLines[i].length);
        }
    }

    free(lines);
}

void splitTextIntoLinesUnitTests() {
    const char *splitters = "_|";

    {
        Line *answLines = nullptr;
        splitTextIntoLinesTest("|", splitters, answLines);
        splitTextIntoLinesTest("", splitters, answLines);
        splitTextIntoLinesTest("||||||", splitters, answLines);


    }

    {    countNumberOfNonEmptyLinesTest("||||||", splitters, 0);

        const char *text = "_|234|6789|";
        Line realAnsw[] = {
                {&text[2], 3},
                {&text[6], 4}
        };

        splitTextIntoLinesTest(
                text,
                splitters,
                realAnsw);
    }

    {
        const char *text = "aaaa";
        Line realAnsw[] = {
                {&text[0], 4},
        };

        splitTextIntoLinesTest(
                text,
                splitters,
                realAnsw);
    }

    {
        const char *text = "a";
        Line realAnsw[] = {
                {&text[0], 1},
        };

        splitTextIntoLinesTest(
                text,
                splitters,
                realAnsw);
    }

    {
        const char *text = "0|_3|_6789";
        Line realAnsw[] = {
                {&text[0], 1},

                {&text[3], 1},

                {&text[6], 4}
        };

        splitTextIntoLinesTest(
                text,
                splitters,
                realAnsw);
    }

    {
        const char *text = "0|2|4|";
        Line realAnsw[] = {
                {&text[0], 1},

                {&text[2], 1},

                {&text[4], 1}
        };

        splitTextIntoLinesTest(
                text,
                splitters,
                realAnsw);
    }

    {
        const char *text = "0|2|4";
        Line realAnsw[] = {
                {&text[0], 1},

                {&text[2], 1},

                {&text[4], 1}
        };

        splitTextIntoLinesTest(
                text,
                splitters,
                realAnsw);
    }

    {
        const char *text = "|1|3|5";
        Line realAnsw[] = {
                {&text[1], 1},

                {&text[3], 1},

                {&text[5], 1}
        };

        splitTextIntoLinesTest(
                text,
                splitters,
                realAnsw);
    }

    {
        const char *text = "|1|3|5|";
        Line realAnsw[] = {
                {&text[1], 1},
                {&text[3], 1},
                {&text[5], 1}
        };

        splitTextIntoLinesTest(
                text,
                splitters,
                realAnsw);
    }

}


void compTest(const void *a, const void *b, int answBegEnd, int answEndBeg) {
    int begToEnd = compFromBegToEnd(a, b);
    int endToBeg = compFromEndToBeg(a, b);

    if (answBegEnd == 0 && begToEnd == 0 && answEndBeg == 0 && endToBeg == 0) {
        return;
    }

    if (answBegEnd * begToEnd <= 0 || answEndBeg * endToBeg <= 0) {
        const Line *lineA = (Line *)a;
        const Line *lineB = (Line *)b;

        FPRINTF_ERROR("\nFor \"")
        outputLine(*lineA, stderr);
        FPRINTF_ERROR("\" and \"")
        outputLine(*lineB, stderr);
        FPRINTF_ERROR("\" WRONG return: begToEnd = %d, endToBeg = %d"
                      "\nExpected: begToEnd = %d, endToBeg  =% d (compare only sign!!!)",
                      begToEnd,
                      endToBeg,
                      answBegEnd,
                      answEndBeg);
    }
}

void compUnitTests() {
    {
        Line a = {"123", 3};
        Line b = {"234", 3};
        int begToEnd = -1;
        int endToBeg = -1;

        compTest((void *)&a, (void *)&b, begToEnd, endToBeg);
    }

    {
        Line a = {"1", 1};
        Line b = {"2", 1};
        int begToEnd = -1;
        int endToBeg = -1;

        compTest((void *)&a, (void *)&b, begToEnd, endToBeg);
    }

    {
        Line a = {"1", 1};
        Line b = {"1", 1};
        int begToEnd = 0;
        int endToBeg = 0;

        compTest((void *)&a, (void *)&b, begToEnd, endToBeg);
    }

    {
        Line a = {"1...1", 5};
        Line b = {"11", 2};
        int begToEnd = 0;
        int endToBeg = 0;

        compTest((void *)&a, (void *)&b, begToEnd, endToBeg);
    }

    {
        Line a = {"...1..1...", 10};
        Line b = {"1....1", 6};
        int begToEnd = 0;
        int endToBeg = 0;

        compTest((void *)&a, (void *)&b, begToEnd, endToBeg);
    }

    {
        Line a = {"123", 3};
        Line b = {"12", 2};
        int begToEnd = 1;
        int endToBeg = 1;

        compTest((void *)&a, (void *)&b, begToEnd, endToBeg);
    }


    {
        Line a = {"1235", 3};
        Line b = {"1245", 3};
        int begToEnd = -1;
        int endToBeg = -1;

        compTest((void *)&a, (void *)&b, begToEnd, endToBeg);
    }


}



int main () {
    UNIT_TESTS(mempbrk);
    UNIT_TESTS(countNumberOfNonEmptyLines);
    UNIT_TESTS(splitTextIntoLines);
    UNIT_TESTS(comp);


}
#endif