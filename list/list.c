// Patrick Cook
// Linked List implementation with test

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodes {
    struct nodes *next;
    struct nodes *previous;
    char data;
}node;

node *anchor = NULL;
node *tail = NULL;
node *current = NULL;

int push(char x);
char *pull(void);
char *pullback(void);
char *tailNode(void);
char *backNode(void);
_Bool isFull(void);
_Bool isEmpty(void);
void reset(int x);
int delete(node *x);
void insertAfterNode(node* node_ptr, char value);
void deleteNode(node* node_ptr);
void findIndex();
node *findValue(char value);
node *getCurrent(void);

char saveElement;
int numElements = 0;
int node_number = 1;

int main() {
    char c;
    printf("Enter one character at a time into list. When finished enter '^':\n");
    while(1){
        scanf("%c",&c); 
        if(c == '^')
            break;
        else 
            push(c);
    }
    /* Print list tail to end */
    printf("Here is the list from head to tail:\n");
    node *print = anchor;
    while(print != NULL){
        printf("%c\n",print -> data);
        print = print -> next;
    }

}

// List driver functions
int push(char x){
    if (isFull() == 1){
        printf("The list is full. Enter the '^' character to ESC");
        return -1;
    }
    node *aNode = malloc(sizeof(node));
    aNode -> data = x;
    aNode -> previous = tail;
    aNode -> next = NULL;
    if(isEmpty()) {
        tail = aNode;
        anchor = aNode;
    } else {
        tail -> next = aNode;
        tail = tail -> next;
        current = tail;
    }
    return 0;
}


char *backNode(void){
    if (anchor == NULL)
        return  NULL;
    else
        return &(anchor -> data);
}
char *tailNode(void){
    if (anchor == NULL)
        return  NULL;
    else
        return &(tail -> data);
}
_Bool isFull(void){
    if (malloc(sizeof(node)) == NULL) /*no more space for nodes*/
        return 1;
    else
        return 0;
}
_Bool isEmpty(void){
    if (tail == NULL) 
        return 1;
    else
        return 0;
}
node *getCurrent(void){
    return current;
}
void reset(int x){
    if (x == 1)
        current = anchor;
    else
        current = tail;
}
int delete(node *x){
    if (x == NULL)
        return 0;
    else if (x == anchor){
        anchor -> next -> previous = NULL;
        anchor = anchor -> next;
        current = anchor;
        return 1;
    }
    else if (x == tail){
        tail -> previous -> next = NULL;
        tail = tail -> previous;
        current = tail;
        return 1;
    }
    else
        x -> previous -> next = x -> next;
        x -> next -> previous = x -> previous;
        current = current -> next;
        return 1;
}
void insertAfterNode(node *node_ptr, char value){
    if(node_ptr){
        node *aNode = malloc(sizeof(node));
        aNode -> data = value;
        aNode -> next = node_ptr -> next;
        aNode -> previous = node_ptr;
        if(node_ptr -> next != NULL)
            node_ptr -> next -> previous = aNode;
        node_ptr -> next = aNode;
        if(node_ptr == tail)
            tail = tail -> next;
    }
}
void deleteNode(node *node_ptr){
    if(anchor == NULL || node_ptr == NULL)
        return;
    if(node_ptr == anchor)
        anchor = node_ptr -> next;
    if(node_ptr == tail)
        node_ptr -> previous -> next = NULL;
    else {
        node_ptr -> previous -> next = node_ptr -> next;
        node_ptr -> next -> previous = node_ptr -> previous;
    }
    free(node_ptr);
}
node *findValue(char value)
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

void findIndex(){
    node *find = anchor;
    printf("The positions of %c are:\n ",saveElement);
    while(find){
        if(find -> data == saveElement)
            printf("%d\n",node_number);
        find = find -> next;
        node_number++;
    }
}
