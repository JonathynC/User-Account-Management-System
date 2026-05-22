#include<iostream>
#include "passserver.h"
using namespace cop4530;
void menu();
int main()
{
    int cap;
    char option;
    char * password = new char [100];
    char * newpassword = new char [100];
    char * file2 = new char[20];
    char * file = new char[20];
    string username, find;
    pair<string,string> data;
    
    do
    {    
        cout<<"Enter your desired capacity: ";
        cin>>cap;
    }while(cap < 0);

    PassServer user(cap);
    do
    {
        menu();
        cin>>option;
        switch(option)
        {
        case 'l':
            cout<<"Enter frile to load from: ";
            cin>>file;
            if(!user.load(file))
                cout<<"Cannot load file"<<endl;
            break;
        case 'a':
            cout<<"Enter Username: ";
            cin>>username;
            if(user.find(username))
            {
                cout<<"User already exists"<<endl;
                break;
            }
            cout<<"Enter Password:";
            cin>>password;
            data = make_pair(username, password);
            if(!user.addUser(data))
                cout<<"Cannot add user"<<endl;
            break;
        case 'r':
            cout<<"Enter a user to remove: ";
            cin>>username;
            data = make_pair(username, password);
            if(!user.removeUser(data.first))
                cout<<"User not found"<<endl;
            break;
        case 'c':
            cout<<"Enter Username: ";
            cin>>username;
            cout<<"Enter Password:";
            cin>>password;
            data = make_pair(username, password);
            if(user.find(data.first))
            {
                cout<<"Enter new password: ";
                cin>>newpassword;
                 if(!user.changePassword(data, newpassword))
                    cout<<"Cannot change password"<<endl;
            }
            else
            {
                cout<<"User not found"<<endl;
            }
            break;
        case 'f':
            cout<<"Enter user: ";
            cin>>find;
            if(user.find(find))
                cout<<find<<"Was found!!";
            else
                cout<<"User not found"<<endl;
            break;
        case 'd':
            user.dump();
            break; 
        case 's':
            cout<<user.size()<<endl;
            break;
        case 'w':
            cout<<"Enter a password file to write to: ";
            cin>>file2;
            if(!user.write_to_file(file2))
                cout<<"Cannot write to file"<<endl;
            break; 
        case 'x':
            break;
        default:
        cout<<"*****Error: Invalid entry.  Try again."<<endl;
        break;
        }
    }while(option != 'x');
    
    delete[]password;
    delete[]newpassword;
    delete[]file;
    delete[]file2;
    
    return 0;
}

void menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}
