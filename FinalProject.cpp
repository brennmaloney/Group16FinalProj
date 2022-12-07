#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <map>
#include <iomanip>
#include <algorithm>

//--------------- Student Structure Functions ---------------
struct Student {
    private:
        std::string studentID;
        std::string name;
        std::string courseCode;
        float finalGrade;
    public:
        // setters for Student Class
        void setStudentID(std::string id) {
            studentID = id;
        }
        void setStudentName(std::string n) {
            name = n;
        }
        void setStudentCourseCode(std::string code) {
            courseCode = code;
        }
        void setStudentGrade(float grade) {
            finalGrade = grade;
        }
        // getters for Student Class
        std::string getStudentID() {
            return studentID;
        }
        std::string getStudentName() {
            return name;
        }
        std::string getStudentCourseCode() {
            return courseCode;
        }
        float getStudentGrade() {
            return finalGrade;
        }
};

// creates a Student to be added to a arrayy of students
Student createStudent(std::string name, std::string studentID, 
                        std::string courseCode, float finalGrade) {
    Student st;
    st.setStudentCourseCode(courseCode);
    st.setStudentName(name);
    st.setStudentID(studentID);
    st.setStudentGrade(finalGrade);
    return st;
}

//----------------------------------------------------------------------------
// check for valid numbers given std::string
int valid(std::string test1, std::string test2, std::string test3,
                    std::string finalExam, std::string id) {
    try {
        stof(test1);
        stof(test2);
        stof(test3);
        stof(finalExam);
        stof(id);
    } catch(...) {
        return 0;
    }
    return 1;
}

// check for valid numbers given std::string
int valid(std::string id, std::string name) {
    if(id.length() == 9) {
        try {
            stoi(id);
        } catch(...) {
            return 0;
        }
    } else {
        std::cout <<"Invalid Student ID length, ";
        return 0;
    }
    if(name.length() > 20 || name.length() <= 0) {
        std::cout <<"Invalid name length, ";
        return 0;
    }
    return 1;
}

// gets all of the valid student data and creates an array of Students
int getStudentsData(Student *st[], int numStudents) {
    *st = new Student[numStudents];
    int lineCount = 1;
    // make a map of course codes to names
    std::fstream nameFile("NameFile.txt", std::ios::in);
    std::map<std::string, std::string> m;
    if (nameFile.is_open()) {
        std::string name, studentID, line;
        // map student IDs to the names of students
        while (std::getline(nameFile, line)) {
            std::istringstream ss(line);
            std::string token;
            int tokenCount = 0;
            while (std::getline(ss, token, ',') && tokenCount < 2) {
                token.erase(token.begin(), std::find_if(token.begin(), token.end(), std::bind1st(std::not_equal_to<char>(), ' ')));
                if (tokenCount) name = token;
                else studentID = token;
                tokenCount++;
            }
            if(tokenCount == 2 && valid(studentID, name)) {
                m[studentID] = name;
            // Only print error message if the line isn't blank
            } else if (tokenCount > 0) {
                if (tokenCount == 1) std::cout <<"Missing comma, ";
                std::cout << "Error on line: " <<lineCount<<" of 'NameFile.txt'\n";
            }
            lineCount++;
        }
    } else {
        std::cout << "Error 'NameFile.txt' is not open" << std::endl;
        return 0;
    }
    // run through CourseFile.txt and output to FormatStudents.txt
    std::fstream courseFile("CourseFile.txt", std::ios::in);
    if (courseFile.is_open()) {
        // initialize headers for FormatStudents.txt
        std::string studentID, courseCode, test1, test2, test3, finalExam;
        int index = 0;
        while (std::getline(courseFile, studentID, ',')) {
            std::getline(courseFile, courseCode, ',');
            std::getline(courseFile, test1, ',');
            std::getline(courseFile, test2, ',');
            std::getline(courseFile, test3, ',');
            std::getline(courseFile, finalExam);
            // test inputs from CourseFile.txt
            if(valid(test1, test2, test3, finalExam, studentID) && courseCode.length() <= 6) {
                if(m.count(studentID)) {
                    // convert inputs from in files to floats
                    float finalGrade = ((stof(test1) + stof(test2) + stof(test3)) / 3 * 0.6)
                                         + (stof(finalExam) * 0.4);
                    (*st)[index] = createStudent(m[studentID], studentID, courseCode, finalGrade);
                    // output to final grade
                    index++;
                }
            }
        }
    } else {
        std::cout << "Error 'CourseFile.txt' is not open" << std::endl;
    }
    nameFile.close();
    courseFile.close();
    return 0;
}

// prints array of students to the output file 'FormatStudents.txt'
void outputStudents(Student st[], int numStudents) {
    std::ofstream output("FormatStudents.txt");
    output << "Student ID" << std::setw(20) << "Student Name" << std::setw(20) <<
            "Course Code" << std::setw(20) << "Final Grade" << std::endl;
    output << "-------------------------------------------------------------------------" << std::endl;
    for(int i = 0; i < numStudents; i++) {
        output << st[i].getStudentID() << std::setw(20)<< st[i].getStudentName() << std::setw(20) <<
                st[i].getStudentCourseCode() << std::setw(20) << st[i].getStudentGrade() << std::endl;
    }
    return;
}

// helper sorting function to sort array of students by their ID
bool sortStudentId(Student &x, Student &y) {
    return x.getStudentID() > y.getStudentID();
}

// gets the maximum number of students from 'CourseFile.txt'
int numStudents() {
    int count = 0;
    std::string s;
    std::fstream courseFile("CourseFile.txt", std::ios::in);
    if (courseFile.is_open()) {
        while(std::getline(courseFile, s)) {
            count++;
        }
    } else {
        return 0;
    }
    courseFile.close();
    return count;
}

int numValidStudents(Student *st, int numStudents) {
    int count = 0;
    for(int i = 0; i < numStudents; i++) {
        if(st[i].getStudentGrade() != 0) {
            count++;
        }
    }
    return count;
}
//----------------------------------------------------------------------------

int main() {    
    Student *st;
    int count = numStudents();
    getStudentsData(&st, count);
    std::sort(&st[0], &st[count], sortStudentId);
    count = numValidStudents(st, count);
    outputStudents(st, count);
    return 1;
}
