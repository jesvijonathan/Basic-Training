#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>   
#include <map>

using namespace std;

int* getTime();

class Employee {
public:
    // constructor
    Employee(const string& name, const string& position, const string& department, const string& joinDate, const int& age, const int& percent)
        : name(name), position(position), department(department), joinDate(joinDate), age(age), percent(percent) {
        id = ++currentId;
        logger->log("Employee " + to_string(id) + " created");
    }
    Employee() {

    }
    // destructor
    ~Employee() {
        logger->log("Employee " + to_string(id) + " deleted");
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

    int getPercent() const {
        return percent;
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

    void setPercent(const int& percent) {
        this->percent = percent;
    }

    static int currentId;

private:
    int id;
    string name;
    string position;
    string department;
    string joinDate;
    int age;
    int percent;

};


vector<Employee*> employees;

int Employee::currentId = employees.size();


void employeeMenu() {
    int* date = getTime();
    string dateStr = to_string(date[0]) + "/" + to_string(date[1]) + "/" + to_string(date[2]);

    Employee* employee = new Employee("", "", "", dateStr, 0, 0);

    vector<string> menuData = { to_string(employee->getId()), employee->getName(), employee->getPosition(), employee->getDepartment(), employee->getJoinDate(), to_string(employee->getAge()), to_string(employee->getPercent()) };
    vector<string> menuOptions;

    int selectedOption = 0;

    while (true) {
        menuOptions = { "Name : " + menuData[1], "Position : " + menuData[2], "Department : " + menuData[3], "Join Date : " + menuData[4], "Age : " + menuData[5], "Percent : " + menuData[6], "Save" };
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
            cout << "Percent : ";
            getline(cin, menuData[6]);
            break;
        case 6:
        case -2:
            // relevant data  
            try {
                employee->setName(menuData[1]);
                employee->setPosition(menuData[2]);
                employee->setDepartment(menuData[3]);
                employee->setJoinDate(menuData[4]);
                employee->setAge(stoi(menuData[5]));
                employee->setPercent(stoi(menuData[6]));
                employees.push_back(new Employee(*employee));
            }
            catch (exception e) {
                cout << "Invalid input\n";
                logger->log("Employee not created");
                system("pause");
                return;
            }
            logger->log("Employee created & saved");
            return;
            break;
        default:
            employee->~Employee();
            logger->log("Employee not created");
            return;
        }
    }


    return;
}

int* printTableHeader(int* columnLengths, const vector<string>& headers);

namespace emp {


    // passing by reference | function overloading
    int* calculateColumnLengths(const vector<Employee*>& employees, int* columnLengths = new int[7] {0}) {

        // auto type assigning / templates 
        for (const auto& employee : employees) {
            columnLengths[0] = max(columnLengths[0], static_cast<int>(to_string(employee->getId()).length()));
            columnLengths[1] = max(columnLengths[1], static_cast<int>(employee->getName().length()));
            columnLengths[2] = max(columnLengths[2], static_cast<int>(employee->getPosition().length()));
            columnLengths[3] = max(columnLengths[3], static_cast<int>(employee->getDepartment().length()));
            columnLengths[4] = max(columnLengths[4], static_cast<int>(employee->getJoinDate().length()));
            columnLengths[5] = max(columnLengths[5], static_cast<int>(to_string(employee->getAge()).length()));
            columnLengths[6] = max(columnLengths[6], static_cast<int>(to_string(employee->getPercent()).length()));
        }

        return columnLengths;
    }


    void EmployeesDataTable(const int* columnLengths, boolean reversed = false) {

        // print employee data
        for (const auto& employee : employees) {
            cout << " " << setw(columnLengths[0]) << employee->getId() << " | "
                << setw(columnLengths[1]) << employee->getName() << " | "
                << setw(columnLengths[2]) << employee->getPosition() << " | "
                << setw(columnLengths[3]) << employee->getDepartment() << " | "
                << setw(columnLengths[4]) << employee->getJoinDate() << " | "
                << setw(columnLengths[5]) << employee->getAge() << " | "
                << setw(columnLengths[6]) << employee->getPercent() << " |\n";
        }

        delete[] columnLengths;
    }
    void generateEmployeeReport() {
        multimap<double, Employee> employeeMap;

        cout << " Employee Ranked -\n";
        for (const auto& employee : employees) {
            employeeMap.insert(pair<double, Employee>(employee->getPercent(), *employee));
        }

        int* columnLengths = new int[7] {0};
        vector<string> headers = { "ID", "Name", "Position", "Department", "Join Date", "Age", "Percent" };
        columnLengths = calculateColumnLengths(employees, columnLengths);
        columnLengths = printTableHeader(columnLengths, headers);

        multimap<double, Employee>::reverse_iterator it;

        for (it = employeeMap.rbegin(); it != employeeMap.rend(); it++) {
            cout << " " << setw(columnLengths[0]) << it->second.getId() << " | "
                << setw(columnLengths[1]) << it->second.getName() << " | "
                << setw(columnLengths[2]) << it->second.getPosition() << " | "
                << setw(columnLengths[3]) << it->second.getDepartment() << " | "
                << setw(columnLengths[4]) << it->second.getJoinDate() << " | "
                << setw(columnLengths[5]) << it->second.getAge() << " | "
                << setw(columnLengths[6]) << it->second.getPercent() << " |\n";
        }

        cout << "\n\n";
    }
};