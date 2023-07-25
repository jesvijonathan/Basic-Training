// Training Management Application

#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

#include "menu.h"
#include "course.h"
#include "employee.h"
#include "enrollment.h"

#define AddCourse 0
#define AddEmployee 1
#define EnrollEmployee 2
#define GenerateReport 3
#define Exit 4

using namespace std;

void SetConsoleTitle(const std::string& title)
{
    SetConsoleTitleA(title.c_str());

}

int* getTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentDay = ltm->tm_mday;
    int currentMonth = 1 + ltm->tm_mon;
    int currentYear = 1900 + ltm->tm_year;

    int* dateArr = new int[3];
    dateArr[0] = currentDay;
    dateArr[1] = currentMonth;
    dateArr[2] = currentYear;
    return dateArr;
}

void TrainingManager() {
    vector<string> menuOptions = { "Add new course", "Add new employee", "Enroll employee in course", "Generate report", "Exit" };

    Menu menu(menuOptions, "Training Management Application\n\nMain Menu\n", "Press 'Enter' to select an option or 'q' to quit :");
    int selectedOption = menu.run();

    if (selectedOption < menuOptions.size() - 1) {
        switch (selectedOption) {
        case AddCourse:
            cout << "Add new course\n";
            courseMenu();
            break;
        case AddEmployee:
            cout << "Add new employee\n";
            employeeMenu();
            break;
        case EnrollEmployee:
            cout << "Enroll employee in course\n";
            break;
        case GenerateReport:
            cout << "Generate report\n";
            break;
        default:
            break;
        }
    }
    else {
        cout << "Exiting...\n";
        exit(0);
    }
}

int main() {
    SetConsoleTitle("Worldline - Training Management Application");

    while (true) {
        TrainingManager();
    }

    system("pause");
    return 0;
}

