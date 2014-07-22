#ifndef _COURSE_H_
#define _COURSE_H_

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