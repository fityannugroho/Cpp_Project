// Developed by : Fityandhiya Islam Nugroho
// Binary Tree
// topic : cpp, tree, binary tree, linked list, node, head.
// language : Eng

#include <iostream>
#include <sstream>
#include <conio.h>

using namespace std;

// declaration node 'tree'
struct tree{
    int value;
    tree *left, *right;
};

// declare the 'root' (grand-grand-grand-...-parent) of the tree
tree *root;

// variable to catch the user input
string str;

void createTree();                              // create new tree by setting the root to NULL
bool isInteger(string str);                     // checking the user input to make sure it is a integer, either positive or negative
int numConversion(string str);                  // convert the type data of user input from string to integer
void insertTree(tree** current, int num);       // to add a new node of the tree, and set it to left or right-side based on the comparison of new value with its parent value 
void preOrder(tree *node);                      // show the data from each node of the tree using pre-order rule
void inOrder(tree *node);                       // show the data from each node of the tree using in-order rule
void postOrder(tree *node);                     // show the data from each node of the tree using post-order rule
void findNode(tree *node, int x);               // to search a value in the tree

main(){
    createTree();
    while (1){
        system("cls");
        cout << "\n ================== TREE ==================";
        cout << "\n           1. Insert New Data";
        cout << "\n           2. Show Preorder";
        cout << "\n           3. Show InOrder";
        cout << "\n           4. Show PostOrder";
        cout << "\n           5. Find";
        cout << "\n                                   0. Exit";
        cout << "\n  Select : "; cin >> str;

        if (isInteger(str) == false){
            cout << "\n Please input a number to select the menu !!!";
            cout << "\n Press Any Key To Continue..."; getch();
            continue;
        }
        
        switch(numConversion(str)) {
            case 1:
                system("cls");
                cout << "\n Insert The Data : "; cin >> str;

                if (isInteger(str) == true)
                    insertTree(&root, numConversion(str));
                else
                    cout << "\n Please just input the data in integers !!!";
                break;

            case 2:
                cout << "\n Data Pre-Order : ";
                preOrder(root);
                break;

            case 3:
                cout << "\n Data In-Order : ";
                inOrder(root);
                break;

            case 4:
                cout << "\n Data Post-Order : ";
                postOrder(root);
                break;

            case 5:
                system("cls");
                cout << "\n Please enter the data to be searched : "; cin >> str;
                findNode(root, numConversion(str));
                break;

            case 0:
                cout << "\n You exit the application \n";
                exit(1);
                break;

            default:
                cout << "\n Sorry, your choice in not available !!!";
                break;
        }
        cout << "\n Press Any Key To Continue..."; getch();
    }
}

void createTree(){
    root = NULL;
}

bool isInteger(string str){
    int result, isNum = 0, notNum = 0, isNegative = 0;

	for (int i = 0; i < str.size(); ++i){
        if (str[0] == '-')
            isNegative = 1;
		else if (isdigit(str[i]))
			isNum++;
		else 
			notNum++;
	}

	if (notNum == 0)
		return true;
	else
    return false;
}

int numConversion(string str){
	int result;

	if (isInteger(str) == true){
		stringstream stream(str);
		stream >> result;
	}
    return result;
}

void insertTree(tree** current, int num){
    
    // to creating a new node
    if ((*current) == NULL){
        tree *newNode = new tree;
        newNode->value = num;
        newNode->left = newNode->right = NULL;
        
        (*current) = newNode;

        // set the root value when the first newNode created
        if (root == NULL)
            root = (*current);

        cout << "\n\n New node is created with value = " << (*current)->value;
        return;
    }

    // Checking value of data to set the moving
    if (num < (*current)->value){
        cout << " -move to left-";
        insertTree(&(*current)->left, num);
    }
    if (num > (*current)->value){
        cout << " -move to right-";
        insertTree(&(*current)->right, num);
    }
    if (num == (*current)->value)
        cout << "\n\n This number is already exists in the tree !!!";
}

void preOrder(tree *node){
    if (node != NULL){
        cout << node->value << "  ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

void inOrder(tree *node){
    if (node != NULL){
        inOrder(node->left);
        cout << node->value << "  ";
        inOrder(node->right);
    }
}

void postOrder(tree *node){
    if (node != NULL){
        postOrder(node->left);
        postOrder(node->right);
        cout << node->value << "  ";
    }
}

void findNode(tree *node, int x){
    if (node == NULL){
        cout << "\n Sorry, Data " << x << " is not found in the tree !!!";
        return;
    }
    if (x > node->value)
        findNode(node->right, x);

    if (x < node->value)
        findNode(node->left, x);

    if (x == node->value)
        cout << "\n Data " << x << " is founded in the tree.";
}
