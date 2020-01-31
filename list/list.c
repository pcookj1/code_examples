//#include "tstdata.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct nodes {
    struct nodes *next;
    struct nodes *previous;
    char data;
}node;

node *anchor = NULL;
node *rear = NULL;
node *current = NULL;

int Push(char x);
char *Pull(void);
char *Pulback(void);
char *Front(void);
char *Back(void);
int isFull(void);
node *GetCurrent(void);
void Reset(int x);
int Delete(node *x);
void InsertAfter(node* node_ptr, char value);
void DeleteNode(node* node_ptr);
node *FindValue(char value);
void find_index();

char saveElement;
int numElements = 0;
int node_number = 1;

int main() {
    char c;
    printf("Enter sequence of at least 10 characters into the list. When finished enter '^':\n");
    while(1){
        scanf("%c",&c); 
        if(c == '^'){
            if(numElements < 10){
                printf("You must enter at least 10 elements - keep entering!\n");
                continue;
            }
            else
                break;
        }
        else if (c != '\n' && c != ' '){
            Push(c);
            if(numElements == 3){
                saveElement = c;
            }
        }
    }
    /* Print list front to end */
    printf("Here is the list from front to end:\n");
    node *print = anchor;
    while(print != NULL){
        printf("%c\n",print -> data);
        print = print -> next;
    }

    /* search list for saveElement */
    node *find = FindValue(saveElement);
    if(find != NULL){
        find_index();
    }

    /* Insert symbol */
    printf("Inserting '*'\n");
    InsertAfter(FindValue(saveElement),'*');

    /* Print list front to end */
    printf("Here is the list from front to end:\n");
    print = anchor;
    while(print != NULL){
        printf("%c\n",print -> data);
        print = print -> next;
    }

    /* Deleted Remembered character  */
    printf("Removing %c\n",saveElement);
    DeleteNode(FindValue(saveElement));

    /* Print list front to end */
    printf("Here is the list from front to end:\n");
    print = anchor;
    while(print != NULL){
        printf("%c\n",print -> data);
        print = print -> next;
    }

    /* Delete rest of instances of value */
    printf("Removing rest of %c\n",saveElement);
    while(FindValue(saveElement) != NULL)
        DeleteNode(FindValue(saveElement));

    /* Print list front to end */
    printf("Here is the list from front to end:\n");
    print = anchor;
    while(print != NULL){
        printf("%c\n",print -> data);
        print = print -> next;
    }
    return 0;
}

/*Functions*/
int Push(char x){
    if (isFull() == 1){
        printf("The stack is full. Enter the '^' character to stop");
        return -1;
    }
    else if (isFull() == -1){
        node *fNode = malloc(sizeof(node));
        fNode -> data = x;
        fNode -> next = NULL;
        fNode -> previous = NULL;
        anchor = fNode;
        rear = fNode;
        current = rear;
        numElements = 1;
        return 0;
    }
    else{
        node *aNode = malloc(sizeof(node));
        aNode -> data = x;
        aNode -> next = NULL;
        aNode -> previous = rear;
        rear -> next = aNode;
        rear = rear -> next;
        current = rear;
        numElements++;
        return 0;
    }
}
char *Pull(void){
    if (rear == NULL) /*empty*/
        return  NULL;
    else{
        node *pNode = malloc(sizeof(node));
        pNode = anchor;
        anchor = anchor -> next;
        return &(pNode -> data);
    }
}
char *Pulback(void){
    if (rear == NULL)
        return  NULL;
    else{
        node *pNode = malloc(sizeof(node));
        pNode = rear;
        rear = rear -> previous;
        return &(pNode -> data);
    }
}
char *Front(void){
    if (anchor == NULL)
        return  NULL;
    else
        return &(anchor -> data);
}
char *Back(void){
    if (anchor == NULL)
        return  NULL;
    else
        return &(rear -> data);
}
int isFull(void){
    if (anchor == NULL)
        return -1;
    else if (malloc(sizeof(node)) == NULL) /*no more space for nodes*/
        return 1;
    else
        return 0;
}

node *GetCurrent(void){
    return current;
}
void Reset(int x){
    if (x == 1)
        current = anchor;
    else
        current = rear;
}
int Delete(node *x){
    if (x == NULL)
        return 0;
    else if (x == anchor){
        anchor -> next -> previous = NULL;
        anchor = anchor -> next;
        current = anchor;
        numElements--;
        return 1;
    }
    else if (x == rear){
        rear -> previous -> next = NULL;
        rear = rear -> previous;
        current = rear;
        numElements--;
        return 1;
    }
    else
        x -> previous -> next = x -> next;
        x -> next -> previous = x -> previous;
        current = current -> next;
        numElements--;
        return 1;
}
void InsertAfter(node* node_ptr, char value){
    if(node_ptr){
        node *aNode = malloc(sizeof(node));
        aNode -> data = value;
        aNode -> next = node_ptr -> next;
        aNode -> previous = node_ptr;
       // rear -> next = aNode;
       // rear = rear -> next;
        numElements++;
        if(node_ptr -> next != NULL)
            node_ptr -> next -> previous = aNode;
        node_ptr -> next = aNode;
        if(node_ptr == rear)
            rear = rear -> next;
    }
}
void DeleteNode(node* node_ptr){
    if(anchor == NULL || node_ptr == NULL)
        return;
    if(node_ptr == anchor)
        anchor = node_ptr -> next;
    if(node_ptr == rear)
        node_ptr -> previous -> next = NULL;
    else {
        node_ptr -> previous -> next = node_ptr -> next;
        node_ptr -> next -> previous = node_ptr -> previous;
    }
    numElements--;
    free(node_ptr);
}
node* FindValue(char value)
{
    node *step = anchor;
    while(step){
        if(step->data == value){
            return step;     
        }
        step = step->next;
    }
    return NULL;
}

void find_index(){
    node* find = anchor;
    printf("The positions of %c are:\n ",saveElement);
    while(find){
        if(find -> data == saveElement)
            printf("%d\n",node_number);
        find = find -> next;
        node_number++;
    }
}
