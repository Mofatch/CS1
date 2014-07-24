#ifndef _STUDENT_H_
#define _STUDENT_H_

// libraries
#include <iostream>
#include <string>
#include <map>
#include <vector>

// declarations
using namespace std;

// typedefs
typedef unsigned int uint;

class Student {
  uint PID;
  string name;
  uint academicYear;
public:
  uint getPID();
  void setPID(uint);
  string getName();
  void setName(string);
  uint getAcademicYear();
  void setAcademicYear(uint year);
};

#endif /* _STUDENT_H_ */