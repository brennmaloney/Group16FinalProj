
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <map>
#include <iomanip>

int main() {
    // make a map of course codes to names
    std::fstream nameFile("NameFile.txt", std::ios::in);
    std::map<std::string, std::string> m;
    if (nameFile.is_open()) {
        std::string name, studentID;
        // map student IDs to the names of students
        while (std::getline(nameFile, studentID, ',')) {
            std::getline(nameFile, name);
            m[studentID] = name;
        }
    } else {
        std::cout << "Error 'NameFile.txt' is not open" << std::endl;
        return 0;
    }
    // run through CourseFile.txt and output to FormatStudents.txt
    std::fstream courseFile("CourseFile.txt", std::ios::in);
    std::ofstream output("FormatStudents.txt");
    if (courseFile.is_open()) {
        // initialize headers for FormatStudents.txt
        std::string studentID, courseCode, test1, test2, test3, finalExam;
        output << "Student ID" << std::setw(20) << "Student Name" << std::setw(20) <<
        "Course Code" << std::setw(20) << "Final Grade" << std::endl;
        output << "-------------------------------------------------------------------------" << std::endl;
        while (std::getline(courseFile, studentID, ',')) {
            std::getline(courseFile, courseCode, ',');
            std::getline(courseFile, test1, ',');
            std::getline(courseFile, test2, ',');
            std::getline(courseFile, test3, ',');
            std::getline(courseFile, finalExam);
            // convert inputs from in files to floats
            float finalGrade = ((stof(test1) + stof(test2) + stof(test3)) / 3 * 0.6) + (stof(finalExam) * 0.4);
            // output to final grade
            output << studentID << std::setw(20)<< m[studentID] << std::setw(20) <<
            courseCode << std::setw(20) << finalGrade << std::endl;
        }
        nameFile.close();
        courseFile.close();
        output.close();
    } else {
        std::cout << "Error 'CourseFile.txt' is not open" << std::endl;
    }
    return 0;
}

