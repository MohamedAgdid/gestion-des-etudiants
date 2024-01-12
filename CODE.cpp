//GESTION DES ETUDIANTS 
//REALISE PAR : MOHAMED AGDID - ABDELHALIM EL MOUSSAOUI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //pour permetter de fermer le CMD 
#define N_MAX 50 //nombre maximale des etudiants

//structure Etudiant
typedef struct {
    char N_insc[20];
    char nom[50];
    float presence;
    int IDP;
    char matiere[7][20];  
    float note_matiere[7];
    int cmpt; 
} Etudiant;

//stucture Matiere
typedef struct Matiere{
	float note;
	char nomM[10];
	
}Matiere;

// prototypes des fonction
void option2(char id[]);
void affiche_note_Matiere(char id[]);
void affiche_infs_Matiere(char id[]);
void affiche_presence(char id[]);
void trier_notes(char id[]);
void moyenne(char id[]);
void main_fonctionEtud(char id[]);
void quite_ok();
void option(Etudiant Tab[],int Idd);
void main_fonction(Etudiant Tab[],int Idd);
void Ajout_etudiants(Etudiant Tab[],int IDd);
void afficher_etudiants(Etudiant Tab[],int Idd);
void affiche_sans_fichier(Etudiant Tab[], int N,int Idd);
void recherche_etudiant(Etudiant Tab[],int Idd);
void trier_etudiants(Etudiant Tab[],int Idd);
int login();
int validation(char id[],char nom[], float note, int presence, Etudiant Tab[]);
void supprimer_etudiant(Etudiant Tab[], int Idd);
void affiche_note_tout_etudiant(Etudiant Tab[],int Idd);
void moyenne_trie_etudiant(Etudiant Tab[],int id);
void updateEtu(Etudiant Tab[],int Idd);
void modifier_etudiant(Etudiant Tab[],int Idd);


//trier les etudiant selon leurs moyennes genereaux 
void moyenne_trie_etudiant(Etudiant Tab[],int id) {
    FILE *pfile;
    Matiere mat[6];
    int i, j,k=0;
    float some = 0.00, moy[40];
    char IDS[11][40];

   float temp;
   char temp1[11];
    pfile = fopen("Matiere1.txt", "r");
    if (pfile == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        option(Tab,id);
    }

    char ID[11];
    int nbr=0;
    int Idp;
    while (fscanf(pfile, "%s", ID) == 1) {
         some=0.00;
            for (i = 0; i < 6; i++) {
            	
                fscanf(pfile, "%s %f", mat[i].nomM, &mat[i].note);
                some += mat[i].note;
				}
                fscanf(pfile, "%d\n", &Idp);
                
                nbr++;
                moy[k]=some/6;
                
                strcpy(IDS[k],ID);
                k++; 
                
        }
        
    
    fclose(pfile);

 for (i = 0; i < nbr - 1; i++) {
        for (j = 0; j < nbr - i - 1; j++) {
            if (moy[j] < moy[j+1]) {
    
                temp = moy[j];
                strcpy(temp1,IDS[j]);
                moy[j] =moy[j+1];
                strcpy(IDS[j],IDS[j+1]);
                moy[j + 1] = temp;
                strcpy(IDS[j+1],temp1);
            }
        }
    }

     printf("________________________________________________\n");
    printf("|       CNE         |       note generale        |\n");
    printf("|___________________|____________________________|\n");

    for (i = 0; i < nbr; i++) {
        printf("|%-19s|%28.2f|\n", IDS[i], moy[i]);
       printf("|___________________|____________________________|\n");
    }
option(Tab,id);
}


//pour faire les option de l etudiant
void option2(char id[]){
 int y;
 printf("\n Voulez-vous faire une autre option ? 0-non  1-oui:");
 scanf("%d",&y);
 if(y) {
    system("cls");
    main_fonctionEtud(id);
 }
 else quite_ok();
}

