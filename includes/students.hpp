#ifndef struct_H // include guard
#define struct_H

#include <vector>
#include <string>

using namespace std;

struct Students{
    string name;
    string surname;
    int homeworkQuant;
    vector<int> grades;
    int examGrade;
    double finalGrade;
};

struct StudentsFromFile{
    string name;
    string surname;
    double finalGrade;
};

#endif