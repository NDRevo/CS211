#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Node { 
    int value;
    char variable[16];
    struct Node* next;
}; 

void print(int *num, int n){
    int i;
    for ( i = 0 ; i < n ; i++)
        printf("%d", num[i]);

}
void printList(struct Node *node) 
{ 
  while (node != NULL) 
  { 
     printf("Output Variable: %s\n", node->variable); 
     printf("Output Value: %d\n", node->value); 
     node = node->next; 
  } 
} 
void insert(int oneorzero, char *outputname, struct Node** head){
    struct Node* temp = (struct Node*) malloc(sizeof(struct Node)); 
    struct Node *last = *head;
    strcpy(temp->variable, outputname);
    temp->value= oneorzero ;
    temp->next = NULL; 
    if (*head == NULL){
       *head = temp; 
       return; 
    }   
    while (last->next != NULL){
        last = last->next;
    } 
    last->next = temp; 

    return;
}

void exclusiveorgate(int *values, struct Node** head, char *outputname){
    int oneorzero;
    if(values[0] == 0 && values[1] == 0 ){
       oneorzero = 0;
    }
    else if(values[0] == 1 && values[1] == 1){
        oneorzero = 0;
    }
    else{
        oneorzero = 1;
    }
    insert(oneorzero,outputname,head);
}
void notgate(int *values, struct Node** head, char *outputname){
    int oneorzero;
    if(values[0] == 1){
       oneorzero = 0;
    }
    else{
        oneorzero = 1;
    }
    insert(oneorzero,outputname,head);
}
void passgate(int *values, struct Node** head, char *outputname){
    int *oneorzero = values;
    insert(*oneorzero,outputname,head);
}

void norgate(int *values, struct Node** head, char *outputname){
    int oneorzero;
    if(values[0] == 0 && values[1] == 0 ){
       oneorzero = 1;
    }
    else{
        oneorzero = 0;
    }
    insert(oneorzero,outputname,head);
}
void nandgate(int *values, struct Node** head, char *outputname){
    int oneorzero;
    //int found = 0;
    if(values[0] == 1 && values[1] == 1){
       oneorzero = 0;
    }
    else{
        oneorzero = 1;
    }
    insert(oneorzero,outputname,head);
}

void orgate(int *values, struct Node** head, char *outputname){
    int oneorzero;
    if(values[0] == 0 && values[1] == 0 ){
       oneorzero = 0;
    }
    else{
        oneorzero = 1;
    }
    insert(oneorzero,outputname,head);
}

void andgate(int *values, struct Node** head, char *outputname){
    int oneorzero;
    if(values[0] == 1 && values[1] == 1){
       oneorzero = 1;
    }
    else{
        oneorzero = 0;
    }
    insert(oneorzero,outputname,head);
}

void inputs(FILE** circuit,int *values, struct Node* inputvariable, struct Node* templist , int gatesize){
    for(int i = 0; i < gatesize; i++){
        int found = 0;
        char inputname[16];
        fscanf(*circuit,"%s", inputname);
        if(strcmp(inputname,"1") == 0){
            //printf("here at 1 ");
            values[i] = 1;
          
        }
        if(strcmp(inputname,"0") == 0){
            //printf("here at 0 ");
            values[i] = 0;
           
        }
        //searches inputvariables
        struct Node *Temp;
        Temp = inputvariable;

        char variablename[16];
        while(Temp != NULL){
            strcpy(variablename,Temp->variable);
            if(strcmp( inputname,variablename) == 0){
                values[i] = Temp ->value;
                found = 1;
                break;
            }
            Temp = Temp->next;
            
        }
        //Now searches in temp variables
        struct Node *TempTwo;
        TempTwo = templist;
        if(found == 0){
            while(TempTwo != NULL){
                //if it finds it
                strcpy(variablename,TempTwo->variable);
                if(strcmp( inputname,variablename) == 0){
                    //printf("FROM TEMP: %s\n",templist->variable);
                    // printf("%s : ",TempTwo->variable);
                    // printf("%d |||",TempTwo->value);
                    values[i] = TempTwo->value;
                    break;
                }
                TempTwo = TempTwo->next;
            }
        }   
    }
    return;

}

