// standard libs
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// This is a compiler for my custom language called Bad!!
// The extension is .bapl
// The language is compiled to C, then to assembly and then to machine code.
// the compiler accepts the following arguments:
// -o <output file> - the output file
// -c - compile only
// -e - execute the program
// -S - compile to assembly
// -f - file name
//

// global variables
char *output_file = NULL;
char *input_file = NULL;
bool compile_only = false;
bool execute = false;
bool compile_to_assembly = false;



void printHelp() {
    // asici art of "Bad!!"
    printf("   ____              _  _  _ \n  |  _ \\            | || || | \n  | |_) |  __ _   __| || || | \n  |  _ <  / _` | / _` || || | \n  | |_) || (_| || (_| ||_||_| \n  |____/  \\__,_| \\__,_|(_)(_)\n");
    printf("Bad!! Compiler v0.1 by @AnAnnoyinGoose\n");
    printf("Usage: bad-compile [options] [file]\n");
    printf("Options:\n");
    printf("  -o <output file> the output file\n");
    printf("  -c compile only\n");
    printf("  -e execute the program\n");
    printf("  -S compile to assembly\n");
    printf("  -f <filename.bapl || filename> input file\n");
};

// get input file contents
char *readFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s", filename);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(length);
    if (buffer) {
        fread(buffer, 1, length, file);
    }
    fclose(file);
    return buffer;
}

// compile to C
void compileToC(char *input, char *output, bool execute) {
//    a variable is declared with the keyword "var" the type is specified after the variable name (eg var::int x) the value is specified after the type (eg var::int x < 5) the value can be a string, int, float, bool or char (eg var::string x < "Hello World")
//    a function is declared with the keyword "fnc" the return type is specified after the function name (eg fnc::int main) the arguments are specified after the return type (eg fnc::int main (int x, int y)) the body is specified after the arguments (eg fnc::int main (int x, int y) { return x + y; })
//    a loop is declared with the keyword "loop" the type is specified after (eg loop::for) the condition is specified after the type (eg loop::for (int i < 0; i < 10; i++)) the body is specified after the condition (eg loop::for (int i < 0; i < 10; i++) { console << i; })
//    a conditional is declared with the keyword "if" the condition is specified after the keyword (eg if (x < 5) { console << "x is less than 5"; }) the body is specified after the condition (eg if (x < 5) { console << "x is less than 5"; })
//    a conditional is declared with the keyword "else" the body is specified after the keyword (eg else { console << "x is greater than 5"; })
//    a conditional is declared with the keyword "elif" the condition is specified after the keyword (eg elif (x == 5) { console << "x is equal to 5"; }) the body is specified after the condition (eg elif (x == 5) { console << "x is equal to 5"; })

    // create output file
    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Error: Could not open file %s", output_file);
        exit(1);
    }

    // write to output file
    fprintf(output, "#include <stdio.h> \n");
    fprintf(output, "#include <string.h> \n");
    fprintf(output, "#include <stdbool.h> \n");
    fprintf(output, "#include <stdlib.h> \n");
    fprintf(output, "int main() { \n");

    // rewrite he code to C
    char *line = strtok(input, " ");
    while (line != NULL) {
        if (strcmp(line, "var::int") == 0) {
            fprintf(output, "int ");
        } else if (strcmp(line, "var::float") == 0) {
            fprintf(output, "float ");
        } else if (strcmp(line, "var::bool") == 0) {
            fprintf(output, "bool ");
        } else if (strcmp(line, "var::char") == 0) {
            fprintf(output, "char ");
        } else if (strcmp(line, "var::string") == 0) {
            fprintf(output, "char *");
        } else if (strcmp(line, "fnc::int") == 0) {
            fprintf(output, "int ");
        } else if (strcmp(line, "fnc::float") == 0) {
            fprintf(output, "float ");
        } else if (strcmp(line, "fnc::bool") == 0) {
            fprintf(output, "bool ");
        } else if (strcmp(line, "fnc::char") == 0) {
            fprintf(output, "char ");
        } else if (strcmp(line, "fnc::string") == 0) {
            fprintf(output, "char *");
        } else if (strcmp(line, "loop::for") == 0) {
            fprintf(output, "for (");
        } else if (strcmp(line, "loop::while") == 0) {
            fprintf(output, "while (");
        } else if (strcmp(line, "loop::do") == 0) {
            fprintf(output, "do {");
        } else if (strcmp(line, "if") == 0) {
            fprintf(output, "if (");
        } else if (strcmp(line, "else") == 0) {
            fprintf(output, "else {");
        } else if (strcmp(line, "elif") == 0) {
            fprintf(output, "else if (");
        } else if (strcmp(line, "console <<") == 0) {
            fprintf(output, "printf(");
        } else if (strcmp(line, "return") == 0) {
            fprintf(output, "return ");
        } else if (strcmp(line, "true") == 0) {
            fprintf(output, "true");
        } else if (strcmp(line, "false") == 0) {
            fprintf(output, "false");
        }
        line = strtok(NULL, " ");
    }

    // close output file
    fprintf(output, "}");
    fclose(output);

    // compile to assembly
    char *command = malloc(strlen("gcc -o ") + strlen(output_file) + strlen(" ") + strlen(output_file) + strlen(".c"));
    strcpy(command, "gcc -o ");
    strcat(command, output_file);
    strcat(command, " ");
    strcat(command, output_file);
    strcat(command, ".c");
    system(command);

    if (execute) {
        // execute assembly
        char *command = malloc(strlen("./") + strlen(output_file));
        strcpy(command, "./");
        strcat(command, output_file);
        system(command);
    }

    // delete C file
    char *command = malloc(strlen("rm ") + strlen(output_file) + strlen(".c"));
    strcpy(command, "rm ");
    strcat(command, output_file);
    strcat(command, ".c");
    system(command);
}

int main(int argc, char *argv[]) {
    // check if there are any arguments
    if (argc == 1) {
        printHelp();
        return 0;
    } else{
        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], "-o") == 0) {
                printf("output file: %s \n", argv[i+1]);
                output_file = argv[i+1];
            } else if (strcmp(argv[i], "-c") == 0) {
                printf("compile only \n");
                compile_only = true;
            } else if (strcmp(argv[i], "-e") == 0) {
                printf("execute \n");
                execute = true;
            } else if (strcmp(argv[i], "-S") == 0) {
                printf("compile to assembly \n");
                compile_to_assembly = true;
            } else if (strcmp(argv[i], "-f") == 0) {
                // check if the file is a .bapl file
                if (strstr(argv[i+1], ".bapl") != NULL) {
                    printf("input file: %s \n", argv[i+1]);
                    input_file = argv[i+1];
                } else {
                    printf("input file: %s.bapl \n", argv[i+1]);
                    input_file = strcat(argv[i+1], ".bapl");
                }
            } else if (strcmp(argv[i], "-h") == 0) {
                printHelp();
            }
        }
    }

    // check if the input file is set
    if (input_file == NULL) {
        printf("Error: No input file specified");
        exit(1);
    } else {
        // read the input file
        char *input_file_contents = readFile(input_file);
        printf("input file contents: %s \n", input_file_contents);
    }






    return 0;
}
