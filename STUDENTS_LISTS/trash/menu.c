#include <header.h>



printf("\n\n\n\tCe programme ecrit permet de mettre en application \
    \n\tles outils developpes dans le cadre des listes chainee d'etudiants d'une ecole\
     \n\n\t\t\t AUTHOR : KENGALI FEGUE PACOME, ENSPY MSP1-B1 21P027\n");
    StudentList list = new_list();//Declaration et initialisation d'une liste

    //Creation de quelques profils d'etutiants
    Student pacome, samuel, jerome, allan;
    pacome = N_S("Kengali", "Pacome", "21p027", 18);
    samuel = N_S("Kemdje Kemdje", "Samuel", "21P227", 14);
    allan = N_S("Kameni Nsangou", "Allan", "21P307", 19);
    jerome = N_S("Ikito", "jerome Anael", "21P187", 18);

    //insertion de quelques etudiants dans la liste
    list = insert_student_in_front(list, pacome);
    list = insert_student_at_end(list, samuel);
    list = insert_student_at_node(list, jerome, 1);
    list = insert_student_at_node(list, allan, 2);
    /*  certains etudiants(pacome, samuel, jerome) seront insérés plusieurs 
        fois mais n'auront qu'un seul nom sur la liste 
    */

    printf("\n\tAffichage de la liste des etudiants :\n");
    set_list(list);//Affichage de la liste d'etudiants

    //Exportons notre liste vers un fichier csv

    get_students_list(list, "data/student_list.csv");
    
    printf("\n\t Generons et affichons la liste des etudiants ayant 18 ans\n");
    StudentList t = find_student(list, age, (char *) 18);//Liste des etudiant ayant 18 ans
    set_list(t);//On affiche la liste en question