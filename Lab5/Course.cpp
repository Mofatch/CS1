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
Course::Course(string title, uint credits) {
  // assign class fields
  numberCredits = credits;
  courseName = title;

  cout << "Course is being created..." << endl;
}
string Course::toString() {
  // TODO: patch minGW to get to_string working
  return "Title: " + courseName + "\n";
  // + "Number of Credits: " + std::to_string(numberCredits) + "\n";
}
ostream& operator<<(ostream &strm, const Course &crs) {
  return strm << crs.toString();
}