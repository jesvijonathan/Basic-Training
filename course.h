
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

int* getTime();

class Course {
public:
    Course(const string& title, const string& description, const string& instructor, const string& startDate, const string& endDate)
        : title(title), description(description), instructor(instructor), startDate(startDate), endDate(endDate) {
        id = ++currentId;
    }

    ~Course() {
        currentId--;
        cout << "Course destructor called\n";
    }

    static int getCurrentId() {
        return currentId;
    }

    int getId() const {
        return id;
    }

    string getTitle() const {
        return title;
    }

    string getDescription() const {
        return description;
    }

    string getInstructor() const {
        return instructor;
    }

    string getStartDate() const {
        return startDate;
    }

    string getEndDate() const {
        return endDate;
    }

    void setInstructor(const string& instructor) {
        this->instructor = instructor;
    }

    void setTitle(const string& title) {
        this->title = title;
    }

    void setDescription(const string& description) {
        this->description = description;
    }

    void setStartDate(const string& startDate) {
        this->startDate = startDate;
    }

    void setEndDate(const string& endDate) {
        this->endDate = endDate;
    }



private:
    int id;
    string title;
    string description;
    string instructor;
    string startDate;
    string endDate;

    static int currentId;
};

int Course::currentId = 0; // Initializing the static member outside the class definition 


void courseMenu() {
    int* date = getTime();
    string dateStr = to_string(date[0]) + "/" + to_string(date[1]) + "/" + to_string(date[2]);

    Course* course = new Course("", "", "", dateStr, dateStr);

    vector<string> menuData = { to_string(course->getId()), course->getTitle(), course->getDescription(), course->getInstructor(), course->getStartDate(), course->getEndDate() };
    vector<string> menuOptions;

    int selectedOption = 0;


    while (1) {
        menuOptions = { "Title : " + menuData[1], "Description : " + menuData[2], "Instructor : " + menuData[3], "Start Date : " + menuData[4], "End Date : " + menuData[5], "Save" };
        Menu menu(
            menuOptions,
            "\n\nMain Menu / Add Course :\n\n  ID : " + menuData[0],
            "Press 'Enter' to select an option or 'q' to quit & 's' to save :",
            selectedOption);

        selectedOption = menu.run();

        switch (selectedOption) {
        case 0:
            cout << "Title : ";
            // getline
            getline(cin, menuData[1]);
            break;
        case 1:
            cout << "Description : ";
            getline(cin, menuData[2]);
            break;
        case 2:
            cout << "Instructor : ";
            getline(cin, menuData[3]);
            break;
        case 3:
            cout << "Start Date : ";
            getline(cin, menuData[4]);
            break;
        case 4:
            cout << "End Date : ";
            getline(cin, menuData[5]);
            break;
        case 5:
        case -2:
            cout << "Saving..";
            course->setTitle(menuData[1]);
            course->setDescription(menuData[2]);
            course->setInstructor(menuData[3]);
            course->setStartDate(menuData[4]);
            course->setEndDate(menuData[5]);
            cout << "Returning...\n";
            return;
            break;
        default:
            delete course;
            cout << "Returning...\n";
            return;
        }
    }

    cout << "Returning...\n";
    return;



}