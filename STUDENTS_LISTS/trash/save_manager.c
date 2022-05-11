#include <header.h>
void print_saves(SavesList saves){
    if(saves == NULL){
        printf("\n\t\t\tAucune sauvegarde\n");
        return;
    }
    while(saves != NULL){
        printf("\n\t %s ", saves->name);
        saves = saves->next;
    }
}
SavesList remove_save(SavesList saves, char * save_name){
    if(saves == NULL)
        return NULL;
    if(saves->name==save_name)
        return saves->next;
    
    Save *tmp = saves, *save = saves;
    while(tmp != NULL){
        if(tmp->name == save_name){
            save -> next = tmp->next;
            return saves;
        }
        save = tmp;
        tmp = tmp->next;
    }
    return saves;
}
SavesList add_save(SavesList saves, char * save_name){
    Save *save = (Save *) malloc(sizeof(*save));
    strcpy(save->name , save_name);
    save->next = NULL;
    if(saves == NULL)
        return save;
    save -> next = saves;
    return save;
}

SavesList get_saves_list(){//retourne la liste des sauvegardes
    FILE *saves_reg = fopen(SAVES_REGISTER, "r");
    if(saves_reg == NULL)
        return NULL;
    SavesList saves = NULL;
    int letter;
    if((letter = fgetc(saves_reg)) == ' '){
        fclose(saves_reg);
        return NULL;
    }
    rewind(saves_reg);
    while(!feof(saves_reg)){
        char save[S_LEN];
        fscanf(saves_reg, "%[^\n]%*c", save);
        if(save[0]==' ' || save[0] == '\0')
            return NULL;
        saves = add_save(saves, save);
    }
    fclose(saves_reg);
    return saves;
}

void update_saves_register(SavesList saves){
    if(saves == NULL){
        remove(SAVES_REGISTER);
        FILE *saves_reg = fopen(SAVES_REGISTER, "w");
        fprintf(saves_reg, " ");
        fclose(saves_reg);
        return;
    }
    FILE *saves_reg = fopen(SAVES_REGISTER, "w");
    Save *save = saves;
    while(save != NULL){
        fprintf(saves_reg, "%s", save->name);
        save = save -> next;
    }
    fclose(saves_reg);
}

void delete_save(char * save_name){
    SavesList saves = get_saves_list();
    saves = remove_save(saves, save_name);
    update_saves_register(saves);
    remove(generate_file_path(save_name));
}
 
void make_a_save(StudentList list, char * save_name){
    delete_save(save_name);
    SavesList saves = get_saves_list();
    saves = add_save(saves, save_name);
    update_saves_register(saves);
    //creer la sauvegarde proprement dite ; le fichier en question
    char * filepath = generate_file_path(save_name);
    FILE *file = fopen(filepath, "w");

    if(is_empty(list)){
        fprintf(file, " ");
        fclose(file);
        return;
    }
        
    Student *student =list;
    while(student != NULL){
       /* char *name = format_for_saving(student->name);
        char *surname = format_for_saving(student->surname);
        char *matricule = format_for_saving(student->matricule);
        char *filiere = format_for_saving(student->filiere);
        char *classe = format_for_saving(student->classe);*/

        fprintf(file, "%s %s %s %d %s %s\n", format_for_saving(student->name), format_for_saving(student->surname), 
            format_for_saving(student->matricule), student->age, format_for_saving(student->filiere), format_for_saving(student->classe));

        /*fprintf(file, "%s %s %s %d %s %s\n", name, surname, 
            matricule, student->age, filiere, classe);*/
        student = student->next;
    }
    fclose(file);
}
StudentList load_a_save(char * save_name){
    char * filepath = generate_file_path(save_name);
    FILE * file = fopen(filepath, "w");
    int letter;
    if((letter = fgetc(file)) == ' '){
        fclose(file);
        return NULL;
    }
    rewind(file);
    StudentList list = NULL;
    Student student;
    while(!feof(file)){
        char *name = (char *)malloc(C_LEN*sizeof(char));
        char *surname = (char *)malloc(C_LEN*sizeof(char));
        char *matricule = (char *)malloc(C_LEN*sizeof(char));
        char *filiere = (char *)malloc(C_LEN*sizeof(char));
        char *classe = (char *)malloc(C_LEN*sizeof(char));
        int age = 0;
        
        fscanf(file, "%s %s %s %d %s %s\n", name, surname, 
            matricule, &age, filiere, classe);

        strcpy(student.name, format_from_saving(name));
        strcpy(student.surname, format_from_saving(surname));
        strcpy(student.matricule, format_from_saving(matricule));
        strcpy(student.filiere, format_from_saving(filiere));
        strcpy(student.classe, format_from_saving(classe));
        student.age = age;
        list = insert_student_in_front(list, student);
    }
    fclose(file);
    return list;
}




/********************************************************************************/

//gestion des sauvegardes

// permet de mettre les info d'un etudiant dans un format facilitant leur exploitation
char * format_for_saving(char *value);
char * format_from_saving(char *value);
void save_list(StudentList list, char * list_name); // TDODO
//Sauvegarder une liste d'etudiants


SavesList remove_save(SavesList saves, char * save_name);
SavesList add_save(SavesList saves, char * save_name);
SavesList get_saves_list();//Reccuperer la liste des sauvegardes
void update_saves_register(SavesList saves);
void delete_save(char * save_name);
char * generate_file_path(char *filename);
void print_saves(SavesList saves);

StudentList load_a_save(char * save_name);
void make_a_save(StudentList list, char * save_name);