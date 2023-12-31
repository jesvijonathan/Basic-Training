
class Enrollment {

public:
    Enrollment(Employee& employee, Course& course) : employee_(employee), course_(course) {}

    ~Enrollment() {}

    Employee& employee_;
    Course& course_;
};



class VirtualView {

public:
    virtual void view() = 0;
};


class EnrollmentManager : public VirtualView {

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
            logger->log("Course " + to_string(currentCourse_->getId()) + " selected");
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
            logger->log("Employee " + to_string(currentEmployee_->getId()) + " selected");
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

    void view() {
        cout << "Enrollments: \n\n";
        cout << "Employee_ID | Employee_Name | Course_ID | Course_Title\n";
        for (const auto& enrollment : enrollments_) {
            cout << " " << setw(11) << enrollment->employee_.getId() << " | "
                << setw(13) << enrollment->employee_.getName() << " | "
                << setw(9) << enrollment->course_.getId() << " | "
                << setw(12) << enrollment->course_.getTitle() << " | \n";
        }
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


    void addToEnroll(Employee* employeeT, Course* courseT) {
        enrollments_.push_back(new Enrollment(*employeeT, *courseT));
        logger->log("Employee " + to_string(employeeT->getId()) + " enrolled in course " + to_string(courseT->getId()));
    }

    void enroll() {
        selectEmployee();
        selectCourse();

        if (currentCourse_ != nullptr && currentEmployee_ != nullptr) {
            cout << "\nEmployee enrolled in course\n";
            system("pause");

            enrollments_.push_back(new Enrollment(*currentEmployee_, *currentCourse_));
            logger->log("Employee " + to_string(currentEmployee_->getId()) + " enrolled in course " + to_string(currentCourse_->getId()));
        }
        else {
            cout << "course or employee not selected\n";
        }
        currentCourse_ = nullptr;
        currentEmployee_ = nullptr;
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
            logger->log("Employee " + to_string(id) + " unenrolled");
        }
        else {
            cout << "Employee with id " << id << " not found ! \n\n";
        }

        system("pause");
    }


    auto getEnrollments() {
        return enrollments_;
    }

    auto setEnrollments(vector<Enrollment*> enrollments) {
        enrollments_ = enrollments;
    }

    auto clearEnrollments() {
        enrollments_.clear();
    }


private:

    Course* currentCourse_;
    Employee* currentEmployee_;
    vector<Enrollment*> enrollments_;

};

EnrollmentManager enrollManager;


void enrollManagerMenu() {
    vector<string> menuData = { "Enroll Employee", "Unenroll Employee", "View Enrollments" ,"Return" };
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
        case 3:
        case -2:
        default:
            logger->log("Returning to Main Menu");
            return;
        }
    }
}