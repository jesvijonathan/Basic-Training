
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <deque> 

class Employee;
class Course;

class Enrollment {
public:
    Enrollment(Employee* employee, Course* course) : employee(employee), course(course) {
    }

    ~Enrollment() {
        delete employee;
        delete course;
    }

    Employee* getEmployee() const {
        return employee;
    }

    Course* getCourse() const {
        return course;
    }

private:
    Employee* employee;
    Course* course;
};

class EnrollmentManager {
public:
    EnrollmentManager() {
    }

    ~EnrollmentManager() {
        for (auto it = enrollments.begin(); it != enrollments.end(); ++it) {
            delete it->second;
        }
    }

    void addEnrollment(Enrollment* enrollment) {
        enrollments.insert(std::pair<int, Enrollment*>(enrollment->getEmployee()->getId(), enrollment));
    }

    void removeEnrollment(int employeeId) {
        enrollments.erase(employeeId);
    }

    Enrollment* getEnrollment(int employeeId) {
        return enrollments[employeeId];
    }

    std::map<int, Enrollment*> getEnrollments() const {
        return enrollments;
    }

private:
    std::map<int, Enrollment*> enrollments;
};
