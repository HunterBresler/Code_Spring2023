#include <iostream>


using namespace std;


//Binary tree data structure
struct binaryTree
{
    int data;
    binaryTree *left, *right;
};
typedef binaryTree node;

node* root;

//*Binary Tree functions
//Create a node and return a pointer to it
node* getNode();
//Create a node and return a pointer to it
node* getNode(int data);
//Create a binary tree of n levels
void createBinaryTree(node* level, int n);
//Display binary tree values through in order traversal
node* inOrder(node* node);


//stack data structure
node* stack[10];
int top_of_stack = 0;


//*Stack functions
//Add a new node at the end of the stack
void push(node* node);
//Delete the node at the beginning of the stack
void pop();
//Outputs all elements of a stack
void display();


int main(){

    createBinaryTree(root, 3);
    inOrder(root);

    return 0;
}


//*Binary Tree functions
node* getNode()
{
    //Create node
    node* newNode;
    newNode = (node*)malloc(sizeof(node));

    //Enter data value
    cout << "\nEnter data of type int: ";
    cin >> newNode->data;

    //Enter left/right values
    newNode->left = newNode->right = NULL;

    //Return the pointer to the new node
    return newNode;
}

node* getNode(int data)
{
    //Create node
    node* newNode;
    newNode = (node*)malloc(sizeof(node));

    //Enter data value
    newNode->data = data;

    //Enter left/right values
    newNode->left = newNode->right = NULL;

    //Return the pointer to the new node
    return newNode;
}

void createBinaryTree(node* level, int n)
{
    if (n < 0)
    {
        cout << "\nERROR: Cannot create a tree of 0 or negative size";
        exit(3);
    }
    
    //Create root
    if (root == NULL)
    {
        cout << "\nCreate root.";
        root = getNode();
        level = root;

        //Decrement n because the root is a level
        n--;
    }

    if (n == 0)
    {
        return;
    }

    //Create level
    level->left = getNode();
    level->right = getNode();

    //Recur for each branch
    createBinaryTree(level->left, n - 1);
    createBinaryTree(level->right, n - 1);

}

node* inOrder(node* node)
{
    if (node == NULL)
    {
        //pop();
        return node;
    }

    if (node == root)
    {
        //push node
        //push(node);
    }
    
    //Recur for the left branch
    //push(node->left);
    inOrder(node->left);
 
    //Display data
    cout << node->data << " ";
 
    //Recur for right branch
    //push(node->right);
    inOrder(node->right);

    return node;
}

//*Stack functions
void push(node* node)
{
    // Check for a full stack
    if (top_of_stack >= (sizeof(stack) / sizeof(int)))
    {
        cout << "\nERROR: Stack is full";
        exit(2);
    }
    else
    {
        //Add data
        stack[top_of_stack] = node;

        // increment top_of_stack
        top_of_stack++;
    }
}

void pop()
{
    //Check for empty stack
    if (top_of_stack == 0)
    {
        cout << "\nThere is no data to pop.";
    }
    else
    {   
        //Update top_of_stack
        top_of_stack--;

        //Display popped data
        cout << "\nData: " << stack[top_of_stack - 1]->data;
        //display();
    }
}



void display()
{
    //iterates through stack
    int i = 0;

    //Display
    cout << "\nStack {";

    //Get to the end of the stack
    while (i < top_of_stack - 1)
    {
        //Display element of stack
        cout << stack[i]->data << ", ";

        //increment i
        i++;
    }

    cout << stack[i]->data << "}";
}