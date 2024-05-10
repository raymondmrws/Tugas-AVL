#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
    int ht; // height of node
};
struct node* root = NULL;

struct node* rotate_left(struct node* root);
struct node* rotate_right(struct node* root);
int height(struct node* root);
struct node* minValueNode(struct node* node);

struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;

    // update the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);

    // return the new node after rotation
    return right_child;
}

struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;

    // update the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);

    // return the new node after rotation
    return left_child;
}

int height(struct node* root)
{
    int lh, rh;

    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
    {
        lh = 0;
    }
    else
    {
        lh = 1 + root->left->ht;
    }
    if (root->right == NULL)
    {
        rh = 0;
    }
    else
    {
        rh = 1 + root->right->ht;
    }
    if (lh > rh)
        return lh;
    return rh;
}

int balance_factor(struct node* root)
{
    int lh, rh;

    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
    {
        lh = 0;
    }
    else
    {
        lh = 1 + root->left->ht;
    }
    if (root->right == NULL)
    {
        rh = 0;
    }
    else
    {
        rh = 1 + root->right->ht;
    }
    return lh - rh;
}

struct node* create_node(int data)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->right = NULL;
    new_node->left = NULL;

    return new_node;
}

struct node* insert(struct node* root, int data)
{
    if (root == NULL)
    {
        struct node* new_node = create_node(data);
        root = new_node;
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);

       
        if (balance_factor(root) == -2)
        {
            if (data > root->right->data)
            { // case RR
                root = rotate_left(root);
            }
            else
            { // case RL
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    }
    else
    {
        root->left = insert(root->left, data);

        if (balance_factor(root) == 2)
        {
            // CASE LL
            if (data < root->left->data)
            {
                root = rotate_right(root);
            }
            // CASE LR
            else
            {
                root->left = rotate_left(root->left);
                root = rotate_right(root);
            }
        }
    }
    
    root->ht = height(root);
    return root;
}

struct node* delete_node(struct node* root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = delete_node(root->left, data);
    else if (data > root->data)
        root->right = delete_node(root->right, data);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            struct node* temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            struct node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->ht = height(root);

    int balance = balance_factor(root);

    if (balance > 1 && balance_factor(root->left) >= 0)
        return rotate_right(root);

    if (balance > 1 && balance_factor(root->left) < 0)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && balance_factor(root->right) <= 0)
        return rotate_left(root);

    if (balance < -1 && balance_factor(root->right) > 0)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

struct node* minValueNode(struct node* node)
{
    struct node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

struct node* search(struct node* root, int data)
{
    if (root == NULL || root->data == data)
        return root;

    if (root->data < data)
        return search(root->right, data);

    return search(root->left, data);
}


void inorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}


void postorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main()
{

    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 16);
    root = insert(root, 17);
    root = insert(root, 8);
    root = insert(root, 6);

    printf("Inorder traversal before deletion: ");
    inorder(root);
    printf("\n");

    int key = 16;
    root = delete_node(root, key);
    printf("Inorder traversal after deletion of %d: ", key);
    inorder(root);
    printf("\n");

    key = 10;
    struct node* result = search(root, key);
    if (result != NULL)
        printf("%d found in the tree\n", key);
    else
        printf("%d not found in the tree\n", key);

    return 0;
}
