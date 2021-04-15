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

int chooseStrategy(){
    cout << "Pasirinkite testavimo strategija (1-3): ";
    int strat;
    while(true){
        cin >> strat;
        if(strat >= 1 && strat <= 3) return strat;
        else cout << "Ivesti duomenys yra neteisingo formato, pasirinkite strategija tarp 1, 2, 3: ";
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
        student.examGrade = dist(mt);
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

template <class T>
void printResult(T students, bool printMedian, string outDir){

    string finalType = "";
    finalType = printMedian ? "(Med.)" : "(Vid.)";

    ofstream out(outDir);

    out << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw(0) << "Galutinis " << finalType << endl << "----------------------------------------------" << endl;

    for(auto student : students){
        out << left << setw(15) << student.name << left << setw(15) << student.surname << left << setw(15) << setprecision(2) << fixed << student.finalGrade << endl;
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

bool comepareTwoStudents2(StudentsFromFile a, StudentsFromFile b){
    if(a.finalGrade>b.finalGrade) return true;
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

template <class T>
void readFromFile(T &studentsFF, bool printMedian, string fileName){

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

template <class T>
void splitStudents(T &students, int studentQuantity, bool printMedian){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    T badStudents;
    T goodStudents;
    int goodStudentsQuant = 0, badStudentsQuant = 0;
    for(auto student : students){
        if(student.finalGrade<5){
            badStudents.push_back(student);
            badStudentsQuant++;
        }
        else{
            goodStudents.push_back(student);
            goodStudentsQuant++;
        }
    }
    students.clear();


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Irasu surusiavimo laikas: " << time << endl;

    printResult(badStudents, printMedian, "rezultatai/blogi_studentai.txt");

    printResult(goodStudents, printMedian, "rezultatai/geri_studentai.txt");

    badStudents.clear();
    goodStudents.clear();
}

void splitStudentsOptimisedVector(vector<StudentsFromFile> &students, int studentQuantity, bool printMedian){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    vector<StudentsFromFile> badStudents;
    int goodStudentsQuant = 0, badStudentsQuant = 0, index = 0;
    for(auto student : students){
        if(student.finalGrade<5){
            badStudents.push_back(student);
            badStudentsQuant++;
            students.erase(students.begin() + index);
        }
        index++;
    }


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Irasu surusiavimo laikas: " << time << endl;

    printResult(badStudents, printMedian, "rezultatai/blogi_studentai.txt");

    printResult(students, printMedian, "rezultatai/geri_studentai.txt");

    badStudents.clear();
    students.clear();
}

void splitStudentsOptimisedList(list<StudentsFromFile> &students, int studentQuantity, bool printMedian){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    list<StudentsFromFile> badStudents;
    int goodStudentsQuant = 0, badStudentsQuant = 0;
    for(auto it = students.begin(); it != students.end(); it++){
        if(it->finalGrade < 5){
            badStudents.push_back(*it);
            badStudentsQuant++;
            it = students.erase(it);
        }
    }


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Irasu surusiavimo laikas: " << time << endl;

    printResult(badStudents, printMedian, "rezultatai/blogi_studentai.txt");

    printResult(students, printMedian, "rezultatai/geri_studentai.txt");

    badStudents.clear();
    students.clear();
}

void splitStudentsOptimisedDeque(deque<StudentsFromFile> &students, int studentQuantity, bool printMedian){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    deque<StudentsFromFile> badStudents;
    int goodStudentsQuant = 0, badStudentsQuant = 0, index = 0;
    for(auto student : students){
        if(student.finalGrade<5){
            badStudents.push_back(student);
            badStudentsQuant++;
            students.erase(students.begin() + index);
        }
        index++;
    }


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Irasu surusiavimo laikas: " << time << endl;

    printResult(badStudents, printMedian, "rezultatai/blogi_studentai.txt");

    printResult(students, printMedian, "rezultatai/geri_studentai.txt");

    badStudents.clear();
    students.clear();
}

bool lessThanFive(StudentsFromFile student){
    if(student.finalGrade < 5) return true;
    else return false;
}

template <class T>
void splitStudents3(T &students, int studentQuantity, bool printMedian){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    T badStudents;
    int badStudentsQuant = 0, index = 0;

    sort(students.begin(), students.end(), comepareTwoStudents2);

    
    auto it = find_if(students.begin(), students.end(), lessThanFive);
    copy(it, students.end(), back_inserter(badStudents));
    students.resize(students.size() - badStudents.size());


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Irasu surusiavimo laikas: " << time << endl;

    printResult(badStudents, printMedian, "rezultatai/blogi_studentai.txt");

    printResult(students, printMedian, "rezultatai/geri_studentai.txt");

    badStudents.clear();
    students.clear();
}

void splitStudents3(list<StudentsFromFile> &students, int studentQuantity, bool printMedian){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    list<StudentsFromFile> badStudents;
    int badStudentsQuant = 0, index = 0;

    students.sort(comepareTwoStudents2);
    
    auto it = find_if(students.begin(), students.end(), lessThanFive);
    copy(it, students.end(), back_inserter(badStudents));
    students.resize(students.size() - badStudents.size());


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Irasu surusiavimo laikas: " << time << endl;

    printResult(badStudents, printMedian, "rezultatai/blogi_studentai.txt");

    printResult(students, printMedian, "rezultatai/geri_studentai.txt");

    badStudents.clear();
    students.clear();
}

//Program tests --------------------------------------------- begin

void programTestVector(int size, string fileName, int strategy){
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    double time;

    cout << "--------------------------------------------------" << endl;
    cout << "Pradedamas testavimas su " << size << " duomenu:" << endl;
    cout << "- Naudojant vector: " << endl;
    begin = std::chrono::steady_clock::now();
    vector<StudentsFromFile> studentsVector;
    readFromFile(studentsVector, false, fileName);
    sort(studentsVector.begin(), studentsVector.end(), comepareTwoStudents);

    if(strategy == 1) splitStudents(studentsVector, studentsVector.size(), false);
    else if(strategy == 2) splitStudentsOptimisedVector(studentsVector, studentsVector.size(), false);
    else splitStudents3(studentsVector, studentsVector.size(), false);

    studentsVector.clear();
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Bendras laikas: " << time << endl;
}

void programTestList(int size, string fileName, int strategy){
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    double time;

    begin = std::chrono::steady_clock::now();
    cout << "- Naudojant list: " << endl;
    list<StudentsFromFile> studentsList;
    readFromFile(studentsList, false, fileName);
    studentsList.sort(comepareTwoStudents);

    if(strategy == 1) splitStudents(studentsList, studentsList.size(), false);
    else if(strategy == 2) splitStudentsOptimisedList(studentsList, studentsList.size(), false);
    else splitStudents3(studentsList, studentsList.size(), false);

    studentsList.clear();
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Bendras laikas: " << time << endl;
}



void programTestDeque(int size, string fileName, int strategy){
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    double time;

    begin = std::chrono::steady_clock::now();
    cout << "- Naudojant deque: " << endl;
    deque<StudentsFromFile> studentsDeque;
    readFromFile(studentsDeque, false, fileName);
    sort(studentsDeque.begin(), studentsDeque.end(), comepareTwoStudents);

    if(strategy == 1) splitStudents(studentsDeque, studentsDeque.size(), false);
    else if(strategy == 2) splitStudentsOptimisedDeque(studentsDeque, studentsDeque.size(), false);
    else splitStudents3(studentsDeque, studentsDeque.size(), false);

    studentsDeque.clear();
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /1000000.0;
    cout << "Bendras laikas: " << time << endl;
}

//Program tests --------------------------------------------- end

void runProgramTest(int strategy){
    int size[5] = {1000, 10000, 100000, 1000000, 10000000};

    for(int i=0; i<5; i++){
        string fileName = "duomenys/duomenys" + to_string(size[i]) + ".txt";

        programTestVector(size[i], fileName, strategy);

        programTestList(size[i], fileName, strategy);

        programTestDeque(size[i], fileName, strategy);
    }
}
