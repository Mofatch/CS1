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
typedef map<string, Student> NameMap;
typedef map<uint, vector<Course> > CourseListMap;

// // prototypes
void createStudent();
Course createCourse();
void addCourse(Student, Course);
void printStudents();
bool contains(vector<Course>, Course);

// global map variable
NameMap sMap;
CourseListMap cMap;

int main() {
  // add student to map
  createStudent();

  // display student
  NameMap::iterator studentIterator = sMap.begin();
  cout << studentIterator->second << endl;

  // create/display test course 
  Course testCourse = createCourse();
  cout << "Course Information: " << endl << testCourse << endl << endl;

  // add test course to student's list
  addCourse(studentIterator->second, testCourse);

  return 0;
}

// main.cpp functions
void createStudent() {
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

  // add student to sMap
  sMap[stud.getName()] = stud;
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

  // return new course
  return crs;
}
void addCourse(Student stud, Course crs) {
  // list of student's courses
  vector<Course> list = cMap[stud.getPID()];

  // if the student does not have this course
  if(!contains(list, crs)) {
    cMap[stud.getPID()].push_back(Course(crs.getCourseName(), crs.getNumberCredits()));
  }
}
void printStudents() {
  
}
bool contains(vector<Course> v, Course crs) {
  // check for this course in the vector
  for(vector<Course>::iterator i = v.begin(); i != v.end(); ++i) {
    if (*i == crs) return true;
  }

  return false;
}