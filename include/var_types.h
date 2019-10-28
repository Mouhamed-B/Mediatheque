#ifndef VAR_TYPES_H
#define VAR_TYPES_H
#define N 15
#define END 0
#define PROCESS_DONE 1
#define INPUT_ERROR 2
#define MAX 100
#define MIN 0
#define ADD_HELP "- ADD type : permet d'ajouter des medias\nTypes pris en charges : video | DVD | CD | livre |revue\n"
#define DEL_HELP "- DEL id : Permet de supprimer le media de matricule id.\n"
#define SEARCH_HELP "- SEARCH word : Recherche le mot(titre, auteur etc) fourni en parametre\n"
#define SHOW_HELP "- SHOW id : Permet d'afficher les informations detaillees sur une ressource de matricule id\n"
#define LOAD_HELP "-LOAD fichier : permet de charger un fichier contenant des ressources disponibles\n"
#define SAVE_HELP "-SAVE : permet a l'utilisateur de sauvegarder les donnees actuellement dans l'outil dans le fichier dont le nom est specifie en parametre\n"

typedef struct media media;
struct media
{
	int id;
	char titre[N];
	char auteur[N];
	char size[6]; // nombre de minutes, pages ou Megaoctets

};

//Fin du fichier
#endif