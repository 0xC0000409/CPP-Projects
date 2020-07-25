#include <cstring>
#include "Header.h"
using std::cout; using std::endl;

int String::num_strings = 0;

int String::HowMany() {
	return num_strings;
}

String::String(const char* s) {
	len = strlen(s);
	str = new char[len + 1];
	strcpy_s(str, len + 1, s);
	num_strings++;
}

String::String(const String& s) {
	len = s.len;
	str = new char[len + 1];
	strcpy_s(str, len + 1, s.str);
	num_strings++;
}

String::String() {
	len = 0;
	str = new char[1];
	str[0] = '\0';
	num_strings++;
}

String& String::operator = (const String& st) {
	if (this == &st)
		return *this;
	else {
		delete[] str;
		len = st.len;
		str = new char[len + 1];
		strcpy_s(str, len + 1, st.str);
		return *this;
	}
}

String& String::operator = (const char* s) {
	delete[] str;
	len = strlen(s);
	str = new char[len + 1];
	strcpy_s(str, len + 1, s);
	return *this;
}

ostream& operator <<(ostream& os, const String& st) {
	cout << st.str;
	return os;
}

istream& operator >>(istream& is, String& st) {
	char inputBuff[String::CINLIM];
	is.get(inputBuff, String::CINLIM + 1);

	if (is) //evalutes false if input failed
		st = inputBuff;

	while (is && is.get() != '\n')
		continue;

	return is;
}

bool operator <(const String& st, const String& st2) {
	return (std::strcmp(st.str, st2.str) < 0);
}

bool operator >(const String& st, const String& st2) {
	return st.str < st2.str;
}

bool operator ==(const String& st, const String& st2) {
	return (std::strcmp(st.str, st2.str) == 0);
}

char& String::operator[](int i) {
	return str[i];
}

const char& String::operator [](int i) const {
	return str[i];
}

String::~String() {
	--num_strings;
	delete[] str;
}