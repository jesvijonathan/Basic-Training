// Training Management Application

#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip> // for setw

#include "logger.h"
#define logger Logger::getInstance()

#include "menu.h"
#include "course.h"
#include "employee.h"
#include "enrollment.h"
#include "report.h"

#define AddCourse 0
#define AddEmployee 1
#define EnrollEmployee 2
#define GenerateReport 3
#define Exit 4

using namespace std;
using namespace crs;
using namespace emp;

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
    int currentHour = ltm->tm_hour;
    int currentMinute = ltm->tm_min;
    int currentSecond = ltm->tm_sec;


    int* dateArr = new int[3];
    dateArr[0] = currentDay;
    dateArr[1] = currentMonth;
    dateArr[2] = currentYear;
    dateArr[3] = currentHour;
    dateArr[4] = currentMinute;
    dateArr[5] = currentSecond;

    return dateArr;
}



void TrainingManager() {
    vector<string> menuOptions = { "Add new course", "Add new employee", "Enroll employee in course", "Generate report", "Exit" };

    Menu menu(menuOptions, "Training Management Application\n\nMain Menu\n", "Press 'Enter' to select an option or 'q' to quit :");
    int selectedOption = menu.run();

    if (selectedOption < menuOptions.size() - 1) {
        switch (selectedOption) {
        case AddCourse:
            logger->log("Add new course");
            courseMenu();
            break;
        case AddEmployee:
            logger->log("Add new employee");
            employeeMenu();
            break;
        case EnrollEmployee:
            logger->log("Enroll employee in course");
            break;
        case GenerateReport:
            logger->log("Generate report");
            reportMenu();
            break;
        default:
            break;
        }
    }
    else {

        logger->log("Application Exited");
        exit(0);
    }
}



int main() {
    try {
        SetConsoleTitle("Worldline - Training Management Application");
        logger->log("Application Started");

        while (true) {
            logger->log("Training Manager Invoked");
            TrainingManager();
        }

    }
    // exception hadnling
    catch (exception& e) {
        logger->log("Exception : " + string(e.what()));
    }
    catch (...) {
        logger->log("Exception : Unknown");
    }
    system("pause");
    return 0;
}