//affichage de note d une matiere spesifique a un etudiant 
void affiche_note_Matiere(char id[]) {
    Matiere mat[20];
    int i,idd;
    char ID[11];
    char matiere[20];
    int ok = 0;

    FILE *pfile;
    pfile = fopen("Matiere1.txt", "r");

    if (pfile == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        option2(id);
    }

    printf("Donner le nom de la matiere : ");
    scanf("%s", matiere);

    while (fscanf(pfile, "%s", ID) == 1) {
        if (strcmp(ID, id) == 0) {
            for (i = 0; i < 6; i++) {
                fscanf(pfile, "%s %f", mat[i].nomM, &mat[i].note);
                if (strcmp(matiere, mat[i].nomM) == 0) {
                    printf("____________________________________\n");
                    printf("| %-20s | %-10s |\n", "Matiere", "Note");
                    printf("|______________________|____________|\n");

                    printf("| %-20s | %-10.2f | \n", mat[i].nomM, mat[i].note);
                    printf("|______________________|____________|\n");
                    ok = 1;
                    break;
                }
            }
            fscanf(pfile, "%d\n",&idd);
            if (ok == 0) {
                printf("La matiere n'existe pas!\n");
            }
        }
    }

    fclose(pfile);
    option2(id);
}


// permetter a l etudiant de voir tous les note de chaque matiere
void affiche_infs_Matiere(char id[]) {
    Matiere mat[20];
    int i;
    char ID[20];
    FILE *pfile, *pfile2;
    char mention[15];
    
    pfile = fopen("Matiere1.txt", "r");

    if (pfile == NULL || pfile2 == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        option2(id);
    }

    printf("__________________________________________________________\n");
    printf("| %-20s | %-10s | %-20s |\n", "Matiere", "Note", "Mention");
    printf("|______________________|____________|______________________|\n");
    int idd;
    while (fscanf(pfile, "%s", ID) == 1) {
        if (strcmp(ID, id) == 0) {
            for (i = 0; i < 6; i++) {
                fscanf(pfile, "%s %f", mat[i].nomM, &mat[i].note);

                if (mat[i].note >= 16.00) {
                    strcpy(mention, "Tres bien");
                } else if (mat[i].note >= 14.00) {
                    strcpy(mention, "Bien");
                } else if (mat[i].note >= 12.00) {
                    strcpy(mention, "Assez bien");
                } else if (mat[i].note >= 10.00) {
                    strcpy(mention, "Passable");
                } else {
                    strcpy(mention, "non admis");
                }

                printf("| %-20s | %-10.2f | %-20s | \n", mat[i].nomM, mat[i].note, mention);
                printf("|______________________|____________|______________________|\n");
            }
        }
        fscanf(pfile, "%d\n",&idd);
    }
    fclose(pfile);
    printf("\n");
    affiche_presence(id);
    option2(id);
}

//pour afficher la presence d un etudiant
void affiche_presence(char id[]) {
    int j;
    FILE *pfile;
    Etudiant etudiant;

    pfile = fopen("etudiants.txt", "r");

    if (pfile == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        option2(id);
    }

    printf(" __________\n");
    printf("| Presence |\n");
    printf("|__________|\n");

    while (fscanf(pfile, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, &etudiant.presence,&etudiant.IDP) == 4) {
        if (strcmp(id, etudiant.N_insc) == 0) {
            printf("| %8.2f |\n", etudiant.presence);
        }
    }

    printf("|__________|\n");

    fclose(pfile);
    option2(id);
}


//pour trier les note des etudiant de grand vers le petit
void trier_notes(char id[]) {
    FILE *pfile;
    Matiere mat[6];
    int i, j;

    pfile = fopen("Matiere1.txt", "r");
    if (pfile == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        option2(id);
    }
    int idd;
    char ID[11];
    while (fscanf(pfile, "%s", ID) == 1) {
        if (strcmp(ID, id) == 0) {
            for (i = 0; i < 6; i++) {
                fscanf(pfile, "%s %f", mat[i].nomM, &mat[i].note);
            }
            fscanf(pfile, "%d\n",&idd);
            break;
        }
    }

    fclose(pfile);

    for (i = 0; i < 6 - 1; i++) {
        for (j = 0; j < 6 - i - 1; j++) {
            if (mat[j].note < mat[j + 1].note) {
                Matiere temp = mat[j];
                mat[j] = mat[j + 1];
                mat[j + 1] = temp;
            }
        }
    }

    printf("____________________________________\n");
    printf("| %-20s | %-10s |\n", "Matiere", "Note");
    printf("|______________________|____________|\n");

    for (i = 0; i < 6; i++) {
        printf("| %-20s | %-10.2f | \n", mat[i].nomM, mat[i].note);
        printf("|______________________|____________|\n");
    }

    option2(id);
}

