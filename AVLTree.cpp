#include <bits/stdc++.h> 

class BinaryTreeNode {
public : 
    T data;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;
    int height;

    BinaryTreeNode(T data) {
        this -> data = data;
        left = NULL;
        right = NULL;
        height=1;
    }
};


class AVLTree {
 public:
    BinaryTreeNode<int> *root = NULL;
    int getHeight(BinaryTreeNode<int> *root) {
        int leftHeight = root->left != NULL ? root->left->height : 0;
        int rightHeight = root->right != NULL ? root->right->height : 0;
        return 1 + max(leftHeight,rightHeight);
    }
    
    int getBalanceFactor(BinaryTreeNode<int> *root) {
        int leftHeight = root->left != NULL ? root->left->height : 0;
        int rightHeight = root->right != NULL ? root->right->height : 0;
        return leftHeight - rightHeight;
    }
    
    BinaryTreeNode<int> *rightRotate(BinaryTreeNode<int> *y)  {  
        BinaryTreeNode<int> *x = y->left;  
        BinaryTreeNode<int> *T2 = x->right;  
        x->right = y;  
        y->left = T2;  
        y->height = getHeight(y);
        x->height = getHeight(x);  
        return x;  
    }  
    
    
    BinaryTreeNode<int> *leftRotate(BinaryTreeNode<int> *x)  {  
        BinaryTreeNode<int> *y = x->right;  
        BinaryTreeNode<int> *T2 = y->left;  
        y->left = x;  
        x->right = T2;  
        y->height = getHeight(y);
        x->height = getHeight(x);  
        return y;  
    } 
    
    
    BinaryTreeNode<int> * minValueNode(BinaryTreeNode<int>* node) { 
        BinaryTreeNode<int>* current = node; 
        while (current->left != NULL) 
            current = current->left; 
     
        return current; 
    } 
     
    
    BinaryTreeNode<int>* insert(int data,BinaryTreeNode<int> *root) {
        if (root == NULL) {
            root = new BinaryTreeNode<int>(data);
            root->left = NULL;
            root->right = NULL;
            root->height = getHeight(root);
            return root;
        }
        
        if (data < root->data) {
            root->left = insert(data,root->left);
        } else {
            root->right = insert(data,root->right);
        }
        
        root->height = getHeight(root);
        int balanceFactor = getBalanceFactor(root);
        
        if (balanceFactor > 1 && root->left && data < root->left->data) {
            return rightRotate(root);
        } else if (balanceFactor > 1 && root->left && data > root->left->data) {
            root->left = leftRotate(root->left);  
            return rightRotate(root);  
        } else if (balanceFactor < -1 && root->right && data > root->right->data) {
            return leftRotate(root);
        } else if (balanceFactor < -1 && root->right && data < root->right->data) {
            root->right = rightRotate(root->right);  
            return leftRotate(root);  
        }
        return root;
    }

    
    BinaryTreeNode<int>* deleteNodeFromTree(int data,BinaryTreeNode<int> *root) {
        if (root == NULL) 
            return root; 
        if (data < root->data) {
            root->left = deleteNodeFromTree(data,root->left);
        } else if (data > root->data ){
            root->right = deleteNodeFromTree(data,root->right);
        } else{  
            if((root->left == NULL) || (root->right == NULL)) { 
                BinaryTreeNode<int> *temp = root->left ? root->left : root->right; 
     
                if (temp == NULL) { 
                    temp = root; 
                    root = NULL; 
                } 
                else
                *root = *temp; 
                free(temp); 
            }  else { 
                BinaryTreeNode<int> *temp = minValueNode(root->right); 
                root->data = temp->data; 
                root->right = deleteNodeFromTree(temp->data,root->right); 
            } 
        } 
    
        if (root == NULL) {
            return NULL;
        }
        
        root->height = getHeight(root);
        int balance = getBalanceFactor(root);
        
        if (balance > 1 && 
            getBalanceFactor(root->left) >= 0) 
            return rightRotate(root); 
     
        if (balance > 1 && 
            getBalanceFactor(root->left) < 0) 
        { 
            root->left = leftRotate(root->left); 
            return rightRotate(root); 
        } 
    
        if (balance < -1 && 
            getBalanceFactor(root->right) <= 0) 
            return leftRotate(root); 
    
        if (balance < -1 && 
            getBalanceFactor(root->right) > 0) 
        { 
            root->right = rightRotate(root->right); 
            return leftRotate(root); 
        } 
        return root;
    }
};


