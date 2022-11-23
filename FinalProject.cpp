
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

int main() {
    // make a map of course codes to names
    fstream nameFile("NameFile.txt", ios::in);
    std::map<std::string, std::string> m;
    if (nameFile.is_open()) {
        string name, studentID;
        while (getline(nameFile, studentID, ',')) {
            getline(nameFile, name);
            m[studentID] = name;
        }
    } else {
        cout << "Error 'NameFile.txt' is not open" << endl;
        return 0;
    }
    // run through CourseFile.txt and output to FormatStudents.txt
    fstream courseFile("CourseFile.txt", ios::in);
    std::ofstream output("FormatStudents.txt");
    if (courseFile.is_open()) {
        // initialize headers for FormatStudents.txt
        string studentID, courseCode, test1, test2, test3, finalExam;
        output << "Student ID" << setw(20) << "Student Name" << setw(20) << "Course Code" << setw(20) << "Final Grade" << std::endl;
        output << "-------------------------------------------------------------------------" << std::endl;
        while (getline(courseFile, studentID, ',')) {
            getline(courseFile, courseCode, ',');
            getline(courseFile, test1, ',');
            getline(courseFile, test2, ',');
            getline(courseFile, test3, ',');
            getline(courseFile, finalExam);
            //convert inputs from in files to floats
            float finalGrade = ((stof(test1) + stof(test2) + stof(test3)) / 3 * 0.6) + (stof(finalExam) * 0.4);
            //output to final grade
            output << studentID << setw(20)<< m[studentID] << setw(20) << courseCode << setw(20) << finalGrade << std::endl;
        }
        nameFile.close();
        courseFile.close();
        output.close();
    } else {
        cout << "Error 'CourseFile.txt' is not open" << endl;
    }
    return 0;
}

