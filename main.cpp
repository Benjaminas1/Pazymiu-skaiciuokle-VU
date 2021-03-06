#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <cstring>

using namespace std;

struct Students{
    string name;
    string surname;
    int homeworkQuant;
    vector<int> grades;
};

bool confirm(){
    string yesNo;
    while(true){
        cin >> yesNo;
        if(yesNo == "T") return true;
        else if(yesNo == "N") return false;
        else {
            cout << "Ivesti duomenys yra neteisingo formato, iveskite 'T' arba 'N': ";
        }
    }
}

int numberInput(bool enterToEnd = false){
    int number = 0;
    while(true){
        cin >> number;
        if(enterToEnd && number == -1){
            return -1;
        }
        if(cin.fail() || number<1) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Ivesti duomenys yra neteisingo formato, iveskite skaiciu (ne mazesni nei 1): ";
        }
        else return number;
    }
}

bool optionInput(){
    int number = 0;
    while(true){
        cin >> number;
        if(number == 1) return false;
        else if(number == 2) return true;
        else cout << "Ivesti duomenys yra neteisingo formato, iveskite skaiciu 1 arba 2: ";
    }
}

void isGrade(int &grade){
    while(true){
        if(grade>0 && grade<=10) break;
        else cout << "Ivestas pazymys neatitinka reikalavimu, iveskite skaiciu nuo 1 iki 10: ";
        grade = numberInput();
    }
}

void examResult(Students &student){
    cout << "Iveskite egzamino rezultata: ";
    student.grades[student.homeworkQuant-1] = numberInput();
    isGrade(student.grades[student.homeworkQuant-1]);
}

bool fillWithRandomNumbers(Students &student, int gradeQuant = 10){
    cout << "Ar norite kad mokinio balai butu sugeneruojami atsitiktiniu budu? (T/N): ";
    bool confirmation = confirm();

    if(confirmation){
        //random sk generavimas
        using hrClock = chrono::high_resolution_clock;
        std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));

        uniform_int_distribution<int> dist(1, 10);

        student.homeworkQuant = gradeQuant;
        student.grades.resize(gradeQuant);
        for(int i=0; i<student.homeworkQuant; i++){
            student.grades[i] = dist(mt);
        }
        return true;
    }
    return false;
}

void newStudent(Students &student){
    cout << "Iveskite studento varda ir pavarde: ";
    cin >> student.name >> student.surname;

    cout << "Ar zinomas namu darbu kiekis? (T/N): ";
    bool confirmation = confirm();
    
    if(confirmation){
        cout << "Iveskite namu darbu kieki: ";
        student.homeworkQuant = numberInput();
        student.grades.resize(student.homeworkQuant);

        bool filledRandom = fillWithRandomNumbers(student, student.homeworkQuant);
        
        if(!filledRandom){
            cout << "Iveskite namu darbu pazymius: " << endl;
            for(int i=0; i<student.homeworkQuant; i++){
                student.grades[i] = numberInput();
                isGrade(student.grades[i]);
            }
            examResult(student);
        }
    }
    else{
        bool filledRandom = fillWithRandomNumbers(student);

        if(!filledRandom){
            cout << "Iveskite namu darbu pazymius: " << endl;
            int gradeIndex = 0;
            student.homeworkQuant = 1;
            student.grades.resize(student.homeworkQuant);
            while(true){
                student.grades[gradeIndex] = numberInput(true);
                if(student.grades[gradeIndex] == -1){
                    examResult(student);
                    break;
                }
                isGrade(student.grades[gradeIndex]);
                //cout << student.homeworkQuant << " " << student.grades[gradeIndex] << " " << gradeIndex << endl;
                //expandArray(student.grades, student.homeworkQuant);
                student.homeworkQuant++;
                student.grades.resize(student.homeworkQuant);
                gradeIndex++;
            }
        }
    }

}

