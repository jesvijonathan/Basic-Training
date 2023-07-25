#include <iostream>
#include <fstream>
#include <mutex>

class Logger {
private:
    std::ofstream logfile;
    static Logger* instance;

    Logger() {
        logfile.open("log.txt", std::ios::app);
    }

public:
    static Logger* getInstance() {
        if (!instance) {
            instance = new Logger();
        }
        return instance;
    }

    void log(const std::string& message) {
        if (logfile.is_open()) {
            logfile << message << std::endl;
        }
    }

    ~Logger() {
        if (logfile.is_open()) {
            logfile.close();
        }
    }
};

Logger* Logger::instance = nullptr;
