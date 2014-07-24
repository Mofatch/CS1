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
  string getCourseName();
  void setCourseName(string);
  uint getNumberCredits();
  void setNumberCredits(uint num);
};

#endif /*_COURSE_H_*/