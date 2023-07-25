#include <iostream>
#include <string>
#include <conio.h>
#include <vector>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

int arrow_menu(const std::vector<std::string>& options) {
    int selectedOption = 0;

    while (true) {
        system("cls"); // Clear the console (for Windows)
        // Use "system("clear")" for Unix-like systems

        std::cout << "Menu:\n";
        for (int i = 0; i < options.size(); ++i) {
            if (i == selectedOption)
                std::cout << "--> " << options[i] << std::endl;
            else
                std::cout << "    " << options[i] << std::endl;
        }

        std::cout << "\nPress 'Enter' to select an option or 'q' to quit: ";

        // Wait for arrow key press
        char ch = 0;
        ch = _getch();
        if (ch == 0 || ch == -32) {
            ch = _getch(); // Get the extended key code
            switch (ch) {
            case KEY_UP:
                // Move the arrow up (unless at the first option)
                if (selectedOption > 0)
                    --selectedOption;
                break;
            case KEY_DOWN:
                // Move the arrow down (unless at the last option)
                if (selectedOption < options.size() - 1)
                    ++selectedOption;
                break;
            default:
                break;
            }
        }
        else if (ch == KEY_ENTER) {
            return selectedOption; // Return the selected option index
        }
        else if (ch == 'q' || ch == 'Q') {
            return -1; // Return -1 to indicate quitting
        }
    }
}

int main() {
    std::vector<std::string> options = { "name", "description", "date", "title" };

    while (true) {
        int selectedOption = arrow_menu(options);

        if (selectedOption != -1) {
            std::string userInput;
            std::cout << "Enter a string for '" << options[selectedOption] << "': ";
            std::getline(std::cin, userInput);
            std::cout << "Stored value: " << userInput << std::endl;
            std::cout << "Press 'Enter' to continue...";
            std::cin.ignore();
        }
        else {
            break;
        }
    }

    return 0;
}