void submitStudent(Students student, Students *&students, int &studentQuantity){
    //expand students array
    Students* newArr = new Students[studentQuantity+1];
    for(int i=0; i<studentQuantity; i++){
        newArr[i] = students[i];
    }
    delete[] students;
    students = newArr;
    studentQuantity+=1;

    //submit student
    students[studentQuantity-1] = student;
}

void printResult(Students *students, int studentQuantity, bool printMedian, bool offstream){

    double finalGrade = 0;
    string finalType = "";
    finalType = printMedian ? "(Med.)" : "(Vid.)";

    ofstream out("rez.txt");

    if(offstream){
        out << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw(0) << "Galutinis " << finalType << endl << "----------------------------------------------" << endl;
    } 
    else cout << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw(0) << "Galutinis " << finalType << endl << "----------------------------------------------" << endl;
    
    for(int i=0; i<studentQuantity; i++){
        finalGrade = 0;
        if(printMedian){
            int midIndex = (students[i].homeworkQuant/2)-1;
            //sort(students[i].grades, students[i].grades + students[i].homeworkQuant);
            sort(students[i].grades.begin(), students[i].grades.end()); 

            if(students[i].homeworkQuant % 2 == 0){
            
                finalGrade = 1.00 * (students[i].grades[midIndex] + students[i].grades[midIndex+1]) / 2;
            }
            else{
                finalGrade = students[i].grades[midIndex];
            }
        }
        else{
            double avg = 0;
            for(int gradeIndx=0; gradeIndx < students[i].homeworkQuant-1; gradeIndx++){
                avg += students[i].grades[gradeIndx];
            }
            avg = avg/(students[i].homeworkQuant-1);
            finalGrade = avg*0.4 + students[i].grades[students[i].homeworkQuant-1]*0.6;
        }

        if(offstream){
            out << left << setw(15) << students[i].name << left << setw(15) << students[i].surname << left << setw(15) << setprecision(2) << fixed << finalGrade << endl;
        }
        else cout << left << setw(15) << students[i].name << left << setw(15) << students[i].surname << left << setw(15) << setprecision(2) << fixed << finalGrade << endl;

    }
}

// void printStudent(Students student, bool printMedian){

//     ofstream out("")

//     double finalGrade = 0;
//     string finalType = "";
//     finalType = printMedian ? "(Med.)" : "(Vid.)";
    
//     cout << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw(0) << "Galutinis " << finalType << endl << "----------------------------------------------" << endl;

//         finalGrade = 0;
//         if(printMedian){
//             int midIndex = (student.homeworkQuant/2)-1;
//             //sort(students[i].grades, students[i].grades + students[i].homeworkQuant);
//             sort(student.grades.begin(), student.grades.end()); 

//             if(student.homeworkQuant % 2 == 0){
            
//                 finalGrade = 1.00 * (student.grades[midIndex] + student.grades[midIndex+1]) / 2;
//             }
//             else{
//                 finalGrade = student.grades[midIndex];
//             }
//         }
//         else{
//             double avg = 0;
//             for(int gradeIndx=0; gradeIndx < student.homeworkQuant-1; gradeIndx++){
//                 avg += student.grades[gradeIndx];
//             }
//             avg = avg/(student.homeworkQuant-1);
//             finalGrade = avg*0.4 + student.grades[student.homeworkQuant-1]*0.6;
//         }
//         cout << left << setw(15) << student.name << left << setw(15) << student.surname << left << setw(15) << setprecision(2) << fixed << finalGrade << endl;

// }

int wordCount(string str){
    int wc = 1;

    for(int i=0; i<str.length(); i++){
        if(i >= 1 && !isspace(str[i]) && isspace(str[i-1])) wc++;
    }

    return wc;
}

bool comepareTwoStudents(Students a, Students b){
    if(a.name<b.name) return true;
    else return false;
}

int main(){
    ifstream in("duomenys.txt");
    ofstream out("rez.txt");

    int studentQuantity = 0;
    Students* students = new Students[studentQuantity];

    //Students student;

    cout << "Ar norite kad duomenys butu nuskaityti is failo? (T/N): ";
    if(confirm()){
        string firstLine;
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