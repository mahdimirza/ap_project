#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

using namespace std;



class users
{
private:
    string FirstName;
    string LastName;
    string Password;
    string UserName;
protected:
    int check_username(string);
    int check_password(string, string);
    void set_user(string username)
    {
        UserName = username;
    }
    void set_pass(string password)
    {
        Password = password;
    }
    void set_firstname(string firstname)
    {
        FirstName = firstname;
    }
    void set_lastname(string lastname)
    {
        LastName = lastname;
    }
};

class books:public menu
{
private:
    string Title;
    string ShelfNumber;
    string Authors;
    int Edition;
    string Publisher;
    int year_Of_publish;
    string ISBN;
    int length;
    string subject;
    string user;
    string status;
protected:
    void search();
    void search_by_4(string, int);
    void borrow_book(string, string);
    void return_book(string, string);
    void search_bookname();
    void search_author();
    void search_publisher();
    void search_year();
};


class menu:public users, public books
{
public:
    void main_menu();
    void register_user();
    void sign_in();
    void sign_menu(string, string);
};

int main()
{
    menu menu1;
    menu1.main_menu();
}

void menu::main_menu()
{
        cout << "1.   register" << endl << endl;
        cout << "2.   signIn" << endl << endl;
        cout << "3.   exit" << endl << endl;
        cout << "please take your option? (1-3)" << endl;
        int option;
        cin >> option;
        while(option > 3 || option < 1)
        {
            cout << "invalid" << endl << "please take your option? (1-3)" << endl;
            cin >> option;
        }
        if(option == 1)
            register_user();
        else if(option == 2)
            sign_in();
        else
            exit(0);
}

void menu::register_user()
{
            users TestUser;
            string Test_firstname, Test_lastname, Test_user, Test_pass;
            cout << "enter username : " << endl;
            cin >> Test_user;
            cout << "enter password : " << endl;
            cin >> Test_pass; 
            while(check_username(Test_user) != 1)
            {
                cout << "invalid username" << endl;
                cout << "enter username : ";
                cin >> Test_user;
                cout << "enter password : " << endl;
                cin >> Test_pass;
            }
            cout << "please enter your firstname : " << endl;
            cin >> Test_firstname;
            cout << "please enter your your lastname : " << endl;
            cin >> Test_lastname;
            set_user(Test_user);
            set_firstname(Test_firstname);
            set_lastname(Test_lastname);
            set_pass(Test_pass);
            ofstream myfile;
            myfile.open("users.txt", ios::app);
            myfile << endl << Test_user << " " << Test_pass<< " " << Test_firstname << " " << Test_lastname;
            myfile.close();
            cout << "register successfully!" << endl;
            
}

void menu::sign_in()
{
        string TestUser , TestPass;
        cout << "enter username : " << endl;
        cin >> TestUser;
        cout << "enter password : " << endl;
        cin >> TestPass;
        if(check_username(TestUser) != 1)
        {
            cout << "invalid username" << endl;
            main_menu();
        }
        cout << "valid username" << endl;
        if(check_password(TestUser, TestPass) != 1)
        {
            cout << "invalid password" << endl;
            main_menu();
        }
        cout << "signed in successfully!" << endl;
        sign_menu(TestUser, TestPass);

}


void menu::sign_menu(string TestUser, string TestPass)
{
    int option;
    cout << "1.   searchbook" << endl << endl;
    cout << "2.   borrowbook" << endl << endl;
    cout << "3.   retrunbook" << endl << endl;
    cout << "4.   exit" << endl << endl;
    cout << "take one option? (1-4)" << endl;
    cin >> option;
    while(option > 4 and option < 1)
    {
        cout << "invalid"<< endl;
        cout << "take one option? (1-4)" << endl;
        cin >> option;
    }
    if(option == 1)
        search();
    else if(option == 2)
        borrow_book(TestUser, TestPass);
    else if(option == 3)
        return_book(TestUser, TestPass);
    else
        exit(0);
}

void books::borrow_book(string TestUser, string TestPass)
{
    search_by_4(TestUser, 2);
}
void books::return_book(string TestUser, string TestPass)
{
    search_by_4(TestUser, 1);
}