//permetter de calculer le moyenne generale
void moyenne(char id[]) {
    FILE *pfile;
    Matiere mat[6];
    int i, j = 0;
    float some = 0.00, moy;

    pfile = fopen("Matiere1.txt", "r");
    if (pfile == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        option2(id);
    }
    int idd;
    char ID[11];
    while (fscanf(pfile, "%s", ID) == 1) {
        if (strcmp(ID, id) == 0) {
            for (i = 0; i < 6; i++) {
                fscanf(pfile, "%s %f", mat[i].nomM, &mat[i].note);
                j++;
                some += mat[i].note;
            }
            fscanf(pfile, "%d\n",&idd);
            break;
        }
    }
    fclose(pfile);

    char mention[10];
    moy = some / 6;
    if (moy >= 16.0) {
        strcpy(mention, "Tres bien");
    } else if (moy >= 14.0) {
        strcpy(mention, "Bien");
    } else if (moy >= 12.0) {
        strcpy(mention, "Assez bien");
    } else if (moy >= 10.0) {
        strcpy(mention, "Passable");
    } else {
        strcpy(mention, "non admis");
    }

    printf("____________________________________\n");
    printf("| %-20s | %-10s |\n", "Moyene generale", "Mention");
    printf("|______________________|____________|\n");
    printf("| %-20.2f | %-10s |\n", moy, mention);
    printf("|______________________|____________|\n");

    option2(id);
}

//fonction pour savoir le besoin de l utilisateur
void main_fonctionEtud(char id[]){
	
	int x;
    printf(" ________________________________________________\n");
    printf("|___MENU_________________________________________|\n");
    printf("| [1] Afficher la note d une matiere             |\n");
    printf("| [2] Afficher la presence                       |\n");
    printf("| [3] Afficher tout les information              |\n");
    printf("| [4] Trier les notes                            |\n");
    printf("| [5] le moyenne generale                        |\n");
    printf("| [6] Quitter                                    |\n");
    printf("|________________________________________________|\n");

    printf("Taper votre choix : ");
    scanf("%d", &x);
    system("cls");
    switch (x) {
        case 1: affiche_note_Matiere(id); break;
        case 2: affiche_presence(id); break;
        case 3: affiche_infs_Matiere(id); break;
        case 4: trier_notes(id); break;
        case 5: moyenne(id);break;
        case 6: quite_ok(); break;
        default:  break;
    }
}



// fonction de connection  
int login() {
    int e,patr, v = 0;
    char nom_proff[50], mot_De_passe_pr[50], nommp[50], passwprof[50], type;
    FILE *pfile6;
    
    printf(" __________________________________________\n");
    printf("|                 LOGIN                    |\n");
    printf("|__________________________________________|\n");
    printf("|    [1] PROFESSEUR                        |\n");
    printf("|    [2] ETUDIANT                          |\n");
    printf("|__________________________________________|\n");
    printf("\nEnter votre choix: ");
    scanf("%d", &e);
    system("cls");
    if (e==1){
    printf("_____l'utilisation de professeur____\n");
    printf("Entrer votre nom : ");
    scanf("%s", nom_proff);
    printf("Entrer votre mot de passe: ");
    scanf("%s", mot_De_passe_pr);
	}
	if (e==2){
	printf("_____l'utilisation de l'etudiant____\n");
    printf("Entrer votre nom : ");
    scanf("%s", nom_proff);
    printf("Entrer votre mot de passe: ");
    scanf("%s", mot_De_passe_pr);
	}
	
    

    pfile6 = fopen("ETABLISSEMENT1.txt", "r");

    if (pfile6 == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        exit(1);
    }

    while (fscanf(pfile6, "%s %s %c %d\n", nommp, passwprof, &type,&patr) == 4) {

        if (strcmp(nommp, nom_proff) == 0 && strcmp(passwprof, mot_De_passe_pr) == 0) {
            if (type == 'E') {
                v = 1;
            } else {
                v = patr;
            }
            break;
        }
    }

    fclose(pfile6);
    return v;
}


