#ifndef _COURSE_H_
#define _COURSE_H_

// libraries
#include <iostream>
#include <string>

// declarations
using std::string;

// typedefs
typedef unsigned int uint;

class Course {
  string courseName;
  uint numberCredits;
public:
  string getCourseName();
  void setCourseName(string);
  uint getNumberCredits();
  void setNumberCredits(uint num);
};

#endif /*_COURSE_H_*/