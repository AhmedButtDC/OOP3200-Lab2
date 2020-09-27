//Name:             Ahmed Butt, Muzhda Ehsan
//Student ID:       100770449, 100770164
//Last Modified:    September 25, 2020
//File:             OOP3200-Lab2.cpp

#include <iostream>
#include <iomanip>	
#include <sstream>
#include <string>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <stdio.h>
#include <ctype.h>
#include <cctype>
#include <regex>

using namespace std;

//CLASS DECLARATION
class WorkTicket
{
private:
    //Variables and thier default vaulues
    int workTicketNumber = 0;
    string clientID = "";
    int dDay = 1, dMonth = 1, dYear = 2000;
    string issueDiscription = "";

public:

    //Default constructor
    WorkTicket();

    //Copy constructor
    WorkTicket(WorkTicket& new_ticket);

    //Conversion operator
    operator string();  //not entirely sure about this one

    //Equality (==) operator
    bool operator==(WorkTicket& other_ticket);

    //Assignment (=) operator
    WorkTicket operator=(WorkTicket& new_ticket);

    //Overload '>>' operator
    friend istream& operator>>(istream& in, WorkTicket& ticket);

    //Overload '<<' operator
    friend ostream& operator<<(ostream& out, WorkTicket& ticket);

    //Gets; all returning values of variables that hold WorkTicket information
    const int GetWorkTicketNumber() { return workTicketNumber; }
    const string GetClientID() { return clientID; }
    const int GetDay() { return dDay; }
    const int GetMonth() { return dMonth; }
    const int GetYear() { return dYear; }
    const string GetIssueDiscription() { return issueDiscription; }

    //Sets; all change values of the variables that hold WorkTicket information
    void SetWorkTicketNumber(int number) { workTicketNumber = number; }
    void SetClientID(string id) { clientID = id; }
    void SetWorkTicketDate(int day, int month, int year) { dDay = day; dMonth = month; dYear = year; }
    void SetIssueDiscription(string issue) { issueDiscription = issue; }

    //SetWorkTicket() mutator, sets all attributes of object to parameters if parameters valid...
    bool SetWorkTicket(int number, string id, int day, int month, int year, string issue);

    //ShowWorkTicket() accessor, display all object's attributes
    string ShowWorkTicket();
};
string DateValidation(string dayMonthYear, const int min, const int max, string dMY);   //to decrease some repeated validation
string CheckIfEmpty(string text);   //to decrease some repeated validation

//Validators for >> operator, mostly copied from validation from main()
int TicketNumValidation(string number);
string TicketIdValidation(string id);

