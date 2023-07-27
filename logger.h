using namespace std;

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

class Logger {

private:
    ofstream logfile;

    static Logger* instance;
    static mutex mtx;

    Logger() {
        logfile.open("data\\log.log", ios::app);
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
            const int* time = getTime();
            logfile << "[" << time[0] << ":" << time[1] << ":" << time[2] << ":" << time[3] << ":" << time[4] << ":" << time[5] << "]" << " ";
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


