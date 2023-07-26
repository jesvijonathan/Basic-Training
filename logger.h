#include <iostream>
#include <fstream>
#include <mutex>

using namespace std;

class Logger {

private:
    ofstream logfile;

    static Logger* instance;
    static mutex mtx;

    Logger() {
        logfile.open("log.txt", ios::app);
    }

public:
    static Logger* getInstance() {
        lock_guard<mutex> lock(mtx);

        if (!instance) {
            instance = new Logger();
        }

        return instance;
    }

    void log(const string& message) {
        lock_guard<mutex> lock(mtx);
        if (logfile.is_open()) {
            logfile << message << endl;
        }
    }

    ~Logger() {
        if (logfile.is_open()) {

            logfile.close();
        }
    }
};

Logger* Logger::instance = nullptr;

mutex Logger::mtx;


