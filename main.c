#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// This is a compiler for my custom language called Bad!!
// The extension is .bapl
// The language is compiled to C, then to assembly and then to machine code.
// the compiler accepts the following arguments:
// bapl statements are written in one line

// -o <output file> - the output file
// -c - compile only
// -e - execute the program
// -S - compile to assembly
// -f - file name
// -h - help


char str[1024];
char *output_file = NULL;
char *input_file = NULL;
bool compile_only = false;
bool execute = false;
bool compile_to_assembly = false;
bool print_file = false;


struct variable {
    char *name;
    char *type;
    char *value;
};




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
    printf("  -i print the file content\n");
}


// compiler
int compiler (char *input_file, char *output_file, bool compile_only, bool execute, bool compile_to_assembly, bool print_file) {
    printf("Compiling to C...\n");
    FILE *input = fopen(input_file, "r"); // open the input file
    FILE *output = fopen(output_file, "w"); // open the output file
    char *line = NULL;
    size_t len = 0; // length of the line
    ssize_t read; // read the line
    if (input == NULL) {
        printf("Error: I File not found\n");
        return 1;
    }
    if (output == NULL) {
        printf("Error: O File not found\n");
        return 1;
    }
    fprintf(output, "#include <stdio.h>\n#include <string.h>\n#include <stdbool.h>\n#include <stdlib.h>\n");
    fprintf(output,"void reverse(char s[])\n{\nint i, j;\nchar c;\nfor (i = 0, j = strlen(s)-1; i<j; i++, j--) {\nc = s[i];\ns[i] = s[j];\ns[j] = c;\n}\n}\n");
    fprintf(output, " void itoa(int n, char s[]){\nint i, sign;\nif ((sign = n) < 0)\nn = -n;\ni = 0;\ndo {\ns[i++] = n % 10 + \'0\';\n} while ((n /= 10) > 0);\nif (sign < 0)\ns[i++] = \'-\';\ns[i] = '\\0';\nreverse(s);}\n\n"); // itoa function
    fprintf(output, "\nchar str[1024];\nint main(int argc, char *argv[]) {\n");

    while ((read = getline(&line, &len, input)) != -1) {  // read the input file line by line
        if (line[0] == '#') { // if the line starts with #, it is a comment
            continue;
        }
        // write the current line into an array
        char *current_line = line;
        // split the array into multiple arrays if ; is found
        char *token = strtok(current_line, ";");
        while (token != NULL) {
            // if the token is a variable declaration
            // var:::int::x:<2>;  <- this is a variable declaration (write int x = 2)
            if (strstr(token, "var:::") != NULL) {
                // get the type
                char *type = strtok(token, ":::");
                type = strtok(NULL, "::");
                // get the name
                char *name = strtok(NULL, "::");
                // get the value
                char *value = strtok(NULL, "::");
                // remove the < and > from the value
                value = strtok(value, "<");
                value = strtok(value, ">");

                // remove all unneeded spaces
                type = strtok(type, " ");
                name = strtok(name, " ");


                // write the variable declaration
                fprintf(output, "   %s %s = %s;\n", type, name, value);

            }
            // if the token is a variable redeclaration
            // &::<x>::<2>;  <- this is a variable redeclaration (write x = 2)
            else if (strstr(token, "&::") != NULL) {
                // get the name
                char *name = strtok(token, "::");
                name = strtok(NULL, "::");
                // get the value
                char *value = strtok(NULL, "::");
                // remove the < and > from the value ant name
                value = strtok(value, "<");
                value = strtok(value, ">");
                name = strtok(name, "<");
                name = strtok(name, ">");

                // remove all unneeded spaces
                name = strtok(name, " ");

                // write the variable redeclaration
                fprintf(output, "   %s = %s;\n", name, value);
            }
            // if the token is a print statement
            // csn<:<"Hello World!">;  <- this is a print statement (write puts("Hello World!"))
            // or
            // csn<:<&<x>>;  <- this is a print statement (write puts(x))
            else if (strstr(token, "csn<:") != NULL) {
                // get the value
                char *value = strtok(token, "<:");
                value = strtok(NULL, "<:");
                // remove the < and > from the value
                value = strtok(value, "<");
                value = strtok(value, ">");

                // remove all unneeded spaces
                value = strtok(value, " ");

                // if the value is a variable
                if (strstr(value, "&") != NULL) {
                for (int i = 0; i < strlen(value); i++) {
                    if (value[i] == '&') {
                        value[i] = ' ';
                        value[i+1] = ' ';
                    }
                }
                // remove all unneeded spaces and > from the value
                value = strtok(value, " ");
                value = strtok(value, ">");
                // write the print statement
                // if the variable is an int
                if (strstr(value, "int") != NULL) {
                    fprintf(output, "   itoa(%s, str);\n", value);
                    fprintf(output, "   puts(str);\n");
                }
                }
                // if the value is a string
                else {
                    // write the print statement
                    fprintf(output, "   puts(\"%s\");\n", value);
                }
            }
            // if the token is a stdin statement
            // csn>:&<x> <- this is a input statement
            else if (strstr(token, "csn>:") != NULL) {
                // get the value
                char *value = strtok(token, ">:");
                value = strtok(NULL, ">:");
                // remove the &, < and > from the value
                value = strtok(value, "&");
                value = strtok(value, "<");
                value = strtok(value, ">");


                // remove all unneeded spaces
                value = strtok(value, " ");

                // write the stdin statement
                fprintf(output, "   scanf(\"%%d\", &%s);\n", value);
            }
            // if the token is a if statement




            printf("%s;\n", token); // debug

            token = strtok(NULL, ";");
        }
   }
    fprintf(output, "return 0;\n}");
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
            } else if (strcmp(argv[i], "-i") == 0) {
                print_file = true;
            }
        }
    }


// compile to C
    compiler(input_file, output_file, compile_only, execute, compile_to_assembly, print_file);
    // compile the C code
    if (compile_only) {
        system("gcc -o output " "test.c");
    }
    // compile to assembly
    if (compile_to_assembly) {
        system("gcc -S -o output.s " "test.c");
    }
    // run the C code
    if (execute) {
        system("clear");
        system("./output");
    }
    // print the C code
    if (print_file) {
        system("cat output.c");
    }
    return 0;
}
