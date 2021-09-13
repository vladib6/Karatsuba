#include "factor.h"
#include<chrono>
#include<fstream>
#include <iomanip>
using namespace std;
int main() {
	int n=0;
	char ch;
	char num[10];
	cin.get(ch);
	while (ch ==' ')
		cin.get(ch);
	if (ch == '0') {
		cout << "wrong output";
		exit(1);
	}
	int i = 0;
	while (ch != '\n')
	{
		num[i] = ch - '0';
		i++;
		cin.get(ch);
	}
	i--;
	int c = 1;
	for (i; i >= 0; i--) {
		n += num[i] * c;
		c *= 10;
	}
	
	factor f1(n), f2(n),f3(2*n),f4(2*n),f5(2*n);

	if (f1.getNumber() && f2.getNumber())
	{
		auto start = chrono::high_resolution_clock::now();// unsync the I/O of C and C++.
		ios_base::sync_with_stdio(false);
		f3 = f1 * f2;// Here you put the name of the function you wish to measure
		auto end = chrono::high_resolution_clock::now();// Calculating total time taken by the program.
		double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		time_taken *= 1e-9;
		ofstream myfile("Measure.txt"); // The name of the file
		myfile << "Time taken by function <*> is : " << fixed << time_taken << setprecision(9);
		myfile << " sec" << endl;

	    auto start2 = chrono::high_resolution_clock::now();// unsync the I/O of C and C++.
		ios_base::sync_with_stdio(false);
		f4.karatsubaOuter(f1, f2);// Here you put the name of the function you wish to measure
	    auto end2 = chrono::high_resolution_clock::now();// Calculating total time taken by the program.
		double time_taken2 = chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();
		time_taken2 *= 1e-9;
		myfile << "Time taken by function <karatsubaOuter> is : " << fixed << time_taken2 << setprecision(9);
		myfile << " sec" << endl;

		auto start3 = chrono::high_resolution_clock::now();// unsync the I/O of C and C++.
		ios_base::sync_with_stdio(false);
		f5.karatsubaOuterIterative(f1, f2);// Here you put the name of the function you wish to measure
		auto end3 = chrono::high_resolution_clock::now();// Calculating total time taken by the program.
		double time_taken3 = chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count();
		time_taken3 *= 1e-9;
		myfile << "Time taken by function <karatsubaOuterIterative> is : " << fixed << time_taken3 << setprecision(9);
		myfile << " sec" << endl;
		myfile.close();

		cout << "Long multiplication: x * y =   ";
		f3.print();
		cout << "Karatsuba (recursive): x * y = ";
		f4.print();
		cout << "Karatsuba (iterative): x * y = ";
		f5.print();


	}
}