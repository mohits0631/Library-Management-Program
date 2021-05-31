#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
using namespace std;

void MOVETOXY(int x, int y)
{
    static HANDLE handler = NULL;
    if (!handler)
        handler = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD co_ordinate = {x, y};
    SetConsoleCursorPosition(handler, co_ordinate);
}

class LibraryBook
{
    char number[6];
    char name[50];
    char author[20];

public:
    void createNewBook()
    {
        cout << "\nCreating a new book..\n";
        cout << "\nEnter book number: ";
        cin >> number;
        cout << "\n\nEnter book name: ";
        cin.ignore();
        gets(name);
        cout << "\n\nEnter author\'s name: ";
        gets(author);
        cout << "\n\n\nBook Created";
    }
    void printBookDetails()
    {
        cout << "\nBook number: " << number;
        cout << "\nBook name: ";
        puts(name);
        cout << "Author name: ";
        puts(author);
    }
    void reviseBookDetails()
    {
        cout << "\nBook number: " << number;
        cout << "\nRevise book name: ";
        cin.ignore();
        gets(name);
        cout << "\nRevise author\'s name: ";
        gets(author);
    }
    char *getNum()
    {
        return number;
    }
    void displayBook()
    {
        cout << number << setw(30) << name << setw(30) << author << endl;
    }
}; //class ends here

class Student
{
    char admNum[6];
    char name[20];
    char bookNum[6];
    int bookStamp;

public:
    void createNewStudent()
    {
        system("CLS");
        cout << "\nCreating a new student..\n";
        cout << "\nEnter admission number: ";
        cin >> admNum;
        cout << "\n\nEnter student name: ";
        cin.ignore();
        gets(name);
        bookStamp = 0;
        bookNum[0] = '/0';
        cout << "\n\nStudent Created";
    }
    void printStudentDetails()
    {
        cout << "\nAdmission number: " << admNum;
        cout << "\nStudent Name: ";
        puts(name);
        cout << "\nNo of Book issued: " << bookStamp;
        if (bookStamp == 1)
            cout << "\nBook Number: " << bookNum;
    }
    void reviseStudentDetails()
    {
        cout << "\nAdmission number: " << admNum;
        cout << "\nRevise Student Name: ";
        cin.ignore();
        gets(name);
    }
    char *getAdmNum()
    {
        return admNum;
    }
    char *getBookNum()
    {
        return bookNum;
    }
    int getBookStamp()
    {
        return bookStamp;
    }
    void depositToken()
    {
        bookStamp = 1;
    }
    void undepositToken()
    {
        bookStamp = 0;
    }
    void getStudBookNum(char t[])
    {
        strcpy(bookNum, t);
    }
    void displayStudent()
    {
        cout << "\t" << admNum << setw(20) << name << setw(10) << bookStamp << endl;
    }
};

fstream f1, f2;
LibraryBook myBook;
Student myStudent;

