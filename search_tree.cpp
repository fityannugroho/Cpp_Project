// SEARCH TREE PROGRAM
// Develop by : Fityandhiya Islam Nugroho
// Language   : Eng
// Keyword      : search_tree, binary_tree, tree, node, preorder, inorder, postorder, numeric, alphabet

#include <iostream>
#include <sstream>
#include <conio.h>
#include <cstdlib>

using namespace std;

// declaration node 'tree'
struct tree {
    int value;
    tree *left, *right;
};

// declare the 'root' (grand-grand-grand-...-parent) of the tree
tree *root;

// variable to catch the user input
string str;

// mode data type
bool typeAlphabet = false;

void createTree();                              // create new tree by setting the root to NULL
bool isInteger(string str);                     // checking the user input to make sure it is a integer, either positive or negative
int numConversion(string str);                  // convert the type data of user input from string to integer
string alphabetConvert(string str);             // to checking user input if it is an alphabet word
char displayAlpha(int num);                     // to convert integer to a alphabet word based on alphabet order
void menuInputData();                           // menu to input a data
void insertTree(tree** current, int num);       // to add a new node of the tree, and set it to left or right-side based on the comparison of new value with its parent value 
void printValue(tree *node);                    // to print the value of a node
void preOrder(tree *node);                      // show the data from each node of the tree using pre-order rule
void inOrder(tree *node);                       // show the data from each node of the tree using in-order rule
void postOrder(tree *node);                     // show the data from each node of the tree using post-order rule
void findNode(tree *node, int x);               // to search a value in the tree

main(){
    createTree();
    
    while (1){
        system("cls");
        cout << "\n ================ SEARCH TREE ================";
        cout << "\n           1. Insert New Data";
        cout << "\n           2. Show Preorder";
        cout << "\n           3. Show InOrder";
        cout << "\n           4. Show PostOrder";
        cout << "\n           5. Find";
        cout << "\n                                   0. Exit";
        cout << "\n  Select : "; cin >> str;

        if (!isInteger(str)){
            cout << "\n Please input a number to select the menu !!!";
            cout << "\n Press Any Key To Continue..."; getch();
            continue;
        }
        
        switch(numConversion(str)) {
            case 1:
                menuInputData();
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
                findNode(root, numConversion(alphabetConvert(str)));
                break;
            case 0:
                cout << "\n You exit the application \n";
                exit(1); break;
            default:
                cout << "\n Sorry, your choice in not available !!!";
                break;
        }
        cout << "\n Press Any Key To Continue..."; getch();
    }
}

void createTree(){
    root = NULL;

    do {
        system("cls");
        cout << "\n --- Select Type Data : ---";
        cout << "\n 1. Numbers";
        cout << "\n 2. Alphabet";
        cout << "\n   Select : "; cin >> str;

        if (numConversion(str) == 2)
            typeAlphabet = true;
        if (numConversion(str) == 1 || numConversion(str) == 2)
            cout << "\n Type Data Selected\n";
        else
            cout << "\n Please input a number to select the menu !!!";
        getch();
    } while ((str != "1" && str != "2"));
}

bool isInteger(string str){
    int isNum = 0, notNum = 0, isNegative = 0;

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

string alphabetConvert(string str){
    int valid = 0;
    char word[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    if (str.size() != 1)
        return "FALSE";
    
    for (int i = 0; i < str.size(); i++){
        for (int j = 0; j < sizeof(word); j++){
            if (tolower(str[i]) == word[j]){
                str = to_string(j+1);
                valid++;
            }
        }
    }

    if (valid == 1)
        return str;
    else
        return "FALSE";
}

char displayAlpha(int num){
    char word[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char temp;
    
    for (int i = 0; i < sizeof(word); i++){
        if (num == i+1){
            temp = toupper(word[i]);
            break;
        }
    }
    return temp;
}

void menuInputData(){
    system("cls");

    /* Input Data */
    if (typeAlphabet)
        cout << "\n Insert The Data (A Word) : ";
    else
        cout << "\n Insert The Data (A Number) : ";
    cin >> str;
    
    /* checking user input */
    if (typeAlphabet && alphabetConvert(str) != "FALSE"){
        insertTree(&root, numConversion(alphabetConvert(str)));
        return;
    }
    if (!typeAlphabet && isInteger(str)){
        insertTree(&root, numConversion(str));
        return;
    }
    
    // error input value
    if (typeAlphabet)
        cout << "\n Please just input the data in one word !!!";
    else
        cout << "\n Please just input the data in integer !!!";
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

        if (typeAlphabet)
            cout << "\n\n New node is created with value = " << displayAlpha((*current)->value);
        else
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
        cout << "\n\n This value is already exists in the tree !!!";
}

void printValue(tree *node){
    if (typeAlphabet)
            cout << displayAlpha(node->value) << "  ";
    else
        cout << node->value << "  ";
}

void preOrder(tree *node){
    if (node != NULL){
        printValue(node);
        preOrder(node->left);
        preOrder(node->right);
    }
}

void inOrder(tree *node){
    if (node != NULL){
        inOrder(node->left);
        printValue(node);
        inOrder(node->right);
    }
}

void postOrder(tree *node){
    if (node != NULL){
        postOrder(node->left);
        postOrder(node->right);
        printValue(node);
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

    if (x == node->value){
        if (typeAlphabet)
            cout << "\n Data " << displayAlpha(x) << " is founded in the tree.";
        else if (!typeAlphabet)
            cout << "\n Data " << x << " is founded in the tree.";
    }
}
