#include <stdio.h>
#include <iostream>
#include "libs/read_csv.h"
#include "libs/template.h"

using namespace std;

struct Student {
    string id;
    string name;
    string faculty;
    string school_year;
    string birthday;
    string avatar;
    string info;
    string *hobbies;
};

void importStudents(Student *&students, int total_students, string *string_lines) {
    students = new Student[total_students];
    for (int i = 0; i < total_students; i++) {
        int index_read = 0;
        string line = string_lines[i];
        readCSV_Variable(line, index_read, students[i].id);
        readCSV_Variable(line, index_read, students[i].name);
        readCSV_Variable(line, index_read, students[i].faculty);
        readCSV_Variable(line, index_read, students[i].school_year);
        readCSV_Variable(line, index_read, students[i].birthday);
        readCSV_Variable(line, index_read, students[i].avatar);
        readCSV_Variable(line, index_read, students[i].info);
    }
}

void showStudents(Student *students, int total_students) {
    for (int i = 0; i < total_students; i++) {
        cout << "MMSV: " << students[i].id << endl;
        cout << "Name: " << students[i].name << endl;
        cout << "Faculty: " << students[i].faculty << endl;
        cout << "School year: " << students[i].school_year << endl;
        cout << "Avatar: " << students[i].avatar << endl;
        cout << "Biography: " << students[i].info << endl;
        cout << "------------------" << endl;
    }
}

void exportStudentToHtml(Student student) {
    string *lines_template;
    int total_lines = Template_Read(lines_template);
    const int total_variables = 7;
    string variables[total_variables] = {"$id", "$name", "$birthday", "$faculty", "$school_year", "$avatar", "$info"};
    string values[total_variables] = {student.id, student.name, student.birthday, student.faculty, student.school_year,
                                      student.avatar,
                                      student.info};
    Template_PutVariable(lines_template, total_lines, variables, values, total_variables);
    Template_WriteFile(lines_template, total_lines, student.id);
    delete[] lines_template;
}

void exportStudents(Student *students, int total_students) {
    for (int i = 0; i < total_students; i++) {
        exportStudentToHtml(students[i]);
    }
}


int main() {
    bool read_error = false;
    string *string_lines;
    int total_students = 0;
    Student *students;

    total_students = readCSV_ToLines(string_lines, read_error);

    if (read_error) {
        cout << "File students not exists, please create file: " << file_src;
    }
    else if (total_students == 0) {
        cout << file_src << " empty";
    } else {
        importStudents(students, total_students, string_lines);
        delete[] string_lines;
        showStudents(students, total_students);
        exportStudents(students, total_students);
        delete[] students;
    }

    return 1;
}