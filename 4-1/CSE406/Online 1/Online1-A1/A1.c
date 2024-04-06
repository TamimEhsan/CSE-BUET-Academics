#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARAM_1 30
#define PARAM_2 50
#define PARAM_3 400

#define DARK_WEB_SECRET 134774920
#define DARK_WEB_SECRET_NO 4
#define PASS 5004

typedef struct
{
	char pass[PARAM_1];
} User;

typedef struct
{
	void (*execute)(char *, char *);
} Service;

void inside_dark_web(int secret, int secret_no)
{
	printf("We're dealing with the dark web dealers! But they want the secret password for the dealing!\n");
	if (secret ==  DARK_WEB_SECRET && secret_no == DARK_WEB_SECRET_NO)
	{
		printf("It's time to put the CSE FEST 2023 website down!\n");
		system("sudo rm -r CSEFESTSERVER");
		printf("Successfully down\n");
	}
	else
	{
		printf("You fraud!\n");
	}
}

void get_service(char *user, char *pass)
{
	char buffer[PARAM_1];
	strcpy(buffer, pass);
	printf("Service running on!\n");
}

void check_password(char *user, char *pass)
{
	int pass_int = atoi(pass);
	if (pass_int == PASS)
	{
		get_service(user, pass);
	}
	else
	{
		printf("Wrong password!\n");
	}
}

void execute(char *name, char *pass)
{
	User *user;
	Service *service;
	char username[PARAM_2];
	strcpy(username, name);

	service = malloc(sizeof(Service));
	user = malloc(sizeof(User));

	service->execute = check_password;
	strcpy(user->pass, pass);

	service->execute(username, user->pass);
}

int main()
{
	printf("In main function\n");
	char username[PARAM_3];
	char password[PARAM_3];
	FILE *username_file, *password_file;

	username_file = fopen("username", "r");
	password_file = fopen("password", "r");
	fread(username, sizeof(char), PARAM_3, username_file);
	fread(password, sizeof(char), PARAM_3, password_file);
	char dummy[PARAM_3*4];
	execute(username, password);

	return 0;
}

