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
bool ask(string);

// global map variable
NameMap sMap;
CourseListMap cMap;

int main() {

  do {
    createStudent();
    do {
      NameMap::iterator studentIterator = sMap.end();
      studentIterator--;
      // add classes
      Course thisCourse = createCourse();
      addCourse(studentIterator->second, thisCourse);
    } while(ask("Add another course?"));
  } while(ask("Would You like to add more students?"));
  printStudents();

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
  // declare iterators
  NameMap::iterator studentIterator;

  // Title
  cout << "**Students**" << endl << endl;

  for(studentIterator = sMap.begin(); studentIterator != sMap.end(); studentIterator++) {
    // identify PID and use PID to get course list
    uint idNo = studentIterator->second.getPID();
    vector<Course> list = cMap[idNo];

    // print student's name
    cout << "-Student: " + studentIterator->first << endl;

    // loop through course list for this student printing courses
    for(int i = 0; i < list.size(); ++i) {
      cout << list.at(i) << endl;
    }

    // space for next student
    cout << endl;
  }

}
// check for this course in the vector
bool contains(vector<Course> v, Course crs) {
  for(vector<Course>::iterator i = v.begin(); i != v.end(); ++i) {
    if (*i == crs) return true;
  }

  return false;
}
// ask for input from user return true for yes, false for no
bool ask(string question) {
  bool goodAnswer = false;
  string response;
  do {
    cout << question << endl;
    cout << "1: Yes\n";
    cout << "2: No\n";
    cout << ">";
    cin >> response;

    // validate input
    if(response == "1" || response == "2")
     goodAnswer = true;
    else 
      cout << "Please select 1 or 2." << endl;

    // continue to ask until valid input is offered
  } while (!goodAnswer); 

  return response == "1" ? true : false;
}