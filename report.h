
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>   
#include <iomanip> // for setw

int* printTableHeader(int* columnLengths, const vector<string>& headers) {

    for (int i = 0; i < headers.size(); ++i) {
        columnLengths[i] = max(columnLengths[i], static_cast<int>(headers[i].length()));
        cout << " " << setw(columnLengths[i]) << headers[i] << " |";
    }
    cout << "\n";

    return columnLengths;
}

using namespace std;
using namespace crs;
using namespace emp;

template <class T>

class ReportGenerator {
public:
    ReportGenerator() {

    }

    ~ReportGenerator() {
    }

    void generateEmployeeReport() {
        // display employee ID | Name | Percent use sort and itterators


    }

    void viewAll() {
        viewCourses();
        cout << "\n\n";
        viewEmployees();
        system("notepad.exe log.txt");
    }

    void viewCourses() {
        int* columnLengths = new int[7] {0};

        vector<string> headers = { "ID", "Title", "Description", "Instructor", "Start Date", "End Date" };

        columnLengths = crs::calculateColumnLengths(courses, columnLengths);
        columnLengths = printTableHeader(columnLengths, headers);

        crs::CoursesDataTable(columnLengths);


    }

    void viewEmployees() {
        int* columnLengths = new int[7] {0};

        vector<string> headers = { "ID", "Name", "Position", "Department", "Join Date", "Age", "Percent" };

        columnLengths = emp::calculateColumnLengths(employees, columnLengths);
        columnLengths = printTableHeader(columnLengths, headers);

        emp::EmployeesDataTable(columnLengths);


    }
};



void reportMenu() {
    vector<string> menuOptions = { "View Courses", "View Employees", "View All", "Return to Main Menu" };

    ReportGenerator<Course> courseReport;

    while (true) {
        Menu menu(menuOptions, "\n\nMain Menu / Generate Report :\n\n", "Press 'Enter' to select an option or 'q' to quit :");

        int selectedOption = menu.run();

        switch (selectedOption) {
        case 0:

            cout << "Courses \n\n";
            courseReport.viewCourses();
            break;
        case 1:
            cout << "Employees \n\n";
            courseReport.viewEmployees();
            break;
        case 2:
            cout << "Courses, Employees, Logs\n\n";
            //courseReport.generateEmployeeReport();
            generateEmployeeReport();
            generateCourseReport();
            courseReport.viewAll();
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