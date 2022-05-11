#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    FILE *file = fopen("a.txt", "a+");
    remove("a.txt");
    /*char text[256];*/
    // int letter;
    // printf("%d", (letter = fgetc(file)) == EOF);
    fprintf(file, "Yo\n");
    /*
    while(!feof(file)){
        fscanf(file, "%[^\n]%*c", text);
        printf("%s", text);
    }
    */
    fclose(file);
}