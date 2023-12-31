

void deleteCourse() {
    int id;
    char choice;

    cout << "\nEnter course id to delete: ";
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
        cout << "\n\n ID : " << selectedCourse->getId()
            << "\n Title : " << selectedCourse->getTitle()
            << "\n Description : " << selectedCourse->getDescription()
            << "\n Instructor : " << selectedCourse->getInstructor()
            << "\n Start Date : " << selectedCourse->getStartDate()
            << "\n End Date : " << selectedCourse->getEndDate() << "\n\n";

        cout << "\nAre you sure you want to delete this course? (y/n) : ";
        cin >> choice;

        if (choice == 'y') {
            logger->log("Course " + to_string(selectedCourse->getId()) + " deleted");
            courses.erase(it);
            delete selectedCourse;
        }
        else {
            logger->log("Course " + to_string(selectedCourse->getId()) + " deletion cancelled");
        }
    }
    else {
        logger->log("Course " + to_string(id) + " not found");
    }
}

void deleteEmployee() {
    int id;
    char choice;

    cout << "\nEnter employee id to delete : ";
    cin >> id;

    auto it = find_if(employees.begin(), employees.end(), [id](const Employee* employee) {
        return employee->getId() == id;
        });

    if (it != employees.end()) {
        Employee* selectedEmployee = *it;
        cout << "Employee found: ";
        cout << "\n\n ID : " << selectedEmployee->getId()
            << "\n Name : " << selectedEmployee->getName()
            << "\n Position : " << selectedEmployee->getPosition()
            << "\n Department : " << selectedEmployee->getDepartment()
            << "\n Join Date : " << selectedEmployee->getJoinDate()
            << "\n Age : " << selectedEmployee->getAge()
            << "\n Percent : " << selectedEmployee->getPercent() << "\n\n";

        cout << "Are you sure you want to delete this employee? (y/n) : ";
        cin >> choice;

        if (choice == 'y') {
            employees.erase(it);
            logger->log("Employee " + to_string(id) + " deleted");
        }
        else {
            logger->log("Employee " + to_string(id) + " not deleted");
        }
    }
    else {
        cout << "Employee not found\n";
        logger->log("Employee " + to_string(id) + " not found");
    }
}

void updateMenu() {
    vector<string> menuOptions = { "Delete Course", "Delete Employee", "Return" };
    ReportGenerator<Course> courseReport;

    while (true) {
        Menu menu(
            menuOptions,
            "\n\nMain Menu / Update \n\n",
            "Press 'Enter' to select an option or 'q' to quit :",
            0);

        int selectedOption = menu.run();

        switch (selectedOption) {
        case 0:
            cout << "\n\n";
            courseReport.viewCourses();
            deleteCourse();
            break;
        case 1:
            cout << "\n\n";
            courseReport.viewEmployees();
            deleteEmployee();
            break;
        case 2:
        case -1:
            return;
        }
    }
}