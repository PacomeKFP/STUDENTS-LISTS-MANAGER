#include <header.h>
void make_a_save(StudentList list, char * save_name){
    delete_save(save_name);//ecraser la sauvegarde si existante (fichier + registre)

    /*La remettre dans le registre*/
    SavesList saves = get_saves_list();
    saves = add_save(saves, save_name);
    update_saves_register(saves);


    //creer la sauvegarde proprement dite ; le fichier en question
    char * filepath = generate_file_path(save_name);
    FILE *file = fopen(filepath, "w");

    if(is_empty(list)){
        fclose(file);
        return;
    }
        
    Student *student =list;
    while(student != NULL){
       

        fprintf(file, "%s %s %s %d %s %s\n", format_for_saving(student->name), format_for_saving(student->surname), 
            student->matricule, student->age, format_for_saving(student->filiere), format_for_saving(student->classe));
        student = student->next;
    }
    fclose(file);
    

}

StudentList load_a_save(char * save_name){
    FILE *file = fopen(generate_file_path(save_name), "r");
    if(feof(file))
        return NULL;
    StudentList result = NULL;
    Student student;
    char name[C_LEN], surname[C_LEN], matricule[ID_LEN], classe[C_LEN], filiere[C_LEN];
    int age;
    while(!feof(file)){
        fscanf(file, "%s %s %s %d %s %s", name, surname, matricule, &age, filiere, classe );
        strcpy(student.name, format_from_saving(name));
        strcpy(student.surname, format_from_saving(surname));
        strcpy(student.matricule, format_from_saving(matricule));
        student.age = age;
        strcpy(student.filiere, format_from_saving(filiere));
        strcpy(student.classe, format_from_saving(classe));

        result = insert_student_in_front(result, student);
    }
    fclose(file);
    return result;
}