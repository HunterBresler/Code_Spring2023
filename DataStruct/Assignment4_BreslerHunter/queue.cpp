#include <iostream>


using namespace std;


//Queue data structure
//queue is a list of positive numbers with a default value of -1
int queue[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int first_in_line = 0;


//*Linked list functions
//Add a new node at the end of the queue
void enqueue();
//Delete the node at the beginning of the queue
void dequeue();
//Outputs all elements of a queue
void display();


int main(){

    for (int i = 0; i < 10; i++)
    {
        enqueue();
    }
    
    for (int i = 0; i < 5; i++)
    {
        dequeue();
    }

    for (int i = 0; i < 4; i++)
    {
        enqueue();
    }

    display();

    return 0;
}

//*Linked list functions
void enqueue()
{
    //iterates through queue
    int i = first_in_line;

    //Get to the end of the queue
    while (queue[i] != -1)
    {
        //increment i
        i++;

        //Loop through array
        if (i >= sizeof(queue) / sizeof(int))
        {
            i = 0;
        }

        if (i == first_in_line)
        {
            cout << "\nERROR: Queue is full";
            exit(2);
        }

    }

    //Get input for new queue element
    int input;
    cout << "\nEnter the data you'd like to queue: ";
    cin >> input;

    queue[i] = input;
}

void dequeue()
{
    //Check for empty queue
    if (queue[first_in_line] == -1)
    {
        cout << "\nThere is no data to dequeue.";
    }
    else
    {   
        //Display deleted data
        cout << "\nData: " << queue[first_in_line];

        //Remove the first item in queue and update first_in_line
        queue[first_in_line] = -1;
        first_in_line++;

        //Loop back through array
        if (first_in_line >= sizeof(queue) / sizeof(int))
        {
            first_in_line = 0;
        }
    }
}



void display()
{
    //iterates through queue
    int i = first_in_line;

    //Display
    cout << "\nQueue {";

    //Get to the end of the queue
    while (queue[i] != -1)
    {

        //Display element of queue
        cout << queue[i];

        //Loop through array
        if (i + 1 >= sizeof(queue) / sizeof(int))
        {
            i = 0;
        }
        else
        {
            i++;
        }
        
        //Add , 
        if (queue[i] != -1 && i != first_in_line)
        {
            cout << ", ";
        }
        else if (i == first_in_line)
        {
            //break to prevent infinite loop
            break;
        }

    }

    cout << "}";
}