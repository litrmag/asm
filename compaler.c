#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include "vm.h"

char* ReadFromFile (const char* input_file_name);
char** LineCounter (char* buffer, size_t* num_lines);
void ExpandSize (char*** program, size_t* capacity);
bool WritingToFile (FILE* code_file, char* func, int num_args, int num);

int main ()
{
    size_t num_lines = 0;
    char* buffer = ReadFromFile ("code.asm");
    char** program = LineCounter (buffer, &num_lines);

    assert (buffer);
    assert (program);

    FILE* code_file = fopen ("code.txt", "w");
    if (!code_file)
    {
        printf ("Error: file not opened\n");
        return 1;
    }

    char func[10] = {};
    int num = 0;
    for (int line_index = 0; line_index < num_lines; line_index++)
    {
        int num_args = sscanf (program[line_index], "%s %d", func, &num);
        if(num_args == -1)
            continue;
        if (WritingToFile (code_file, func, num_args, num))
            break;
    }
}

char* ReadFromFile (const char* input_file_name)
{
    assert (input_file_name);

    struct stat file_stat;
    stat (input_file_name, &file_stat);
    char* buffer = (char*)calloc(file_stat.st_size + 1, sizeof(char));
    if (!buffer) {
        printf ("Error in allocating memory for writing strings to the buffer\n");
        return NULL;
    }

    FILE* file = fopen (input_file_name, "r");
    if (!file) {
        printf ("Error while opening file for reading\n");
        return NULL;
    }
    size_t read_char = fread (buffer, sizeof(char), file_stat.st_size, file);
    if (read_char != file_stat.st_size) {
        printf ("Error in reading the file\n");
        return NULL;
    }
    if (fclose (file) == EOF) {
        printf ("Error in closing the file\n");
    }

    return buffer;
}

char** LineCounter (char* buffer, size_t* num_lines)
{
    assert (buffer);

    size_t capacity = 10;
    char** program = (char**)calloc(capacity, sizeof(char*));

    program[0] = buffer;
    *num_lines = 1;
    for (size_t num_char = 0; buffer[num_char] != '\0'; num_char++)
    {
        if (buffer[num_char] == '\n') {
            buffer[num_char] = '\0';
            if (*num_lines >= capacity)
                ExpandSize (&program, &capacity);
            program[*num_lines] = &buffer[num_char+1];
            (*num_lines)++;
        }
    }
    return program;
}

void ExpandSize (char*** program, size_t* capacity)
{
    size_t new_capacity = 2 * (*capacity);
    char** new_ptr = (char**)realloc(program, new_capacity * sizeof(char*));
    if(!new_ptr){
        printf("Error while realloc:(\n");
        free(program);
        abort();
    }
    *program = new_ptr;
}

bool WritingToFile (FILE* code_file, char* func, int num_args, int num)
{
    if (strcmp ("HLT", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments: %d\n", __LINE__);
            return 1;
        } else {
            fprintf (code_file, "%d", HLT);
        }
        }
    if (strcmp ("PUSH", func) == 0) {
        if (num_args != 2) {
            printf ("Error in the number of arguments: %d\n", __LINE__);

            return 1;
        } else {
            fprintf (code_file, "%d %d\n", PUSH, num);
        }
    }
    if (strcmp ("ADD", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments: %d\n", __LINE__);

            return 1;
        } else {
            fprintf (code_file, "%d\n", ADD);
        }
    }
    if (strcmp ("SUB", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments: %d\n", __LINE__);

            return 1;
        } else {
            fprintf (code_file, "%d\n", SUB);
        }
    }
    if (strcmp ("MUL", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments: %d\n", __LINE__);

            return 1;
        } else {
            fprintf (code_file, "%d\n", MUL);
        }
    }
    if (strcmp ("DIV", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments: %d\n", __LINE__);

            return 1;
        } else {
            fprintf (code_file, "%d\n", DIV);
        }
    }
    if (strcmp ("OUT", func) == 0) {
        if (num_args != 1) {
            printf ("Error in the number of arguments: %d\n", __LINE__);

            return 1;
        } else {
            fprintf (code_file, "%d\n", OUT);
        }
    }
    return 0;
}
