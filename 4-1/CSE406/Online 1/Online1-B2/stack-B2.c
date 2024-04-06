#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


#define PARAM_1 <PARAM_1>
#define PARAM_2 <PARAM_2>
#define PARAM_3 <PARAM_3> 

char str[PARAM_3];

typedef struct {
        char name[PARAM_2];
        char pass[PARAM_1];
} Info;

typedef struct {
        void (*fp1)();
        void (*fp2)();
} Callback;

void hack() {
        execve("/bin/sh", NULL, NULL);
        printf("Sorry, hack failed!!");
}

void testandtry(int off) {
        char buffer[PARAM_2];
        printf("Welcome to trial session...\n");
        strcpy(buffer, &str[off]);
}

void random_print() {
        printf("Normally Executed!\n");
}

void overflow_in_action() {
        Info* data;
        Callback* ptr;
        
        data = malloc(sizeof(Info));
        ptr = malloc(sizeof(Callback));

        strcpy(data->name, str);
        ptr->fp2 = random_print;

        strcpy(data->pass, str);
        ptr->fp2();
}

int main() {
        printf("In main function\n");
        FILE *badfile;

        badfile = fopen("badfile", "r");
        fread(str, sizeof(char), PARAM_3, badfile);
        fclose(badfile);
        overflow_in_action();

        return 0;
}

