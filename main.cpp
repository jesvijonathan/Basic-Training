// Training Management Application

#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>  


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_Q 113
#define KEY_S 115

#define default_username "wl2028"
#define default_password "123"

#include "logger.h"
#define logger Logger::getInstance()


#include "menu.h"
#include "course.h"
#include "employee.h"
#include "report.h"
#include "enrollment.h"
#include "update.h"

#include "persistentSave.h"
PersistentSave persistentSave;

#include "trainingManager.h"
#include "proxy.h"



// names spaces
using namespace std;
using namespace crs;
using namespace emp;

void SetConsoleTitle(const std::string& title)
{
    SetConsoleTitleA(title.c_str());

}

int* getTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentDay = ltm->tm_mday;
    int currentMonth = 1 + ltm->tm_mon;
    int currentYear = 1900 + ltm->tm_year;
    int currentHour = ltm->tm_hour;
    int currentMinute = ltm->tm_min;
    int currentSecond = ltm->tm_sec;

    int* dateArr = new int[3];
    dateArr[0] = currentDay;
    dateArr[1] = currentMonth;
    dateArr[2] = currentYear;
    dateArr[3] = currentHour;
    dateArr[4] = currentMinute;
    dateArr[5] = currentSecond;

    return dateArr;
}

int main() {
    try {
        SetConsoleTitle("Worldline - Training Management Application");
        logger->log("Application Started");

        TrainingManagerProxy trainingManagerProxy;

    retryCredentials:
        try {
            trainingManagerProxy.authenticate();
        }
        catch (string e) {
            logger->log("Exception : " + e);
            cout << e << "\n";
            system("pause");
            goto retryCredentials;
        }

        // persistentSave.globalLoad();
        while (true) {
            logger->log("Training Manager Invoked");
            trainingManagerProxy.run();
        }

    }
    // exception hadnling
    catch (exception& e) {
        logger->log("Exception : " + string(e.what()));
    }
    catch (...) {
        logger->log("Exception : Unknown");
    }
    system("pause");
    return 0;
}