//pour fermer le cmd c est a dire quitter l application
void quite_ok(){
  system("cls");
  
  FreeConsole();
    // Trouvez la fenetre de cmd
  HWND hwnd = FindWindow("ConsoleWindowClass", NULL);
    //envoyer a message pour fermer la fenetre
    PostMessage(hwnd, WM_CLOSE, 0, 0);
}

//pour faire autre option apres un option
void option(Etudiant Tab[],int Idd){
 int y;
 printf("\n Voulez-vous faire une autre option ? 0-non  1-oui:");
 scanf("%d",&y);
 if(y) {
    system("cls");
    main_fonction(Tab,Idd);
 }
 else quite_ok();
}

//fonction des instruction de professeur
void main_fonction(Etudiant Tab[],int Idd){
	int x;
    printf(" ________________________________________________\n");
    printf("|___MENU_________________________________________|\n");
    printf("| [1] Ajoute d'etudiant                          |\n");
    printf("| [2] Afficher etudiants                         |\n");
    printf("| [3] Rechercher un etudiant                     |\n");
    printf("| [4] Modifier etudiant                          |\n");
    printf("| [5] Trier les etudiants                        |\n");
    printf("| [6] Supprimer un etudiant                      |\n");
    printf("| [7] Affichage notes                            |\n");
    printf("| [8] Modifier notes                             |\n");
    printf("| [9] Trie Moyenne generale                      |\n");
    printf("| [10] Quitter                                   |\n");
    printf("|________________________________________________|\n");

    printf("Taper votre choix Monsieur: ");
    scanf("%d", &x);
    system("cls");
    switch (x) {
        case 1: Ajout_etudiants(Tab,Idd); break;
        case 2: afficher_etudiants(Tab,Idd); break;
        case 3 : recherche_etudiant(Tab,Idd); break;
        case 4 : modifier_etudiant(Tab,Idd);break;
        case 5 : trier_etudiants(Tab,Idd); break;
        case 6: supprimer_etudiant(Tab, Idd); break;
        case 7 : affiche_note_tout_etudiant(Tab,Idd); break;
        case 8 : updateEtu(Tab,Idd); break;
        case 9 : moyenne_trie_etudiant(Tab,Idd); break;
        case 10 : quite_ok(); break;
        default:  break;
    }
}

