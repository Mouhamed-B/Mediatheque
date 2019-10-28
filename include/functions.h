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

int show(char *id,FILE *fic, char *fname)
{
	char texte[60];
	int found=0;
	fic=fopen(fname,"r");
	while((fgets(texte,60,fic) != NULL))
    	{
    		if(strstr(texte, id) != NULL){
                found++;
    			printf("%s\n", texte);
    			return PROCESS_DONE;
    		}
        }
    printf("DEL : Pas de media d'id %s\n", id);
    return INPUT_ERROR;
    fclose(fic);
}
void search(char *search,FILE *fic, char *fname)
{
	char texte[60];
	int found=0;
	fic=fopen(fname,"r");
	while((fgets(texte,60,fic) != NULL))
    	{
    		if(strstr(texte, search) != NULL){
                found++;
    			printf("%s\n", texte);
    		}
        }
    if (found==0)
    	printf("Aucune occurence a %s\n", search);
    else
        printf("%d occurence a %s\n", found, search);
    fclose(fic);        
}
int del(char *iden, FILE *fic, char *fname)
{
	char texte[50];
	char id[4];
	snprintf(id,sizeof(id),"%s",iden);
	int found=0;
	fic=fopen(fname,"r");
	FILE *fic1;
	char fname1[]="..\\docs\\media1.txt";
	while((fgets(texte,50,fic) != NULL))
    	{
    		if(strstr(texte, iden) != NULL && found==0){
                found++;
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
    if (found>0)
       	system("cd ..\\docs && del media.txt && rename media1.txt media.txt");
    else if (found==0){
    	system("del ..\\docs\\media1.txt");
        printf("DEL : Pas de media d'id %s\n", id);
        }   
}  
void list(FILE *fichier, char *fname)
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

void load(char* arg,char* fname)
{
	/*char texte[60];
	fic=fopen(fname,"w+");
    FILE* fic1=fopen(fname1,"r") 
	while((fgets(texte,60,fic1) != NULL))
    	{
    		fprintf(fic,"%s", texte);
        }
    printf("Chargement terminee\n");*/
    char fname1[30];
    sprintf(fname1,"..\\docs\\%s",arg);
    sprintf(arg,"..\\docs\\%s",fname);
    sprintf(fname,"..\\docs\\%s", fname1);
    sprintf
}

void reset(FILE* fic, char *fname)
{
	char rep;
	do
	{
		printf("Etes vous sur de vouloir tout supprimer ?(o/n)\n");
		fflush(stdin);
		scanf("%c",&rep);
		if (rep=='o')
			fic=fopen(fname,"w+");
            printf("Suppression terminee\n");
            fclose(fic);
    }while(rep!='o'&&rep!='n');

}

void aide()
{

	printf("  - ADD : permet d'ajouter des medias\n  - AIDE : montre cette interface\n  - BYE : Permet de quitter le programme.\n  - DEL : Permet de supprimer des medias \n  - LIST : Affiche tous les medias\n  - SEARCH : Recherche de medias a partir d'un mot cle\n  - SHOW : Affiche les informations d'un media\n  -SAVE : permet de sauvegarder les medias actuellement charges\n");
}

int add(int type, FILE* fichier, char *arg, char *fname)
{
	srand(time(NULL));
	int randn = (rand())%99;
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
	if (type==2||type==3)
		p.id+=randn;
    fichier=fopen(fname,"a+");
    fprintf(fichier, "%d   %s   %s   %s\n", p.id, p.titre, p.auteur, p.size);
    fclose(fichier);
    printf("ressource ajoutee avec succes ! id : %d\n", p.id);
    return PROCESS_DONE;
}

void save(char* arg,char* fname,FILE* fic)
{
	FILE *fic1=fopen(arg,"a+");
	char *content=malloc(128*sizeof(char));
	fic= fopen(fname,"r");
	while(fgets(content,128,fic)!=NULL)
	{
		fprintf(fic1,"%s", content);
	}
	free(content);
	fclose(fic);
	fclose(fic1);
}

int convert(char *arg)
{
	if (strcmp(arg,"video")==0){return 1;}
    else if (strcmp(arg,"DVD")==0)
    {
    	return 2;
    }
    else if (strcmp(arg,"CD")==0)
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
    if (strcmp(fname,"..\\docs\\media.txt")==0){
    	printf("~>");
    }
    else{
    	printf("%s>", fname);
    }
	int j=0;
	char *arg;
	int type;
	fflush(stdin);
	scanf("%s",commande);
	commande=deblank(commande);
	if (strcmp(commande,"add")==0)
	{
		gets(arg);
		arg=deblank(arg);
        type=convert(arg);
        if (type==0){
        	printf("-ADD : Aucun type fourni en parametre\n");
        	printf(ADD_HELP);
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
		gets(arg);
        arg=deblank(arg);
        strcat(arg," ");
		if (strcmp(arg,"\0")==0){
			printf("-DEL : Aucune id fourni en parametre \n");
			printf(DEL_HELP);
		}
		else
			del(arg,fichier,fname);
	}
	else if(strcmp(commande,"list")==0)
	{

		list(fichier,fname);
	}
	else if (strcmp(commande,"search")==0)
	{
		gets(arg);
        arg=deblank(arg);
		if (strcmp(arg,"\0")==0){
			printf("-SEARCH : Aucune id fourni en parametre \n");
			printf(SEARCH_HELP);
		}
		else
		    search(arg,fichier,fname);
	}
	else if (strcmp(commande,"show")==0)
	{
		gets(arg);
        arg=deblank(arg);
		if (strcmp(arg,"\0")==0){
			printf("-SHOW : Aucun parametre fourni\n");
			printf(SHOW_HELP);
		}
		else
		    show(arg,fichier,fname);
	}
	else if(strcmp(commande,"reset")==0)
	{

		reset(fichier,fname);
	}
	else if (strcmp(commande,"load")==0)
	{
		gets(arg);
		arg=deblank(arg);
		if (strcmp(arg,"\0")==0){
			printf("-LOAD : Aucun fichier fourni en parametre \n");
			printf(LOAD_HELP);
		}
		else
		   load(arg,fname);
	}
	else if (strcmp(commande,"save")==0)
	{
		gets(arg);
		arg=deblank(arg);
		if (strcmp(arg,"\0")==0){
			printf("-SAVE : Aucun fichier fourni en parametre \n");
			printf(SAVE_HELP);
		}
		else
		   save(arg,fname,fichier);
	}
	else
	{
		printf("-mediatheque : commande inconnue\n");
		return INPUT_ERROR;
	}
    return PROCESS_DONE;
}

#endif