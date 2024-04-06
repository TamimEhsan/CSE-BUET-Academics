#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define PARAM_1 <PARAM_1>
#define PARAM_2 <PARAM_2>
#define PARAM_3 <PARAM_3> 

int magic;
char *argv[2];
char str[PARAM_3];

typedef struct {
    char name[PARAM_2];
    char pass[PARAM_1];
    int val;
} Info;

typedef struct {
    void (*fp1)();
    void (*fp2)();
} Callback;

void hack() {
    argv[0] = "/bin/sh";
    argv[1] = NULL;
    execve(argv[0], argv, NULL);
    printf("Sorry, hack failed again!!");
}

void fun() {
    magic ? magic++ : setuid(0);
    // printf("Welcome to unnecessary session...\n");
}

void degrade(int v) {
    magic = ++v;
    nothing(v);
}

void more_fun(int v) {
    while(--v) {
        degrade(v);
    }
}

void testandtry(int off) {
    char buffer[PARAM_1];
    FILE *badfile;
    badfile = fopen("badfile", "r");
    fseek(badfile, PARAM_3, SEEK_SET);
    fread(str, sizeof(char), PARAM_3, badfile);
    fclose(badfile);
    strcpy(buffer, str);
    printf("sorry, hack failed!!\n");
}

void nothing(int n) {
    printf("What do you think? \n");
    fun();
}

void random_print() {
    if(!magic) {
        testandtry(0);
    }
    printf("Normally Executed!\n");
}

void overflow_in_action() {
    Info* data;
    Callback* ptr;

    data = malloc(sizeof(Info));
    ptr = malloc(sizeof(Callback));

    magic = PARAM_3;
    data->val = magic;

    ptr->fp1 = nothing;
    strcpy(data->name, &str[PARAM_2]);
    ptr->fp2 = random_print;
    strcpy(data->pass, &str[PARAM_1]);
    ptr->fp1(data->val);
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

