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

// syntax of bapl is as follows:
// 2. every statement ends with a semicolon
// 3. every variable is declared with the keyword "var"
// 4. every variable is assigned a type with :: (double colon)
// 5. every variable is assigned a value with =
// 7. eg var::int x = 5; <- this is a variable declaration of int x = 5 in C
// 8. print statements are written with the keyword "csn"
// 9. eg csn << "Hello World"; <- this is a print statement in C
// 10. if statements are written with the keyword "if"
// 11. eg if::param(x == 5)::output(csn << "x is 5"); <- this is an if statement in C
// 12. while statements are written with the keyword "while"
// 13. eg while::param(x < 5)::output(csn << "x is less than 5"); <- this is a while statement in C
// 14. for statements are written with the keyword "for"
// 15. eg for::param(x = 0; x < 5; x++)::output(csn << "x is less than 5"); <- this is a for statement in C
// 16. functions are written with the keyword "func"
// 17. eg func::return_type(int)::name(main)::param(int argc, char** argv)::output(csn << "Hello World";) <- this is a function in C
// 18. functions can be called with the keyword "call"
// 19. eg call::name(main)::param(argc, argv); <- this is a function call in C

// 20. the following are the types of variables:
// 21. int - integer (32 bit)
// 22. char - character (single character)
// 23. double - double (64 bit)
// 24. float - float (32 bit)
// 25. bool - boolean (true or false)
// 26. string - string (array of characters)
// 27. void - void (nothing)

// 28, Example program:
// var::int x = 5;
// var::int y = 10;
// var::int z = x + y;
// csn << "x + y = " << z;

// Output: x + y = 15

// 29. Example program2:
// var::int x = 5;
// var::int y = 10;
// if::param(x>y)::output(csn << "x is greater than y");
// else::output(csn << "x is less than y");

// Output: x is less than y

// 30. Example program3:
// var::int x = 5;
// var::int y = 10;
// while::param(x < y)::output(csn << "x is less than y");
// x++;

// Output: x is less than y ( 5 times )



char *output_file = NULL;
char *input_file = NULL;
bool compile_only = false;
bool execute = false;
bool compile_to_assembly = false;
bool print_file = false;



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
//    rewrite the bapl code to C
    printf("Compiling to C...\n");
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    if (input == NULL) {
        printf("Error: I File not found\n");
        return 1;
    }
    if (output == NULL) {
        printf("Error: O File not found\n");
        return 1;
    }
    fprintf(output,"#include <stdio.h>\n#include <string.h>\n#include <stdbool.h>\n#include <stdlib.h>\nint main(int argc, char** argv) {\n");
    while ((read = getline(&line, &len, input)) != -1) {
        printf("Retrieved line of length %zu: %s \n", read, line);
        // csn << "Hello World";
        if (strstr(line, "csn <<") != NULL) {
            char *line2 = strstr(line, "csn <<");
            line2 = line2 + 6;
            // with a forloop read the line and replace << with nothing and replace " with nothing and remove all abundant spaces
            for (int i = 0; i < strlen(line2); i++) {
                if (line2[i] == '<' && line2[i+1] == '<') {
                    line2[i] = ' ';
                    line2[i+1] = ' ';
                }
                if (line2[i] == '"') {
                    line2[i] = ' ';
                }
                if (line2[i] == ' ' && line2[i+1] == ' ') {
                    line2[i] = ' ';
                }
                if (line2[i] == ';') {
                    line2[i] = ' ';
                }
            }
            fprintf(output, "printf(\"%s\");\n", line2);
        }
    }
    fprintf(output,"return 0;\n}");
    fclose(input);
    fclose(output);
    if (print_file) {
        printf("Printing the file...\n");
        FILE *output = fopen(output_file, "r");
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, output)) != -1) {
            printf("Retrieved line of length %zu: %s \n", read, line);
        }
        fclose(output);
    }
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
