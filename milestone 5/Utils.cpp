/***********************************************************************
// OOP244 Project, Utils Module
//
// File	Utils.h
// Version 0.6
// Date 2024-11-13
// started by Fardad
// Description
// utility function to be used in the project
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// Fardad          11-20           makeBillFileName
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
using namespace std;
#include "Utils.h"
namespace seneca {
    Utils ut;
    bool debug = false;
    const size_t AllocationBlockSize = 128;

    char* Utils::alocpy(const char* src) const {
        char* des{};
        return alocpy(des, src);
    }

    char* Utils::alocpy(char*& des, const char* src)const {
        delete[] des;
        des = nullptr;
        if (src) {
            des = new char[strlen(src) + 1];
            strcpy(des, src);
        }
        return des;
    }


    char* Utils::strcpy(char* des, const char* src)const {
        int i;
        for (i = 0; src[i]; i++) des[i] = src[i];
        des[i] = char(0);
        return des;
    }
    char* Utils::strcpy(char* des, const char* src, int len)const {
        int i;
        for (i = 0; i < len && src[i]; i++) des[i] = src[i];
        des[i] = 0; // unlike strncpy, this function null terminates the des cstring
        return des;
    }
    char* Utils::strncpy(char* des, const char* src, int len)const {
        int i = 0;
        while (i < len - 1 && src[i]) {
            des[i] = src[i];
            i++;
        }
        des[i] = src[i];
        return des;
    }
    char* Utils::makeBillFileName(char* filename, size_t billNo)const {
        char billFileName[21] = "bill_";
        size_t temp = billNo;
        int cnt = 5;
        int length;
        // Calculate the number of digits
        do {
            cnt++;
            temp /= 10;
        } while (temp > 0);
        length = cnt;
        // Convert each digit to character from the end
        while (billNo > 0) {
            billFileName[--cnt] = (billNo % 10) + '0';
            billNo /= 10;
        }
        // Handle the case when billNo is 0
        if (billFileName[cnt - 1] == '\0') {
            billFileName[--cnt] = '0';
        }
        // Attach .txt to the end of the file name
        for (int i = 0; ".txt"[i]; i++) {
            billFileName[length++] = ".txt"[i];
        }
        billFileName[length] = '\0';
        strcpy(filename, billFileName);
        return filename;
    }
    int Utils::strlen(const char* str)const {
        int len;
        for (len = 0; str[len]; len++);
        return len;
    }

    // Dynamically reads a cstring from istream
    char* Utils::read(char*& toRet, istream& istr, char delimiter)const {
        bool done = false;
        char* cstr = new char[AllocationBlockSize];
        toRet = cstr;
        int size = AllocationBlockSize;
        int nullindex = 1;
        do {
            cin.getline(cstr, AllocationBlockSize, delimiter);
            if (cin.fail()) {
                char* temp = new char[size + AllocationBlockSize];
                strcpy(temp, toRet);
                delete[] toRet;
                toRet = temp;
                cstr = &toRet[size - nullindex++];
                size += AllocationBlockSize;
                cin.clear();
            }
            else {
                done = true;
            }
        } while (!done);
        char* temp = new char[strlen(toRet) + 1];
        strcpy(temp, toRet);
        delete[] toRet;
        toRet = temp;
        return toRet;
    }

    bool Utils::isspace(char ch)const {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r';
    }

    bool Utils::isspace(const char* cstring) const {
        while (cstring && isspace(*cstring)) {
            cstring++;
        }
        return cstring && *cstring == 0;
    }

    // added on 11/14/2024 
    // edited on 12/01/2024
    // foolproof entry.
    int Utils::getInt()
    {
        int num;
        bool valid = false;
        do {

            cin.clear();

            if (cin.peek() == '\n') {
                cout << "You must enter a value: ";
                cin.ignore(10000, '\n');  
                continue;
            }

            cin >> num;
            if (cin.fail()) {
                cin.clear();
                cout << "Invalid integer: ";
                cin.ignore(10000, '\n');
                continue;
            }

            if (cin.peek() != '\n') {
                cout << "Only an integer please: ";
                cin.ignore(10000, '\n');
                continue;
            }

            valid = true;

        } while (!valid);

        cin.ignore(10000, '\n');

        return num;
    }



    int Utils::getInt(int min, int max)
    {
        int num;
        bool valid = false;
        do {
            num = getInt();

            if (num < min || num > max) {
                cout << "Invalid value: ["<< min << "<= value <="<< max <<"], try again: ";
            }
            else {
                valid = true;
            }
        } while (!valid);

        return num;
    }


}