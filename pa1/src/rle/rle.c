#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void rlee(int intputlength, char input[],char output[], int position,int arrayindex){

    int aol = 0;
    if(isdigit(input[position])){
        
        printf("error");
        return;
    }
    if(position == intputlength){
        if(intputlength < strlen(output)){
            printf("%s",input);
            return;
        }
        else{
           printf("%s",output);
           return;
        }
    }
    
    char letter = input[position];



    while(letter == input[position]){
        aol++;
        position++;
    }
    char plustwo[2];

    sprintf(plustwo, "%c%d", letter,aol);
    strcat(output, plustwo);
  
 
 
    
    rlee(intputlength,input,output,position,arrayindex+2);
    output[arrayindex+1]='\0';
}

int main(int argc, char* argv[]) {
   
    char *input;
    input = argv[1];

    int inputlength = strlen(input);
    
    char *output = (char *)malloc(sizeof(char)*inputlength);


    rlee(inputlength,input, output,0,0);

    
};
