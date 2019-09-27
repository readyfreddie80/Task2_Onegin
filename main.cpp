#include <assert.h>
#include <iostream>
#include <io.h>


struct Lines {
    char* beggining;
};

int main() {
    char *iputFileName = "Onegin.txt";
    FILE *inputTextFile = fopen(iputFileName, "r");
    assert(inputTextFile != NULL);



    fclose(inputTextFile);
    return 0;
}