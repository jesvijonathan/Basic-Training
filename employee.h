#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

int* getTime();

class Employee {
public:

    Employee(const string& name, const string& position, const string& department, const string& joinDate, const int& age, const int& salary)
        : name(name), position(position), department(department), joinDate(joinDate), age(age), salary(salary) {
        id = ++currentId;
    }

    ~Employee() {
        cout << "Employee destructor called\n";
        currentId--;
    }

    static int getCurrentId() {
        return currentId;
    }

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getPosition() const {
        return position;
    }

    string getDepartment() const {
        return department;
    }

    string getJoinDate() const {
        return joinDate;
    }

    int getAge() const {
        return age;
    }

    int getSalary() const {
        return salary;
    }

    void setName(const string& name) {
        this->name = name;
    }

    void setPosition(const string& position) {
        this->position = position;
    }

    void setDepartment(const string& department) {
        this->department = department;
    }

    void setJoinDate(const string& joinDate) {
        this->joinDate = joinDate;
    }

    void setAge(const int& age) {
        this->age = age;
    }

    void setSalary(const int& salary) {
        this->salary = salary;
    }

private:
    int id;
    string name;
    string position;
    string department;
    string joinDate;
    int age;
    int salary;

    static int currentId;
};

int Employee::currentId = 0;



void employeeMenu() {
    int* date = getTime();
    string dateStr = to_string(date[0]) + "/" + to_string(date[1]) + "/" + to_string(date[2]);

    Employee* employee = new Employee("", "", "", dateStr, 0, 0);

    vector<string> menuData = { to_string(employee->getId()), employee->getName(), employee->getPosition(), employee->getDepartment(), employee->getJoinDate(), to_string(employee->getAge()), to_string(employee->getSalary()) };
    vector<string> menuOptions;

    int selectedOption = 0;
    while (true) {
        menuOptions = { "Name : " + menuData[1], "Position : " + menuData[2], "Department : " + menuData[3], "Join Date : " + menuData[4], "Age : " + menuData[5], "Salary : " + menuData[6], "Save" };
        Menu menu(
            menuOptions,
            "\n\nMain Menu / Add Empoyee :\n\n  ID : " + menuData[0],
            "Press 'Enter' to select an option or 'q' to quit & 's' to save :",
            selectedOption);

        selectedOption = menu.run();

        switch (selectedOption) {
        case 0:
            cout << "Name : ";
            getline(cin, menuData[1]);
            break;
        case 1:
            cout << "Position : ";
            getline(cin, menuData[2]);
            break;
        case 2:
            cout << "Department : ";
            getline(cin, menuData[3]);
            break;
        case 3:
            cout << "Join Date : ";
            getline(cin, menuData[4]);
            break;
        case 4:
            cout << "Age : ";
            getline(cin, menuData[5]);
            break;
        case 5:
            cout << "Salary : ";
            getline(cin, menuData[6]);
            break;
        case 6:
        case -2:
            employee->setName(menuData[1]);
            employee->setPosition(menuData[2]);
            employee->setDepartment(menuData[3]);
            employee->setJoinDate(menuData[4]);
            employee->setAge(stoi(menuData[5]));
            employee->setSalary(stoi(menuData[6]));
            cout << "Returning...\n";
            return;
            break;
        default:
            employee->~Employee();
            cout << "Returning...\n";
            return;
        }
    }
    cout << "Returing...\n";
    return;


}





/*

• A class called Employee that represents an individual employee. The class should have a constructor
that initializes the employee with a name, position, department, and other relevant details. The class
should also have a destructor that deallocates any memory used by the object.

• An array of objects of type Employee that stores the employees. The array should be dynamically
allocated on the heap using a smart pointer to manage memory.

*/