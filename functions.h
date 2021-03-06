#ifndef functions_H // include guard
#define functions_H

bool confirm();

int numberInput(bool enterToEnd = false);

bool optionInput();

void isGrade(int &grade);




void examResult(Students &student);

bool fillWithRandomNumbers(Students &student, int gradeQuant = 10);

void newStudent(Students &student);

void submitStudent(Students student, Students *&students, int &studentQuantity);

void printResult(Students *students, int studentQuantity, bool printMedian, bool offstream);

int wordCount(string str);

bool comepareTwoStudents(Students a, Students b);


#endif