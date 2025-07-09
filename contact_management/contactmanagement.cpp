#include<iostream>
#include<conio.h>
#include<fstream>
using namespace std;

//Global Variables
string fname,lname,phone_num;


//Functions

void addContact();
void searchContact();
void help();
void self_exit();
bool check_digits(string);
bool check_numbers(string);

int main()
{
    short int choice;
    system("cls");
    system("color 0A");
    cout << "\n\n\n\t\t\t Contact Management";
    cout<<"\n\n\t1. Add Contact\n\t2. Search Contact\n\t3. Help\n\t4. Exit\n\t  >";
    cin>> choice;

    switch(choice)
    {
        case 1:
            addContact();
            break;

        case 2:
            searchContact();
            break;

        case 3:
            help();
            break;

        case 4:
            self_exit();
            break;
        default:
            cout<<"\n\n\t Invalid Input!";
            cout<<"\n\n\t-- Press any key to continue --";
            getch();
            main();


    }
    return 0;
}


void self_exit()
{
    system("cls");
    cout<<"         Thank You for using! "<<endl;
    exit(1);

}

void help()
{
    cout<<"Press 1 to add a new Contact"<<endl;
    cout<<"Press 2 to Search a Contact from the file"<<endl;
    cout<<"Press 3 to get help"<<endl;
    cout<<"Press 4 to Exit the program"<<endl;
}

void addContact()
{
    ofstream phone("number.txt", ios::app);
    system("cls");
    cout<<"\n\n\tEnter the First name : ";
    cin>>fname;
    cout<<"\n\tEnter the Last name : ";
    cin>>lname;
    cout<<"\n\tEnter 10-Digit Number : ";
    cin>>phone_num;

    if(check_digits(phone_num) == true )
    {
        if (check_numbers(phone_num) == true)
        {
            if(phone.is_open())
            {
                phone << fname << " " << lname << " " << phone_num << endl;
                cout<<"\n\tContact saved Successfully!";
            }
            else{
                cout<<"\n\tError Opening File !";
            }
        }
        else
        {
            cout<< "\n\tA Phone number must contain only Numbers!";
        }
    }
    else
    {
        cout<< "\n\tA Phone number must contain 10 Digits!";
    }
    phone.close();

}

void searchContact()
{
    bool found = false;
    ifstream myfile("number.txt");
    string keyword;
    cout<<"\n\tEnter  Name to Search : ";
    cin>>keyword;
    while(myfile >> fname >> lname >> phone_num)
    {
        if(keyword == fname || keyword == lname )
        {
            cout<<"\n\n\n\t\t--Contact Details--";
            cout<<"\n\n\tFirst Name : "<< fname;
            cout<<"\n\tLast Name : "<< lname;
            cout<<"\n\tPhone Number : "<< phone_num;
            found = true;
            break;
        }
    }
    if(found == false)
    {
        cout<<"\n\t--No such Contact Found in Database--";
    }


}

bool check_digits(string x)
{
    if(x.length() == 10)
    return true;
    else
    return false;
}

bool check_numbers(string x)
{
    bool check = true;

    for(int i=0;i<x.length();i++)
    {
        if(!(int(x[i]) >=48 && int(x[i]) <= 57))
        {
            check = false;
            break;

        }
    }
    if(check == true)
        return true;
    else
        return false;
}
