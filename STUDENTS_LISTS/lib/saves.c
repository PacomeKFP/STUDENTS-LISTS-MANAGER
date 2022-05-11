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
            free(tmp);
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
    if(feof(saves_reg) || saves_reg ==  NULL)
        return NULL;
    SavesList saves = NULL;
    
    rewind(saves_reg);
    while(!feof(saves_reg)){
        char save[S_LEN+1];
        fscanf(saves_reg, "%s", save);
        saves = add_save(saves, save);
    }
    fclose(saves_reg);
    return saves;
}

void update_saves_register(SavesList saves){
    FILE *saves_reg = fopen(SAVES_REGISTER, "w");
    if(saves == NULL){
        
        fclose(saves_reg);
        return;
    }

    rewind(saves_reg);
    Save *save = saves;
    while(save != NULL){
        fprintf(saves_reg, "%s\n", save->name);
        save = save -> next;
    }
    fclose(saves_reg);
}

void delete_save(char * save_name){
    SavesList saves = get_saves_list();
    saves = remove_save(saves, save_name);
    remove(generate_file_path(save_name));
    update_saves_register(saves);
    
}
 
