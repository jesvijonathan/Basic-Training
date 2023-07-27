// Training Management Application

// Main headers
#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>   
#include <map>
#include <fstream>
#include <sstream>
#include <mutex>

// Macros
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_Q 113
#define KEY_S 115

#define auto_load false
#define default_username "wl2028"
#define default_password "123"
std::string current_user;

// Custom headers
#include "logger.h"
#define logger Logger::getInstance() 
#include "menu.h"
#include "course.h"
#include "employee.h"
#include "report.h"
#include "enrollment.h"
#include "update.h" 
#include "persistentSave.h" 
#include "trainingManager.h"
#include "proxy.h"



// names spaces
using namespace std;
using namespace crs;
using namespace emp;

void SetConsoleTitle(const std::string& title) {
    SetConsoleTitleA(title.c_str());
}

int main() {
    try {
        SetConsoleTitle("Worldline - Training Management Application");
        logger->log("\n\nApplication Started");

        TrainingManagerProxy trainingManagerProxy;

    retryCredentials:
        try {
            trainingManagerProxy.authenticate();
        }
        catch (string e) {
            logger->log("Exception : " + e);
            goto retryCredentials;
        }

        while (true) {
            logger->log("Training Manager Invoked");
            trainingManagerProxy.run();
        }
    }
    catch (exception& e) {
        logger->log("Exception : " + string(e.what()));
    }
    catch (...) {
        logger->log("Exception : Unknown");
    }

    system("pause");
    return 0;
}

