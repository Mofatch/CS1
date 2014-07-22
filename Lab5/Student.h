#ifndef _STUDENT_H_
#define _STUDENT_H_

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