void greycode(int n, char *buf, int inputsize) {
    char *b = buf + inputsize;
    *b = 0;
    do {
        *--b = '0' + (n & 1);
        n >>= 1;
    }while (b != buf);
}

void decodergate(FILE** circuit,int *values,struct Node** templist , int gatesize){
    int oneorzero;
    char *greycodeline;
    greycodeline = (char *)malloc(4 * sizeof(char *));
    int k = pow(2,gatesize);
    char valueslist[16];
    for(int j = 0; j < k; j++){
        char outputname[16]; 
        fscanf(*circuit,"%s", outputname);
        for(int i = 0; i < gatesize; i++){
            valueslist[i] = values[i]+'0';
        }
        greycode(j,greycodeline,gatesize); 
        if(strstr(valueslist,greycodeline) != NULL){
            oneorzero = 1;
        }
        else{
            oneorzero = 0;
        }
        insert(oneorzero,outputname,templist);
    }   
    return;
}
void multiplexergate(FILE** circuit,int *values,struct Node** inputvariable,struct Node** templist,int gatesize,int totalsize){
    int oneorzero = 0;
    int *selectors = (int *)malloc(gatesize*sizeof(int *));
    inputs(circuit,selectors,*inputvariable, *templist , gatesize);


    char valueslist[16];
    for(int i = 0; i < gatesize; i++){
        valueslist[i] = selectors[i]+'0';
    }  
    
    //int oneorzero;
    char *greycodeline;
    greycodeline = (char *)malloc(4 * sizeof(char *));
    //char valueslist[16];
    for(int j = 0; j < totalsize; j++){
 
        greycode(j,greycodeline,gatesize); 
        if(strstr(valueslist,greycodeline) != NULL){
            oneorzero = values[j];
            
        }
    }
    char outputname[16]; 
    fscanf(*circuit,"%s",outputname);
    insert(oneorzero,outputname,templist);    

    return;
    
}

void setvalues(struct  Node* inputvariable, char *greycodeline, int inputsize,int i){
    if(inputvariable->next == NULL){
        if(greycodeline[inputsize-1-i] == '1'){
            inputvariable->value = 1;
        }
        else{
            inputvariable->value = 0;
        }
        return;
    }
    setvalues(inputvariable->next,greycodeline,inputsize,i-1);
     if(greycodeline[inputsize-1-i] == '1'){
            inputvariable->value = 1;
    }
    else{
        inputvariable->value = 0;
    }
    return;

    
};
void printoutputs(struct Node* templist, struct Node* outputlist, int current){
    int i = 0;
    struct Node *temporary;
    temporary = templist;
    struct Node *outputs;
    outputs = outputlist;
    while(outputs != NULL){
        temporary = templist;
        while(temporary != NULL){
           
            if(strcmp(temporary->variable,outputs->variable) == 0){
                if(i == current-1){
                    printf("%d",temporary->value);
                    break;
                }
                else{  
                    i++;
                    printf("%d ",temporary->value);
                    break;
                }

            }
            temporary = temporary -> next;
        }

        outputs = outputs ->next;
    }
}

 

