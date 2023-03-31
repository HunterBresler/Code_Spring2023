#include <iostream>


using namespace std;


//Double linked list data structure
struct dLinkedList
{
    int data;
    dLinkedList* right;
    dLinkedList* left;
};
typedef dLinkedList node;


//*Linked list functions
node* getNode();
//Create a node and return a pointer to it
int getLen(node* start);
//Gets the length of a linked list
void createList(int n, node* &start);
//Create a linked list/append to a linked list
void deleteAtMid(int position, node* start);
//Delete the nth node of a linked list
void insertAtMid(int position, node* start);
//Add a new node at the nth position of a linked list
void output(node* start);
//Outputs all elements of the linked list parameter


//*MAIN
int main(){

    //Create our linked list
    node* start = NULL;
    output(start);
    createList(4, start);
    output(start);

    //Delete the node at the nth position
    deleteAtMid(2, start);
    output(start);

    //Insert a new node at the nth position
    insertAtMid(2, start);
    output(start);

    return 0;

}


//*Linked list functions
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


int getLen(node* start)
{
    //Declare variables
    node* temp = start;
    int len = 0;

    //Increment for start node
    if (start == NULL)
    {
        return 0;
    }
    else
    {
        len++;
    }

    //Increment len for each additional member of the linked list
    while (temp->right != NULL)
    {
        temp = temp->right;
        len++;
    }

    return len;
}


void createList(int n, node* &start)
{
    //Declare node pointers
    node* newNode;
    node* prev;
    node* temp;
    int i = 0; //To iterate through the loop

    //Check for an empty list
    if (start == NULL)
    {
        start = getNode();
        i++;
    }

    //Set temp to start
    temp = prev = start;

    //Loop to create loop
    for (; i < n; i++)
    {
        //Create new node and point temp to it
        newNode = getNode();
        temp->right = newNode;

        //Set temp to the new node
        temp = temp->right;

        //Set temp->left to point at the previous node
        temp->left = prev;

        //Set prev equal to temp
        prev = temp;
    }
}


void deleteAtMid(int position, node *start)
{
    //Declare node pointers
    node* temp;
    node* prev;

    //Error check for an empty list
    if (start == NULL)
    {
        cout << "\nError:Empty List";
        return;
    }

    //Make sure the position is a middle position
    int listLen = getLen(start);

    //Error check for empty list
    if (listLen > 1 && position < listLen)
    {
        //Set temp and prev to start
        temp = prev = start;

        //Loop to position
        for (int i = 1; i < position; i++) //1 to represent the first element
        {
            prev = temp;
            temp = temp->right;
        }

        //Delete the node at the position
        prev->right = temp->right;
        temp->right->left = prev;
        free(temp);

        cout << "\nNode deleted.\n";
    }
    else
    {
        cout << "\nError: Position is not a middle position";
    }
}


void insertAtMid(int position, node* start)
{
    //Declare node pointers
    node* temp;
    node* prev;
    node* newNode = getNode();

    //Error check for an empty list
    if (start == NULL)
    {
        cout << "\nError:Empty List";
        return;
    }

    //Make sure the position is a middle position
    int listLen = getLen(start);

    //Error check for empty list
    if (listLen > 1 && position < listLen)
    {
        //Set temp and prev to start
        temp = prev = start;

        //Loop to position
        for (int i = 1; i < position; i++) //1 to represent the first element
        {
            prev = temp;
            temp = temp->right;
        }

        //Insert the new node at the position
        newNode->right = temp;
        newNode->left = prev;

        //Point temp and prev to the new node
        temp->left = newNode;
        prev->right = newNode;

        cout << "\nNode inserted.\n";
    }
    else
    {
        cout << "\nError: Position is not a middle position";
    }
}


void output(node* start)
{
    node* temp = start;

    //Check for empty list
    if (start == NULL)
    {
        cout << "\nThe list is empty.";
        return;
    }
    //Print the first element
    else
    {
        cout << "\nThe elements of the linked list are: " << start->data;
    }

    //Loop through the list and display the data element of each node
    while (temp->right != NULL)
    {
        temp = temp->right;
        cout << ", " << temp->data;
    }
}