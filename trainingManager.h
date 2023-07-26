#define AddCourse 0
#define AddEmployee 1
#define EnrollEmployee 2
#define GenerateReport 3
#define Exit 4

class Quit {
public:
    //base class fun
    void quit_seq() {
        logger->log("Application Exited");
        cout << "\n\nExiting...";
        exit(0);
    }
    void quit() {
        quit_seq();
    }
};

// inheritence
class TrainingManager : public Quit {
private:
    vector<string> menuOptions;


public:
    TrainingManager() {
        menuOptions = { "Add new course", "Add new employee", "Enroll employee in course", "Generate report", "Exit" };
    }
    TrainingManager(vector<string> menuOptions) {
        this->menuOptions = menuOptions;
    }
    //deri class fun
    void quit_seq() {
        cout << "asbtract class test | this will not be printed lol";
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
                enrollManagerMenu();
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
            // abstract class
            quit();
        }
    }
};