void books::search_by_4(string testuser, int oper)
{
    string test_title, test_author, test_publisher;
    int test_year;
    cout << "please enter the title : " << endl;
    cin >> test_title;
    cout << "enter the name of author : " << endl;
    cin >> test_author;
    cout << "enter the nameof publisher : " << endl;
    cin >> test_publisher;
    cout << "enter year of publish : "<< endl;
    cin >> test_year;
    string title1, author1, publisher1, ISBN1, subject1, status, user;
    int shelf1, edition1, year1, length1;
    ifstream myfile;
    myfile.open("books.txt", ios::in);
    ofstream outfile;
    outfile.open("temp.txt", ios::app);
    while(myfile >> title1 >> shelf1 >> author1 >> edition1 >> publisher1 >> year1 >> ISBN1 >> length1 >> subject1 >> status >> user)
    {
        if(title1 == test_title and test_author == author1 and test_publisher == publisher1 and test_year == year1)
        {
            cout << "book found!" << endl;
            if(oper == 2)
            {
                if(status != "null")
                    cout << "this book borrowed by others" << endl;
                else
                {
                    
                    user = testuser;
                    status = "yes";
                    outfile << title1 << shelf1 << author1 << edition1 << publisher1 << year1 << ISBN1 << length1 << subject1 << status << user;
                    cout << "borrowed successfully" << endl;
                    outfile.close();
                }
            }
            else if(oper == 1)
            {
                    user = "no";
                    status = "null";
                    outfile << title1 << shelf1 << author1 << edition1 << publisher1 << year1 << ISBN1 << length1 << subject1 << status << user;   
                    cout << "return successfully" << endl;
                    outfile.close();
            }
            else
            {
                cout << "book not found" << endl;
            }
        }
        
        else
        {
            outfile << title1 << shelf1 << author1 << edition1 << publisher1 << year1 << ISBN1 << length1 << subject1 << status << user;
        }
    }

    outfile.close();
    myfile.close();
    rename("temp.txt", "books.txt");

    
}

int users::check_username(string test_user)
{
    int length;
    ifstream myfile;
    myfile.open("users.txt", ios::in);
    myfile.seekg(0, ios::beg);
    length = myfile.tellg();
    myfile.close();
    if(length == 0)
        return 1;
    else
    {
        string user, pass, first, last;
        myfile.open("users.txt", ios::in);
        myfile.seekg(0, ios::beg);
        int flag = 1;
        while(myfile >> user >> pass >> first >> last)
        {
            if(user == test_user)
            {
                flag = 0;
                myfile.close();
                break;
            }
        }
        if(flag == 0)
        {
            myfile.close();
            return 0;
        }
        else
        {
            myfile.close();
            return 1;
        }
        
    }

}

int users::check_password(string testuser, string testpass)
{
    string user, pass, first , last;
    ifstream myfile;
    myfile.open("users.txt", ios::in);
    myfile.seekg(0, ios::beg);
    int flag1 = 0;
    while(myfile >> user >> pass >> first >> last)
    {
        if(user == testuser)
        {
            flag1 = 1;
            if(pass == testpass)
            {
                myfile.close();
                return 1;
                break;
            }
            else
            {
                myfile.close();
                return 0;
                break;
            }
        }
    }
    if(flag1 == 0)
    {
        myfile.close();
        return 0;
    }
}

void books::search()
{
    cout << endl;
    cout << "1.   search by bookname" << endl << endl;
    cout << "2.   search by author name" << endl << endl;
    cout << "3.   search by publisher" << endl << endl;
    cout << "4.   search by published year" << endl;
    int option;
    cout << "enter your option ?";

    search_bookname();
    search_author();
    search_publisher();
    search_year();
}

