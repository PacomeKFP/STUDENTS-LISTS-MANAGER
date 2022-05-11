#ifndef HEADER_H
#define HEADER_H

//Inclusion des bibliotheques
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"


typedef enum{//implementation du type boolen
    false, true
}Bool;

typedef enum{
    name, surname, id, age, filiere, classe
}Token;

typedef struct Student{
    //Definition de la structure d'une liste et d'un etudiant
    char name[C_LEN];
    char surname[C_LEN];
    int age;
    char matricule[ID_LEN];
    char filiere[C_LEN];
    char classe[C_LEN];

    struct Student * next;
}Student, *StudentList;

typedef struct Save //*Type _sauvegarde
{
    char name[S_LEN];
    struct Save *next;
}Save, *SavesList;

Student N_S(char *name, char *surname, char *id, int age);//*utilisé en mode dev


/*==================fonctions et procedures utilitaires===============================*/
StudentList new_list(void);//Initialiser une liste
Bool is_empty(StudentList list);//Verifier si une liste est vide
void set_list(StudentList list);//Afficher une liste
void duplicateStudent(Student *new_student, Student old_student);//Duplicquer les info d'un etudiant
int list_lenght(StudentList list); //retourne la taille d'une liste
//Recherche d'un etudiant : retourne sa position (noeud) ou il est ou alors -1;
int find_by_id(StudentList list, char id[6]);//recherche à partir du matricule
//Pour ajouter un etudiant il faudra etre sûr que son matricule n'est pas encore utilisé

/*=====================================================================================*/


/*====================Ajout d'etudiants à une liste===============================*/
StudentList insert_student_in_front(StudentList list, Student student);//en tete
StudentList insert_student_at_end(StudentList list, Student student);//en queue
StudentList insert_student_at_node(StudentList list, Student student, int node);//n'importe où
/*================================================================================*/


/*====================Suppression d'etudiants à la liste==========================*/
StudentList remove_first_student(StudentList list);//en tete
StudentList remove_last_student(StudentList list);//en queue
StudentList remove_student_at_node(StudentList list, int node);//n'importe où
StudentList clear_list(StudentList list);//Vider la liste
/*================================================================================*/


/*==============RECHERCHE D'ELEMENTS D'UNE LISTE SELON UN CRITERE===================*/

Bool student_have_prop(Student student,Token token,char * value);
//permet de savoir si un etudiant a une donnée particuliere dans ses info  
StudentList find_student(StudentList list, Token token, char * value);
//retourne la liste des etudiants ayant une valuer comune pour un token

/*================================================================================*/



/*============================Gestion des données=================================*/

//Genereration de liste d'etudiant sous forme de fichier exploitable avec excel ou autre 
void get_students_list(StudentList list, char *filepath);

char * generate_file_path(char *filename);//Genere le chemin d'acces à un fichier

/*================================================================================*/



/*=====================SAUVEGARDES ET RESAURATION DES DONNEES============================*/

        /*----------------------------UTILITAIRES----------------------------*/
        void file_treatment(char*filename);//créé un fichier temporaire bien formaté
        char * format_for_saving(char *value);
        char * format_from_saving(char *value);
                //.............Sur les listes de sauvegardes........//
        void print_saves(SavesList saves);//Afficher une liste de sauvegardes
        SavesList add_save(SavesList saves, char * save_name);//Ajouter un elem à une liste de saves
        SavesList remove_save(SavesList saves, char * save_name);//retirer un elem d'une liste de saves
                
                //...Sur le registre de sauvegardes et les fichiers....//
        SavesList get_saves_list();//retourne la liste des sauvegardes
        void update_saves_register(SavesList saves);//mettre le registre à jour
        void delete_save(char * save_name);//Effacer une save (registre + fichier)

        /*-------------------------------------------------------------------*/


        /*----------------------------SAUVEGARDE DE LISTE----------------------------*/
        void make_a_save(StudentList list, char *save_name);
        /*---------------------------------------------------------------------------*/

        /*----------------------------CHARGEMENT DE LISTE----------------------------*/
        StudentList load_a_save(char * save_name);
        /*---------------------------------------------------------------------------*/

/*=====================================================================================*/






/*=====================OUTILS POUR LE MENU D'APPLICATION==============================*/
Student create_student();// Permet de creer un nouvel etudiant
int position(char *msg); // La paresse seulement !!!
Token intToken(int n);   // Transforme un entier en Token()clé de recherche 
char * get_save_name();
char * get_loaded_save_name();
#endif // !HEADER_H

