//
// Created by Phan Tùng on 4/1/16.
//

#ifndef DO_AN_CUOI_KY_MEMORY_H
#define DO_AN_CUOI_KY_MEMORY_H

#include <iostream>
using namespace std;
void allocate_memory_string(string *&a, int n) {
    string *Temp = new string[n]; // Khởi tạo và cấp phát 1 mảng phụ Temp chứa các phần tử mảng a
    for (int i = 0; i < n; i++) {
        Temp[i] = a[i];
    }
    a = new string[n + 1]; // Cấp phát lại vùng nhớ cho con trỏ a <=> nới rộng thêm 1 ô nhớ
    for (int i = 0; i < n; i++) {
        a[i] = Temp[i];
    }
    delete[] Temp;
}
#endif //DO_AN_CUOI_KY_MEMORY_H
