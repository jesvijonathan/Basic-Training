
#include <conio.h> 


using namespace std;

class Menu {

public:
    Menu(const vector<string>& options, const string& option_text = "Select an option :",
        const string& option_enter = "", const size_t currentOption = 0) :
        options(options), option_text(option_text), option_enter(option_enter), currentOption(currentOption) {
    }

    void display() const {
        system("cls");

        cout << option_text << "\n";
        for (size_t i = 0; i < options.size(); ++i) {
            if (i == currentOption) {
                cout << "* " << options[i] << "\n";
            }
            else {
                cout << "  " << options[i] << "\n";
            }
        }

        if (option_enter != "") {
            cout << "\n" << option_enter << " ";
        }
    }

    int run() {
        int key;

        while (true)
        {
            display();
            key = 0;

            switch ((key = getch())) {
            case KEY_ENTER:
                return currentOption;
                break;
            case KEY_UP:
                currentOption = (currentOption - 1 + options.size()) % options.size();
                break;
            case KEY_DOWN:
                currentOption = (currentOption + 1) % options.size();
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            case KEY_Q:
                return -1;
                break;
            case KEY_S:
                return -2;
                break;
            default:
                cout << "Invalid input !\n";
                break;
            }

        }


    }

private:
    vector<string> options;
    size_t currentOption;
    string option_text;
    string option_enter;
};


