class PersistentSave {

public:

    static void loadEnrollment() {
        ifstream enrollmentFile("data\\enrollment.csv");

        if (enrollmentFile.is_open()) {
            string line;
            getline(enrollmentFile, line);

            enrollManager.clearEnrollments();

            while (getline(enrollmentFile, line)) {
                stringstream ss(line);
                string data[4];
                for (int i = 0; i < 4; ++i) {
                    getline(ss, data[i], ',');
                }

                Employee* employeeT = nullptr;
                Course* courseT = nullptr;

                for (const auto& emp : employees) {
                    if (emp->getId() == stoi(data[0])) {
                        employeeT = emp;
                        break;
                    }
                }

                for (const auto& crs : courses) {
                    if (crs->getId() == stoi(data[2])) {
                        courseT = crs;
                        break;
                    }
                }

                if (employeeT != nullptr && courseT != nullptr) {
                    enrollManager.addToEnroll(employeeT, courseT);
                }
                else {
                    cout << "Employee or course not found\n";
                }
            }
            logger->log("Enrollment data loaded");
        }
        else {
            cout << "Unable to open file";
        }
    }


    static void loadCourse() {
        ifstream coursesFile("data\\courses.csv");

        if (coursesFile.is_open()) {
            string line;
            getline(coursesFile, line);

            while (getline(coursesFile, line)) {
                stringstream ss(line);
                string data[6];
                for (int i = 0; i < 6; ++i) {
                    getline(ss, data[i], ',');
                }
                courses.push_back(new Course(data[1], data[2], data[3], data[4], data[5]));
            }

            Course::currentId = courses.size();

            logger->log("Courses data loaded");
        }
        else {
            cout << "Unable to open file";

        }
    }


    static void loadEmployee() {
        ifstream employeesFile("data\\employees.csv");

        if (employeesFile.is_open()) {
            string line;
            getline(employeesFile, line);

            while (getline(employeesFile, line)) {
                stringstream ss(line);
                string data[7];
                for (int i = 0; i < 7; ++i) {
                    getline(ss, data[i], ',');
                }
                employees.push_back(new Employee(data[1], data[2], data[3], data[4], stoi(data[5]), stoi(data[6])));
            }

            Employee::currentId = employees.size();

            logger->log("Employees data loaded");
        }
        else {
            cout << "Unable to open file";
        }
    }



    static  void saveEnrollment() {
        ofstream enrollmentFile("data\\enrollment.csv");
        int* columnLengths = new int[7] {0};
        if (enrollmentFile.is_open()) {
            enrollmentFile << "Employee_ID,Employee_Name,Course_ID,Course_Title,\n";
            auto it_enrollments = enrollManager.getEnrollments();
            for (const auto& enrollment : it_enrollments) {
                enrollmentFile << " " << setw(columnLengths[0]) << enrollment->employee_.getId() << " ,"
                    << " " << setw(columnLengths[1]) << enrollment->employee_.getName() << " ,"
                    << " " << setw(columnLengths[2]) << enrollment->course_.getId() << " ,"
                    << " " << setw(columnLengths[3]) << enrollment->course_.getTitle() << " , \n";
            }
            enrollmentFile.close();
            logger->log("Enrollment data saved");
        }
        else {
            cout << "Unable to open file";
        }
    }
    PersistentSave() {
        //globalLoad();
    }


    static  void saveCourse() {
        ofstream coursesFile("data\\courses.csv");
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
            logger->log("Courses data saved");
        }
        else {
            cout << "Unable to open file";
        }

    }

    static void saveEmployee() {
        ofstream employeesFile("data\\employees.csv");
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
            logger->log("Employees data saved");
        }
        else {
            cout << "Unable to open file";
        }
    }


    static void globalSave() {
        saveCourse();
        saveEmployee();
        saveEnrollment();
    }

    static void globalLoad() {
        loadCourse();
        loadEmployee();
        loadEnrollment();

    }
    ~PersistentSave() {
        //globalSave();
    }
};
