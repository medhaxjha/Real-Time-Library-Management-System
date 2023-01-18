#include <fstream>
#include "conio.h"
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <iostream>
using namespace std;
class book
{
    char bno[6];
    char bname[50];
    char aname[20];

public:
    void create_book()
    {
        cout << "\nNEW BOOK ENTRY\n";
        cout << "\nEnter The book no:";
        cin >> bno;
        cout << "\nEnter The Name of The Book :";
        cin >> bname;
        cout << "\nEnter The Author's Name: ";
        cin >> aname;
        cout << "\nBook Created..";
    }
    void show_book()
    {
        cout << "\nBook no. : ";
        cout << bno;
        cout << "\nBook Name : ";
        puts(bname);
        cout << "Author Name : ";
        puts(aname);
    }

    void modify_book()
    {
        cout << "\nBook no. : " << bno;
        cout << "\nModify Book Name : ";
        cin >> bname;
        cout << "\nModify Author's Name of Book:";
        cin >> aname;
    }
    char *retbno()
    {
        return bno;
    }
    void report()
    {
        cout << bno << setw(30) << bname << setw(30) << aname << endl;
    }

}; // CLASS BOOK ENDS HERE

class student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;

public:
    void create_student()
    {
        cout << "\nNEW STUDENT ENTRY\n";
        cout << "\nEnter The Roll no: ";
        cin >> admno;
        cout << "\nEnter The Name of the student:";
        cin >> name;
        token = 0;
        stbno[0] = '\0';
        cout<<endl<<endl; 
        cout << "\nStudent Record Created";
    }
    void show_student()
    {
        cout << "\nRoll no. : ";
        cout << admno;
        cout << "\nStudent Name : ";
        puts(name);
        cout << "\nNo of Book issued : " << token;
        if (token == 1)
        {
            cout << "\nBook No " << stbno;
        }
    }
    void modify_student()
    {
        cout << "\nRoll no. : " << admno;
        cout << "\nModify Student Name : ";
        cin >> name;
    }
    char *retadmno()
    {
        return admno;
    }
    char *retstbno()
    {
        return stbno;
    }
    int rettoken()
    {
        return token;
    }
    void addtoken()
    {
        token = 1;
    }
    void resettoken()
    {
        token = 0;
    }
    void getstbno(char t[])
    {
        strcpy(stbno, t);
    }
    void report()
    {
        cout << "\t" << admno << setw(20) << name << setw(10);
        cout << token << endl;
    }
};
fstream fp, fp1;
book bk;
student st;
void write_book()
{
    char ch;
    fp.open("D:/bookdata.txt", ios::out | ios::app);
    do
    {
        bk.create_book();
        fp.write((char *)&bk, sizeof(book));
        cout << "\n\nDo you want to add more record..(y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}
void write_student()
{
    char ch;
    fp.open("D:/studentdata.txt", ios::out | ios::app);
    do
    {
        st.create_student();
        cout<<endl;
        fp.write((char *)&st, sizeof(student));
        cout << "\ndo you want to add more record.(y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}
void display_spb(char n[])
{
    cout << "\n-----------------------------------";
    cout << "\n|      BOOK DETAILS                |";
    cout << "\n-----------------------------------";
    int flag = 0;
    fp.open("D:/bookdata.txt", ios::in);
    while (fp.read((char *)&bk, sizeof(book)))
    {
        if (strcmp(bk.retbno(), n) == 0)
        {
            bk.show_book();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "\n\nBook does not exist";
    }
    cin.get();
}
void display_sps(char n[])
{
    cout << "\n-----------------------------------";
    cout << "\n|      STUDENT DETAILS             |";
    cout << "\n-----------------------------------";
    int flag = 0;
    fp.open("D:/studentdata.txt", ios::in);
    while (fp.read((char *)&st, sizeof(student)))
    {
        if ((strcmp(st.retadmno(), n) == 0))
        {
            st.show_student();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "\nStudent does not exist";
    }
    cin.get();
}
void modify_book()
{
    char n[6];
    int found = 0;
    cout << "\nMODIFY BOOK REOCORD.... ";
    cout << "\nEnter The book no. of The book";
    cin >> n;
    fp.open("D:/bookdata.txt", ios::in | ios::out);
    while (fp.read((char *)&bk, sizeof(book)) && found == 0)
    {
        if (strcmp(bk.retbno(), n) == 0)
        {
            bk.show_book();
            cout << "\nEnter The New Details of book";
            cout << endl;
            bk.modify_book();
            long long int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&bk, sizeof(book));
            cout << "\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\nRecord Not Found ";
    }
    cin.get();
}

void modify_student()
{
    char n[6];
    int found = 0;
    cout << "\nMODIFY STUDENT RECORD... ";
    cout << "\nEnter The Roll no. of The student";
    cin >> n;
    fp.open("D:/studentdata.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmp(st.retadmno(), n) == 0)
        {
            st.show_student();
            cout << "\nEnter The New Details of  student";
            cout << endl;
            st.modify_student();
            long long int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&st, sizeof(student));
            cout << "\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\nRecord Not Found ";
    }
    cin.get();
}
void delete_student()
{
    char n[6];
    int flag = 0;
    cout << "\nDELETE STUDENT...";
    cout << "\nEnter The Roll no. of the Student you:";
    cout << "want To Delete : ";
    cin >> n;
    fp.open("D:/studentdata.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("D:/tempdata.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&st, sizeof(student)))
    {
        if (strcmp(st.retadmno(), n) != 0)
        {
            fp2.write((char *)&st, sizeof(student));
        }
        else
        {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("D:/studentdata.txt");
    rename("D:/tempdata.txt", "D:/studentdata.txt");
    if (flag == 1)
    {
        cout << "\nRecord Deleted ..";
    }
    else
    {
        cout << "\nRecord not found";
    }
    cin.get();
}
void delete_book()
{
    char n[6];
    //  clrscr();
    cout << "\nDELETE BOOK ...";
    cout << "\nEnter The Book no. of the Book You Want To ";
    cout << "Delete: ";
    cin >> n;
    fp.open("D:/bookdata.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("D:/tempdata.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&bk, sizeof(book)))
    {
        if (strcmp(bk.retbno(), n) != 0)
        {
            fp2.write((char *)&bk, sizeof(book));
        }
    }
    fp2.close();
    fp.close();
    remove("D:/bookdata.txt");
    rename("D:/tempdata.txt", "D:/bookdata.txt");
    cout << "Record Deleted ..";
    cin.get();
}
void display_alls()
{
    //  clrscr();
    fp.open("D:/studentdata.txt", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        cin.get();
        return;
    }
    cout << "\nSTUDENT LIST";
    cout << "\n\tRollNo:";
    cout << setw(15) << "Name" << setw(15) <<"Book Issued\n";
    while (fp.read((char *)&st, sizeof(student)))
    {
        st.report();
    }
    fp.close();
    cin.get();
}
void display_allb()
{
    fp.open("D:/bookdata.txt", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        cin.get();
        return;
    }
    cout << "\nBook LIST\n\n";
    cout << "BookNumber" << setw(20) << "BookName" << setw(25);
    cout << "Author\n";
    while (fp.read((char *)&bk, sizeof(book)))
    {
        bk.report();
    }
    fp.close();
    cin.get();
}
void book_issue()
{
    char sn[6], bn[6];
    int found = 0, flag = 0;
    //  clrscr();
    cout << "\n-----------------------------------";
    cout << "\n|      BOOK ISSUE                 |";
    cout << "\n-----------------------------------";
    cout << "\nEnter The student's Roll no:";
    cin >> sn;
    fp.open("D:/studentdata.txt", ios::in | ios::out);
    fp1.open("D:/bookdata.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmp(st.retadmno(), sn) == 0)
        {
            found = 1;
            if (st.rettoken() == 0)
            {
                cout << "Enter the book no: ";
                cin >> bn;
                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
                {
                    if (strcmp(bk.retbno(), bn) == 0)
                    {
                        bk.show_book();
                        flag = 1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        long long int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));
                        cout << "\n Book issued successfully";
                        cout << "\nPlease Note: Write current";
                        cout << " date in backside of book and";
                        cout << " submit within 15 days\n.";
                        cout << " Fine of Rs.1 for each day will be";
                        cout << " taken after 15 days period";
                    }
                }
                if (flag == 0)
                {
                    cout << "Book no. does not exist";
                }
            }
            else
            {
                cout << "You have not returned the last book.";
                cout << " Book can be issued only after returning the";
                cout << " previous one.";
            }
        }
        if (found == 0)
        {
            cout << "Student record not exist...";
        }
        cin.get();
        fp;
        }