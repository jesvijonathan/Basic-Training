#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace crs;
using namespace emp;
class Enrollment {
public:
    // copy constructor    
    Enrollment(Employee& employee, Course& course) : employee_(employee), course_(course) {}


    ~Enrollment() {}


    Employee& employee_;
    Course& course_;
};



class VirtualExampleFunction {
public:
    virtual void view() = 0;
};


class EnrollmentManager : public VirtualExampleFunction {
public:
    EnrollmentManager() {}
    ~EnrollmentManager() {}



    void selectCourse() {
        int id;
        ReportGenerator<Course> courseReport;

        cout << "\n\n";
        int* columnLengths = courseReport.viewCourses();

        cout << "\nEnter course id: ";
        cin >> id;

        sort(courses.begin(), courses.end(), [](const Course* course1, const Course* course2) {
            return course1->getId() < course2->getId();
            });

        // lambda function
        auto it = find_if(courses.begin(), courses.end(), [id](const Course* course) {
            return course->getId() == id;
            });

        if (it != courses.end()) {
            Course* selectedCourse = *it;
            cout << "Course found: ";

            cout << "\n\n " << setw(columnLengths[0]) << selectedCourse->getId() << " | "
                << setw(columnLengths[1]) << selectedCourse->getTitle() << " | "
                << setw(columnLengths[2]) << selectedCourse->getDescription() << " | "
                << setw(columnLengths[3]) << selectedCourse->getInstructor() << " | "
                << setw(columnLengths[4]) << selectedCourse->getStartDate() << " | "
                << setw(columnLengths[5]) << selectedCourse->getEndDate() << " |\n";
            currentCourse_ = selectedCourse;
        }
        else {
            cout << "Course with id " << id << " not found ! \n\n";
            system("pause");
            currentCourse_ = nullptr;
        }

        return;
    }

    void selectEmployee() {
        int id;
        ReportGenerator<Course> courseReport;

        cout << "\n\n";
        int* columnLengths = courseReport.viewEmployees();

        cout << "\nEnter employee id: ";
        cin >> id;

        sort(employees.begin(), employees.end(), [](const Employee* emp1, const Employee* emp2) {
            return emp1->getId() < emp2->getId();
            });

        // lambda function
        auto it = find_if(employees.begin(), employees.end(), [id](const Employee* emp) {
            return emp->getId() == id;
            });

        if (it != employees.end()) {
            Employee* selectedEmployee = *it;
            cout << "Employee found: ";

            cout << "\n\n " << setw(columnLengths[0]) << selectedEmployee->getId() << " | "
                << setw(columnLengths[1]) << selectedEmployee->getName() << " | "
                << setw(columnLengths[2]) << selectedEmployee->getPosition() << " | "
                << setw(columnLengths[3]) << selectedEmployee->getDepartment() << " | "
                << setw(columnLengths[4]) << selectedEmployee->getJoinDate() << " | "
                << setw(columnLengths[5]) << selectedEmployee->getAge() << " | "
                << setw(columnLengths[6]) << selectedEmployee->getPercent() << " |\n";

            currentEmployee_ = selectedEmployee;
        }
        else {
            cout << "Employee with id " << id << " not found ! \n\n";
            system("pause");
            currentEmployee_ = nullptr;
        }

        return;
    }

    void viewCurrent() {
        if (currentCourse_ != nullptr && currentEmployee_ != nullptr) {
            cout << "Current Course: " << currentCourse_->getTitle() << "\n";
            cout << "Current Employee: " << currentEmployee_->getName() << "\n";
        }
        else {
            cout << "No current course or employee selected\n";
        }
        system("pause");
    }

    void enroll() {
        selectEmployee();
        selectCourse();
        if (currentCourse_ != nullptr && currentEmployee_ != nullptr) {


            cout << "\nEmployee enrolled in course\n";
            system("pause");

            enrollments_.push_back(new Enrollment(*currentEmployee_, *currentCourse_));
        }
        else {
            cout << "course or employee not selected\n";

        }
    }

