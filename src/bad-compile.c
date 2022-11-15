#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This is a compiler for my custom language called Bad!!
// The extension is .bapl
// The language is compiled to C, then to assembly and then to machine code.
// the compiler accepts the following arguments:
// -o <output file> - the output file
// -c - compile only
// -s - compile and assemble
// -S - compile to assembly
// -e - compile, assemble and execute
// -h - print help
// -v - print version
// -d - print debug info
// -i - print info
// -w - print warnings
// -f - file name
//




void getFile(char file){
    FILE *f = fopen(&file, "r");
    if (f == NULL){
        printf("Error opening file %s;\n exiting...", file);
        exit(1);
    }
    else{
        printf("Succes\n");
    }
}



void printHelp() {
    // asici art of an apple
    printf("   ____              _  _  _ \n  |  _ \\            | || || | \n  | |_) |  __ _   __| || || | \n  |  _ <  / _` | / _` || || | \n  | |_) || (_| || (_| ||_||_| \n  |____/  \\__,_| \\__,_|(_)(_)\n");
    printf("Bad!! Compiler v0.1 by @AnAnnoyinGoose\n");
    printf("Usage: bad-compile [options] [file]\n");
    printf("Options:\n");
    printf("  -o <output file> the output file\n");
    printf("  -c compile only\n");
    printf("  -s compile and assemble\n");
    printf("  -S compile to assembly\n");
    printf("  -e compile, assemble and execute\n");
    printf("  -h print help\n");
    printf("  -v print version\n");
    printf("  -d print debug info\n");
    printf("  -i print info\n");
    printf("  -w print warnings\n");
    printf("  -f <filename.bapl || filename> input file\n");
};

int main(int argc, char *argv[]) {
    char filename[1024];
    char output[1024];


    if (argc == 1) {
        printHelp();
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'o':
                    printf("Output file: %s\n", argv[i + 1]);
                    strcpy(output, argv[i + 1]);
                    break;

                case 'c':
                    printf("Compile only\n");
                    break;

                case 's':
                    printf("Compile and assemble\n");
                    break;

                case 'S':
                    printf("Compile to assembly\n");
                    break;

                case 'e':
                    printf("Compile, assemble and execute\n");
                    break;

                case 'h':
                    printHelp();
                    break;

                case 'v':
                    printf("Bad!! Compiler v0.1 by @AnAnnoyinGoose\n");
                    break;

                case 'd':
                    printf("Debug info\n");
                    break;
                    
                case 'i':
                    printf("Info\n");
                    break;

                case 'w':
                    printf("Warnings\n");
                    break;

                case 'f':
                    // if the ends with .bapl print the file name
                    // if it doesnt end with .bapl add .bapl to the end
                    if (strstr(argv[i + 1], ".bapl") != NULL) {
                        printf("File name: %s\n", argv[i + 1]);
                        strcpy(filename, argv[i + 1]);
                        } else {
                        printf("File name: %s.bapl\n", argv[i + 1]);
                        strcpy(filename, argv[i + 1]);
                        }
                    break;
                    

                default:
                    printf("Unknown option: %s\n", argv[i]);
                    break;

            }
        }
    }

    return 0;
}
