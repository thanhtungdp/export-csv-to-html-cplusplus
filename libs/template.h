//
// Created by Phan Tùng on 4/1/16.
//

#ifndef DO_AN_CUOI_KY_TEMPLATE_H
#define DO_AN_CUOI_KY_TEMPLATE_H

#include <iostream>
#include <fstream>
#include "memory.h"

using namespace std;
const string profile_template = "data/templates/profile.html";
const string profile_public_folder = "public";

/**
 * Read file template: (profile_template | profile.html)
 * And push to *lines_templates[]
 * return @total_lines in template
 */
int Template_Read(string *&lines_template) {
    ifstream file(profile_template);
    int line = 0;
    if (file.is_open()) {
        lines_template = new string[1];
        while (!file.eof()) {
            getline(file, lines_template[line]);
            line++;
            allocate_memory_string(lines_template, line);
        }
    }
    return line;
}

/**
 * Change variable in template
 * Example: "xin chao $name"
 * Change to: "xin chao thanh tung"
 */
void Template_ReplaceVariable(string &str, const string &from, const string &to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

/**
 * Change variable in line;
 */
void Template_PutVariableToLine(string &line, string variables[], string values[], int total_variables) {
    for (int i = 0; i < total_variables; ++i) {
        Template_ReplaceVariable(line, variables[i], values[i]);
    }
}

/**
 * Put variables
 * Example: [$name,$age] ["thanh tung","18"]
 */
void Template_PutVariable(string *&lines_template, int lines, string variables[], string values[],
                          int total_variables) {
    for (int i = 0; i < lines; ++i) {
        Template_PutVariableToLine(lines_template[i], variables, values, total_variables);
    }
}

/**
 * Write out file from lines_template
 */
void Template_WriteFile(string *lines_template, int lines, string file_name) {
    file_name = profile_public_folder + "/" + file_name + ".html";
    ofstream file_template;
    file_template.open(file_name, ios::out);
    for (int i = 0; i < lines; ++i) {
        file_template << lines_template[i];
        file_template << "\n";
    }
    file_template.close();
}


#endif //DO_AN_CUOI_KY_TEMPLATE_H
