#ifndef _COURSE_H_
#define _COURSE_H_

// libraries
#include <iostream>
#include <string>
#include <map>
#include <vector>

// declarations
using namespace std;

// typedefs
typedef unsigned int uint;

class Course {
  string courseName;
  uint numberCredits;
public:
  Course(string, uint);
  virtual ~Course() {
  }
  string getCourseName();
  void setCourseName(string);
  uint getNumberCredits();
  void setNumberCredits(uint num);
  friend ostream& operator<<(ostream &strm, const Course &crs) {
    return strm << "Course: " << crs.courseName << endl
     << "Number of Credits: " << crs.numberCredits << endl;
  }
  friend bool operator==(Course crs1, Course crs2) {
    return (crs1.courseName == crs2.courseName &&
            crs1.numberCredits == crs2.numberCredits);   
  }
  friend bool operator!=(Course crs1, Course crs2) {
    return !(crs1 == crs2);
  }
};

#endif /*_COURSE_H_*/