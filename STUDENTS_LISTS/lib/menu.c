#include <header.h>

Student create_student(){
    Student student;
    printf("\n Entrez le nom de l'etudiant :");
    scanf("%*c%[^\n]", student.name);
    printf("\n Entrez le prenom de l'etudiant :");
    scanf("%*c%[^\n]", student.surname);
    printf("\n Entrez le matricule de l'etudiant (6 caracteres) :");
    scanf("%s", student.matricule);
    printf("\n Entrez l'age de l'etudiant :");
    scanf("%d", &(student.age));
    printf("\n Entrez la filiere de l'etudiant :");
    scanf("%*c%[^\n]", student.filiere);
    printf("\n Entrez le classe de l'etudiant :");
    scanf("%*c%[^\n]", student.classe);
    return student;
}
int position(char *msg){
    int node;
    printf("\n%s", msg);
    scanf("%d", &node);
    return node;
}
Token intToken(int n){ //Convert an integet into a Token 
    if(n==0) return name;
    if(n==1) return surname;
    if(n==2) return id;
    if(n==3) return age;
    if(n==4) return filiere;
    if(n==5) return classe;
    return id;//Default

}
char * get_save_name(){
    char *save_name = (char *) calloc(S_LEN, sizeof(char));
    printf("\nListe des sauvegardes existantes \n");
    print_saves(get_saves_list());
    printf("\n\t Quel nom voulez vous donner a votre sauvegarde (pas d'espaces.)?");
    printf("\n\t NB: si ce nom de sauvegarde est deja utilise, la sauvegarde en question sera ecrasee ");
    scanf("%s", save_name);
    
    return save_name;
}
char * get_loaded_save_name(){
    char *save_name = (char *) calloc(S_LEN, sizeof(char));
    printf("\nListe des sauvegardes existantes \n");
    print_saves(get_saves_list());
    printf("\n\t Quelle sauvegarde souhaitez vous charger ? (pas d'espaces.)?");
    printf("\n\t NB: Ceci efface le contenu de la liste courante");
    scanf("%s", save_name);
    
    return save_name;
}