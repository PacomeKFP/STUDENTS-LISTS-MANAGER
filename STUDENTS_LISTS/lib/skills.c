#include <header.h>
void file_treatment(char*filename){
    FILE *file = fopen(filename, "r");
    FILE *tmp = fopen("data/tmp.txt", "w");
    int letter;
    while ((letter=fgetc(file)) != EOF )
        if((char)letter != ' ')
            fputc(letter, tmp);
    fclose(tmp);
    fclose(file);
}Student N_S(char *name, char *surname, char *id, int age){
    Student student;
    strcpy(student.name, name);
    strcpy(student.surname, surname);
    strcpy(student.matricule, id);
    strcpy(student.filiere, "Ingenieur");
    strcpy(student.classe, "MSP1 - B1");
    student.age = age;

    return student;
}
void duplicateStudent(Student *new_student, Student old_student)
{
    strcpy(new_student->name, old_student.name);
    strcpy(new_student->surname, old_student.surname);
    strcpy(new_student->matricule, strupr(old_student.matricule));
    strcpy(new_student->filiere, strupr(old_student.filiere));
    strcpy(new_student->classe, strupr(old_student.classe));

    new_student->age = old_student.age;
}

Bool student_have_prop(Student student,Token token,char * value)
{
    switch (token)
    {
        case name:
            if(strcmp(student.name, value) == 0)
                return true;
            return false;
        case surname:
            if(strcmp(student.surname, value) == 0)
                return true;
            return false;
        case id:
            if(strcmp(student.matricule, value) == 0)
                return true;
            return false;
        case age:
            if(student.age == (int)value)
                return true;
            return false;

        case filiere:
            if(strcmp(student.filiere, value) == 0)
                return true;
            return false;
        case classe:
            if(strcmp(student.classe, value) == 0)
                return true;
            return false;
        default:
            break;
    }
    return false;
}


char * format_for_saving(char *value){
    char *result =(char*)calloc(C_LEN,  sizeof(char));
    
    //On remplacera les espaces par des _ (underscore)
    
    for(int i=0; i<strlen(value); i++){
        if(value[i] == ' ')
            result[i] = '_';
        else
            result[i] = value[i];
    }
    return result;
}
char * format_from_saving(char *value){
    char *result =(char*)calloc(C_LEN,  sizeof(char));
    
    //On remplacera les espaces par des _ (underscore)
    for(int i=0; i<strlen(value); i++){
        if(value[i] == '_')
            result[i] = ' ';
        else
            result[i] = value[i];
    }
    return result;
}
char * generate_file_path(char *filename){
    char *path = (char *)malloc((strlen(filename)+20)*sizeof(char));
    char a[256];
    strcpy(a, filename);
    char *p = strcat(a, SAVES_EXTENSION);
    strcpy(path,SAVES_FOLDER);
    
    strcpy(path, strcat(path, p));
    return path;
}