//fonction qui permetter au professeur d ajouter des etudiants
void Ajout_etudiants(Etudiant Tab[],int Idd) {
    FILE *pfile, *etudiant,*pfile2;
    char mot_passe[20];
    
    char matiere[7][20];
    
    pfile = fopen("Matiere1.txt", "w+");
    etudiant = fopen("etudiants.txt", "w+");
    pfile2 = fopen("ETABLISSEMENT1.txt", "w+");

    if (pfile == NULL || etudiant == NULL || pfile2 == NULL) {
        printf("Error opening files.\n");
        option(Tab,Idd);
    }
    int N, i, nbr=6, j,valid;
    printf("Precisez le nombre d'etudiants a ajouter :");
    scanf("%d", &N);

    for (j = 0; j < nbr; j++){
        printf("Indiquez le nom de la matiere %d: ",j+1);
        scanf("%s", matiere[j]);
    }

    printf("___ADD ETUDIANT___\n");
    for (i = 0; i < N; i++) {
        Tab[i].cmpt = nbr;
        printf("_______\n");
        printf("Etudiant %d :\n", i + 1);
        printf("numero d'inscription : ");
        scanf("%s", &Tab[i].N_insc);
        while ((getchar()) != '\n');
        printf("\nle nom :");
        scanf(" %s", Tab[i].nom);
        while ((getchar()) != '\n');
        printf("\nla presence:");
        scanf("%f", &Tab[i].presence);
        while ((getchar()) != '\n');
        printf("\n");
        for (j = 0; j < nbr; j++) {
            strcpy(Tab[i].matiere[j], matiere[j]); 
            printf("Enter note de maitere %s: ", Tab[i].matiere[j]);
            scanf("%f", &Tab[i].note_matiere[j]);
            valid=validation(Tab[i].N_insc,Tab[i].nom, Tab[i].note_matiere[j], Tab[i].presence,Tab);
            if (valid == 3 || valid == 2){
            	printf("Voulez-vous reentrer les informations correctement\n");
                printf("numero d'inscription : ");
                scanf("%s", &Tab[i].N_insc);
                while ((getchar()) != '\n');
                printf("\nle nom :");
                scanf(" %s", Tab[i].nom);
                while ((getchar()) != '\n');
                printf("\nla presence:");
                scanf("%f", &Tab[i].presence);
                while ((getchar()) != '\n');
            	printf("\nEnter note de maitere %s: ", Tab[i].matiere[j]);
                scanf("%f", &Tab[i].note_matiere[j]);
                valid=validation(Tab[i].N_insc,Tab[i].nom, Tab[i].note_matiere[j], Tab[i].presence,Tab);
                
            if (valid == 3 || valid == 2){
                	printf("ERROR!, a neuveux");
                	option(Tab,Idd);
				}
                
			
			} else if (valid == 0 ){
				option(Tab,Idd);
			}
        }

        
        strcpy(mot_passe, Tab[i].N_insc);
        strcat(mot_passe, Tab[i].N_insc);
        char typ='E';
        fprintf(etudiant, "%s %s %f %d\n", Tab[i].N_insc, Tab[i].nom, Tab[i].presence,Idd);
        fprintf(pfile2,"%s %s %c %d\n",Tab[i].nom,mot_passe,typ,Idd);
        fprintf(pfile, "%s ",Tab[i].N_insc);
        for (j = 0; j < Tab[i].cmpt; j++) {
            fprintf(pfile, "%s %.2f ", Tab[i].matiere[j], Tab[i].note_matiere[j]);
        }
        fprintf(pfile,"%d\n",Idd);
        
    }

    fclose(pfile);
    fclose(pfile2);
    fclose(etudiant);
    option(Tab,Idd);
}

//fonction qui permetter l affichage des information des etudiants 
void afficher_etudiants(Etudiant Tab[],int Idd) {
    int j;
    FILE *pfile;
    Etudiant etudiant;
   
    pfile = fopen("etudiants.txt", "r"); 

    if (pfile == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        
    }
    int k=0;
    printf(" _____________________________________________________\n");
    printf("|      N d'insc      |          NOM       | Presence  |\n");
    printf("|____________________|____________________|___________|\n");
    
  
    while (fscanf(pfile, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, &etudiant.presence, &etudiant.IDP) == 4) {
    if (etudiant.IDP == Idd) {
        printf("| %-19s| %-19s| %9.2f |\n", etudiant.N_insc, etudiant.nom, etudiant.presence);
        k++;
    }
    }

    printf("|____________________|____________________|___________|\n");
    printf("\n nombre des etudiants est : %d\n",k);

    fclose(pfile);
    option(Tab,Idd);
}

//fonction qui affiche pour eviter la repetition de tableau
void affiche_sans_fichier(Etudiant Tab[],int N,int Idd){
	int i;
	printf(" _____________________________________________________\n");
    printf("|      N d'insc      |          NOM       | Presence  |\n");
    printf("|____________________|____________________|___________|\n");
    
    for(i=0;i<N;i++){
    	
    printf("| %-19s| %-19s| %9.2f |\n", Tab[i].N_insc, Tab[i].nom, Tab[i].presence);
    
    }
    printf("|____________________|____________________|___________|\n");
    option(Tab,Idd);
}

