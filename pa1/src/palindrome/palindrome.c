#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[]) {

    char *word;
    word = argv[1];
    int x = strlen(word);

    char justletters[100];
    

    int b = 0;
    for(int i = 0; i <= x; i++){
        if(isalpha(word[i])){
            justletters[b] = word[i];
            b++;
        }    
    }
    justletters[b] = '\0';
    
    int j = strlen(justletters);

    int z = j-1;
    for(int i = 0; i < (j/2); i++){
       if(toupper(justletters[i]) == toupper(justletters[z-i])){
           continue;
       }
       else{
           printf("no\n");
           return 0;
       }
    }

    printf("yes");

    return 0;
};
