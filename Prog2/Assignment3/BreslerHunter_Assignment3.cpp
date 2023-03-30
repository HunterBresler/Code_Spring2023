/*
    Author: Hunter Bresler
    Date: 2/26/2023
    Assignment3: Class of our class
*/

#include <iostream>
#include <string>

using namespace std;



struct allGrades_COP3014
{
    double quiz1;   
    double quiz2;
    double quiz3;
    double midterm;
    double final;
};



//*Defines a class that records a student and they're grades
class COP3014
{
    private:
        //*Declare member variables
        string firstName;
        string lastName;
        int zNumber;
        bool missed_exam;
        double totalGrade;
        char finalGrade;
        allGrades_COP3014 allGrades; 

    public:
        //*Constructor
        COP3014();
        
        
        //*Getter Functions
        string get_firstName();
        string get_lastName();
        int get_zNumber();
        bool get_missed_exam();
        double get_totalGrade();
        char get_finalGrade();
        allGrades_COP3014 get_allGrades();


        //*Setter Functions
        void set_firstName(string new_firstName);
        void set_lastName(string new_lastName);
        void set_zNumber(int new_zNumber);
        void set_missed_exam(bool new_missed_exam);
        void set_totalGrade(double new_totalGrade);
        void set_finalGrade(char new_finalGrade);
        void set_allGrades(allGrades_COP3014& new_allGrades);

        //*Computational Functions (calc_...)
        void calc_totalGrade();
        void calc_finalGrade();

        //*IO Functions
        void input();
        void output();

        //*Check Functions
        void check_inputs();
 
};

 

//*MAIN
int main(){

    //Test class
    COP3014 A_student, input_student;
    allGrades_COP3014 A_studentGrades = {93, 79, 91, 90, 99};

    //*Test case 1: A_student
    //Test setter functions
    A_student.set_firstName("Hunter");
    A_student.set_lastName("Bresler");
    A_student.set_zNumber(12345678);
    A_student.set_allGrades(A_studentGrades);
    A_student.set_totalGrade(59.3);
    A_student.set_finalGrade('C');
    A_student.output();
    //Test calc functions
    A_student.calc_totalGrade();
    A_student.calc_finalGrade();
    A_student.output();


    //*Test case 2: input_student
    //Test setter functions
    input_student.input();
    input_student.output();


    return 0;
}



/*
    !This is the list of functions in the COP3014 Class 
    !The functions will be folded below
*/
//*Constructor
COP3014::COP3014()
{
    allGrades = {100,100,100,100,100};
    missed_exam = 0;
}


//*Getter Functions
string COP3014::get_firstName()
{
    return firstName;
}

string COP3014::get_lastName()
{
    return lastName;
}

int COP3014::get_zNumber()
{
    return zNumber;
}

bool COP3014::get_missed_exam()
{
    return missed_exam;
}

double COP3014::get_totalGrade()
{
    return totalGrade;
}

char COP3014::get_finalGrade()
{
    return finalGrade;
}

allGrades_COP3014 COP3014::get_allGrades()
{
    return allGrades;
}


//*Setter Functions
void COP3014::set_firstName(string new_firstName)
{
    firstName = new_firstName;
}

void COP3014::set_lastName(string new_lastName)
{
    lastName = new_lastName;
}

void COP3014::set_zNumber(int new_zNumber)
{
    zNumber = new_zNumber;
}

void COP3014::set_missed_exam(bool new_missed_exam)
{
    missed_exam = new_missed_exam;
}

void COP3014::set_totalGrade(double new_totalGrade)
{
    calc_totalGrade(); //The illusion of choice
}

void COP3014::set_finalGrade(char new_finalGrade)
{
    finalGrade = new_finalGrade;
}

void COP3014::set_allGrades(allGrades_COP3014& new_allGrades)
{
    allGrades = new_allGrades;

    //Automatically calculates totalGrade
    get_totalGrade();
}


//*Computational Functions (calc_...)
void COP3014::calc_totalGrade()
{
    totalGrade = (allGrades.quiz1 + allGrades.quiz2 + allGrades.quiz3)*.2/3 + allGrades.midterm*0.3 + allGrades.final*0.5;
}

void COP3014::calc_finalGrade()
{
    if (missed_exam)
    {
        finalGrade = 'F';
    }
    else if (totalGrade>=90)
    {
        finalGrade = 'A';
    }
    else if (totalGrade>=80)
    {
        finalGrade = 'B';
    }
    else if (totalGrade>=70)
    {
        finalGrade = 'C';
    }
    else if (totalGrade>=60)
    {
        finalGrade = 'D';
    }
    else
    {
        finalGrade = 'F';
    }
}


//*IO Functions
void COP3014::input()
{
    cout << "Enter the student's first and last name: ";
    cin >> firstName >> lastName;

    cout << "Enter the student's Z-number: ";
    cin >> zNumber;

    cout << "Enter the student's total grade in the class: ";
    cin >> totalGrade;

    cout << "Enter the student's final letter grade: ";
    cin >> finalGrade;

    cout << "Enter the student's 3 quiz grades: ";
    cin >> allGrades.quiz1 >> allGrades.quiz2 >> allGrades.quiz3;

    cout << "Enter the student's midterm and final grades: ";
    cin >> allGrades.midterm >> allGrades.final;

    cout << endl;

    //Check for valid input
    check_inputs();

    //Automatically calculates totalGrade and finalGrade
    calc_totalGrade();
    calc_finalGrade();
}

void COP3014::output()
{
    cout << firstName << " " << lastName << "-Z" << zNumber << endl << endl
         << "\tQuiz 1: " << allGrades.quiz1 << endl 
         << "\tQuiz 2: " << allGrades.quiz2 << endl 
         << "\tQuiz 3: " << allGrades.quiz3 << endl  
         << "\tMidterm: " << allGrades.midterm << endl 
         << "\tFinal: " << allGrades.final << endl 
         << "\tTotal Grade: " << totalGrade << endl 
         << "\tFinal Grade: " << finalGrade << endl
         << endl;
}

//*Check Functions
void COP3014::check_inputs()
{
    //Checks for INVALID Z-number
    while (to_string(zNumber).size() != 8) //8 is the size of all Z-numbers
    {
        cout << "INVALID Z-number: must be 8 digits\nEnter a correct Z-number here: ";
        cin >> zNumber;
        cout << endl;
    }

    //Checks for INVALID grades
    while (allGrades.quiz1 < 0 || allGrades.quiz1 > 120 || //120 is the maximum grade I decided to allow
           allGrades.quiz2 < 0 || allGrades.quiz2 > 120 ||
           allGrades.quiz3 < 0 || allGrades.quiz3 > 120 ||
           allGrades.midterm < 0 || allGrades.midterm > 120 ||
           allGrades.final < 0 || allGrades.final > 120)
    {
        cout << "INVALID grade: grades must be positive and <= 120%\nPlease re-enter the grades.\n\n";

        cout << "Enter the student's 3 quiz grades: ";
        cin >> allGrades.quiz1 >> allGrades.quiz2 >> allGrades.quiz3;

        cout << "Enter the student's midterm and final grades: ";
        cin >> allGrades.midterm >> allGrades.final;
        cout << endl;
    }

    if (allGrades.midterm == 0 || allGrades.final == 0)
    {
        cout << "Was " << firstName << " " << lastName << " absent for the final or midterm?\nEnter 1 for yes, 0 for no: ";
        cin >> missed_exam;
        cout << endl;
    }
}
