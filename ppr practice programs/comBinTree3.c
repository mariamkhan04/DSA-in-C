#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *create_node(int data) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct node *insert(struct node *root, int data) {
    if (root == NULL) {
        return create_node(data);
    }

    struct node *parent = root;
    while (1) {
        if (parent->left == NULL) {
            parent->left = create_node(data);
            break;
        } else if (parent->right == NULL) {
            parent->right = create_node(data);
            break;
        } else {
            parent = parent->left;
        }
    }

    return root;
}

void print_tree(struct node *root) {
    if (root == NULL) {
        return;
    }

    print_tree(root->left);
    printf("%d ", root->data);
    print_tree(root->right);
}

int get_user_input() {
    int data;
    printf("Enter a value to insert into the tree: ");
    scanf("%d", &data);
    return data;
}

int main() {
    struct node *root = NULL;

    while (1) {
        int data = get_user_input();
        if (data == -1) {
            break;
        }

        root = insert(root, data);
    }

    print_tree(root);

    return 0;
}
