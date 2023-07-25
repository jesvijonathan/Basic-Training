#include <iostream>
#include <fstream>
#include <mutex>

class Logger {
private:
    std::ofstream logfile;
    static Logger* instance;
    static std::mutex mtx;

    Logger() {
        logfile.open("log.txt", std::ios::app);
    }

public:
    static Logger* getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!instance) {
            instance = new Logger();
        }
        return instance;
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
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
std::mutex Logger::mtx;


