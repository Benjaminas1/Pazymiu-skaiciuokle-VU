#include "students.hpp"
#include "functions.hpp"

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

int numberInput(bool enterToEnd){
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
        grade = numberInput(false);
    }
}

//new ones

void examResult(Students &student){
    cout << "Iveskite egzamino rezultata: ";
    student.examGrade = numberInput(false);
    isGrade(student.examGrade);
}

bool fillWithRandomNumbers(Students &student, int gradeQuant){
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
        student.homeworkQuant = numberInput(false);


        bool filledRandom = fillWithRandomNumbers(student, student.homeworkQuant);
        
        if(!filledRandom){
            cout << "Iveskite namu darbu pazymius: " << endl;
            for(int i=0; i<student.homeworkQuant; i++){
                student.grades.push_back(numberInput(false));
                isGrade(student.grades[i]);
            }
            examResult(student);
        }
    }
    else{
        bool filledRandom = fillWithRandomNumbers(student, 10);

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

double calculateFinalGrade(vector<int> grades, int homeworkCount, int exam, bool printMedian){
    if(printMedian){
        int median = 0;
        int midIndex = (homeworkCount/2)-1;
        //sort(students[i].grades, students[i].grades + students[i].homeworkQuant);
        sort(grades.begin(), grades.end());

        if(homeworkCount % 2 == 0){
        
            median = 1.00 * (grades[midIndex] + grades[midIndex+1]) / 2;
        }
        else{
            median = grades[midIndex];
        }
        return median*0.4 + exam*0.6;
    }
    else{
        double avg = 0;
        for(int gradeIndx=0; gradeIndx < homeworkCount; gradeIndx++){
            avg += grades[gradeIndx];
        }
        avg = avg/homeworkCount;
        return avg*0.4 + exam*0.6;
    }
}

void printResult(vector<StudentsFromFile> students, int studentQuantity, bool printMedian, bool offstream, string outDir){

    string finalType = "";
    finalType = printMedian ? "(Med.)" : "(Vid.)";

    ofstream out(outDir);

    if(offstream){
        out << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw(0) << "Galutinis " << finalType << endl << "----------------------------------------------" << endl;
    } 
    else cout << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw(0) << "Galutinis " << finalType << endl << "----------------------------------------------" << endl;
    
    for(int i=0; i<studentQuantity; i++){
        if(offstream){
            out << left << setw(15) << students[i].name << left << setw(15) << students[i].surname << left << setw(15) << setprecision(2) << fixed << students[i].finalGrade << endl;
        }
        else cout << left << setw(15) << students[i].name << left << setw(15) << students[i].surname << left << setw(15) << setprecision(2) << fixed << students[i].finalGrade << endl;

    }
}

int wordCount(string str){
    int wc = 1;

    for(int i=0; i<str.length(); i++){
        if(i >= 1 && !isspace(str[i]) && isspace(str[i-1])) wc++;
    }

    return wc;
}

bool comepareTwoStudents(StudentsFromFile a, StudentsFromFile b){
    if(a.name<b.name) return true;
    else return false;
}

void generateFiles(){
    int homeworkQuant = 6;
    int size[5] = {1000, 10000, 100000, 1000000, 10000000};
    //int size[5] = {1000, 10000, 100000, 1000000, 10000000};

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for(int i=0; i<5; i++){
        string outDirectory = "duomenys\\duomenys" + to_string(size[i]) + ".txt";
        ofstream out(outDirectory);

        out << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";
        for(int hw = 0; hw<homeworkQuant; hw++){
            string mark = "ND" + to_string(hw);
            out << left << setw(15) << mark;
        }
        out << left << setw(15) << "Egz." << endl;

        using hrClock = chrono::high_resolution_clock;
        std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
        uniform_int_distribution<int> dist(1, 10);

        for(int j=0; j<size[i]; j++){
            string name = "Vardas" + to_string(j+1);
            string surname = "Pavarde" + to_string(j+1);
            out << left << setw(20) << name << left << setw(20) << surname;

            for(int hw = 0; hw<homeworkQuant+1; hw++){
                out << left << setw(15) << dist(mt);
            }
            out << endl;
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Irasu sugeneravimo laikas: " << time << endl;
}

void splitStudents(vector<StudentsFromFile> &students, int studentQuantity, bool printMedian){
    
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    vector<StudentsFromFile> badStudents;
    vector<StudentsFromFile> goodStudents;
    int goodStudentsQuant = 0, badStudentsQuant = 0;
    for(int i=studentQuantity-1; i >= 0; i--){
        if(students[i].finalGrade<5){
            badStudents.push_back(students[i]);
            badStudentsQuant++;
        }
        else{
            goodStudents.push_back(students[i]);
            goodStudentsQuant++;
        }
        students.pop_back();
    }
    //students.erase(students.begin(), students.end());
    //students.clear();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Irasu padalinimo laikas: " << time << endl;


    begin = std::chrono::steady_clock::now();
    printResult(badStudents, badStudentsQuant, printMedian, true, "rezultatai/blogi_studentai.txt");
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Blogu studentu isvedimo laikas: " << time << endl;

    begin = std::chrono::steady_clock::now();
    printResult(goodStudents, goodStudentsQuant, printMedian, true, "rezultatai/geri_studentai.txt");
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Geru studentu isvedimo laikas: " << time << endl;
}

void readFromFile(vector<StudentsFromFile>& studentsFF, bool printMedian, string fileName){
    
    string firstLine;
    ifstream in;

    try{
        in.open(fileName);
        if(in.fail()) throw 1;
        
        getline(in, firstLine);

        //int homeworkCount = wordCount(firstLine) - 3;

        // bool printMedian = confirm();

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        string line;

        while(getline(in, line)){
            StudentsFromFile student;
            vector<int> grades;
            double examGrade;

            istringstream ss(line);

            ss >> student.name >> student.surname;

            int grade;

            while(ss >> grade){
                grades.push_back(grade);
            }

            grades.pop_back();
            examGrade = grade;
            //students[studentQuantity] = student;
            student.finalGrade = calculateFinalGrade(grades, grades.size(), examGrade, printMedian);

            studentsFF.push_back(student);
            
            if(in.eof()) break;
        }
        in.close();
        
        studentsFF.pop_back();

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
        cout << "Irasu nuskaitymo laikas: " << time << endl;

    }
    catch(int e){
        if(e==1) std::cout << "Error: failas pavadinimu 'duomenys.txt' nerastas" << endl;
        exit(1);
    }
}

void runProgramTest(){
    int size[5] = {1000, 10000, 100000, 1000000, 10000000};
    string fileName[5];
    for(int i=0; i<5; i++){
        fileName[i] = "duomenys/duomenys" + to_string(size[i]) + ".txt";
    }

    for(int i=0; i<5; i++){
        cout << "Pradedamas testavimas su " << size[i] << " duomenu" << endl;
        vector<StudentsFromFile> studentsFF;
        readFromFile(studentsFF, false, fileName[i]);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        sort(studentsFF.begin(), studentsFF.end(), comepareTwoStudents);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
        cout << "Irasu surusiavimo laikas: " << time << endl;
        
        //printResult(studentsFF, studentsFF.size(), false, true, "rezultatai/rezultatai.txt");
        
        splitStudents(studentsFF, studentsFF.size(), false);

        cout << endl;
    }
}

// void splitStudents(vector<StudentsFromFile> &students, int studentQuantity, bool printMedian){
    
//     std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
//     vector<StudentsFromFile> badStudents;
//     vector<StudentsFromFile> goodStudents;
//     int goodStudentsQuant = 0, badStudentsQuant = 0;
//     for(int i=studentQuantity-1; i >= 0; i--){
//         if(students[i].finalGrade<5){
//             badStudents.push_back(students[i]);
//             badStudentsQuant++;
//         }
//         else{
//             goodStudents.push_back(students[i]);
//             goodStudentsQuant++;
//         }
//         students.pop_back();
//         if(i%10000==0) cout << i << " " << students.size() << endl;
//     }
//     //students.erase(students.begin(), students.end());
//     //students.clear();

//     std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//     double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
//     cout << "Irasu padalinimo laikas: " << time << endl;


//     begin = std::chrono::steady_clock::now();
//     printResult(badStudents, badStudentsQuant, printMedian, true, "rezultatai/blogi_studentai.txt");
//     end = std::chrono::steady_clock::now();
//     time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
//     cout << "Blogu studentu isvedimo laikas: " << time << endl;

//     begin = std::chrono::steady_clock::now();
//     printResult(goodStudents, goodStudentsQuant, printMedian, true, "rezultatai/geri_studentai.txt");
//     end = std::chrono::steady_clock::now();
//     time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
//     cout << "Geru studentu isvedimo laikas: " << time << endl;
// }
