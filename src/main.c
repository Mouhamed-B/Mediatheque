#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "..\include\functions.h"

int main(int argc, char const *argv[])
{
	FILE* fichier=NULL;
	char user[15];
	char commande[20];
	int process;
	welcome(user);
	char fname[30]="..\\docs\\media.txt";
	do
	{
		printf("%s@mediatheque:", user);
		process=getline(commande, fichier, fname);
	} while (process!=END);
	quit();
}
