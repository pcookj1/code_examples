#include <stdio.h>
#include <stdlib.h>


typedef struct nodes {
    struct nodes *next;
    char data;
}node;
typedef struct i_nodes {
    struct i_nodes *next;
    int data;
}i_node;


//Anchors for queue (1)
node *anchor1 = NULL;
node *rear1 = NULL;
//Anchors for stack (2)
node *anchor2 = NULL;
node *top2 = NULL;
//Anchors for stack (3)
node *anchor3 = NULL;
node *top3 = NULL;
//Anchors for int stack
i_node *anchor4 = NULL;
i_node *top4 = NULL;

int Push(char x, int i);
int Push_int(int x);
char *Pull(int i);
char *Pop(int i);
int *Pop_int();
char *Top(int i);
int *Top_int();
int isFull(int i);
int isFull_int();
int prec(char x);
void to_postfix();
int evaluate();
void print_infix();


int main() {

    //user input for infix expression
    printf("\nEnter expression:\n");
    while(1){
       char c = fgetc(stdin);
        if(c == '^')
            break;
        else if (c != '\n')
            Push(c,1);
    }

    //print infix expression
    print_infix();

    //convert to postfix expression
    to_postfix();

    //Reversing the stack
    while(Top(3) != NULL){
        char e = *Pop(3);
        Push(e,2);
    }

    //evaluate and print answer
    printf("\nThe answer is: %i\n",evaluate());
   
    return 0;
}

/* Behemoth of functions for operating the various stacks/queues */
/*char queue and stacks are controlled through the Push/Pull functions*/
/*int stack is controlled through Push_int, Pop_int and other _int functions*/

