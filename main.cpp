#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <cstring>

#include "students.h"
#include "functions.h"

using namespace std;

int main(){
    ofstream out("rez.txt");

    int studentQuantity = 0;
    Students* students = new Students[studentQuantity];

    //Students student;
    cout << "Ar norite kad duomenys butu nuskaityti is failo? (T/N): ";
    if(confirm()){
        string firstLine;
        ifstream in;
        try{
            in.open("duomenys.txt");
            if(in.fail()) throw 1;
            
            getline(in, firstLine);

            int homeworkCount = wordCount(firstLine) - 2;

            // bool printMedian = confirm();

            students = new Students[1000000];

            while(true){
                Students student;
                student.homeworkQuant = homeworkCount;
                student.grades.resize(homeworkCount);
                in >> student.name >> student.surname;

                student.grades.resize(homeworkCount);
                for(int i=0; i<student.homeworkQuant; i++){
                    in >> student.grades[i];
                }
                
                students[studentQuantity] = student;
                studentQuantity++;
                
                if(in.eof()) break;
            }
            in.close();
        }
        catch(int e){
            if(e==1) cout << "Error: failas pavadinimu 'duomenys.txt' nerastas" << endl;
            exit(1);
        }

        
    }
    else{
        Students student;
        newStudent(student);
        submitStudent(student, students, studentQuantity);

        bool confirmation = true;
        while(confirmation){
            cout << "Ar norite prideti dar viena moksleivi? (T/N): ";
            confirmation = confirm();
            if(confirmation){
                Students student;
                //expandArray(student.grades, studentQuantity);
                newStudent(student);
                submitStudent(student, students, studentQuantity);
            }
        }
    }

    

    //cout << students[0].name << " " << students[1].name << endl;
    sort(students, students + studentQuantity, comepareTwoStudents);

    cout << "Pasirinkite atspausdinti galutinio balo Vidurki(1) arba Mediana(2): ";
    bool printMedian = optionInput();

    printResult(students, studentQuantity, printMedian, true);
}