#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
struct Stack
{
    int data;
    struct Stack *next;
}*top=NULL;

void push(int data){
    struct Stack *temp=(struct Stack *)malloc(sizeof(struct Stack));
    temp->data=data;
    temp->next=top;
    top=temp;
}
int pop(){
    int poppedvalue;
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
// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}
int applyOperator(char Operator,int op1,int op2){
    switch (Operator)
    {
    case '+':
        return op1+op2;
    case '-':
        return op1-op2;
    case '*':
        return op1*op2;
    case '/':
        if (op2==0)
        {
            printf("Error: Division by zero error\n");
        }else{
            return op1/op2;
        }
    case '^':
        return (int)pow(op1,op2);
    
    default:
        printf("Error: Invalid operator %c\n",Operator);
        break;
    }
}
int evaluatePostfix(char *postfix){
    int i=0;
    while (postfix[i]!='\0')
    {
        if (isalpha(postfix[i]))
        {
            int value;
            printf("enter value for %c : ",postfix[i]);
            scanf("%d",&value);
            push(value);
            i++;
        }else if(isdigit(postfix[i])){
            int value=0;
            while (isdigit(postfix[i]))
            {
                value=value*10+(postfix[i]-'0');
                i++;
            }
            push(value);
        }else if(isOperator(postfix[i])){
            int op2=pop();
            int op1=pop();
            char Operator=postfix[i];
            int result=applyOperator(Operator,op1,op2);
            push(result);
            i++;
        }else{
            i++;
        }
    }
    int finalresult=pop();
    if(top!=NULL){
        printf("Error: invalid postfix expression\n");
    }
    return finalresult;
}
int main() {
    char postfix[100];
    printf("Enter a postfix expression: ");
    fgets(postfix, sizeof(postfix), stdin);

    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}