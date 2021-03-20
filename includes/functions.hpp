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

using namespace std;


bool confirm();

int numberInput(bool enterToEnd = false);

bool optionInput();

void isGrade(int &grade);




void examResult(Students &student);

bool fillWithRandomNumbers(Students &student, int gradeQuant = 10);

void newStudent(Students &student);

double calculateFinalGrade(vector<int> grades, int homeworkCount, int exam, bool printMedian);

void printResult(vector<StudentsFromFile> students, int studentQuantity, bool printMedian, bool offstream, string outDir = "rezultatai/rezultatai.txt");

int wordCount(string str);

bool comepareTwoStudents(StudentsFromFile a, StudentsFromFile b);

void generateFiles();

void filterOutput();

void splitStudents(vector<StudentsFromFile> &students, int studentQuantity, bool printMedian);

void readFromFile(vector<StudentsFromFile>& students, bool printMedian);


#endif