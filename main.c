#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

//color
#define COLOR_RED "\033[0;31m"
#define COLOR_WHITE "\033[0;37m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"

typedef enum {false, true} boolean;

boolean isRunning;
double lastnb = 1.0;

//s'execute au debut du program
void Launch()
{
	printf(COLOR_GREEN);
	printf("\n\n");
	printf("----- bienvenu.e dans super calcuator ! -----\n");
	printf("tapez \033[0;35mhelp \033[0;32mpour afficher la liste des commandes\n");
	printf("\n\n");
	printf(COLOR_WHITE);
}

//------ Commands ------

void Exit()
{
	printf(COLOR_RED);
	printf("exiting...\n");
	isRunning = false;
	printf(COLOR_WHITE);
}

void Help()
{
	printf(COLOR_GREEN);
	printf("Liste des commandes:\n");
	printf("  \033[0;35mhelp                  \033[0;32m:		affiche la liste des commandes\n");
	printf("  \033[0;35mexit                  \033[0;32m:		quite le program\n");
	printf("  \033[0;35mcalc \033[0;33m[n1] [sign] [n2] \033[0;32m:		permet de faire une operation\n");
	printf("  \033[0;35mlastnb                \033[0;32m:		affiche le resulat de la derniere operation. \n");
	printf("                                        peux aussi etre utiliser dans calc (expl: \033[0;35mcalc \033[0;33mlastnb * 5\033[0;32m).");
	printf("\n\n");
	printf(COLOR_WHITE);
}

double Calc(char * num1, char * num2, char* sign)
{
	char *eptr;

	double n1;
	double n2;

	n1 = strtod(num1, &eptr);
	n2 = strtod(num2, &eptr);

	if (strcmp(sign, "+") == 0)
	{
		return (n1 + n2);
	}
	if (strcmp(sign, "-") == 0)
	{
		return (n1 - n2);
	}
	if (strcmp(sign, "*") == 0)
	{
		return (n1 * n2);
	}
	if (strcmp(sign, "/") == 0)
	{
		return (n1 / n2);
	}

	return 1;
}

//------ commande handler
void CommandHandler()
{
	char input[MAX_LENGTH];
	char input_copy[MAX_LENGTH];

	scanf(" %99[0-9a-zA-Z+---/-* ]", input);

	strcpy(input_copy, input);

	if (strlen(input) == 0)
	{
		return;
	}

	int i = 0;
	char * entire_base_cmd = strtok(input, " ");

	char *baseCmds[3];

	while(entire_base_cmd != NULL)
	{
		baseCmds[i++] = entire_base_cmd;
		entire_base_cmd = strtok(NULL, " ");
	}

	char * base_cmd = baseCmds[0];

	if (strcmp(base_cmd, "exit") == 0)
	{
		Exit();
	}
	else if (strcmp(base_cmd, "help") == 0)
	{
		Help();
	}
	else if (strcmp(base_cmd, "calc") == 0)
	{
		i = 0;
		
		char * entire_cmd = strtok(input_copy, " ");

		char *cmds[4];

		while(entire_cmd != NULL)
		{
			cmds[i++] = entire_cmd;
			entire_cmd = strtok(NULL, " ");
		}
	
		char * cmd = cmds[0];
		char * num1 = cmds[1];
		char * sign = cmds[2];
		char * num2 = cmds[3];

		char num1_copy[50];
		char num2_copy[50];
		char sign_copy[2];

		strcpy(sign_copy, sign);
		strcpy(num1_copy, num1);
		strcpy(num2_copy, num2);

		if (strcmp(num1_copy, "lastnb") == 0)
		{
			sprintf(num1_copy,"%f", lastnb);
		}
		if (strcmp(num2_copy, "lastnb") == 0)
		{
			sprintf(num2_copy,"%f", lastnb);
		}

		double result = Calc(num1_copy, num2_copy, sign_copy);
		lastnb = result;

		printf(COLOR_GREEN);
		printf("result: ");
		printf("%lf\n", result);
		printf(COLOR_WHITE);
	}
	else if (strcmp(base_cmd, "lastnb") == 0)
	{
		printf(COLOR_GREEN);
		printf("%lf\n", lastnb);
		printf(COLOR_WHITE);
	}
	else
	{
		printf(COLOR_RED);
		printf("commande incconue: %s\n", base_cmd);
		printf(COLOR_WHITE);
	}	
}

int main()
{
	isRunning = true;

	Launch();

	while(isRunning == true)
	{
		CommandHandler();
	}

	return 0;
}