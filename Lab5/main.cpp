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
#include "Course.h"
#include "Student.h"

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
  // CODE
  cout << "Sup";
  return 0;
}

// main functions
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

  // TODO: student constructor, add to map
}
Course createCourse() {
  // CODE
}
void addCourse(Student stud, Course crs) {
  // CODE
}
void printStudents() {
  // CODE
}