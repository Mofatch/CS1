#include "Course.h"

string Course::getCourseName() {
  return this->courseName;
}
void Course::setCourseName(string title) {
  this->courseName = title;
}
uint Course::getNumberCredits() {
  return this->numberCredits;
}
void Course::setNumberCredits(uint num) {
  this->numberCredits = num;
}