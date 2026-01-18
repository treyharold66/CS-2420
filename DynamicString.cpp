#include <iostream>
#include "DynamicString.h"
#include <cctype>
#include <stdexcept>

using std::out_of_range;
using std::tolower;
using std::toupper;
using std::ostream;

// Helper function for finding the length of strings
int findLen(const char* str) {
	// Sets counter variable to 0
    int count = 0;
	// Keeps counting string characters until null terminator is present
    while (str[count] != '\0') {
        count++;
    }
	// Returns the length of string
    return count;
}

// Helper function for copying strings
void copyStr(char* next, const char* curr) {
    int i = 0;
    while (curr[i] != '\0') {
        next[i] = curr[i];
        i++;
    }
    next[i] = '\0';
}

int compareStr(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

DynamicString::DynamicString() {
    this->cstr = new char[1];
    this->cstr[0] = '\0';
}

DynamicString::DynamicString(const char* str){
	if (str == nullptr) {
        cstr = new char[1];
        cstr[0] = '\0';
    } else {
        int length = findLen(str);
        cstr = new char[length + 1];
        copyStr(this->cstr, str);
    }

}

DynamicString::DynamicString(const DynamicString& other){
	int length = findLen(other.cstr);
	cstr = new char[length+1];
	copyStr(this->cstr, other.cstr);
}

DynamicString& DynamicString::operator=(const DynamicString& other){

	if (this != &other) {
		delete[] cstr;
		int length = findLen(other.cstr);
		cstr = new char[length + 1];
		copyStr(cstr, other.cstr);
	}
	return *this;
}

DynamicString::~DynamicString(){
	delete[] cstr;
	return;
}

int DynamicString::len() const{
	int str_length = 0;
	while (cstr[str_length] != '\0') {
		str_length++;
	}
   return str_length;
}

const char* DynamicString::c_str() const{
   return cstr;
}

char DynamicString::char_at(int position) const{
	if (position < 0 || position >= len()) {
		throw std::out_of_range("Index out of range");
	}
	return cstr[position];
}

char& DynamicString::operator[](int position){
	if (position < 0 || position >= len()) {
		throw std::out_of_range("Index out of range");
	}
	return cstr[position];
}

bool DynamicString::startsWith(const DynamicString& other) const{

	int otherLength = other.len();
	int currentLength = len();

	if (currentLength < otherLength) {
		return false;
	}

	for (int i = 0; i < otherLength; i++) {
		if (cstr[i] != other.cstr[i]) {
			return false;
		}
	}
	return true;
}

bool DynamicString::endsWith(const DynamicString& other) const{
	int otherLength = other.len();
	int currentLength = len();

	if (otherLength > currentLength) {
		return false;
	}

	int distance = currentLength - otherLength;
	for (int i = 0; i < otherLength; i++) {
		if (cstr[distance + i] != other.cstr[i]) {
			return false;
		}
	}
	return true;
}

int DynamicString::compare(const DynamicString& other) const{
	return compareStr(cstr, other.cstr);
}

DynamicString& DynamicString::toLower(){
	for (int i = 0; i < len(); i++) {
		cstr[i] = tolower(cstr[i]);
	}
   return *this;
}

DynamicString& DynamicString::toUpper(){
	for (int i = 0; i < len(); i++) {
		cstr[i] = toupper(cstr[i]);
	}
   return *this;
}

DynamicString& DynamicString::replace(char old, char newCh){

	for (int i = 0; i < len(); i++) {
		if (cstr[i] == old) {
			cstr[i] = newCh;
		}
	}
   return *this;
}

int DynamicString::find(char needle, int start) const{
	int length = len();

	if (start < 0) {
		start = 0;
	}

	if (needle == '\0' && start <= length) {
        return length;
    }

	for (int i = start; i < length; i++) {
		if (cstr[i] == needle) {
			return i;
		}
	}
   return -1;
}

ostream& operator<<(ostream& out, const DynamicString& str){
   out << str.cstr;
   return out;
}
