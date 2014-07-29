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
  Student(uint, string, uint);
  Student();
  virtual ~Student() {
    PID = 0;
    name = "";
    academicYear = 0;
  }
  uint getPID();
  void setPID(uint);
  string getName();
  void setName(string);
  uint getAcademicYear();
  void setAcademicYear(uint year);
  friend ostream& operator<<(ostream &strm, const Student &stud) {
    return strm << "Student: " << stud.name << endl
                << "PID: " << stud.PID << endl
                << "Academic Year: " << stud.academicYear << endl;
  }
};

#endif /* _STUDENT_H_ */