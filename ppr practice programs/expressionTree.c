#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct Stack
{
    char data;
    struct Stack *next;
}*top=NULL;

void push(char data){
    struct Stack *temp=(struct Stack *)malloc(sizeof(struct Stack));
    temp->data=data;
    temp->next=top;
    top=temp;
}
char pop(){
    char poppedvalue;
    if (top==NULL)
    {
        return 0;
    }else{
        poppedvalue=top->data;
        struct Stack *temp=top;
        top=top->next;
        free(temp);
        return poppedvalue;
    }
}
char peek(){
    char peek;
    if (top==NULL)
    {
        return 0;
    }else{
        return top->data;
    }   
}
int precedence(char ch){
    switch (ch)
    {
    case '*':
    case '/':
        return 5;
    case '+':
    case '-':
        return 4;
    case '<':
    case '>':
    case '~':
        return 3;
    case '&':
        return 2;
    case '|':
        return 1;
    default:
        return 0;
    }
}
int isOperator(char ch){
    return (ch=='*' || ch == '/' || ch == '+' || ch == '-' || ch == '<' || ch == '>' || ch == '~' || ch == '&' || ch == '|');
}
void infixTopostfix(char *infix,char *postfix){
    int i,j;
    i=j=0;
    while (infix[i]!='\0')
    {
        if (infix[i]==' ' || infix[i]=='\t')
        {
            i++;
        }else if(isalnum(infix[i])){
            postfix[j++]=infix[i++];
        }else if(isOperator(infix[i])){
            while (precedence(infix[i])<=precedence(peek()) && peek()!='(')
            {
                postfix[j++]=pop();
            }
            push(infix[i++]);
        }else if(infix[i]=='('){
            push(infix[i++]);
        }else if(infix[i]==')'){
            while (peek()!='(')
            {
                postfix[j++]=pop();
            }
            pop();
            i++;
        }
    }
    while (peek()!=0){
        postfix[j++]=pop();
    }
    postfix[j]='\0';
}
struct Node{
    char data;
    struct Node *left;
    struct Node *right;
};
struct Node *createNode(char data){
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->data=data;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
struct Node *ExpressionTree(char *postfix){
    struct Node *root=NULL;
    struct Node *tempStack[100];
    int top=-1;
    for (int i = 0; postfix[i]!='\0'; i++)
    {
        if (!isOperator(postfix[i]))
        {
            struct Node *node=createNode(postfix[i]);
            tempStack[++top]=node;
        }else{
            struct Node *operator=createNode(postfix[i]);
            operator->right=tempStack[top--];
            operator->left=tempStack[top--];
            tempStack[++top]=operator;
        }
    }
    if(top==0){
        root=tempStack[0];
    }else{
        printf("Inavlid postfix exp\n");
    }
    return root;
}
void inOrder(struct Node *node){
    if(node!=NULL){
        inOrder(node->left);
        printf("%c ",node->data);
        inOrder(node->right);
    }
}
int main(){
    char infix[100],postfix[100];
    printf("Enter infix expression: ");
    gets(infix);

    infixTopostfix(infix,postfix);
    printf("postfix Expression is: %s\n",postfix);

    struct Node *root=ExpressionTree(postfix);
    printf("In Order of Epression tree is: ");
    inOrder(root);
    return 0;
}