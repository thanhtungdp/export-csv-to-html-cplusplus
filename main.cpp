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
    int total_hobbies;
};

/**
 * Convert hobbies[] to string lists
 * Ex:  <li>1</li>
 *      <li>2</li>
 */
string getHobbyString(string *hobbies, int total_hobbies) {
    string hobby_string = "";
    for (int i = 0; i < total_hobbies; ++i) {
        hobby_string += "<li>" + hobbies[i] + "</li>";
    }
    return hobby_string;
}

/**
 * Import students to Students from string_lines
 * string_lines have read from CSV
 */
void importStudents(Student *&students, int total_students, string *string_lines) {
    students = new Student[total_students];
    for (int i = 0; i < total_students; i++) {
        int index_read = 0;
        string line = string_lines[i];
        /* Read information basic */
        readCSV_Variable(line, index_read, students[i].id);
        readCSV_Variable(line, index_read, students[i].name);
        readCSV_Variable(line, index_read, students[i].faculty);
        readCSV_Variable(line, index_read, students[i].school_year);
        readCSV_Variable(line, index_read, students[i].birthday);
        readCSV_Variable(line, index_read, students[i].avatar);
        readCSV_Variable(line, index_read, students[i].info);

        /* Read hobbies */
        string tmp = "tmp";
        int hobbies = 0;
        students[i].total_hobbies = 0;
        while (tmp != "") {
            tmp = "";
            readCSV_Variable(line, index_read, tmp);
            if (tmp != "") {
                allocate_memory_string(students[i].hobbies, hobbies);
                students[i].hobbies[hobbies] = tmp;
                hobbies++;
            }
        }
        students[i].total_hobbies = hobbies;
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

/**
 * Export student to HTML
 */
void exportStudentToHtml(Student student) {
    string *lines_template;
    int total_lines = Template_Read(lines_template);
    const int total_variables = 8;
    string variables[total_variables] = {
            "$id", "$name", "$birthday", "$faculty",
            "$school_year", "$avatar", "$info", "$hobbies"
    };
    string values[total_variables] = {
            student.id, student.name, student.birthday, student.faculty,
            student.school_year, student.avatar, student.info, getHobbyString(student.hobbies, student.total_hobbies)
    };
    Template_PutVariable(lines_template, total_lines, variables, values, total_variables);
    Template_WriteFile(lines_template, total_lines, student.id);
    delete[] lines_template;
}

/**
 * Export all students
 */
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
        cout <<"\nBuild file successed. Please view files in folder /public"<<endl;
        delete[] students;
    }

    return 1;
}