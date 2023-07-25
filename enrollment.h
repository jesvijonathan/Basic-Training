
#include <iostream>
#include <string>

// Forward declaration of classes
class Employee;
class Course;

class Enrollment {
private:
    const Employee& employee; // Reference to the enrolled employee
    const Course& course;     // Reference to the enrolled course

public:
    // Constructor: Initializes the enrollment with employee and course references
    Enrollment(const Employee& emp, const Course& crs) : employee(emp), course(crs) {}

    // Destructor: No dynamic memory to release, so it's not necessary to define it explicitly
    // However, it's good practice to have it in the header.

    // Getter functions
    const Employee& getEmployee() const {
        return employee;
    }

    const Course& getCourse() const {
        return course;
    }
};

// For demonstration purposes, let's define the Employee and Course classes as well

class Employee {
private:
    std::string name;
    std::string position;
    // Other relevant details related to an employee

public:
    // Constructor
    Employee(const std::string& empName, const std::string& empPosition)
        : name(empName), position(empPosition) {}

    // Add more functions and data members as needed
};

class Course {
private:
    std::string title;
    std::string description;
    std::string instructor;
    // Other relevant details related to a course

public:
    // Constructor
    Course(const std::string& crsTitle, const std::string& crsDescription, const std::string& crsInstructor)
        : title(crsTitle), description(crsDescription), instructor(crsInstructor) {}

    // Add more functions and data members as needed
};


/*
A class called Enrollment that represents an individual employee's enrollment in a course. The class
should have a constructor that initializes the enrollment with a reference to the employee and a
reference to the course. The class should also have a destructor that deallocates any memory used by
the object.

• A class called Enrollment Manager that manages employee enrollments. The class should be
implemented as a std::map container that stores objects of type Enrollment.

*/