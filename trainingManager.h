#define AddCourse 0
#define AddEmployee 1
#define Update 2
#define EnrollEmployee 3
#define GenerateReport 4
#define Save 5
#define Load 6
#define Exit 7

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
        menuOptions = { "Add new course", "Add new employee", "Update Details", "Enroll employee in course", "Generate report","Save", "Load", "Exit" };
    }
    TrainingManager(vector<string> menuOptions) {
        this->menuOptions = menuOptions;
    }
    //deri class fun
    void quit_seq() {
        cout << "asbtract class for above quit_seq | this will not be printed";
    }

    void run() {
        Menu menu(menuOptions, "Training Management Application\n\nMain Menu\n", "Press 'Enter' to select an option or 'q' to quit :");
        int selectedOption = menu.run();

        if (selectedOption < menuOptions.size() - 1) {
            switch (selectedOption) {
            case AddCourse:
                logger->log("Course Menu");
                courseMenu();
                break;
            case AddEmployee:
                logger->log("Employee Menu");
                employeeMenu();
                break;
            case Update:
                logger->log("Update Menu");
                updateMenu();
                break;
            case EnrollEmployee:
                logger->log("Enroll employee Menu");
                enrollManagerMenu();
                break;
            case GenerateReport:
                logger->log("Generate report");
                reportMenu();
                break;
            case Save:
                try {
                    logger->log("Saved");
                    persistentSave.globalSave();
                    cout << "\n\nSaved !";
                }
                catch (exception e) {
                    cout << "\n\nError while saving !";
                }
                system("pause");
                break;
            case Load:
                try {
                    logger->log("Loaded");
                    persistentSave.globalLoad();
                    cout << "\n\nLoaded !";


                }
                catch (exception e) {
                    cout << "\n\nError while loading !";
                }
                system("pause");
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