//Yvonne Sagina Mwima SCT221-0627/2022
//Hailley Wanjiru Njunji SCT221-0225/2022
//Yuvinalis Maiko SCT221-0261/2022

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* newNode(int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* createBST(int arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = (start + end) / 2;
    struct node* root = newNode(arr[mid]);
    root->left = createBST(arr, start, mid - 1);
    root->right = createBST(arr, mid + 1, end);
    return root;
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

struct node* deleteNode(struct node* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right); 
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

int height(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void printLevelHeight(struct node* root, int data, int level) {
    if (root == NULL) {
        return;
    }

    if (root->data == data) {
        printf("Level of %d: %d\n", data, level);
        printf("Height of %d: %d\n", data, height(root));
        return;
    }

    printLevelHeight(root->left, data, level + 1);
    printLevelHeight(root->right, data, level + 1);
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct node* root = createBST(arr, 0, n - 1);

    printf("Initial height of BST: %d\n", height(root));

    root = deleteNode(root, 30); 

    printf("Height of BST after deletion: %d\n", height(root));

    printLevelHeight(root, 45, 1); 

    return 0;
}