int main(int argc, char* argv[]){
	FILE *circuit;
    circuit = fopen(argv[1],"r");

    char input[6];
	fscanf(circuit,"%s",input);
    int inputsize;
    fscanf(circuit,"%d", &inputsize);

    //LL: INPUT VARIABLES
    struct Node *inputvariable;
    struct Node *current;
    struct Node *temp;
    for(int i = 0; i <= inputsize; i++){
        if(i == inputsize){
            temp->next = NULL;
            break;
        }
        current = (struct Node*)malloc( sizeof(struct Node)); 
        
        current -> value = 0;
        fscanf(circuit,"%s", current -> variable);

        //First input
        if(i == 0){
            inputvariable = temp = current;
        }
        else{
            temp->next = current;
            temp = current;
        }
    } 
    //printList(inputvariable);

 
    char output[7];
	fscanf(circuit,"%s",output);
    int outputsize;
    fscanf(circuit,"%d", &outputsize);

    //LL: OUTPUT VARIABLES
    struct Node *outputvariable;
    struct Node *outcurrent;
    struct Node *outtemp;
    for(int i = 0; i <= outputsize; i++){
        if(i == outputsize){
            outtemp->next = NULL;
            break;
        }
        outcurrent = (struct Node*)malloc(sizeof(struct Node)); 
        
        outcurrent -> value = 0;
        fscanf(circuit,"%s", outcurrent -> variable);

        //First input
        if(i == 0){
            outputvariable = outtemp = outcurrent;
        }
        else{
            outtemp->next = outcurrent;
            outtemp = outcurrent;
        }
    }
    for (int i = 0 ; i < pow(2,inputsize) ; i++) {
        char *greycodeline;
        greycodeline = (char *)malloc(4 * sizeof(char *));
	    greycode(i,greycodeline,inputsize); 
        setvalues(inputvariable, greycodeline,inputsize,inputsize-1);
        
        rewind(circuit);

        struct Node *templist = NULL;
        char *gatename;
        gatename = (char *)malloc(2*sizeof(char *));
        while(fscanf(circuit,"%s", gatename) == 1){    
            if(strcmp(gatename, "NAND") == 0){
                int gatesize = 2;
                int values[2];
                inputs(&circuit,values, inputvariable, templist,gatesize);
                //printf("%d & %d\n", values[0],values[1]); 
                char outputname[16];
                fscanf(circuit,"%s", outputname);
                nandgate(values,&templist, outputname);

            }
            else if(strcmp(gatename, "DECODER") == 0){
                int gatesize;
                fscanf(circuit,"%d", &gatesize);
                int *values = (int *)malloc(gatesize*sizeof(int *));
                inputs(&circuit,values,inputvariable,templist,gatesize);
                decodergate(&circuit, values, &templist, gatesize);         
            }
            else if(strcmp(gatename, "MULTIPLEXER") == 0){
                int gatesize;
                fscanf(circuit,"%d", &gatesize);
                int totalsize = pow(2,gatesize);
                int *values = (int *)malloc(totalsize*sizeof(int *));
                inputs(&circuit,values,inputvariable,templist,totalsize);

                multiplexergate(&circuit, values,&inputvariable, &templist, gatesize, totalsize); 
                

            }
            else if(strcmp(gatename, "XOR") == 0){
                int gatesize = 2;
                int values[2];
                inputs(&circuit,values, inputvariable, templist,gatesize);
                char outputname[16];
                fscanf(circuit,"%s", outputname);
                exclusiveorgate(values,&templist, outputname);

            }  
            else if(strcmp(gatename, "NOR") == 0 ){
                int gatesize = 2;
                int values[2];
                inputs(&circuit,values, inputvariable, templist,gatesize);
                //printf("%d & %d\n", values[0],values[1]); 
                char outputname[16];
                fscanf(circuit,"%s", outputname);
                norgate(values,&templist, outputname);

            }
            //IF OR GATE
            else if(strcmp(gatename, "OR") == 0){
                int gatesize = 2;
                int values[2];
                inputs(&circuit,values, inputvariable, templist,gatesize);
                //printf("%d & %d\n", values[0],values[1]); 
                char outputname[16];
                fscanf(circuit,"%s", outputname);
                orgate(values,&templist, outputname);

            }  
            //IF AND GATE
            else if(strcmp(gatename, "AND") == 0){
                int gatesize = 2;
                int values[2];
                inputs(&circuit,values, inputvariable, templist,gatesize); 
                //printf("%d & %d\n", values[0],values[1]); 
                char outputname[16];
                fscanf(circuit,"%s", outputname);
                andgate(values,&templist, outputname);

            }  
            else if(strcmp(gatename, "PASS") == 0){
                int gatesize = 1;
                int value[1];

                inputs(&circuit,value, inputvariable, templist,gatesize); 
                //printf("%d\n", value[0]); 

                char outputname[16];
                fscanf(circuit,"%s", outputname);
                passgate(value,&templist, outputname);

            }
            else if(strcmp(gatename, "NOT") == 0){
                int gatesize = 1;
                int value[1];
                inputs(&circuit,value, inputvariable, templist,gatesize); 
                //printf("%d\n", value[0]); 

                char outputname[16];
                fscanf(circuit,"%s", outputname);
                notgate(value,&templist, outputname);

            }    
        }
        for(int j = 0; j < inputsize; j++){
            printf("%c ", greycodeline[j]);
        }
        printf("| ");
        printoutputs(templist,outputvariable, outputsize);
        printf("\n");

        
    }


    return 0;


} 