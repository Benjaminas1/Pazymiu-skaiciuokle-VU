#ifndef functions_H // include guard
#define functions_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <cstring>
#include <sstream>
#include <list>
#include <deque>

using namespace std;


bool confirm();

int numberInput(bool enterToEnd = false);

bool optionInput();

void isGrade(int &grade);

void examResult(Students &student);

bool fillWithRandomNumbers(Students &student, int gradeQuant = 10);

void newStudent(Students &student);

double calculateFinalGrade(vector<int> grades, int homeworkCount, int exam, bool printMedian);

template <class T>
void printResult(T students, bool printMedian, string outDir = "rezultatai/rezultatai.txt");

int wordCount(string str);

bool comepareTwoStudents(StudentsFromFile a, StudentsFromFile b);

void generateFiles();

void filterOutput();

template <class T>
void readFromFile(T &studentsFF, bool printMedian, string fileName);

void splitStudentsVector(vector<StudentsFromFile> &students, int studentQuantity, bool printMedian);

void splitStudentsList(list<StudentsFromFile> &students, int studentQuantity, bool printMedian);

void runProgramTest();

#endif