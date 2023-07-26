#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <windows.h>

using namespace std;

class PersistentSave {

public:


    void loadCourse() {
        // Open the "courses.csv" file for reading
        std::ifstream coursesFile("courses.csv");

        if (coursesFile.is_open()) {
            // skip header 
            std::string line;
            std::getline(coursesFile, line);

            // read data
            while (std::getline(coursesFile, line)) {
                std::stringstream ss(line);
                std::string data[6];
                for (int i = 0; i < 6; ++i) {
                    std::getline(ss, data[i], ',');
                }
                courses.push_back(new Course(data[1], data[2], data[3], data[4], data[5]));
            }

            Course::currentId = courses.size();
        }
        else {
            std::cout << "Unable to open file";

        }
    }


    void loadEmployee() {
        // Open the "employees.csv" file for reading
        std::ifstream employeesFile("employees.csv");

        if (employeesFile.is_open()) {
            // skip header 
            std::string line;
            std::getline(employeesFile, line);

            // read data
            while (std::getline(employeesFile, line)) {
                std::stringstream ss(line);
                std::string data[7];
                for (int i = 0; i < 7; ++i) {
                    std::getline(ss, data[i], ',');
                }
                employees.push_back(new Employee(data[1], data[2], data[3], data[4], stoi(data[5]), stoi(data[6])));
            }

            Employee::currentId = employees.size();
        }
        else {
            std::cout << "Unable to open file";

        }
    }




    void saveEnrollment() {
        // save enrollment data to csv file
        ofstream enrollmentFile("enrollment.csv");
        int* columnLengths = new int[7] {0};
        if (enrollmentFile.is_open()) {
            enrollmentFile << "ID,Name,Position,Department,Join Date,Age,Percent\n";
            for (const auto& employee : employees) {
                enrollmentFile << " " << setw(columnLengths[0]) << employee->getId() << " ,"
                    << " " << setw(columnLengths[1]) << employee->getName() << " ,"
                    << " " << setw(columnLengths[2]) << employee->getPosition() << " ,"
                    << " " << setw(columnLengths[3]) << employee->getDepartment() << " ,"
                    << " " << setw(columnLengths[4]) << employee->getJoinDate() << " ,"
                    << " " << setw(columnLengths[5]) << employee->getAge() << " ,"
                    << " " << setw(columnLengths[6]) << employee->getPercent() << " , \n";
            }
            enrollmentFile.close();
        }
        else {
            cout << "Unable to open file";
        }
    }
    PersistentSave() {
        //globalLoad();
    }



    void saveCourse() {
        // save courses data to csv file
        ofstream coursesFile("courses.csv");
        int* columnLengths = new int[7] {0};
        if (coursesFile.is_open()) {
            coursesFile << "ID,Title,Description,Instructor,Start Date,End Date\n";
            for (const auto& course : courses) {
                coursesFile << " " << setw(columnLengths[0]) << course->getId() << " ,"
                    << " " << setw(columnLengths[1]) << course->getTitle() << " ,"
                    << " " << setw(columnLengths[2]) << course->getDescription() << " ,"
                    << " " << setw(columnLengths[3]) << course->getInstructor() << " ,"
                    << " " << setw(columnLengths[4]) << course->getStartDate() << " ,"
                    << " " << setw(columnLengths[5]) << course->getEndDate() << " , \n";
            }
            coursesFile.close();
        }
        else {
            cout << "Unable to open file";
        }
    }

    void saveEmployee() {
        // save employees data to csv file
        ofstream employeesFile("employees.csv");
        int* columnLengths = new int[7] {0};
        if (employeesFile.is_open()) {
            employeesFile << "ID,Name,Position,Department,Join Date,Age,Percent\n";
            for (const auto& employee : employees) {
                employeesFile << " " << setw(columnLengths[0]) << employee->getId() << " ,"
                    << " " << setw(columnLengths[1]) << employee->getName() << " ,"
                    << " " << setw(columnLengths[2]) << employee->getPosition() << " ,"
                    << " " << setw(columnLengths[3]) << employee->getDepartment() << " ,"
                    << " " << setw(columnLengths[4]) << employee->getJoinDate() << " ,"
                    << " " << setw(columnLengths[5]) << employee->getAge() << " ,"
                    << " " << setw(columnLengths[6]) << employee->getPercent() << " , \n";
            }
            employeesFile.close();
        }
        else {
            cout << "Unable to open file";
        }
    }


    void globalSave() {
        saveCourse();
        saveEmployee();
        saveEnrollment();
        enrollManager.saveEnrollmentManager();
    }

    void globalLoad() {
        loadCourse();
        loadEmployee();
        // enrollManager.loadEnrollmentManager();
    }
    ~PersistentSave() {
        //globalSave();
    }
};
