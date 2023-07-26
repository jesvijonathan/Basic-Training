
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip> // for setw


using namespace std;

int* getTime();
class Course {
public:
    // constructor
    Course(const string& title, const string& description, const string& instructor, const string& startDate, const string& endDate)
        : title(title), description(description), instructor(instructor), startDate(startDate), endDate(endDate) {
        id = ++currentId;
        logger->log("Course " + to_string(id) + " created");
    }

    // destructor
    ~Course() {
        logger->log("Course " + to_string(id) + " deleted");
        currentId--;

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

int Course::currentId = 0;



vector<Course*> courses;


void courseMenu() {
    int* date = getTime();
    string dateStr = to_string(date[0]) + "/" + to_string(date[1]) + "/" + to_string(date[2]);

    // smart poniters
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
            // relevant data 
            course->setTitle(menuData[1]);
            course->setDescription(menuData[2]);
            course->setInstructor(menuData[3]);
            course->setStartDate(menuData[4]);
            course->setEndDate(menuData[5]);
            courses.push_back(course);
            logger->log("Course created & saved");
            return;
            break;
        default:
            delete course;
            logger->log("Course creation cancelled");
            return;
        }
    }

    logger->log("Returning to main menu");
    return;
}
// names space
namespace crs {
    // passing by reference | function overloading
    int* calculateColumnLengths(const vector<Course*>& courses, int* columnLengths = new int[7] {0}) {

        // auto type assigning / templates 
        for (const auto& course : courses) {
            columnLengths[0] = max(columnLengths[0], static_cast<int>(to_string(course->getId()).length()));
            columnLengths[1] = max(columnLengths[1], static_cast<int>(course->getTitle().length()));
            columnLengths[2] = max(columnLengths[2], static_cast<int>(course->getDescription().length()));
            columnLengths[3] = max(columnLengths[3], static_cast<int>(course->getInstructor().length()));
            columnLengths[4] = max(columnLengths[4], static_cast<int>(course->getStartDate().length()));
            columnLengths[5] = max(columnLengths[5], static_cast<int>(course->getEndDate().length()));
        }

        return columnLengths;
    }
    void CoursesDataTable(const int* columnLengths) {

        for (const auto& course : courses) {
            cout << " " << setw(columnLengths[0]) << course->getId() << " |"
                << " " << setw(columnLengths[1]) << course->getTitle() << " |"
                << " " << setw(columnLengths[2]) << course->getDescription() << " |"
                << " " << setw(columnLengths[3]) << course->getInstructor() << " |"
                << " " << setw(columnLengths[4]) << course->getStartDate() << " |"
                << " " << setw(columnLengths[5]) << course->getEndDate() << " | \n";
        }

        delete[] columnLengths;

    }

    void generateCourseReport() {
        // multimap<double, Course> CourseMap;


        // idk what to do for course report



    };
};