//fonction pour chercher sur un etudiants
void recherche_etudiant(Etudiant Tab[],int Idd) {
    char N_INSC_rech[20], nom_rech[20];
    int OK = 0, choix;
    FILE *pfile;
    Etudiant etudiant;
    pfile = fopen("etudiants.txt", "r"); 

    if (pfile == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        option(Tab,Idd);
    }

    printf("\n________________rechercher Par_____________\n");
    printf(" __________________________________________\n");
    printf("|    [1] Par N d'insc                      |\n");
    printf("|    [2] par Nom                           |\n");
    printf("|__________________________________________|\n");
    printf("Enter votre choix: ");
    scanf("%d", &choix);
    system("cls");
    switch (choix) {
        case 1: printf("Entrez le numero d'inscription a rechercher : ");
                scanf("%s", N_INSC_rech);
                while (fscanf(pfile, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, &etudiant.presence,&etudiant.IDP) == 4) {
            
                    if ((strcmp(etudiant.N_insc, N_INSC_rech) == 0) && (etudiant.IDP==Idd)) {
                        printf(" _____________________________________________________\n");
                        printf("|      N d'insc      |          NOM       | Presence  |\n");
                        printf("|____________________|____________________|___________|\n");
                        printf("| %-19s| %-19s| %9.2f |\n", etudiant.N_insc, etudiant.nom, etudiant.presence);
                        printf("|____________________|____________________|___________|\n");
                        OK = 1;
                        fclose(pfile);
                        break;
                    }
                }
                if (OK == 0) {
                    printf("etudiant non trouve.\n");
                }
                break;  

        case 2: printf("Entrez le nom a rechercher : ");
                scanf("%s", nom_rech);
                while (fscanf(pfile, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, &etudiant.presence,&etudiant.IDP) == 4) {
                    if ((strcmp(etudiant.nom, nom_rech) == 0)&& (etudiant.IDP==Idd)) {
                       printf(" _____________________________________________________\n");
                       printf("|      N d'insc      |          NOM       | Presence  |\n");
                       printf("|____________________|____________________|___________|\n");
                       printf("| %-19s| %-19s| %9.2f |\n", etudiant.N_insc, etudiant.nom, etudiant.presence);
                        printf("|____________________|____________________|___________|\n");
                        OK = 1;
                        fclose(pfile);
                        break;
                    }
                }
                if (OK == 0) {
                    printf("etudiant non trouve.\n");
                }
                break;  

        default: printf("enter un nombre exacte");
                 break;
    }
    
    option(Tab,Idd);
}

//permetter de trier les etudiants par rapport au nom et par rapport au CNE		         
void trier_etudiants(Etudiant Tab[], int Idd) {
    int i, j, K, choix;
    Etudiant temp;
    char N_insc[11], nom[20];
    float presence;
    int IDP;

    FILE *etudiantFile = fopen("etudiants.txt", "r");

    if (etudiantFile == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        option(Tab, Idd);
    }

    K = 0;

    while (fscanf(etudiantFile, "%s %s %f %d\n", N_insc, nom, &presence, &IDP) == 4) {
        if (IDP == Idd) {
            strcpy(Tab[K].N_insc, N_insc);
            strcpy(Tab[K].nom, nom);
            Tab[K].presence = presence;
            Tab[K].IDP = IDP;
            K++;
        }
    }

    fclose(etudiantFile);

    printf("\n________________Trier Par________________\n");
    printf(" __________________________________________\n");
    printf("|    [1] N d'insc                          |\n");
    printf("|    [2] Nom                               |\n");
    printf("|__________________________________________|\n");
    printf("\nEnter votre choix: ");
    scanf("%d", &choix);
    system("cls");

    switch (choix) {
        case 1:
            for (i = 0; i < K - 1; i++) {
                for (j = 0; j < K - i - 1; j++) {
                    if (strcmp(Tab[j].N_insc, Tab[j + 1].N_insc) > 0) {
                        temp = Tab[j];
                        Tab[j] = Tab[j + 1];
                        Tab[j + 1] = temp;
                    }
                }
            }
            printf("\nLes etudiants ont ete tries avec succes.\n");
            affiche_sans_fichier(Tab, K, Idd);
            break;

        case 2:
            for (i = 0; i < K - 1; i++) {
                for (j = 0; j < K - i - 1; j++) {
                    if (strcmp(Tab[j].nom, Tab[j + 1].nom) > 0) {
                        temp = Tab[j];
                        Tab[j] = Tab[j + 1];
                        Tab[j + 1] = temp;
                    }
                }
            }
            printf("\nLes etudiants ont ete tries avec succes.\n");
            affiche_sans_fichier(Tab, K, Idd);
            break;

        default:
            printf("Entrez un nombre valide.\n");
            break;
    }
    option(Tab, Idd);
}


