/* =========================================================
* Doubly-Linked List (DLL) Implementation 
* Patrick Cook
* Interface: Interactive command line to individually enter and
*   remove characters from the list, free the list, and more
* Etc: There are both head and tail anchors for the list, 
*   allowing for data to be pushed onto the front and back
* =========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodes {
    struct nodes *next;
    struct nodes *prev;
    char data;
}node;

// Interface Functions for DLL
_Bool push_to_tail();
_Bool push_to_head();
_Bool delete_head(void);
_Bool delete_tail(void);
_Bool is_full(void);
_Bool is_empty(void);
_Bool delete_char(void);
_Bool delete_node(node *node_ptr);
char *tail_node(void);
char *head_node(void);
void free_list(void);
_Bool insert_after_node(node* node_ptr, char value);
node *return_node_of_value(char value);
void print_head_to_tail(void);
void print_tail_to_head(void);

node *head = NULL;
node *tail = NULL;

void main() {
    int command = 0;
    while(1) {
        printf("---------------------------------------------------------------------------\n");
        printf("Press 1 to insert a character to the tail of the list.\n");
        printf("Press 2 to insert a character to the head of the list.\n");
        printf("Press 3 to insert a character after a specific character in the list.\n");
        printf("Press 4 to delete the first occurence of a character from the list.\n");
        printf("Press 5 to display the list from head to tail.\n");
        printf("Press 6 to display the list from tail to head.\n");
        printf("Press 7 to free the list.\n");
        printf("Press 8 to exit the program.\n");
        printf("---------------------------------------------------------------------------\n");
        scanf("%d",&command); 

        char x,val;
        switch(command) {
            case 1:
                push_to_tail();
                break;
            case 2:
                push_to_head();
                break;
            case 3:
                if(is_empty()) {
                    printf("\nThe list is empty. There are nodes to insert a value after.\n");
                    break;
                }
                printf("\nChoose a character to add an entry after\n");
                scanf(" %c",&x); 
                printf("\nChoose a value to enter\n");
                scanf(" %c",&val); 
                insert_after_node(return_node_of_value(x),val);
                break;
            case 4:
                delete_char();
                break;
            case 5:
                print_head_to_tail();
                break;
            case 6:
                print_tail_to_head();
                break;
            case 7:
                free_list();
                break;
            case 8:
                printf("\nExiting Program...\n");
                exit(0);
            default:
                printf("\nThe command you entered is not recognized\n");
        }
    }
}
/*===================================
* Implementation of Driver Functions
===================================*/

_Bool push_to_tail(void) {
    char value;
    if (is_full()){
        printf("The list is full");
        return 0;
    }
    printf("Enter a character to push to the tail\n");
    scanf(" %c",&value);

    node *aNode = malloc(sizeof(node));
    aNode -> data = value;
    aNode -> next = NULL;
    if(is_empty()) {
        aNode -> prev = NULL;
        tail = aNode;
        head = aNode;
    } else {
        aNode -> prev = tail;
        tail -> next = aNode;
        tail = aNode;
    }
    return 1;
}

_Bool push_to_head(void) {
    if (is_full()){
        printf("The list is full");
        return 0;
    }
    char value;
    printf("Enter a character to push to the head\n");
    scanf(" %c",&value);

    node *aNode = malloc(sizeof(node));
    aNode -> data = value;
    aNode -> next = NULL;
    if(is_empty()) {
        aNode -> prev = NULL;
        tail = aNode;
        head = aNode;
    } else {
        aNode -> next = head;
        head -> prev = aNode;
        head = aNode;
    }
    return 1;
}

char *head_node(void){
    if (!head)
        return  NULL;
    else
        return &(head -> data);
}
char *tail_node(void){
    if (!tail)
        return  NULL;
    else
        return &(tail -> data);
}
_Bool is_full(void){
    if (malloc(sizeof(node)) == NULL)
        return 1;
    else
        return 0;
}
_Bool is_empty(void){
    if (head == NULL && tail == NULL) 
        return 1;
    else
        return 0;
}

_Bool delete_char(void) {
    char value;
    printf("Enter character to delete from list\n");
    scanf(" %c",&value); 
    return delete_node(return_node_of_value(value));
}

/* Given a value and a specified node, inserts a new node
   * after with the entered value */
_Bool insert_after_node(node *node_ptr, char value) {
    if(is_full()) {
        printf("The list is full");
        return 0;
    }
    if(node_ptr) {
        node *aNode = malloc(sizeof(node));
        aNode -> data = value;
        aNode -> next = node_ptr -> next;
        aNode -> prev = node_ptr;
        node_ptr -> next = aNode;
        if(node_ptr -> next != NULL)
            node_ptr -> next -> prev = aNode;
        if(node_ptr == tail)
            tail = tail -> next;
    } else {
        printf("CANNOT INSERT AFTER SPECIFIED NODE");
        return 0;
    }
    return 1;
}

_Bool delete_node(node *node_ptr) {
    if(!node_ptr) {
        printf("CANNOT DELETE SPECIFIED NODE\n");
        return 0;
    } else if(node_ptr == head) {
        head = head -> next;
        head -> prev = NULL;
    } else if(node_ptr == tail) {
        tail = tail -> prev;
        tail -> next = NULL;
    } else {
        node_ptr -> prev -> next = node_ptr -> next;
        node_ptr -> next -> prev = node_ptr -> prev;
    }
    free(node_ptr);
    return 1;
}

/* Returns the node of an entered list item
  * returns the first occurence of the item, 
  * starting from the head */ 
node *return_node_of_value(char value) { 
    if(is_empty()) {
        printf("List is empty - cannot return specified node\n");
        return NULL;
    }
    node *node_ptr = head;
    while(node_ptr -> data != value) {
        node_ptr = node_ptr -> next;
        if(!node_ptr) {
            printf("CANNOT FIND CORRESPONDING VALUE OF ENTERED NODE\n");
            break;
        }
    } 
    return node_ptr; 
}

void free_list(void) {
    node *temp = head;
    while(is_empty()) {
        temp = head;
        head = head -> next;
        free(temp);
    }
    head = NULL;
    tail = NULL;
}

void print_head_to_tail(void) {
    node *print = head;
    printf("\nHere is the list from head to tail:\n");
    while(print != NULL) { // loop through nodes starting from head
        printf("%c",print -> data);
        print = print -> next;
    }
    printf("\n");
}

void print_tail_to_head(void) {
    node *print = tail;
    printf("\nHere is the list from tail to head:\n");
    while(print != NULL) { // loop through nodes starting from tail
        printf("%c",print -> data);
        print = print -> prev;
    }
    printf("\n");
}
