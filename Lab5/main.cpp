/* Authors: Travis Bashor/Trevor Minnix
  Date: 7/31/14
  Course Info: COP 3502, Summer C 2014 
  Description: The purpose of this program is to demonstrate
  the use of Hash Tables with two classes: Course and Student.
*/ 

// includes
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Course.cpp"
#include "Student.cpp"

// declarations
using namespace std;

// typedefs
typedef unsigned int uint;
typedef map<string, Student> SCMap;

// // prototypes
void createStudent(SCMap);
Course createCourse();
void addCourse(Student, Course);
void printStudents();

int main() {
  Course testCourse = createCourse();
  return 0;
}

// main functions, parameter SCMap myMap
void createStudent(SCMap myMap) {
  // variables used for creating a new student
  string name;
  uint pid, year;

  // gather information for new student
  cout << "Please enter student information.\n";
  cout << "Name: ";
  cin >> name; 
  cout << "PID: ";
  cin >> pid;
  cout << "Academic Year: ";
  cin >> year;

  // create new student
  Student stud(pid, name, year);

  // display student information
  cout << "Name: " << stud.getName() << endl;
  cout << "PID: " << stud.getPID() << endl;
  cout << "Academic Year: " << stud.getAcademicYear() << endl;

  // TODO: add to map
}
Course createCourse() {
  // variables for course information
  string title;
  uint credits;

  // gather information for new course
  cout << "Please enter course information." << endl;
  cout << "Course Title: ";
  cin >> title;
  cout << "Number of Credits: ";
  cin >> credits;

  // create new course
  Course crs(title, credits);

  // display course information
  cout << "Course Title: " << crs.getCourseName() << endl;
  cout << "Number of Credits: " << crs.getNumberCredits() << endl;
}
void addCourse(Student stud, Course crs) {
  // CODE
}
void printStudents() {
  // CODE
}