//fonction qui permetter la modification des informations generales d un etudiant 
void modifier_etudiant(Etudiant Tab[],int Idd) {
    char N_INSC_modif[20];
    int OK = 0;
    FILE *pfile, *test;
    Etudiant etudiant;

    pfile = fopen("etudiants.txt", "r"); 

    test = fopen("test.txt", "w");  

    if (pfile == NULL || test == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        option(Tab,Idd);
    }

    printf("Entrez le numero d'inscription de l'etudiant a modifier : ");
    scanf("%s", N_INSC_modif);

    while (fscanf(pfile, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, &etudiant.presence,&etudiant.IDP) == 4) {
    	if (Idd==etudiant.IDP){
        if (strcmp(etudiant.N_insc, N_INSC_modif) == 0) {
            printf("Entrez les nouvelles informations pour l'etudiant\n");
            printf("nom : ");
            scanf("%s", etudiant.nom);
            printf("presence : ");
            scanf("%f", &etudiant.presence);
            fprintf(test, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, etudiant.presence,etudiant.IDP);
            OK = 1;
        } else {
            fprintf(test, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, etudiant.presence, etudiant.IDP);
        }
    }
    else{
    	fprintf(test, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, etudiant.presence, etudiant.IDP);
	}
    }

    fclose(pfile);
    fclose(test);

    if (OK) {
        remove("etudiants.txt");
        rename("test.txt", "etudiants.txt");
        printf("etudiant modifie avec succes.\n");
    } else {
        printf("etudiant non trouve.\n");
    }
    afficher_etudiants(Tab,Idd);
    option(Tab,Idd);
}

// fonction qui permetter la modification des notes des etudiants
void updateEtu(Etudiant Tab[], int Idd) {
    FILE *pfile7, *temp;
    Matiere mat[6];
    char id[11], ID[11];
    int idpr, i, ok = 0;
    float NoteN;

    printf("donner CNE de l'etudiants que vous vouler modifier : ");
    scanf("%s", id);

    pfile7 = fopen("Matiere1.txt", "r");
    temp = fopen("temp55.txt", "w");
    if (pfile7 == NULL || temp == NULL) {
        printf("ERREUR");
    }

    while (fscanf(pfile7, "%s", ID) == 1) {
        for (i = 0; i < 6; i++) {
            fscanf(pfile7, "%s %f", mat[i].nomM, &mat[i].note);
        }
        fscanf(pfile7, "%d", &idpr);

        if (strcmp(id, ID) == 0 && idpr == Idd) {
            fprintf(temp, "%s", id);
            for (i = 0; i < 6; i++) {
                printf("donner la note de %s : ", mat[i].nomM);
                scanf("%f", &NoteN);
                fprintf(temp, " %s %f ", mat[i].nomM, NoteN);
            }
            fprintf(temp, "%d\n", Idd);
            ok = 1;
        } else {
            fprintf(temp, "%s", ID);
            for (i = 0; i < 6; i++) {
                fprintf(temp, " %s %f ", mat[i].nomM, mat[i].note);
            }
            fprintf(temp, "%d\n", Idd);
        }
    }

    fclose(pfile7);
    fclose(temp);
    if (ok == 1) {
        remove("Matiere1.txt");
        rename("temp55.txt", "Matiere1.txt");
        affiche_note_tout_etudiant(Tab, Idd);
    } else {
        printf("Etudiant non trouve");
    }
}


//permetter d afficher les notes des etudiants au proffesseur responsable de ce classe 
void affiche_note_tout_etudiant(Etudiant Tab[],int Idd){
    int i,j;
	char ID[11];
    int IDP;
    FILE *pfile,*pfile1;
    Matiere mat[7];
    pfile1= fopen ("etudiants.txt","r");
    pfile = fopen("Matiere1.txt", "r");
    
    if (pfile == NULL) {
        printf("Error dans l ouverture de fichier.\n");
        
    }

    printf(" __________________________________________________________________________\n");
    printf("|      N d'insc      |         nom        |        matiere     |    note   |\n");
    printf("|____________________|____________________|____________________|___________|\n");
    
    char Id1[21],nomE[21],nom_Etudiant[21];
    int n;
    
    while (fscanf(pfile, "%s", ID) == 1) {
    	while(fscanf(pfile1,"%s %s %d\n",Id1,nomE,&n)){
    		if (strcmp(Id1,ID)==0){
    			strcpy(nom_Etudiant,nomE);
    			break;
			}
		}
        for (i = 0; i < 6; i++) {
            fscanf(pfile, "%s %f", mat[i].nomM, &mat[i].note);
        }
        fscanf(pfile, "%d\n", &IDP);
        
        if (IDP == Idd){
        for ( i = 0; i < 6; i++) {
    
    	if (i == 3) {
        printf("| %-19s| %-19s| %-19s| %9.2f |\n", ID, nom_Etudiant ,mat[i].nomM, mat[i].note);
    } else {
        printf("| %-19s| %-19s| %-19s| %9.2f |\n", "", "",mat[i].nomM, mat[i].note);
    }
    	
	}
	printf("|__________________________________________________________________________|\n");
}
}

    
    fclose(pfile1);
    fclose(pfile);
    option(Tab,Idd);
}
	

