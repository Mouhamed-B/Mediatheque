#ifndef _FUNCTIONS_H
#define FUNCTIONS_H
#include "var_types.h"

void quit()
{
	printf("------------A BIENTOT DANS LA MEDIATHEQUE !-----------\n");
	exit(0);
}

char* deblank(char* input)                                         
{
	int i,j;
	char *output=input;
	for (i = 0, j = 0; i<strlen(input); i++,j++)          
	{
		if (input[i]!=' ')                           
			output[j]=input[i];                     
		else
			j--;                                     
	}
	output[j]=0;
	return output;
}

void welcome(char *user)
{
	printf("\n----------------------BIENVENUE DANS LA MEDIATHEQUE----------------\n Donnez votre nom : ");
	scanf("%s", user);
	user=deblank(user);
    printf("Vous pouvez interagir par ligne de commande. Tapez aide pour afficher les commandes disponibles\n");
}

int del(char *iden, FILE *fic, char *fname)
{
	char texte[50];
	int found=0;
	fic=fopen(fname,"r");
	FILE *fic1;
	char fname1[]="..\\docs\\media1.txt";
	while((fgets(texte,50,fic) != NULL))
    	{
    		if(strstr(texte, iden) != NULL){
                found=1;
    			continue;
    		}
    		else
    		{
    			fic1=fopen(fname1,"a+");
	    	    fprintf(fic1, "%s", texte);
	    	    fclose(fic1);

    		}
    	}
    fclose(fic);
    fclose(fic1);
    if (found)
       	system("cd ..\\docs && del media.txt && rename media1.txt media.txt");
    else 
        printf("DEL : Pas de media d'id %s\n", iden);   
}  
void show(FILE *fichier, char *fname)
{
	printf("----LECTURE DU FICHIER------\n");
	char *content=malloc(128*sizeof(char));
	fichier = fopen(fname,"r");
	while(fgets(content,128,fichier)!=NULL)
	{
		printf("%s\n", content);
	}
	free(content);
	fclose(fichier);
}

void aide()
{
	
	printf("  - BYE : Permet de quitter le programme.\n  - ADD : permet d'ajouter des medias\n  - AIDE : montre cette interface\n  - DEL : Permet de supprimer des medias \nNB : Plusieurs autres commandes restent a venir\n");
}

int add(int type, FILE* fichier, char *arg, char *fname)
{
	srand(time(NULL));
	int randn = rand()%101;
    media p;
	printf("---------AJOUT D'UNE RESSOURCE : %s---------\n", arg);
	fflush(stdin);
	printf("donnez le titre : ");
    scanf("%[^\n]", &(p.titre));
    printf("donnez le nom de l'auteur : ");
    fflush(stdin);
    scanf("%[^\n]", &(p.auteur));
    printf("donnez la taille du contenu : ");
    fflush(stdin);
    scanf("%[^\n]", &(p.size));
	if (type==1||type==2)
	{
		strcpy(p.size,deblank(strcat(deblank(p.size),"mn")));
	}
	else if (type==3) 
	{
		strcpy(p.size,deblank(strcat(deblank(p.size),"mo")));
	}
	else if (type==4||type==5)
		strcpy(p.size,deblank(strcat(deblank(p.size),"p")));
	else
	{	
		printf("-mediatheque : Type inconnu\n");
		return INPUT_ERROR;
	}
	p.id=(type*100)+randn;
    fichier=fopen(fname,"a+");
    fprintf(fichier, "%d   %s   %s   %s\n", p.id, p.titre, p.auteur, p.size);
    fclose(fichier);
    printf("ressource ajoutee avec succes ! id : %d\n", p.id);
    return PROCESS_DONE;
}

int convert(char *arg)
{
	if (strcmp(arg,"video")==0)
	{
		return 1;
	}
    else if (strcmp(arg,"dvd")==0)
    {
    	printf("a\n");
    	return 2;
    }
    else if (strcmp(arg,"cd")==0)
    {
        return 3;
    }
    else if (strcmp(arg,"livre")==0)
    {
    	return 4;
    }
    else if (strcmp(arg,"revue")==0)
    {
    	return 5;
    }
    else{ 
    	return 0;
    }
}

int getline(char *commande, FILE* fichier, char *fname)
{
	int j=0;
	char *arg;
	int type;
	scanf("%s",commande);
	commande=deblank(commande);
	char del_help[]="- DEL id : Permet de supprimer le media de matricule id.";
	char add_help[]="- ADD type : permet d'ajouter des medias\nType 1 : video\nType 2 : DVD\nType 3 : CD\nType 4 : livre\nType 5 : revue\n";
	if (strcmp(commande,"add")==0)
	{
		//printf("entrez le type de media a ajouter :\nType 1 : video\nType 2 : DVD\nType 3 : CD\nType 4 : livre\nType 5 : revue\n Votre choix : ");
		//scanf("%d",&j);
		fgets(arg,6,stdin);
		arg=deblank(arg);
		type=convert(arg);
        if (type==0){
        	printf("%s\n", add_help);
        }
        else{
        	add(type, fichier,arg,fname);
        }
	}
	else if(strcmp(commande,"bye")==0)
	{
		fclose(fichier);
	    return END;
	}
	else if (strcmp(commande,"aide")==0)
	{
	    aide();
	}
	else if (strcmp(commande,"del")==0)
	{
		fgets(arg,4,stdin);
		arg=deblank(arg);
		if (strcmp(arg,"\n")==0)
			printf("%s\n", del_help);
		else
			del(arg,fichier,fname);
	}
	else if(strcmp(commande,"show")==0)
	{
		show(fichier,fname);
	}
	else
	{
		printf("-mediatheque : commande inconnue\n");
		return INPUT_ERROR;
	}
    return PROCESS_DONE;
}

#endif