#include "includes/students.hpp"
#include "includes/functions.hpp"


int main(){
    long int studentQuantity = 0;

    vector<StudentsFromFile> studentsFF;
    //studentsFF.resize(10000000);
    bool printMedian;
    //Students* studentsArray = new Students[studentQuantity];

    

    std::cout << "Ar norite sugeneruoti studentu sarasu failus? (T/N): ";
    if(confirm()) generateFiles();

    std::cout << "Ar norite atlikti testavima? (T/N): ";
    if(confirm()){
        runProgramTest(chooseStrategy());
        return 0;
    }

    //Students student;
    std::cout << "Ar norite kad duomenys butu nuskaityti is failo? (T/N): ";
    if(confirm()){
        std::cout << "Pasirinkite atspausdinti galutinio balo Vidurki(1) arba Mediana(2): ";
        printMedian = optionInput();

        readFromFile(studentsFF, printMedian, "duomenys/duomenys.txt");
    }
    else{
        Students student;
        StudentsFromFile tempStudent;

        std::cout << "Pasirinkite atspausdinti galutinio balo Vidurki(1) arba Mediana(2): ";
        printMedian = optionInput();

        newStudent(student);

        

        student.finalGrade = calculateFinalGrade(student.grades, student.homeworkQuant, student.examGrade, printMedian);

        tempStudent.name = student.name;
        tempStudent.surname = student.surname;
        tempStudent.finalGrade = student.finalGrade;
        cout << "final grade:  " << tempStudent.finalGrade << endl;
        studentsFF.push_back(tempStudent);

        bool confirmation = true;
        while(confirmation){
            std::cout << "Ar norite prideti dar viena moksleivi? (T/N): ";
            confirmation = confirm();
            if(confirmation){
                Students student;
                newStudent(student);
                //students.resize(studentQuantity+1);
                //students[studentQuantity] = student;
                student.finalGrade = calculateFinalGrade(student.grades, student.homeworkQuant, student.examGrade, printMedian);
                tempStudent.name = student.name;
                tempStudent.surname = student.surname;
                tempStudent.finalGrade = student.finalGrade;
                studentsFF.push_back(tempStudent);
            }
        }
    }



    //cout << students[0].name << " " << students[1].name << endl;
    //sort(students, students + studentQuantity, comepareTwoStudents);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    sort(studentsFF.begin(), studentsFF.end(), comepareTwoStudents);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Irasu surusiavimo laikas: " << time << endl;
    
    printResult(studentsFF, printMedian, "rezultatai/rezultatai.txt");
    
    splitStudents(studentsFF, studentsFF.size(), printMedian);

    
}