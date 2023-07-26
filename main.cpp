// Training Management Application

#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip> // for setw

#include "logger.h"
#define logger Logger::getInstance()

#include "menu.h"
#include "course.h"
#include "employee.h"
#include "enrollment.h"
#include "report.h"
#include "trainingManager.h"



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

// Proxy Design Pattern
class TrainingManagerProxy {
private:
    TrainingManager* trainingManager;

public:
    TrainingManagerProxy() {
        trainingManager = nullptr;
    }

    void run() {
        if (!trainingManager) {
            // Lazy initialization of the TrainingManager
            logger->log("Initializing Training Manager...");
            trainingManager = new TrainingManager();
        }
        trainingManager->run();
    }
};


int main() {
    try {
        SetConsoleTitle("Worldline - Training Management Application");
        logger->log("Application Started");
        TrainingManagerProxy trainingManagerProxy;

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

