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
  friend ostream& operator<<(ostream&, const Course&);
public:
  Course(string, uint);
  string getCourseName();
  void setCourseName(string);
  uint getNumberCredits();
  void setNumberCredits(uint num);
  string toString();
};

#endif /*_COURSE_H_*/