void createABook()
{
    char ch;
    f1.open("librarybooks.txt", ios::out | ios::app);
    do
    {
        system("CLS");
        myBook.createNewBook();
        f1.write((char *)&myBook, sizeof(LibraryBook));
        cout << "\n\nDo you want to add more books..(y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    f1.close();
}
void createAStudent()
{
    char ch;
    f1.open("librarystudents.txt", ios::out | ios::app);
    do
    {
        myStudent.createNewStudent();
        f1.write((char *)&myStudent, sizeof(Student));
        cout << "\n\nDo you want to add more atudents(y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    f1.close();
}
void displayParticularBook(char number[])
{
    cout << "\nBook Details\n";
    int temp = 0;
    f1.open("librarybooks.txt", ios::in);
    while (f1.read((char *)&myBook, sizeof(LibraryBook)))
    {
        if (strcmpi(myBook.getNum(), number) == 0)
        {
            myBook.printBookDetails();
            temp = 1;
        }
    }

    f1.close();
    if (temp == 0)
        cout << "\n\nNo such book exists";
    getch();
}
void displayParticularStudent(char number[])
{
    cout << "\nStudent Details\n";
    int temp = 0;
    f1.open("librarystudents.txt", ios::in);
    while (f1.read((char *)&myStudent, sizeof(Student)))
    {
        if ((strcmpi(myStudent.getAdmNum(), number) == 0))
        {
            myStudent.printStudentDetails();
            temp = 1;
        }
    }

    f1.close();
    if (temp == 0)
        cout << "\n\nNo such student exists";
    getch();
}
void reviseBookRecord()
{
    char number[6];
    int found = 0;
    system("CLS");
    cout << "\n\n\tBook Record Revision";
    cout << "\n\n\tEnter number of the book you want to revise: ";
    cin >> number;
    f1.open("librarybooks.txt", ios::in | ios::out);
    while (f1.read((char *)&myBook, sizeof(LibraryBook)) && found == 0)
    {
        if (strcmpi(myBook.getNum(), number) == 0)
        {
            myBook.printBookDetails();
            cout << "\nEnter new details of the book" << endl;
            myBook.reviseBookDetails();
            int pos = -1 * sizeof(myBook);
            f1.seekp(pos, ios::cur);
            f1.write((char *)&myBook, sizeof(LibraryBook));
            cout << "\n\n\tBook details revised";
            found = 1;
        }
    }

    f1.close();
    if (found == 0)
        cout << "\n\nNo such record exists";
    getch();
}
void reviseStudentRecord()
{
    char number[6];
    int found = 0;
    system("CLS");
    cout << "\n\n\tStudent Record Revision";
    cout << "\n\n\tEnter admission number of the student you want to revise: ";
    cin >> number;
    f1.open("librarystudents.txt", ios::in | ios::out);
    while (f1.read((char *)&myStudent, sizeof(Student)) && found == 0)
    {
        if (strcmpi(myStudent.getAdmNum(), number) == 0)
        {
            myStudent.printStudentDetails();
            cout << "\nEnter new details of student" << endl;
            myStudent.reviseStudentDetails();
            int pos = -1 * sizeof(myStudent);
            f1.seekp(pos, ios::cur);
            f1.write((char *)&myStudent, sizeof(Student));
            cout << "\n\n\tStudent details revised";
            found = 1;
        }
    }

    f1.close();
    if (found == 0)
        cout << "\n\nNo such record exists";
    getch();
}
void removeStudentRecord()
{
    char number[6];
    int temp = 0;
    system("CLS");
    cout << "\n\n\n\tStudent Removal";
    cout << "\n\nEnter admission number of the student you want to remove: ";
    cin >> number;
    f1.open("librarystudents.txt", ios::in | ios::out);
    fstream f3;
    f3.open("librarytemps.txt", ios::out);
    f1.seekg(0, ios::beg);
    while (f1.read((char *)&myStudent, sizeof(Student)))
    {
        if (strcmpi(myStudent.getAdmNum(), number) != 0)
            f3.write((char *)&myStudent, sizeof(Student));
        else
            temp = 1;
    }

    f3.close();
    f1.close();
    remove("librarystudents.txt");
    rename("librarytemps.txt", "librarystudents.txt");
    if (temp == 1)
        cout << "\n\n\tStudent Removed....";
    else
        cout << "\n\nNo such student exists";
    getch();
}
void removeBookRecord()
{
    char number[6];
    system("CLS");
    cout << "\n\n\n\tBook Removal";
    cout << "\n\nEnter number of the book you want to remove: ";
    cin >> number;
    f1.open("librarybooks.txt", ios::in | ios::out);
    fstream f3;
    f3.open("librarytemps.txt", ios::out);
    f1.seekg(0, ios::beg);
    while (f1.read((char *)&myBook, sizeof(LibraryBook)))
    {
        if (strcmpi(myBook.getNum(), number) != 0)
        {
            f3.write((char *)&myBook, sizeof(LibraryBook));
        }
    }

    f3.close();
    f1.close();
    remove("librarybooks.txt");
    rename("librarytemps.txt", "librarybooks.txt");
    cout << "\n\n\tBook removed....";
    getch();
}
void printAllStudent()
{
    system("CLS");
    f1.open("librarystudents.txt", ios::in);
    if (!f1)
    {
        cout << "Error: File could not be opened";
        getch();
        return;
    }

    cout << "\n\n\t\tList of Students\n\n";
    cout << "==================================================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Assigned\n";
    cout << "==================================================================\n";

    while (f1.read((char *)&myStudent, sizeof(Student)))
    {
        myStudent.displayStudent();
    }

    f1.close();
    getch();
}
void printAllBook()
{
    system("CLS");
    f1.open("librarybooks.txt", ios::in);
    if (!f1)
    {
        cout << "Error: File could not be opened";
        getch();
        return;
    }

    cout << "\n\n\t\tList of Books\n\n";
    cout << "=========================================================================\n";
    cout << "Book Number" << setw(20) << "Book Name" << setw(25) << "Author\n";
    cout << "=========================================================================\n";

    while (f1.read((char *)&myBook, sizeof(LibraryBook)))
    {
        myBook.displayBook();
    }
    f1.close();
    getch();
}
void assignBook()
{
    char studNumber[6], bookNumber[6];
    int found = 0, temp = 0;
    system("CLS");
    cout << "\n\nBook Assignment.";
    cout << "\n\n\tEnter student\'s admission number: ";
    cin >> studNumber;
    f1.open("librarystudents.txt", ios::in | ios::out);
    f2.open("librarybooks.txt", ios::in | ios::out);
    while (f1.read((char *)&myStudent, sizeof(Student)) && found == 0)
    {
        if (strcmpi(myStudent.getAdmNum(), studNumber) == 0)
        {
            found = 1;
            if (myStudent.getBookStamp() == 0)
            {
                cout << "\n\n\tEnter the book number: ";
                cin >> bookNumber;
                while (f2.read((char *)&myBook, sizeof(LibraryBook)) && temp == 0)
                {
                    if (strcmpi(myBook.getNum(), bookNumber) == 0)
                    {
                        myBook.printBookDetails();
                        temp = 1;
                        myStudent.depositToken();
                        myStudent.getStudBookNum(myBook.getNum());
                        int pos = -1 * sizeof(myStudent);
                        f1.seekp(pos, ios::cur);
                        f1.write((char *)&myStudent, sizeof(Student));
                        cout << "\n\n\t Book Assigned\n\nPlease Note: A fine of Re.1 starts after 15 days";
                    }
                }
                if (temp == 0)
                    cout << "No such book exists";
            }
            else
                cout << "Please return the last book first";
        }
    }
    if (found == 0)
        cout << "There is no such student record....";
    getch();
    f1.close();
    f2.close();
}
void submitBook()
{
    char studNumber[6], bookNumber[6];
    int found = 0, temp = 0, numDays, FINE;
    system("CLS");
    cout << "\n\nBook Submission ...";
    cout << "\n\n\tEnter Student\'s Admission Number: ";
    cin >> studNumber;
    f1.open("librarystudents.txt", ios::in | ios::out);
    f2.open("librarybooks.txt", ios::in | ios::out);
    while (f1.read((char *)&myStudent, sizeof(Student)) && found == 0)
    {
        if (strcmpi(myStudent.getAdmNum(), studNumber) == 0)
        {
            found = 1;
            if (myStudent.getBookStamp() == 1)
            {
                while (f2.read((char *)&myBook, sizeof(LibraryBook)) && temp == 0)
                {
                    if (strcmpi(myBook.getNum(), myStudent.getBookNum()) == 0)
                    {
                        myBook.printBookDetails();
                        temp = 1;
                        cout << "\n\nNumber of days the book was submitted in:";
                        cin >> numDays;
                        if (numDays > 15)
                        {
                            FINE = (numDays - 15) * 1;
                            cout << "\n\nFine imposed: " << FINE;
                        }
                        myStudent.undepositToken();
                        int position = -1 * sizeof(myStudent);
                        f1.seekp(position, ios::cur);
                        f1.write((char *)&myStudent, sizeof(Student));
                        cout << "\n\n\t Book submission successful";
                    }
                }
                if (temp == 0)
                    cout << "No book with this number exists";
            }
            else
                cout << "No book was assigned";
        }
    }
    if (found == 0)
        cout << "No such student record exists....";
    getch();
    f1.close();
    f2.close();
}
void printHeading()
{
    system("CLS");
    MOVETOXY(35, 11);
    cout << "Library";
    MOVETOXY(35, 14);
    cout << "Management";
    MOVETOXY(35, 17);
    cout << "program";
    getch();
}
void printMainMenu()
{
    system("CLS");
    int choice;
    cout << "\n\n\n\tMain Menu";
    cout << "\n\n\t1=>Create Student Record";
    cout << "\n\n\t2=>Show All Student Records";
    cout << "\n\n\t3=>Show Particular Student Record";
    cout << "\n\n\t4=>Revise Student Record";
    cout << "\n\n\t5=>Remove Student Record";
    cout << "\n\n\t6=>Create A New Book";
    cout << "\n\n\t7=>Show All Books";
    cout << "\n\n\t8=>Show Particular Book";
    cout << "\n\n\t9=>Revise Book";
    cout << "\n\n\t10=>Remove Book";
    cout << "\n\n\t11=>Return to Main Menu";
    cout << "\n\n\tSelect an Option(1-11): ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        system("CLS");
        createAStudent();
        break;
    case 2:
        printAllStudent();
        break;
    case 3:
        char number[6];
        system("CLS");
        cout << "\n\n\tEnter the Admission Number: ";
        cin >> number;
        displayParticularStudent(number);
        break;
    case 4:
        reviseStudentRecord();
        break;
    case 5:
        removeStudentRecord();
        break;
    case 6:
        system("CLS");
        createABook();
        break;
    case 7:
        printAllBook();
        break;
    case 8:
    {
        char number[6];
        system("CLS");
        cout << "\n\n\tEnter book number: ";
        cin >> number;
        displayParticularBook(number);
        break;
    }
    case 9:
        reviseBookRecord();
        break;
    case 10:
        removeBookRecord();
        break;
    case 11:
        return;
    default:
        cout << "\a";
    }
    printMainMenu();
}

int main()
{
    int choice;
    printHeading();
    do
    {
        system("CLS");
        cout << "\n\n\tRoot Menu";
        cout << "\n\n\t1=> Assign Book";
        cout << "\n\n\t2=> Submit Book";
        cout << "\n\n\t3=> Main Menu";
        cout << "\n\n\t4=> Exit";
        cout << "\n\n\tSelect an Option(1-4): ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("CLS");
            assignBook();
            break;
        case 2:
            submitBook();
            break;
        case 3:
            printMainMenu();
            break;
        case 4:
            exit(0);
        default:
            cout << "\a";
        }
    } while (choice != 4);
    return 0;
}