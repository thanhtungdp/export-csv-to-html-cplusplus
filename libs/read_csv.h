//
// Created by Phan Tùng on 4/1/16.
//

#ifndef DO_AN_CUOI_KY_READ_CSV_H
#define DO_AN_CUOI_KY_READ_CSV_H

#include <iostream>
#include <fstream>
#include "memory.h"

using namespace std;
const string file_src = "data/students.csv";
const char file_string_delimiter = ',';
const char file_string_quote = '\"';

/**
 * Next read index read delimiter
 * Example: string, test
 *                ^
 * Move ^ to next index
 * To: string, test
 *            ^
 */
void readCSV_NextIndexReadDelimiter(string line, int &index_read) {
    while (line[index_read] != file_string_delimiter && index_read < line.length()) {
        index_read++;
    }
    index_read++;
}

/**
 * Next read index over space to character
 * Example:"   a "
 *          ^
 * Move ^ to a
 * After: "   a "
 *            ^
 */
void readCSV_NextIndexReadSpace(string line, int &index_read) {
    while (line[index_read] == ' ' && index_read < line.length()) {
        index_read++;
    }
}

/**
 * Read variable have quote from string, and move index_read to new
 * Example: "test 1, tung thanh", "ok baby"
 * Ouput: (test 1, tung thanh) ; (ok baby)
 */
void readCSV_VariableQuote(const string line, int &index_read, string &string_read) {
    string_read = "";
    index_read++;
    while (line[index_read] != file_string_quote && index_read < line.length()) {
        string_read += line[index_read];
        index_read++;
    }
    readCSV_NextIndexReadDelimiter(line, index_read);
    readCSV_NextIndexReadSpace(line, index_read);
}

/**
 * Read variable normal from string, and move index_read to new
 * Example: hello world, hello one
 * Ouput: hello world ; hello one
 */
void readCSV_VariableNormal(const string line, int &index_read, string &string_read) {
    string_read = "";
    while (line[index_read] != file_string_delimiter && index_read < line.length()) {
        string_read += line[index_read];
        index_read++;
    }
    readCSV_NextIndexReadDelimiter(line, index_read);
    readCSV_NextIndexReadSpace(line, index_read);
}

/**
 * Read variable from line
 * Sub:
 *      - Quote ("test")
 *      - Normal (test)
 */
void readCSV_Variable(string line, int &index_read, string &string_read) {
    if (line[index_read] == file_string_quote) {
        readCSV_VariableQuote(line, index_read, string_read);
    }
    else readCSV_VariableNormal(line, index_read, string_read);
}

/**
 * Read line by line
 * Ex: string *lines
 * lines[1] = 
 */
int readCSV_ToLines(string *&string_lines, bool &read_error) {
    ifstream file(file_src);
    int lines_count = 0;
    if (file.is_open()) {
        /* End get lines count */
        string_lines = new string[1];
        while (!file.eof()) {
            getline(file, string_lines[lines_count]);
            lines_count++;
            allocate_memory_string(string_lines, lines_count);
            // allocate new memory (+1 type)
        }
        file.close();
    }
    else {
        read_error = true;
    }
    return lines_count;
}

#endif //DO_AN_CUOI_KY_READ_CSV_H
