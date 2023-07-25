
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





/*
A class called Enrollment that represents an individual employee's enrollment in a course. The class
should have a constructor that initializes the enrollment with a reference to the employee and a
reference to the course. The class should also have a destructor that deallocates any memory used by
the object.

• A class called Enrollment Manager that manages employee enrollments. The class should be
implemented as a std::map container that stores objects of type Enrollment.

*/