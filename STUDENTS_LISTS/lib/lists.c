#include <header.h>

StudentList new_list(void){
    return NULL;
}

Bool is_empty(StudentList list){
    if(list == NULL)
        return true;
    return false;
}

void set_list(StudentList list){
    printf("-----------------------------------------------------------------------------\n");
    if(is_empty(list))
        printf("\n\t\tListe vide: rien a afficher\n");
    int i=0;
    Student *student= list;
    while (student != NULL)
    {
        printf("\t\t [%d] %s  %s  %s  %d ans %s  %s\n",++i, student->name, student->surname, 
            student->matricule, student->age, student->filiere, student->classe);
        student = student->next;
    }
    printf("-----------------------------------------------------------------------------\n");
}
int list_lenght(StudentList list){
    int size=0;
    while (list!=NULL)
    {
        size++;
        list = list -> next;
    }
    return size;
}

StudentList insert_student_in_front(StudentList list, Student student){
    if(find_by_id(list, student.matricule) != -1)
        return list;
    Student *new_student = (Student *) malloc(sizeof(*new_student));
    duplicateStudent(new_student, student);
    new_student->next = NULL;
    if(is_empty(list))
        return new_student;
    new_student->next = list;
    return new_student;
}

StudentList insert_student_at_end(StudentList list, Student student){
    if(find_by_id(list, student.matricule) != -1)
        return list;
    Student *new_student = (Student *) malloc(sizeof(*new_student));
    duplicateStudent(new_student, student);
    new_student->next = NULL;
    if(is_empty(list))
        return new_student;
    Student *last = list;
    while(last->next != NULL )
        last = last->next;
    last->next = new_student;
    return list;
}
StudentList insert_student_at_node(StudentList list, Student student, int node){
    if(find_by_id(list, student.matricule) != -1)
        return list;
    Student *new_student = (Student *) malloc(sizeof(*new_student));
    duplicateStudent(new_student, student);
    new_student->next = NULL;
    if(is_empty(list))
        return new_student;
    if(node == list_lenght(list))
        return insert_student_at_end(list, student);
    if(node<=0)
        return insert_student_in_front(list, student);
    if(node>list_lenght(list))
        return list;

    Student *after = list, *before = list;
    int position = 0;
    while(position != node)
    {
        position++;
        before = after;
        after = after->next;
    }
    before->next = new_student;
    new_student->next = after;
    return list;
}
StudentList remove_first_student(StudentList list){
    if(is_empty(list) || list->next== NULL){
        free(list);
        list = NULL;
        return NULL;
    }
    Student *new_student_list = list->next;
    free(list);
    list = NULL;
    return new_student_list;
}
StudentList remove_last_student(StudentList list){
    if(is_empty(list) || list->next== NULL){
        free(list);
        list = NULL;
        return NULL;
    }
    Student *last_student = list, *before_last_student = list;
    while(last_student -> next != NULL){
        before_last_student = last_student;
        last_student = last_student -> next;
    }
    before_last_student ->next = NULL;
    free(last_student);
    last_student = NULL;
    return list;
}
StudentList remove_student_at_node(StudentList list, int node){
    if(is_empty(list))
        return NULL;
    if(node == 0)
        return remove_first_student(list);
    if(node == list_lenght(list)-1)
        return remove_last_student(list);
    if(node >= list_lenght(list))
        return list;
    int position = 0;
    Student *previous_student = list /*, *next_student = list*/, *student_to_remove= list;
    while(position != node){
        position++;
        previous_student = student_to_remove;
        student_to_remove = student_to_remove -> next;
        //next_student = student_to_remove;
    }
    //next_student = next_student->next;
    //previous_student ->next = next_student; /// le code commentéest une Autre façon de le faire
    previous_student ->next = previous_student -> next -> next;
    free(student_to_remove);
    student_to_remove = NULL;
    return list;
}
StudentList clear_list(StudentList list){//pour vider une liste
    while(list!=NULL)
        list = remove_first_student(list);
    return NULL;
}
int find_by_id(StudentList list, char id[6]){//savoir si un matricule a deja ete utilisé
    if(is_empty(list))
        return -1;
    int position =0;
    while(list != NULL){
        if(strcmp(list->matricule, id) == 0)
            return position;
        list = list -> next;
        position++;
    }
    return -1;
}

void get_students_list(StudentList list, char *filepath){
    //genere le fichier csv de la liste d'etudiants
    FILE *file = fopen(filepath, "w");

    if(is_empty(list)){
        fprintf(file, " La liste est vide ! Ajoutez y des etudiants");
        fclose(file);
        return;
    }

    Student *student =list;
    //fprintf(file, "Nom,Prenom,Matricule,Age\n");
    while(student != NULL){
        fprintf(file, "%s,%s,%s,%d,%s,%s\n", student->name, student->surname, 
            student->matricule, student->age, student->filiere, student->classe);
        student = student->next;
    }
    fclose(file);
}

StudentList find_student(StudentList list, Token token, char *value){
//genere une liste d'etudiants selon un sertain critere (age, matricule, nom, prenom, classee....)
    if(is_empty(list))
        return NULL; 
    
    Student *student = list;
    StudentList result = new_list();
    

    while (student != NULL )
    {
        if(student_have_prop(*student, token, value))
            result = insert_student_at_end(result, *student);
        student = student -> next;
    }
    return result;
}
void save_list(StudentList list, char * list_name){
    if(is_empty(list))
        return;
    FILE *reg = fopen(SAVES_REGISTER, "a");
    char *liste = (char *) calloc(S_LEN, sizeof(char));
    while(!feof(reg)){//s'assurer
        fscanf(reg, "%s", liste);
        if(liste == list_name)
            return;
    }
}