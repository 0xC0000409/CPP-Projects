#ifndef HEADER_H_
#define HEADER_H_
#include <iostream>
using std::istream;
using std::ostream;

class String {
private:
	char* str;
	size_t len;
	static int num_strings; //shared among all objects
	static const int CINLIM = 80; //cin limit
public:
	String();
	String(const char* s);
	String(const String& s); //copy constructor
	size_t length() const { return len; }
	char& operator [](int i);
	const char& operator [](int i) const;
	static int HowMany();
	String& operator = (const String& st);
	String& operator = (const char* s);
	friend ostream& operator <<(ostream& os, const String& str);
	friend bool operator <(const String& st, const String& st2);
	friend bool operator >(const String& st, const String& st2);
	friend bool operator ==(const String& st, const String& st2);
	friend istream& operator >>(istream& is, String& st);
	~String();
};

#endif