//main() FUNCTION
int main()
{
    //Declarations
    string tempClientID, tempIssueDiscription, tempWorkTicketNumber, tempDay, tempMonth, tempYear;
    int ticketIncrement = 0;
    const int min = 1, dayMax = 31, monthMax = 12, yearMin = 2000, yearMax = 2099;
    const string strDay = "day", strMonth = "month", strYear = "year";
    WorkTicket client[3];   //array of 3 WorkTicket objects (0, 1, and 2)

    try
    {
        do  //do-while loop to increment through each work ticket
        {
            cout << "Work Ticket " << (ticketIncrement + 1) << "\n" << "---------------------------------";
            cout << "\nEnter a work ticket number: ";
            getline(cin, tempWorkTicketNumber);
            tempWorkTicketNumber = CheckIfEmpty(tempWorkTicketNumber);
            while (!regex_search(tempWorkTicketNumber, regex("^[0-9]*$")) || stoll(tempWorkTicketNumber) < min) // if input not a whole number
            {
                cout << "* Invalid input. Please try again and enter a whole number greater than 0.\n";
                cout << "\nEnter a work ticket number: ";
                getline(cin, tempWorkTicketNumber);
                tempWorkTicketNumber = CheckIfEmpty(tempWorkTicketNumber);
            }

            cout << "\nEnter a client ID: ";
            getline(cin, tempClientID);
            while (tempClientID.empty() || !regex_search(tempClientID, regex("^[a-zA-Z0-9]*$"))) //check if input is not empty and only includes alphanumeric characters
            {
                cout << "* Invalid input. Client ID must be at least one alphanumeric character. Non-alphanumeric characters are not allowed.\n";
                cout << "\nEnter a client ID: ";
                getline(cin, tempClientID);
            }

            cout << "\nDate\n" << "------------\n"; //*DATE VALIDATION CHANGED TO MATCH STRING VALIDATION, THEY WERE DOUBLE VARIABLES BEFORE

            cout << "Enter day: ";
            getline(cin, tempDay);
            tempDay = CheckIfEmpty(tempDay);
            tempDay = DateValidation(tempDay, min, dayMax, strDay);    //check if day input is a whole number within range

            cout << "Enter month: ";
            getline(cin, tempMonth);
            tempMonth = CheckIfEmpty(tempMonth);
            tempMonth = DateValidation(tempMonth, min, monthMax, strMonth);  //check if month input is a whole number within range

            cout << "Enter year: ";
            getline(cin, tempYear);
            tempYear = CheckIfEmpty(tempYear);
            tempYear = DateValidation(tempYear, yearMin, yearMax, strYear); //check if year input is a whole number within range

            cout << "\nEnter an issue discription: ";
            getline(cin, tempIssueDiscription);
            while (tempIssueDiscription.empty())    //check if input is at least 1 character long
            {
                cout << "* Invalid input. An issue discription must be at least one character long.\n";
                cout << "\nEnter an issue discription: ";
                getline(cin, tempIssueDiscription);
            }
            cout << "\n\n";

            //SetWorkTicket call for specific client, provided all validated variables
            client[ticketIncrement].SetWorkTicket(stoll(tempWorkTicketNumber), tempClientID, stoll(tempDay), stoll(tempMonth), stoll(tempYear), tempIssueDiscription);

            ticketIncrement++; //increment the ticket

        } while (ticketIncrement != 3); //client array goes from 0-2, so 3 would be out of range

        for (int i = 0; i != ticketIncrement; i++)  //output loop to display all WorkTickets using ShowWorkTicket
        {
            cout << "Client " << (i + 1) << "\n--------------------\n";
            cout << client[i].ShowWorkTicket() << "\n\n";
        }
        cout << "\nCopy Constructor" << "\n---------------------\n";
        WorkTicket newWorkTicket = client[0];   //copy constructor gets called here

        cout << "\nConversion Operator" << "\n---------------------\n";
        newWorkTicket.operator string();    //conversion operator gets called here

        cout << "\nEquality Operator" << "\n---------------------\n";
        cout << "Comparing WorkTickets 1 and 2 (0 = inequal, 1 = equal): " << (client[0] == client[1]) << "\n";   //equality operator called here

        cout << "\nAssignment Operator" << "\n---------------------\n";
        newWorkTicket = client[2];  //assignment operator gets called here, also seems to call copy constructor...

        cout << "\nOverload '>>' Operator" << "\n---------------------\n";
        WorkTicket anotherWorkTicket;
        cout << "Enter another WorkTicket" << "\n---------------------\n";
        cin >> anotherWorkTicket;   //>> operator gets called here

        cout << "\nOverload '<<' Operator" << "\n---------------------\n";
        cout << anotherWorkTicket << "\n\n"; //<< operator gets called here
    }
    catch (exception& ia)
    {
        cerr << "* Invalid input. " << ia.what() << ".\n\n";
    }
    return 0;
}
//Constructors/Operators
WorkTicket::WorkTicket()
= default;

WorkTicket::WorkTicket(WorkTicket& new_ticket)   //copy constructor
{
    SetWorkTicket(new_ticket.GetWorkTicketNumber(), new_ticket.GetClientID(), new_ticket.GetDay(), 
        new_ticket.GetMonth(), new_ticket.GetYear(), new_ticket.GetIssueDiscription());
    cout << "First WorkTicket object was COPIED.\n";
}

WorkTicket::operator string()   //conversion operator
{
    stringstream reformatedTicket;
    reformatedTicket << "Work Ticket # " << GetWorkTicketNumber() << " - " << GetClientID() << " (" << GetDay() <<
        "/" << GetMonth() << "/" << GetYear() << "): " << GetIssueDiscription();
    return reformatedTicket.str();
}

bool WorkTicket::operator==(WorkTicket& other_ticket)   //equality operator
{
    return ((GetWorkTicketNumber() == other_ticket.GetWorkTicketNumber()) && (GetClientID() == other_ticket.GetClientID())
        && (GetDay() == other_ticket.GetDay()) && (GetMonth() == other_ticket.GetMonth()) && (GetYear() == other_ticket.GetYear())
        && (GetIssueDiscription() == other_ticket.GetIssueDiscription()));
}

WorkTicket WorkTicket::operator=(WorkTicket& new_ticket)    //assignment operator
{
    SetWorkTicketNumber(new_ticket.GetWorkTicketNumber());
    SetClientID(new_ticket.GetClientID());
    SetWorkTicketDate(new_ticket.GetDay(), new_ticket.GetMonth(), new_ticket.GetYear());
    SetIssueDiscription(new_ticket.GetIssueDiscription());
    cout << "WorkTicket 3 object was ASSIGNED. ";
    return *this;
}

