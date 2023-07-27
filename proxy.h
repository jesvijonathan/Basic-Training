
class TrainingManagerProxy {
private:
    TrainingManager* trainingManager;
    string username, password;
    char ch;

public:
    TrainingManagerProxy() {
        trainingManager = nullptr;
    }

    void authenticate() {
        //return run(); 
        system("cls");
        cout << "Training Management Application | Authentication\n\n";
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";

        while ((ch = _getch()) != KEY_ENTER) {
            if (ch == KEY_BACKSPACE) {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                password.push_back(ch);
                cout << "*";
            }
        }

        if (username == default_username && password == default_password) {
            current_user = username;
            logger->log("User " + username + " logged in");
            return run();
        }
        else {
            string msg = "\n\nInvalid username or password !";
            throw msg;
        }
    }

    void run() {
        if (!trainingManager) {
            logger->log("Initializing Training Manager");
            trainingManager = new TrainingManager();
        }
        trainingManager->run();
    }

    ~TrainingManagerProxy() {
        if (trainingManager) {
            delete trainingManager;
        }
    }
};