#include <map>
#include <iostream>
#include <string>


class Enrollment {
public:
    Enrollment(Employee& employee, Course& course) : employee_(employee), course_(course) {}
    ~Enrollment() {}



private:
    Employee& employee_;
    Course& course_;
};

// use auto return for functions inside EnrollmentManager

class EnrollmentManager {
    ReportGenerator<Course> courseReport;
public:
    EnrollmentManager() {

    }
    ~EnrollmentManager() {}

    auto selectCourse() {
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
            cout << "Course found: \n\n";

            cout << " " << setw(columnLengths[0]) << selectedCourse->getId() << " | "
                << setw(columnLengths[1]) << selectedCourse->getTitle() << " | "
                << setw(columnLengths[2]) << selectedCourse->getDescription() << " | "
                << setw(columnLengths[3]) << selectedCourse->getInstructor() << " | "
                << setw(columnLengths[4]) << selectedCourse->getStartDate() << " | "
                << setw(columnLengths[5]) << selectedCourse->getEndDate() << " |\n";
            return selectedCourse;
        }
        else {
            cout << "Course with id " << id << " not found ! \n\n";
            system("pause");
        }
        return nullptr;
    }

    // templates to dynamically assign return tyoe
    auto selectEmployee() {

        int id;

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
            cout << "Employee found: \n\n";

            cout << " " << setw(columnLengths[0]) << selectedEmployee->getId() << " | "
                << setw(columnLengths[1]) << selectedEmployee->getName() << " | "
                << setw(columnLengths[2]) << selectedEmployee->getPosition() << " | "
                << setw(columnLengths[3]) << selectedEmployee->getDepartment() << " | "
                << setw(columnLengths[4]) << selectedEmployee->getJoinDate() << " | "
                << setw(columnLengths[5]) << selectedEmployee->getAge() << " | "
                << setw(columnLengths[6]) << selectedEmployee->getPercent() << " |\n";

            return selectedEmployee;
        }
        else {
            cout << "Employee with id " << id << " not found ! \n\n";
            system("pause");
        }
        return nullptr;
    }


    void enrollEmployee() {

        Employee& employee = selectEmployee();
        Course& course = selectCourse();

        Enrollment* enrollment = new Enrollment(employee, course);
        enrollments_.insert(std::pair<int, Enrollment*>(employee.getId(), enrollment));
    }

    void viewEnrollments() {
        cout << "\n\n";
        int* columnLengths = courseReport.viewCourses();

        for (const auto& enrollment : enrollments_) {
            cout << " " << setw(columnLengths[0]) << enrollment.first->getId() << " | "
                << setw(columnLengths[1]) << enrollment.first->getName() << " | "
                << setw(columnLengths[2]) << enrollment.first->getPosition() << " | "
                << setw(columnLengths[3]) << enrollment.first->getDepartment() << " | "
                << setw(columnLengths[4]) << enrollment.first->getJoinDate() << " | "
                << setw(columnLengths[5]) << enrollment.first->getAge() << " | "
                << setw(columnLengths[6]) << enrollment.first->getPercent() << " |\n";
        }
    }



private:
    Enrollment* enrollments;
    // map Enrollments
    map<int, Enrollment*> enrollments_;
};



void enrollManagerMenu() {
    EnrollmentManager enrollManager;
    vector<string> menuData = { "1. Enroll Employee", "2. Unenroll Employee", "3. View Enrollments" };
    int selectedOption = 0;

    while (true) {
        Menu menu(menuData, "Enrollment Menu\n", "Press 'Enter' to select an option or 'q' to quit :", selectedOption);
        int selectedOption = menu.run();

        switch (selectedOption) {
        case 0:
            logger->log("Enroll Employee");
            enrollManager.enrollEmployee();
            break;
        case 1:
            logger->log("Unenroll Employee");
            break;
        case 2:
            logger->log("View Enrollments");
            enrollManager.viewEnrollments();
            break;
        case -2:
            logger->log("Enrollment Menu Exited");
            return;
        default:
            return;
        }
    }
}