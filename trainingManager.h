#define AddCourse 0
#define AddEmployee 1
#define EnrollEmployee 2
#define GenerateReport 3
#define Exit 4

class TrainingManager {
private:
    vector<string> menuOptions;


public:
    TrainingManager() {
        menuOptions = { "Add new course", "Add new employee", "Enroll employee in course", "Generate report", "Exit" };
    }

    void run() {
        Menu menu(menuOptions, "Training Management Application\n\nMain Menu\n", "Press 'Enter' to select an option or 'q' to quit :");
        int selectedOption = menu.run();

        if (selectedOption < menuOptions.size() - 1) {
            switch (selectedOption) {
            case AddCourse:
                logger->log("Add new course");
                courseMenu();
                break;
            case AddEmployee:
                logger->log("Add new employee");
                employeeMenu();
                break;
            case EnrollEmployee:
                logger->log("Enroll employee in course");
                break;
            case GenerateReport:
                logger->log("Generate report");
                reportMenu();
                break;
            default:
                break;
            }
        }
        else {
            logger->log("Application Exited");
            exit(0);
        }
    }
};