    // pointer function
    void view() {
        cout << "Enrollments: \n\n";
        cout << "EMPLOYEE ID | EMPLOYEE NAME | COURSE ID | COURSE TITLE\n";
        for (int i = 0; i < enrollments_.size(); i++) {
            cout << enrollments_[i]->employee_.getId() << " | "
                << enrollments_[i]->employee_.getName() << " | "
                << enrollments_[i]->course_.getId() << " | "
                << enrollments_[i]->course_.getTitle() << "\n";
        }
    }

    void unenroll() {
        if (enrollments_.size() > 0) {
            view();
        }
        else {
            cout << "No enrollments\n";
        }

        int id;
        cout << "Enter employee id to unenroll: ";
        cin >> id;

        auto it = find_if(enrollments_.begin(), enrollments_.end(), [id](const Enrollment* enrollment) {
            return enrollment->employee_.getId() == id;
            });

        if (it != enrollments_.end()) {
            enrollments_.erase(it);
            cout << "Employee unenrolled !\n";
        }
        else {
            cout << "Employee with id " << id << " not found ! \n\n";
        }

        system("pause");
    }

    void viewEnrollment() {
        if (enrollments_.size() > 0) {
            view();
        }
        else {
            cout << "No enrollments\n";
        }
        cout << "\n";
        system("pause");
    }

    auto getEnrollments() {
        return enrollments_;
    }
    auto setEnrollments(vector<Enrollment*> enrollments) {
        enrollments_ = enrollments;
    }


    void saveEnrollmentManager() {
        std::string filename = "enrollment.dat";
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Failed to open file for writing." << std::endl;
            return;
        }

        // Write the number of enrollments to the file
        size_t numEnrollments = enrollments_.size();
        outFile.write(reinterpret_cast<const char*>(&numEnrollments), sizeof(numEnrollments));

        // Write each enrollment to the file
        for (const auto& enrollment : enrollments_) {
            // Write the employee object (assuming Employee is serializable)
            outFile.write(reinterpret_cast<const char*>(&enrollment->employee_), sizeof(Employee));
            // Write the course object (assuming Course is serializable)
            outFile.write(reinterpret_cast<const char*>(&enrollment->course_), sizeof(Course));
        }

        outFile.close();
    }


    void loadEnrollmentManager() {
        std::string filename = "enrollment.dat";
        std::ifstream inFile(filename, std::ios::binary);

        if (!inFile) {
            std::cerr << "Failed to open file for reading." << std::endl;
            system("pause");
            return;
        }

        // Clear existing enrollments (if any)
        for (Enrollment* enrollment : enrollments_) {
            delete enrollment;
        }
        enrollments_.clear();

        // Read the number of enrollments from the file
        size_t numEnrollments = 0;
        inFile.read(reinterpret_cast<char*>(&numEnrollments), sizeof(numEnrollments));

        for (size_t i = 0; i < numEnrollments; ++i) {
            // Read the employee object (assuming Employee is serializable)
            Employee employee;

            // Read the course object (assuming Course is serializable)
            Course course;

            // Create a new Enrollment object and add it to the enrollments vector
            enrollments_.push_back(new Enrollment(employee, course));
        }

        inFile.close();
    }


private:
    // have reference to curernt course and employee
    Course* currentCourse_;
    Employee* currentEmployee_;
    vector<Enrollment*> enrollments_;


};


EnrollmentManager enrollManager;

void enrollManagerMenu() {
    vector<string> menuData = { "Enroll Employee", "Unenroll Employee", "View Enrollments" };
    int selectedOption = 0;

    while (true) {
        Menu menu(menuData, "\n\nMain Menu / Enrollment Menu\n", "Press 'Enter' to select an option or 'q' to quit :", selectedOption);
        int selectedOption = menu.run();

        switch (selectedOption) {
        case 0:
            logger->log("Enroll Employee");
            enrollManager.enroll();
            break;
        case 1:
            logger->log("Unenroll Employee");
            enrollManager.unenroll();
            break;
        case 2:
            logger->log("View Enrollments");
            enrollManager.viewEnrollment();
            break;
        case -2:
            logger->log("Enrollment Menu Exited");
            return;
        default:
            return;
        }
    }
}