//for Queue1,Stack2,Stack3 : Stack to push onto is chosen through user input
int Push(char x, int i){
    //pushing on queue 1
    if(i == 1){
        if (isFull(1) == 1){
            printf("The queue is full. Enter the '^' character to stop");
            return -1;
        }
        else if (isFull(1) == -1){
            node *fNode = malloc(sizeof(node));
            fNode -> data = x;
            fNode -> next = NULL;
            anchor1 = fNode;
            rear1 = fNode;
            return 0;
        }
        else{
            node *aNode = malloc(sizeof(node));
            aNode -> data = x;
            aNode -> next = NULL;
            rear1 -> next = aNode;
            rear1 = rear1 -> next;
            return 0;
        }
    }
    //pushing on stack 2
    else if(i == 2){
        if (isFull(2) == 1){
            printf("The stack is full. Enter the '^' character to stop");
            return -1;
        }
        else if (isFull(2) == -1){
            node *fNode = malloc(sizeof(node));
            fNode -> next = anchor2;
            fNode -> data = x;
            top2 = fNode;
            return 1;
        }
        else{
            node *aNode = malloc(sizeof(node));
            aNode -> next = top2;
            aNode -> data = x;
            top2 = aNode;
            return 0;
        }
    }
    //pushing on stack 3
    else
        if (isFull(3) == 1){
            printf("The stack is full. Enter the '^' character to stop");
            return -1;
        }
        else if (isFull(3) == -1){
            node *fNode = malloc(sizeof(node));
            fNode -> next = anchor3;
            fNode -> data = x;
            top3 = fNode;
            return 1;
        }
        else{
            node *aNode = malloc(sizeof(node));
            aNode -> next = top3;
            aNode -> data = x;
            top3 = aNode;
            return 0;
        }
}
//for int stack
int Push_int(int x){
    if (isFull_int() == 1){
        printf("The stack is full. Enter the '^' character to stop");
        return -1;
    }
    else if (isFull_int() == -1){
        i_node *fNode = malloc(sizeof(i_node));
        fNode -> next = anchor4;
        fNode -> data = x;
        top4 = fNode;
        return 1;
    }
    else{
        i_node *aNode = malloc(sizeof(i_node));
        aNode -> next = top4;
        aNode -> data = x;
        top4 = aNode;
        return 0;
    }
}
char *Pull(int i){
    if(i == 1){
        if (rear1 == NULL) /*empty*/
            return  NULL;
        else{
            node *pNode = malloc(sizeof(node));
            pNode = anchor1;
            anchor1 = anchor1 -> next;
            return &(pNode -> data);
        }
    }  
    else
        printf("The inputted queue to pull is invalid");
        return  NULL;
}
char *Pop(int i){
    if(i == 2){
        if (top2 == anchor2)
            return  NULL;
        else{
            node *pNode = malloc(sizeof(node));
            pNode = top2;
            top2 = top2 -> next;
            return &(pNode -> data);
        }
    }
    else if(i == 3){
        if (top3 == anchor3)
            return  NULL;
        else{
            node *pNode = malloc(sizeof(node));
            pNode = top3;
            top3 = top3 -> next;
            return &(pNode -> data);
        }
    }
    else
        printf("This popping ain't working");
        return NULL;
}
//for int stack
int *Pop_int(){
    if (top4 == anchor4)
        return  NULL;
    else{
        i_node *pNode = malloc(sizeof(i_node));
        pNode = top4;
        top4 = top4 -> next;
        return &(pNode -> data);
    }
  
}
char *Top(int i){
    if(i == 1){
        if (anchor1 == NULL)
            return  NULL;
        else
            return &(rear1 -> data);
    }
    else if(i == 2){
        if (top2 == anchor2)
            return  NULL;
        else
            return &(top2 -> data);
    }
    else if(i == 3){
        if (top3 == anchor3)
            return  NULL;
        else
            return &(top3 -> data);
    }
    else
        printf("This Topping ain't working");
        return NULL;
}
//for int stack
int *Top_int(){
    if (anchor4 == NULL)
        return  NULL;
    else
        return &(top4 -> data);
}
int isFull(int i){
    if(i == 1){
        if (anchor1 == NULL)
            return -1;
        else if (malloc(sizeof(node)) == NULL) /*no more space for nodes*/
            return 1;
        else
            return 0;
    }
    else if (i == 2){
        if (top2 == anchor2)
            return -1;
        else if (malloc(sizeof(node)) == NULL) /*no more space for nodes*/
            return 1;
        else
            return 0;
    }
    else if(i ==3){
        if (top3 == anchor3)
            return -1;
        else if (malloc(sizeof(node)) == NULL) /*no more space for nodes*/
            return 1;
        else
            return 0;
    }
    else
        printf("This isFulling ain't working");
        return -2;
}
//for int stack
int isFull_int(){
    if (top4 == anchor4)
        return -1;
    else if (malloc(sizeof(i_node)) == NULL) /*no more space for nodes*/
        return 1;
    else
        return 0;
}
int prec(char x){
    switch(x){
        case '(':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        default:
            return 0;
	}
}
void to_postfix(){
    printf("\nPrinting the PostFix Expression:   ");
    while (Top(1) != NULL) {
        char c = *Pull(1);
        if(c != '\n'){
            if (c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')' ){ //operand
                printf("%c",c);
                Push(c,3);
            }
            else if (c == '('){
                Push(c,2);
            }
            else if (c == ')') {
    
                while (*Top(2) != '(' && Top(2) != NULL){
                    char d = *Pop(2);
                    printf("%c ", d);
                    Push(d,3);
                }
                Pop(2);
            } 
            else { 
                while (Top(2) != NULL && prec(c) <= prec(*Top(2))){ //push operator depending on precendence
                    char a = *Pop(2);
                    printf("%c ", a);
                    Push(a,3);
                }
                Push(c,2);
            }
        } 
    } 
    while(Top(2) != NULL){
        char b = *Pop(2);
        printf("%c ", b);
        Push(b,3);
    } 
    printf("\n");
}
int evaluate(){
    while(Top(2) != NULL){
        char c = *Top(2);

        if (c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')' ){ //operand
            Push_int(c - '0');
        }
        else{
    
            int a = *Pop_int();
            int b = *Pop_int();

            switch(c){
                case '+' : Push_int((a+b)); 
				break;
				case '-' : Push_int((a-b)); 
				break;
				case '*' : Push_int((a*b));
				break;
				case '/' : Push_int((a/c));
				break;
            }
        }
        Pop(2);
    }
    return *Pop_int();
}
void print_infix(){
    printf("\nThe infix expression entered is:   ");
    node *print = anchor1;
    while(print != NULL){
        printf("%c", print -> data);
        print = print -> next;
    }
    printf("\n");
}