istream& operator>>(istream& in, WorkTicket& ticket)    //overload >> operator
{
    string number = to_string(ticket.workTicketNumber);
    string day = to_string(ticket.dDay);
    string month = to_string(ticket.dMonth);
    string year = to_string(ticket.dYear);
    const int min = 1, minYear = 2000, maxDay = 31, maxMonth = 12, maxYear = 2099;

    cout << "Enter a work ticket number: ";
    getline(in, number);
    ticket.workTicketNumber = TicketNumValidation(number);

    cout << "Enter a client ID: ";
    getline(in, ticket.clientID);
    ticket.clientID = TicketIdValidation(ticket.clientID);

    //Used DateValidation() that was specifically meant for lab 1, but could work here if I messed with the code a bit...
    cout << "Enter a day: ";
    getline(in, day);
    ticket.dDay = stoll(DateValidation(day, min, maxDay, "day"));

    cout << "Enter a month: ";
    getline(in, month);
    ticket.dMonth = stoll(DateValidation(month, min, maxMonth, "month"));

    cout << "Enter a year: ";
    getline(in, year);
    ticket.dYear = stoll(DateValidation(year, minYear, maxYear, "year"));

    cout << "Enter an issue discritption: ";
    getline(in, ticket.issueDiscription);
    while (ticket.issueDiscription.empty())    //check if input is at least 1 character long
    {
        cout << "* Invalid input. An issue discription must be at least one character long.\n";
        cout << "\nEnter an issue discription: ";
        getline(in, ticket.issueDiscription);
    }
    return in;
}

ostream& operator<<(ostream& out, WorkTicket& ticket)   //overload << operator
{
    out << "Work Ticket Number: " << ticket.workTicketNumber << "\n"
    << "Client ID: " << ticket.clientID << "\n"
    << "Work Ticket Date: " << ticket.dDay << "/" << ticket.dMonth << "/" << ticket.dYear << "\n"
    << "Issue Discription: " << ticket.issueDiscription;
    return out;
}

//Functions
string CheckIfEmpty(string text)
{
    if (text.empty()) //for stoll() purposes, it doesn't like blank strings
    {
        text = "0";
    }
    return text;
}

string DateValidation(string dayMonthYear, const int min, const int max, string dMY)
{
    while (!regex_search(dayMonthYear, regex("^[0-9]*$")) || stoll(dayMonthYear) < min || stoll(dayMonthYear) > max) //if not whole number within range
    {
        cout << "* Invalid input. Please try again and enter a whole number between " << min << " and " << max << ".\n";
        cout << "\nEnter " << dMY << ": ";
        getline(cin, dayMonthYear);
        dayMonthYear = CheckIfEmpty(dayMonthYear);
    }
    return dayMonthYear;
}
int TicketNumValidation(string number)  //to help validate for >> operator, could also be used in main()
{   
    number = CheckIfEmpty(number);
    while (!regex_search(number, regex("^[0-9]*$")) || stoll(number) < 1) // if input not a whole number
    {
        cout << "* Invalid input. Please try again and enter a whole number greater than 0.\n";
        cout << "\nEnter a work ticket number: ";
        getline(cin, number);
        number = CheckIfEmpty(number);
    }
    return stoll(number);
}
string TicketIdValidation(string id)    //to help validate for >> operator, could also be used in main()
{
    while (id.empty() || !regex_search(id, regex("^[a-zA-Z0-9]*$"))) //check if input is not empty and only includes alphanumeric characters
    {
        cout << "* Invalid input. Client ID must be at least one alphanumeric character. Non-alphanumeric characters are not allowed.\n";
        cout << "\nEnter a client ID: ";
        getline(cin, id);
    }
    return id;
}

bool WorkTicket::SetWorkTicket(int number, string id, int day, int month, int year, string issue)
{
    SetWorkTicketNumber(number);    //changing the default value of work ticket number

    SetClientID(id);    //changing the default value of id

    SetWorkTicketDate(day, month, year);    //changing the default values of work ticket date array

    SetIssueDiscription(issue); //changing the default value of issue discription

    return true;    //returning true because lab requirements say so lol
}

string WorkTicket::ShowWorkTicket() //displays the work ticket
{
    stringstream ticket;
    ticket << "Work Ticket Number: " << workTicketNumber << "\n"
        << "Client ID: " << clientID << "\n"
        << "Work Ticket Date: " << dDay << "/" << dMonth << "/" << dYear << "\n"
        << "Issue Discription: " << issueDiscription;
    return ticket.str();
}