#include "Student.h"

uint getPID() {
  return this->PID;
}
void setPID(uint num) {
  this->PID = num;
}
string getName() {
  return this->name;
}
void setName(string nom) {
  this->name = nom;
}
uint getAcademicYear() {
  return this->academicYear;
}
void setAcademicYear(uint year) {
  this->academicYear = year;
}