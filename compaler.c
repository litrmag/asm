#include <stdio.h>
#include <string.h>
#include "vm.h"

bool WritingToFile (FILE* code_file, char* func, int num_args, int num);

int main ()
{
    FILE* input_file = fopen ("code.asm", "r");
    if (!input_file) {
        printf ("Error: file not found\n");
        return 1;
    }
    FILE* code_file = fopen ("code.txt", "w");
    if (!code_file) {
        printf ("Error: file not opened\n");
        return 1;
    }

    char buffer[400] = {};
    char func[10] = {};
    int num = 0;
    while ((fgets (buffer, sizeof(buffer), input_file)) != NULL)
    {
        int num_args = sscanf (buffer, "%s %d", func, &num);
        if (WritingToFile (code_file, func, num_args, num))
            break;
    }
}

bool WritingToFile (FILE* code_file, char* func, int num_args, int num)
{
    if (strcmp ("HLT", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments\n");
            return 1;
        } else {
            fprintf (code_file, "%d", HLT);
        }
        }
    if (strcmp ("PUSH", func) == 0) {
        if (num_args != 2) {
            printf ("Error in the number of arguments\n");
            return 1;
        } else {
            fprintf (code_file, "%d %d\n", PUSH, num);
        }
    }
    if (strcmp ("ADD", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments\n");
            return 1;
        } else {
            fprintf (code_file, "%d\n", ADD);
        }
    }
    if (strcmp ("SUB", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments\n");
            return 1;
        } else {
            fprintf (code_file, "%d\n", SUB);
        }
    }
    if (strcmp ("MUL", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments\n");
            return 1;
        } else {
            fprintf (code_file, "%d\n", MUL);
        }
    }
    if (strcmp ("DIV", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments\n");
            return 1;
        } else {
            fprintf (code_file, "%d\n", DIV);
        }
    }
    if (strcmp ("OUT", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments\n");
            return 1;
        } else {
            fprintf (code_file, "%d\n", OUT);
        }
    }
    return 0;
}
