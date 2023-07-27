
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>   
#include <iomanip> 

using namespace std;
using namespace crs;
using namespace emp;

int* printTableHeader(int* columnLengths, const vector<string>& headers) {

    for (int i = 0; i < headers.size(); ++i) {
        columnLengths[i] = max(columnLengths[i], static_cast<int>(headers[i].length()));
        cout << " " << setw(columnLengths[i]) << headers[i] << " |";
    }
    cout << "\n";

    return columnLengths;
}


template <class T>

class ReportGenerator {
public:
    ReportGenerator() {

    }

    ~ReportGenerator() {
    }


    static void viewAll() {
        cout << " Courses Report -\n";
        viewCourses();
        cout << "\n\n Employee Report -\n";
        viewEmployees();
        // cout << "\n\n Enrollment Report -\n";
        // enrollManager.viewEnrollment();
        system("notepad.exe data\\log.log");
    }

    static auto viewCourses() {
        int* columnLengths = new int[7] {0};

        vector<string> headers = { "ID", "Title", "Description", "Instructor", "Start Date", "End Date" };

        columnLengths = crs::calculateColumnLengths(courses, columnLengths);

        columnLengths = printTableHeader(columnLengths, headers);

        crs::CoursesDataTable(columnLengths);

        return columnLengths;
    }

    static auto viewEmployees() {
        int* columnLengths = new int[7] {0};

        vector<string> headers = { "ID", "Name", "Position", "Department", "Join Date", "Age", "Percent" };

        columnLengths = emp::calculateColumnLengths(employees, columnLengths);
        columnLengths = printTableHeader(columnLengths, headers);

        emp::EmployeesDataTable(columnLengths);
        return columnLengths;

    }
};



void reportMenu() {
    vector<string> menuOptions = { "View Courses", "View Employees", "Generate Report", "Return" };



    while (true) {
        Menu menu(menuOptions, "\n\nMain Menu / Generate Report :\n\n", "Press 'Enter' to select an option or 'q' to quit :");

        int selectedOption = menu.run();

        switch (selectedOption) {
        case 0:
            cout << "Courses \n\n";
            ReportGenerator<void>::viewCourses();
            break;
        case 1:
            cout << "Employees \n\n";
            ReportGenerator<void>::viewEmployees();
            break;
        case 2:
            cout << "Courses, Employees, Logs\n\n";
            generateEmployeeReport();
            generateCourseReport();
            ReportGenerator<void>::viewAll();
            break;
        case 3:
        case -2:
            return;
            break;
        default:
            return;

        }

        cout << "\n\n";
        system("pause");
    }
}