//permetter la veriffication et la validation des information

int validation(char id[],char nom[], float note, int presence, Etudiant Tab[]) {
    int compt, i = 0;

    if (strlen(id) == 10) {
        i++;
        if (note <= 20.00 && note >= 0.00) {
            i++;
            if (presence < 356 && presence > 0) {
                i++;
            } else {
                return 3;
            }
        } else {
            return 3;
        }
    } else {
        return 3;
    }

    if (i == 3) {
    	system("cls");
        printf("  _________________________VALIDATION_________________________\n");
        printf(" | ID       : %-35s \n", id);
        printf(" |____________________________________________________________|\n");
        printf(" | Nom : %-35s \n", nom);
        printf(" |____________________________________________________________|\n");
        printf(" | Presence : %-35d \n", presence);
        printf(" |____________________________________________________________|\n");
        printf(" | Note     : %-35.2f \n", note);
        printf(" |____________________________________________________________|\n");
        printf("Valider les informations? (Oui: 1, Non: 2, Exit: 0) \n");
        scanf("%d", &compt);
        system("cls");
    }
    return compt;
}



//permetter de supprimer un etudiant donne
void supprimer_etudiant(Etudiant Tab[], int Idd) {
    char N_INSC_suppr[20];
    int OK = 0;
    FILE *pfile, *temp1;
    Etudiant etudiant;

    pfile = fopen("etudiants.txt", "r"); 
    temp1 = fopen("temp1.txt", "w"); 

    if (pfile == NULL || temp1 == NULL) {
        printf("Error\n");
        option(Tab, Idd);
    }
    
    
    printf("Entrez le numero d'inscription de l'etudiant a supprimer : ");
    scanf("%s", N_INSC_suppr);

    while (fscanf(pfile, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, &etudiant.presence, &etudiant.IDP) == 4) {
        if (Idd == etudiant.IDP) {
            if (strcmp(etudiant.N_insc, N_INSC_suppr) == 0) {
                printf("etudiant supprime avec succes.\n");
                OK = 1;
            } else {
                fprintf(temp1, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, etudiant.presence, etudiant.IDP);
            }
        } else {
            fprintf(temp1, "%s %s %f %d\n", etudiant.N_insc, etudiant.nom, etudiant.presence, etudiant.IDP);
        }
    }

    fclose(pfile);
    fclose(temp1);

    if (OK==1) {
        remove("etudiants.txt");
        rename("temp1.txt", "etudiants.txt");
    } else {
        printf("etudiant non trouve.\n");
    }
    
    afficher_etudiants(Tab,Idd);
    option(Tab, Idd);
}

 
//fonction main permeter d acceder soit a linterface de proffesseur ou bien de l etudiant
int main() {
    Etudiant Tab[N_MAX];
    int type;
    char ID[11];
    type = login();
    if (type != 1 && type !=0){
    	system("cls");
    	main_fonction(Tab,type);
	}
	else if (type==1){
		
		char ID[11];
 	printf("Entez votre CNE: ");
	scanf("%s",ID);
	
    	main_fonctionEtud(ID);
    	
	}
	else{
		
		printf("MOTE DE PASSE OU NOM INCORRECT");
		Sleep(4000); //4 sec puis quitte
		quite_ok();
			
	}
    
    return 0;
}
// _____________________________la fin de code source______________________________

