#include <iostream>


using namespace std;


//Single linked list data structure
struct node
{
    int data;
    node *next;
};


//*Linked list functions
node* getNode();
//Create a node and return a pointer to it
int getLen(node *start);
//Gets the length of a linked list
void createList(int n, node *start);
//Create a linked list/append to a linked list
void deleteAtMid(int position, node *start);
//Delete the nth node of a linked list
void insertAtMid(int position, node *start);
//Add a new node at the nth position of a linked list


//*MAIN
int main(){

    //Create our linked list
    node *start = NULL;
    createList(4, start);

    //Delete the node at the nth position
    deleteAtMid(2, start);

    //Insert a new node at the nth position
    insertAtMid(2, start);

    return 0;

}


//*Linked list functions
node* getNode()
{
    //Create node
    node *newNode;
    newNode = (node*)malloc(sizeof(node));

    //Enter data value
    cout << "\nEnter data of type int: ";
    cin >> newNode->data;

    //Return the pointer to the new node
    return newNode;
}


int getLen(node *start)
{
    //Declare variables
    node *temp = start;
    int len = 0;

    //Increment len for each member of the linked list
    while (temp != NULL)
    {
        temp = temp->next;
        len++;
    }

    return len;
}


void createList(int n, node *start)
{
    //Declare node pointers
    node *newNode, *temp;
    int i = 0; //To iterate through the loop

    //Check for an empty list
    if (start == NULL)
    {
        start = getNode();
        i++;
    }

    //Set temp to start
    temp = start;

    //Loop to create loop
    for (; i < n; i++)
    {
        //Create new node and point temp to it
        newNode = getNode();
        temp->next = newNode;

        //Set temp to the new node
        temp = temp->next;

    }

}


void deleteAtMid(int position, node *start)
{
    //Declare node pointers
    node *temp, *prev;

    //Error check for an empty list
    if (start == NULL)
    {
        cout << "Error:Empty List";
        return;
    }

    //Make sure the position is a middle position
    int listLen = getLen(start);

    //Error check for empty list
    if (listLen > 1 && listLen < position)
    {
        //Set temp and prev to start
        temp = prev = start;

        //Loop to position
        for (int i = 0; i < position; i++)
        {
            prev = temp;
            temp = temp->next;
        }

        //Delete the node at the position
        prev->next = temp->next;
        free(temp);
    }
    else
    {
        cout << "\nError: Position is not a middle position";
    }
}


void insertAtMid(int position, node *start)
{
    //Declare node pointers
    node *temp, *prev, *newNode = getNode();

    //Error check for an empty list
    if (start == NULL)
    {
        cout << "Error:Empty List";
        return;
    }

    //Make sure the position is a middle position
    int listLen = getLen(start);

    //Error check for empty list
    if (listLen > 1 && listLen < position)
    {
        //Set temp and prev to start
        temp = prev = start;

        //Loop to position
        for (int i = 0; i < position; i++)
        {
            prev = temp;
            temp = temp->next;
        }

        //Insert the new node at the position
        newNode->next = temp;
        prev->next = newNode;
    }
    else
    {
        cout << "\nError: Position is not a middle position";
    }
}

