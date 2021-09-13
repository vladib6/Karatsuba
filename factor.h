#include <iostream>
#include <string.h>


class factor {

private:
	char* number;
	int size;

public:
	factor() = default;
	~factor() { delete[] number; }
	factor(const factor& other);
	factor(int n) :number(new char[n]), size(n) {}
	factor(int n, char* newstr);
	factor operator*(const factor& other);
	factor operator+(const factor& other);
	factor operator-(const factor& other);
	void operator=(const factor& other);
	bool getNumber();
	char* deleteZero(int size, int* newsize, char* string);
	void print();
	bool isDigit(char ch);
	/////////////////////////////////////////////////////////////////
	void karatsubaOuter( factor& f1,  factor& f2);
	void karatsuba(char* res, char* f1, char* f2, int size);
	void karatsubaOuterIterative(factor& f1, factor& f2);
	void karatsubaIterative(char* res, char* f1, char* f2, int size);
	void mult1(char* res, char* f1, char* f2);
	void plus(char* res, char* f1, int size, int resSize);
	void minus(char* res, char* f1, int size, int resSize);
};