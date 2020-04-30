#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node { 
    int data;
    struct Node* next; 
}; 

int search(struct Node* head, int inum,int count){
    if(count == 0){
        return 0;
    }
    while(head != NULL){
        //if it finds it
        if(head->data == inum){
            return 1;
        }
        head= head->next;
    }
    return 0;
};
void print(struct Node* head,int count){
    struct Node* temp;
    
    if(count > 0){
        temp = head;
        printf("%d : ", count);
        while (head != NULL) { 
            if(head->next == NULL){
                printf("%d", head->data);
                head = head->next;
            }
            else{
                printf("%d ", head->data); 
                head = head->next; 
            }
        }
        printf("\n"); 
        head = temp;           

    }
    else{
        printf("%d :\n",count);
    }
}

void insert(int inum,struct Node** head){
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node)); 
    struct Node *prev;
    prev = (struct Node*)malloc(sizeof(struct Node)); 
  

    temp -> data = inum;
    temp -> next = NULL;


    if (*head == NULL || (*head)->data >= temp->data) { 
        
        temp->next = *head; 
        *head = temp;
    } 
    else{ 
        prev = *head; 
        while (prev -> next != NULL && prev->next->data < temp->data) { 
            prev = prev->next;
        } 
        temp->next = prev->next; 
        prev->next = temp; 
    } 
    
}


void delete(int inum,struct Node** head,int count){
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    struct Node *prev;
    prev = (struct Node*)malloc(sizeof(struct Node)); 

    //inum = number to be deleted
    temp -> data = inum;
    temp -> next = NULL;

    if (count == 1 && (*head)->data == inum) { 
     *head = NULL;
    }
    else{
        if((*head)->data == temp->data){
            *head = (*head)->next;
        }
        else{
            prev = *head; 
            while (prev -> next != NULL && prev->next->data < temp->data) { 
                prev = prev->next;
            } 
            prev->next = prev->next->next; 
        }

    }


}

int main() {
    int num = 0;
    char arg = 0;
    int count = 0;
    struct Node* head = (struct Node*)malloc(sizeof(struct Node)); ;
    for(;;){
        int i = scanf("%c %d", &arg, &num);
        getchar();
        if (i == EOF){
            return 0;
        }
        if (i == 2) {

            if (arg == 'i'){
                //0 Nodes
                if(count == 0){
                    head = (struct Node*)malloc(sizeof(struct Node)); 
                    head -> data = num;
                    head -> next = NULL;
                    count++;
                    print(head,count);
                }
                else{
                   //If duplicate
                    if(search(head, num, count) == 1){
                        print(head,count);
                    }
                    //if not duplicate
                    else{  
                        insert(num,&head);
                        count++;
                        print(head,count);
                        
                    } 
                    
                }
                
            }
            if (arg == 'd'){
                //if no elements || duplicate
                if(search(head, num, count) == 0){
                        print(head,count);
                }
                else{
                    delete(num,&head,count);
                    count--;
                    print(head,count);
                       
                }
                
            } 
        }
        else{
            printf("Invalid Input\n");
            return 0;
        }
    }

    


    return 0;
};
