#include <stdio.h>
#include <iostream>
#include "libs/read_csv.h"
#include "libs/template.h"

using namespace std;

struct Student {
    string id, name, faculty, school_year, birthday;
    string email, avatar, info;
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
        readCSV_Variable(line, index_read, students[i].email);
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
        cout << "Email: " << students[i].email << endl;
        cout << "Avatar: " << students[i].avatar << endl;
        cout << "Biography: " << students[i].info << endl;
        cout << "------------------" << endl;
    }
}

/**
 * Check column export
 * Example: ("id","id, name, game") => return true
 */
bool checkColumnExport(string column, string choose_columns) {
    int index_read = 0;
    string tmp;
    while (1) {
        readCSV_Variable(choose_columns, index_read, tmp);
        if (tmp == column) {
            return true;
        }
        if (tmp == "") break;
    }
    return false;
}

/**
 * Export student to HTML
 */
void exportStudentToHtml(Student student, string choose_export) {
    string *lines_template;
    int total_lines = Template_Read(lines_template);
    const int total_variables = 9;
    string variables[total_variables] = {
            "$id", "$name", "$birthday", "$faculty", "$email",
            "$school_year", "$avatar", "$info", "$hobbies"
    };
    string values[total_variables] = {
            checkColumnExport("id", choose_export) ? student.id : "hide",
            checkColumnExport("name", choose_export) ? student.name : "hide",
            checkColumnExport("birthday", choose_export) ? student.birthday : "hide",
            checkColumnExport("faculty", choose_export) ? student.faculty : "hide",
            checkColumnExport("email", choose_export) ? student.email : "hide",
            checkColumnExport("school_year", choose_export) ? student.school_year : "hide",
            checkColumnExport("avatar", choose_export) ? student.avatar : "hide",
            checkColumnExport("info", choose_export) ? student.info : "hide",
            checkColumnExport("hobbies", choose_export) ? getHobbyString(student.hobbies, student.total_hobbies)
                                                        : "hide"
    };
    Template_PutVariable(lines_template, total_lines, variables, values, total_variables);
    Template_WriteFile(lines_template, total_lines, student.id);
    delete[] lines_template;
}

/**
 * Export all students
 */
void exportStudents(Student *students, int total_students, string choose_export) {
    for (int i = 0; i < total_students; i++) {
        exportStudentToHtml(students[i], choose_export);
    }
}

void selectChooseExport(string &choose_export, int total_students) {
    string tmp;
    cout << "<< Welcome to Student Export" << endl;
    cout << "<< Have :" << total_students << " students" << endl;
    cout << "<< Please select column export to HTML" << endl;
    cout << "<< Lists columns: " << choose_export << endl;
    cout << "- Type: name, email, id" << endl;
    cout << ">>>>> Here, it will only show name, email, id in profile.html" << endl;
    cout << "- Type: *" << endl;
    cout << ">>>>> Here, show all column: " << choose_export << endl;
    cout << "Please choose columns: ";
    getline(cin, tmp);
    if (!checkColumnExport("*", tmp)) {
        choose_export = tmp;
    }
}

int main() {
    bool read_error = false;
    string *string_lines;
    int total_students = 0;
    Student *students;
    string choose_export = "id, name, birthday, faculty, email, school_year, avatar, info, hobbies";


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
        selectChooseExport(choose_export, total_students);
        exportStudents(students, total_students, choose_export);
        cout << "\nBuild file successed. Please view files in folder /public" << endl;
        delete[] students;
    }

    return 1;
}