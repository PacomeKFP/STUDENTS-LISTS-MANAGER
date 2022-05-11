#include <header.h> 
// gcc src/main.c lib/*.c -o bin/app -I include /*En mode developpement*/
// gcc src/main.c lib/*.c -o app -I include /*En mode production*/
char last_saves[C_LEN];

int main(){

    printf("\n\n\n\tCe programme ecrit permet de mettre en application \
    \n\tles outils developpes dans le cadre des listes chainee d'etudiants d'une ecole\
     \n\n\t\t\t AUTHOR : KENGALI FEGUE PACOME, ENSPY MSP1-B1 21P027\n"); 



    StudentList list = new_list(); 
    
    Student pacome, samuel, jerome, allan;
    pacome = N_S("Kengali", "Pacome", "21p027", 18);
    samuel = N_S("Kemdje Kemdje", "Samuel", "21P227", 14);
    allan = N_S("Kameni Nsangou", "Allan", "21P307", 19);
    jerome = N_S("Ikito", "jerome Anael", "21P187", 18);
    list = insert_student_in_front(list, pacome);
    list = insert_student_at_end(list, samuel);
    list = insert_student_at_node(list, jerome, 1);
    list = insert_student_at_node(list, allan, 2);
    
    int choice = 0;
    char *filename =(char*) calloc(S_LEN, sizeof(char));
    int key; char value[256]; int tmp;
    do{
        printf("\nMenu du programme, veuillez faire un choix !");
        printf("\n 1- Consulter la liste courante");
        printf("\n 2- Ajouter un etudiant a la liste");
        printf("\n 3- Retirer un etudiant de la liste");
        printf("\n 4- Faire une recherche dans la liste");
        printf("\n 5- Creer une sauvegarder de liste");
        printf("\n 6- Charger une sauvegarde de liste, sauvegarder la liste courante avant.");
        printf("\n 7- Exporter la liste");
        printf("\n 8- Quitter le programme ");
        printf("\nQue voulez vous faire ?");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                printf(" \n Affichage des ressources de la liste :");
                set_list(list);
                break;
            case 2:
                list = insert_student_at_node(list, create_student(), position("Ou voulez vous faire l'ajout ?: entrez l'indice du noeud"));
                break;
            case 3:
                list = remove_student_at_node(list, position("Ou voulez vous faire la suppression ?: entrez l'indice du noeud"));
                break;
            case 4:
                
                printf("\nPour faire une recherche, entrez la cle puis la valeur\nLes cles possibles 0- name, 1-surname, 2-id, 3-age, 4-filiere, 5-classe\n");
                scanf("%d", &key);
                StudentList result = new_list();
                if(key == 3){
                    scanf("%d", &tmp);
                    result = find_student(list, age, (char *)tmp);
                }else{
                    scanf("%*c%[^\n]", value);
                    result = find_student(list, (Token)intToken(key), value);
                }
                printf("\n\t Resultats de la recherche :\n");
                set_list(result);
                printf("\n Que souhaitez vous faire de ces resultats ?:");
                printf("\n\t 1- Exporter,  2- Faire une sauvegarde, ou rien (autre chiffre)");
                scanf("%d", &tmp);
                switch(tmp){
                    case 1:
                        
                        printf("\n Entrer un nom pour le fichier d'exportation");
                        scanf("%s", filename);
                        get_students_list(result, generate_file_path(filename));
                        printf("Fichie en registre : %s", generate_file_path(filename));
                        break;
                    case 2:
                        make_a_save(result, get_save_name());
                        printf("\nSave made successfully\n");
                        break;
                    default:
                        printf("\nVous avez decide de ne rien en faire de special !");
                        break;
                }
                break;
            case 5:
                make_a_save(list, get_save_name());
                printf("\nSave made successfully\n");
                break;
            case 6:
                list = clear_list(list);
                list = load_a_save(get_loaded_save_name());
                
                break;
            case 7:
                printf("\n Entrer un nom pour le fichier d'exportation");
                scanf("%s", filename);
                get_students_list(list, generate_file_path(filename));
                printf("Fichier enregistre : %s", generate_file_path(filename));
                break;
            default:
                break;
        }
    }while(choice != 8);

    return 1;
}