#include<stdio.h>
#include<stdlib.h>
void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
void buildMaxHeap(int arr[],int size){
    for (int i = 1; i < size; i++)
    {
        int child=i;
        while(child>0){
            int parent=(child-1)/2;
            if (arr[parent]>arr[child])
            {
                swap(&arr[parent],&arr[child]);
                child=parent;
            }else{
                break;
            }
        }
    }
}
struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};
struct Node *createNode(int data){
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->data=data;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
struct Node *buildMinHeapTree(int arr[],int size,int i){
    if(i<size){
        struct Node *root=createNode(arr[i]);
        root->left=buildMinHeapTree(arr,size,2*i+1);
        root->right=buildMinHeapTree(arr,size,2*i+2);
        return root;
    }
    return NULL;
}
void inOrder(struct Node *root){
    if(root!=NULL){
        inOrder(root->left);
        printf("%d ",root->data);
        inOrder(root->right);
    }
}
int main(){
    int *arr=NULL;
    int size=0;
    int value;
    printf("Enter the value you want to insert and press -1 for stop: ");
    while(1){
        scanf("%d",&value);
        if (value==-1)
        {
            break;
        }
        size++;
        arr=(int *)realloc(arr,size*sizeof(int));
        arr[size-1]=value;
    }
    buildMaxHeap(arr,size);
    printf("Min heap array: ");
    for (int i = 0; i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    struct Node *minHeapRoot=buildMinHeapTree(arr,size,0);
    printf("Inorder traversal of min-heap tree is: ");
    inOrder(minHeapRoot);
    printf("\n");
    free(arr);
    return 0;
}