#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node { 
    int data;
    //no more head
    struct Node *left, *right; 
}; 

struct Node* search(int num,struct Node* start) { 

    if (start == NULL || start->data == num) 
       return start; 
    if (start->data < num){
        return search(num,start->right); 
    }
    return search(num,start->left); 
} 
struct Node* insert(int inum,struct Node* start){
    struct Node *temp =  (struct Node *)malloc(sizeof(struct Node)); 
    if (start == NULL){
        temp->data = inum; 
        temp->left = NULL;
        temp->right = NULL; 
        start = temp;
    }; 
    if (inum < start->data){
        start->left  = insert(inum,start->left);
    }
    else if (inum > start->data){
        start->right = insert(inum,start->right);
    }  
    return start; 
} 

void printing(struct Node* start, int count){
    if(start == NULL || count == 0){
        return;
    }
    printf("(");
    printing(start ->left,count);
    printf("%d",start->data);
    printing(start->right,count);
    printf(")");
}


struct Node* delete(int inum,struct Node* start,int count){
    if(count == 1 && start->data == inum){
        start = NULL;
        return start;
    }
    if (start == NULL){
        return start; 
    }

    if (inum < start->data){
        start->left = delete(inum,start->left,count);
    }
    else if (inum > start->data){
        start->right = delete(inum,start->right,count);
    }
    else{ 
        if (start->left == NULL){ 
            struct Node *temp = start->right; 
            free(start); 
            return temp; 
        } 
        else if (start->right == NULL){ 
            struct Node *temp = start->left; 
            free(start); 
            return temp; 
        } 
        struct Node* current = start->right; 

        while (current && current->left != NULL){
            current = current->left; 
        }
        struct Node* temp = current; 

        start->data = temp->data; 
        start->right = delete(temp->data,start->right,count); 
    } 
    return start; 

}


int main() {
    int i = 0;
    int num = 0;
    char arg = 0;
    int count = 0;
    struct Node* start;
    for(;;){       
        i = scanf("%c", &arg); 
        if (i == EOF){
            return 0;
        }
        if(arg == 'p') {
            printing(start,count);
            printf("\n");    
        } 
        if (arg == 'i'){
                i = i + scanf(" %d", &num);
                if(count == 0){
                    start = (struct Node*)malloc(sizeof(struct Node));
                    start ->data = num;
                    start ->left = NULL;
                    start -> right = NULL;
                    count++;
                    printf("inserted\n");
                }
                else{
                    if(search(num,start) == NULL){
                        insert(num,start);
                        count++;
                        printf("inserted\n");
                    }
                    else{
                        printf("not inserted\n");
                    }
                     
                }     
            }
            if (arg == 'd'){
                i += scanf(" %d", &num);
                if(count == 0){
                    printf("absent\n");
                }
                else if(search(num,start) == NULL){
                    printf("absent\n");
                }
                else{
                    if(count == 2){
                        if(start->data == num){
                            if(start ->left == NULL && start->right != NULL){
                                start = start->right;
                            }
                            else{
                                start = start->left;
                            }
                        }
                        else{
                            start ->left = NULL;
                            start ->right = NULL;
                        }
                    }
                    else{
                        delete(num,start,count);
                    }
                    count--;
                    printf("deleted\n");
                }
 
            }
            if (arg == 's'){
                i += scanf(" %d", &num);
                if(count == 0){
                    printf("absent\n");
                }
                else if(search(num,start) != NULL){
                    printf("present\n");
                }
                else{
                    printf("absent\n");
                }
            }
    }

    return 0;
};