void books::search_bookname()
{
    string test_name;
    cout << "please enter bookname : ";
    cin >> test_name;
    ifstream infile;
    infile.open("books.txt", ios::in);
    infile.seekg(0, ios::beg);
    books testbook;
    int flag = 0; 
    while(infile >> testbook.Title >> testbook.ShelfNumber >> testbook.Authors >> testbook.Edition 
    >> testbook.Publisher >> testbook.year_Of_publish >> testbook.ISBN >> testbook.length >> testbook.subject
    >> testbook.status >> testbook.user)
    {
        if(testbook.Title == test_name)
        {    
            int flag = 1;
            cout << testbook.Title <<" " << testbook.ShelfNumber <<" "<< testbook.Authors<< " " << testbook.Edition 
    <<" "<< testbook.Publisher << " "<< testbook.year_Of_publish <<" "<< testbook.ISBN << " " << testbook.length << " " << testbook.subject
    <<" "<< testbook.status << " "<< testbook.user << endl;}
    }
    if(flag == 0)
        cout << "book not found";
    infile.close();
    
}

void books::search_author()
{
    string test_name;
    cout << "please enter author name : ";
    cin >> test_name;
    ifstream infile;
    infile.open("books.txt", ios::in);
    infile.seekg(0, ios::beg);
    books testbook;
    int flag = 0; 
    while(infile >> testbook.Title >> testbook.ShelfNumber >> testbook.Authors >> testbook.Edition 
    >> testbook.Publisher >> testbook.year_Of_publish >> testbook.ISBN >> testbook.length >> testbook.subject
    >> testbook.status >> testbook.user)
    {
        if(testbook.Authors == test_name)
        {    
            int flag = 1;
            cout << testbook.Title <<" " << testbook.ShelfNumber <<" "<< testbook.Authors<< " " << testbook.Edition 
    <<" "<< testbook.Publisher << " "<< testbook.year_Of_publish <<" "<< testbook.ISBN << " " << testbook.length << " " << testbook.subject
    <<" "<< testbook.status << " "<< testbook.user << endl;}
    }
    if(flag == 0)
        cout << "book not found";
    infile.close();
}

void books::search_publisher()
{
    string test_name;
    cout << "please enter the publisher : ";
    cin >> test_name;
    ifstream infile;
    infile.open("books.txt", ios::in);
    infile.seekg(0, ios::beg);
    books testbook;
    int flag = 0; 
    while(infile >> testbook.Title >> testbook.ShelfNumber >> testbook.Authors >> testbook.Edition 
    >> testbook.Publisher >> testbook.year_Of_publish >> testbook.ISBN >> testbook.length >> testbook.subject
    >> testbook.status >> testbook.user)
    {
        if(testbook.Publisher == test_name)
        {    
            int flag = 1;
            cout << testbook.Title <<" " << testbook.ShelfNumber <<" "<< testbook.Authors<< " " << testbook.Edition 
    <<" "<< testbook.Publisher << " "<< testbook.year_Of_publish <<" "<< testbook.ISBN << " " << testbook.length << " " << testbook.subject
    <<" "<< testbook.status << " "<< testbook.user << endl;}
    }
    if(flag == 0)
        cout << "book not found";
    infile.close();
}

void books::search_year()
{
    int test_name;
    cout << "please enter year of publish : ";
    cin >> test_name;
    ifstream infile;
    infile.open("books.txt", ios::in);
    infile.seekg(0, ios::beg);
    books testbook;
    int flag = 0; 
    while(infile >> testbook.Title >> testbook.ShelfNumber >> testbook.Authors >> testbook.Edition 
    >> testbook.Publisher >> testbook.year_Of_publish >> testbook.ISBN >> testbook.length >> testbook.subject
    >> testbook.status >> testbook.user)
    {
        if(testbook.year_Of_publish == test_name)
        {    
            int flag = 1;
            cout << testbook.Title <<" " << testbook.ShelfNumber <<" "<< testbook.Authors<< " " << testbook.Edition 
    <<" "<< testbook.Publisher << " "<< testbook.year_Of_publish <<" "<< testbook.ISBN << " " << testbook.length << " " << testbook.subject
    <<" "<< testbook.status << " "<< testbook.user << endl;}
    }
    if(flag == 0)
        cout << "book not found";
    infile.close();
    
}