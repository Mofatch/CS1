#include "Student.h"

uint Student::getPID() {
  return this->PID;
}
void Student::setPID(uint num) {
  this->PID = num;
}
string Student::getName() {
  return this->name;
}
void Student::setName(string nom) {
  this->name = nom;
}
uint Student::getAcademicYear() {
  return this->academicYear;
}
void Student::setAcademicYear(uint year) {
  this->academicYear = year;
}
Student::Student(uint id, string nom, uint year) {
  PID = id;
  name = nom;
  academicYear = year;

  cout << "Student is being created..." << endl;
}
Student::Student() {
  PID = 1000001;
  name = "Bosephus";
  academicYear = 1;
}
