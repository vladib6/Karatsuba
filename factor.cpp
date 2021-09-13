#include "factor.h"
#include"stack.h"
factor::factor(const factor& other) {
	*this = other;
}

void factor::operator=(const factor& other)
{
	number = new char[other.size];
	this->size = other.size;

	for (int i = 0; i < size; i++)
		this->number[i] = other.number[i];
}

factor::factor(int n, char* newstr) {
	number = new char[n];
	size = n;
	for (int i = 0; i < n; i++)
		this->number[i] = newstr[i];
}

factor factor:: operator+(const factor& other) {
	int sum = 0;
	char* temp = new char[size * 2];
	for (int i = 0; i < size * 2; i++)//initialize array
		temp[i] = 0;

	int write = (size * 2) - 1;
	for (int i = (this->size) - 1; i >= 0; i--) {
		sum = this->number[i] + other.number[i];
		temp[write] += sum % 10;
		temp[write - 1] += sum / 10;
		write--;
	}

	int newsize;
	temp = deleteZero(size * 2, &newsize, temp);
	factor res(newsize, temp);
	std::cout << "success" << std::endl;
	delete[] temp;
	return res;
}

factor factor::operator-(const factor& other)
{
	char* temp = new char[this->size];
	for (int i = 0; i < this->size; i++)
		temp[i] = 0;

	for (int i = this->size - 1; i >= 0; i--) {
		if (this->number[i] < other.number[i]) {
			int j = i - 1;
			while (this->number[j] == 0 && j >= 0) {
				this->number[j] += 10;
				this->number[j - 1] -= 1;
				j--;
			}
			this->number[i] += 10;
			this->number[i - 1] -= 1;
		}
		temp[i] = this->number[i] - other.number[i];
	}
	int newsize;
	temp = deleteZero(this->size, &newsize, temp);
	factor res(newsize, temp);
	delete[] temp;
	return res;
}

factor factor:: operator*(const factor& other) {
	int size1 = size, size2 = other.size;
	int sum = 0, mul = 0;
	char* product = new char[size1 + size2];//the returned array

	for (int i = 0; i < (size1 + size2); i++)//initialize array
		product[i] = 0;

	for (int j = size1 - 1; j >= 0; j--)
	{
		for (int k = size2 - 1; k >= 0; k--)
		{
			mul = (number[j]) * (other.number[k]);//multiplication digits
			sum = product[j + k + 1] + mul;//sum the previous carry with the multiplication
			product[j + k + 1] = sum % 10;//write to place the least sign of sum
			product[j + k] += sum / 10;//'write the carry to place
		}
	}

	int newsize;
	product = deleteZero(size1 + size2, &newsize, product);//delete zero
	factor res(newsize, product);
	delete[] product;
	//std::cout << "compli  succes" << std::endl;
	return res;
}

char* factor::deleteZero(int size, int* newsize, char* string) {//function that delete leading zero
	int i = 0;
	while (string[i] == 0&&i<size-1)// count 0 till end of array
		i++;

	char* tmp = new char[size - i];
	*newsize = size - i;
	for (int j = 0; j < *newsize; j++) {
		tmp[j] = string[i];
		i++;
	}
	delete[] string;
	return tmp;
}

void factor::print() {

	for (int m = 0; m < this->size; m++)
		std::cout <<static_cast<int>(this->number[m]);

	std::cout << "" << std::endl;

}

bool factor::isDigit(char ch)
{
	if ((ch >= 48) && (ch <= 57)) {
		return true;
	}
	else {
		return false;
	}
}


bool factor::getNumber() {
	//std::cout << "enter a " << this->size << " digit number" << std::endl;
	char temp;
	int i = 0;
	std::cin.get(temp);
	while (temp != '\n') {
		if ((i < this->size) && isDigit(temp)) {
			this->number[i] = temp - '0';
			std::cin.get(temp);
			//std::cout << static_cast<int>(this->number[i]) << std::endl;
			i++;
		}
		else {
			std::cout << "wrong output" << std::endl;
			return false;
		}
	}

	if (i < this->size) {
		std::cout << "wrong output" << std::endl;
		return false;
	}
	else
		return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void factor::karatsubaOuter( factor& f1, factor& f2)
{
	for (int i = 0; i < this->size; i++)//init the array
		this->number[i] = 0;
	karatsuba(this->number, f1.number, f2.number, f1.size);//karatsuba algorithem
	int newsize;
	this->number = deleteZero(this->size, &newsize, this->number);
	this->size = newsize;
}
void factor::karatsuba(char* res, char* f1, char* f2, int size)
{//instant mult
	if (size == 1)
		mult1(res, f1, f2);
	else {//complex mult
		int asize, bsize;//takes care of odd size
		asize = size / 2;
		bsize = size - size / 2;
		char* a = new char[asize];//a
		for (int i = 0; i < asize; i++)
			a[i] = f1[i];
		char* b = new char[bsize ];//b
		for (int i = asize; i < size; i++)
			b[i - asize] = f1[i];
		char* c = new char[asize];//c
		for (int i = 0; i < asize; i++)
			c[i] = f2[i];
		char* d = new char[bsize];//d
		for (int i = asize; i < size; i++)
			d[i - asize] = f2[i];
		char* ac = new char[2 * asize]{0};//a*c
		char* bd = new char[2 * bsize]{0};//b*d
		char* f1sum = new char[bsize + 1]{0};//a+b,at most it's size will be bsize+1
		char* f2sum = new char[bsize + 1]{0};//c+d,at most it's size will be bsize+1
		char* f1sumf2sum = new char[2 * bsize + 2]{0};//(a+b)*(c+d),size:2(bsize+1)
		plus(f1sum, a,  asize,  bsize+1);//a+b
		plus(f1sum, b, bsize , bsize+1);
		plus(f2sum, c, asize , bsize+ 1);//c+d
		plus(f2sum, d,  bsize,bsize + 1);
		karatsuba(ac, a, c, asize);
		karatsuba(bd, b, d, bsize);
		int count=0;
		if (f1sum[0] == 0 && f2sum[0] == 0)
			count++;
		karatsuba(f1sumf2sum+2*count, f1sum+count, f2sum+count, bsize + 1-count);
		minus(f1sumf2sum, ac, 2 * asize, 2 * bsize + 2);//(a+b)*(c+d)-ac
		minus(f1sumf2sum, bd, 2*bsize, 2*bsize + 2);//(a+b)*(c+d)-bd
		int i, j;
		int sum = 0;
		for (i = 2*bsize - 1, j = 2 * size - 1; i >= 0; j--, i--)//adds bd
		{
			sum = res[j] + bd[i];
			res[j] = sum % 10;
			res[j - 1] += sum / 10;
		}
		for (i = 2*bsize+1 , j = 2 * size - 1; i >= 0; j--, i--)//adds ((a+b)*(c+d)-ac-bd)*10^(bsize)
		{
			sum = res[j - bsize] + f1sumf2sum[i];
			res[j - bsize] = sum % 10;
			res[j - 1 - bsize ] += sum / 10;
		}
		for (i = 2*asize - 1, j = 2 * size - 1; i > 0; j--, i--)//adds ac*10^(2*bsize)
		{
			sum = res[j - 2*bsize] + ac[i];
			res[j - 2*bsize] = sum % 10;
			res[j - 1 - 2*bsize] += sum / 10;
		}
		res[0] += ac[0];//prevents the program to write outside the allocated memory
		delete[] a;
		delete[] c;
		delete[] b;
		delete[] d;
		delete[] f1sum;
		delete[] f2sum;
		delete[] ac;
		delete[] bd;
		delete[] f1sumf2sum;
	}
}
void factor::mult1(char* res, char* f1, char* f2) {
	int sum = f1[0]*f2[0];
	res[1] = sum % 10;
	res[0] = sum / 10;
 }
void factor::plus(char* res, char* f1,int size,int resSize) {
	int sum = 0,i,j;
	for (i=size-1,j=resSize-1; i >= 0; i--, j--) {
			sum = res[j] + f1[i];
			res[j] = sum % 10;
			res[j - 1] += sum / 10;
		}
 }
void factor::minus(char* res, char* f1, int size, int resSize) {
	int i, m;
	for ( i=size-1, m=resSize-1; i >= 0 ; i--, m--)
	{
		if (res[m] < f1[i]) {//take 1 from the digit from the right
			res[m] += 10;
			res[m-1] -= 1;
		}
		res[m] -= f1[i];
	}
	for (m = resSize - 1; m >= 0; m--)//checks for negetive digits
	{
		if (res[m] < 0)
		{
			res[m] += 10;
			res[m - 1] -= 1;
		}	
	}
 }




void factor::karatsubaOuterIterative(factor& f1, factor& f2)
{
	for (int i = 0; i < this->size; i++)//init the array
		this->number[i] = 0;
	karatsubaIterative(this->number, f1.number, f2.number, f1.size);//karatsuba iterative algorithem
	int newsize;
	this->number = deleteZero(this->size, &newsize, this->number);
	this->size = newsize;
}
void factor::karatsubaIterative(char* res, char* f1, char* f2, int size)
{
	stack s;
	int returnfromrecursion = 0;
	item curr;
	char* Resreturn=nullptr;
	curr.res = new char[size*2];
	for (int i = 0; i < size * 2; i++)
		curr.res[i] = res[i];
	curr.f1 = new char[size];
	for (int i = 0; i < size; i++)
		curr.f1[i] = f1[i];
	curr.f2 = new char[size];
	for (int i = 0; i < size; i++)
		curr.f2[i] = f2[i];
	curr.size = size;
	curr.line = 0;
	do {
		if (returnfromrecursion)
			curr = s.pop();
		if (curr.line == 0)
		{
			if (curr.size == 1) {
				mult1(curr.res, curr.f1, curr.f2);
				returnfromrecursion = 1;
				Resreturn = curr.res;
				delete[]curr.f1;
				delete[]curr.f2;
			}
			else {
				
				int asize, bsize;//takes care of odd size
				asize = curr.size / 2;
				bsize = curr.size - (curr.size / 2);
				char* a = new char[asize];//a
				for (int i = 0; i < asize; i++)
					a[i] = curr.f1[i];
				char* c = new char[asize];//c
				for (int i = 0; i < asize; i++)
					c[i] = curr.f2[i];

				curr.line = 1;
				s.push(curr);

				curr.res = new char[asize * 2]{0};
				curr.f1 = a;
				curr.f2 = c;
				curr.size = asize;
				curr.line = 0;
				returnfromrecursion = 0;
			}
		}
		else if (curr.line == 1)
		{
			int asize, bsize;//takes care of odd size
			asize = curr.size / 2;
			bsize = curr.size - (curr.size / 2);
			char* b = new char[bsize];//b
			for (int i = asize; i < curr.size; i++)
				b[i - asize] = curr.f1[i];
			char* d = new char[bsize];//d
			for (int i = asize; i < curr.size; i++)
				d[i - asize] = curr.f2[i];

			curr.line = 2;
			curr.ac = Resreturn;
			s.push(curr);

			curr.res = new char[bsize * 2]{0};
			curr.f1 = b;
			curr.f2 = d;
			curr.size = bsize;
			curr.line = 0;
			returnfromrecursion = 0;
		}
		else if (curr.line == 2)
		{

			int asize, bsize;//takes care of odd size
			asize = curr.size / 2;
			bsize = curr.size - (curr.size / 2);
			char* f1sum = new char[bsize + 1]{0};
			char* f2sum = new char[bsize + 1]{0};

			plus(f1sum, curr.f1, asize, bsize + 1);//a+b
			plus(f1sum, curr.f1+asize, bsize, bsize + 1);
			plus(f2sum, curr.f2, asize, bsize + 1);//c+d
			plus(f2sum, curr.f2+asize, bsize, bsize + 1);


			curr.flag = 0;
			if (f1sum[0] == 0 && f2sum[0] == 0)
				curr.flag++;
			curr.line = 3;
			curr.bd = Resreturn;
			s.push(curr);


			
			curr.res = new char[2 * (bsize + 1) - 2 * curr.flag]{0};
			curr.f1 = new char[bsize + 1 - curr.flag];
			for (int i = 0; i < bsize + 1 - curr.flag; i++)
				curr.f1[i] = f1sum[i + curr.flag];
			curr.f2 = new char[bsize + 1 - curr.flag];
			for (int i = 0; i < bsize + 1 - curr.flag; i++)
				curr.f2[i] = f2sum[i + curr.flag];
			curr.size = bsize + 1- curr.flag;
			curr.line = 0;
			returnfromrecursion = 0;
			delete[]f1sum;
			delete[]f2sum;
		}
		else if (curr.line == 3)
		{
			int asize, bsize;//takes care of odd size
			asize = curr.size / 2;
			bsize = curr.size - (curr.size / 2);
			curr.f1sumf2sum = Resreturn;

			minus(curr.f1sumf2sum, curr.ac, 2 * asize, 2 * bsize + 2 - 2 * curr.flag);//(a+b)*(c+d)-ac
			minus(curr.f1sumf2sum, curr.bd, 2 * bsize, 2 * bsize + 2 - 2 * curr.flag);//(a+b)*(c+d)-bd

			int i, j;
			int sum = 0;
			for (i = 2 * bsize - 1, j = 2 * curr.size - 1; i >= 0; j--, i--)//adds bd
			{
				sum = curr.res[j] + curr.bd[i];
				curr.res[j] = sum % 10;
				curr.res[j - 1] += sum / 10;
			}
			
			for (i = 2 * bsize + 1-2*curr.flag, j = 2 * curr.size - 1; i >= 0; j--, i--)//adds ((a+b)*(c+d)-ac-bd)*10^(bsize)
			{
				sum = curr.res[j - bsize] + curr.f1sumf2sum[i];
				curr.res[j - bsize] = sum % 10;
				curr.res[j - 1 - bsize] += sum / 10;
			}

			for (i = 2 * asize - 1, j = 2 * curr.size - 1; i > 0; j--, i--)//adds ac*10^(2*bsize)
			{
				sum = curr.res[j - 2 * bsize] + curr.ac[i];
				curr.res[j - 2 * bsize] = sum % 10;
				curr.res[j - 1 - 2 * bsize] += sum / 10;
			}
			curr.res[0] += curr.ac[0];
			Resreturn = curr.res;
			delete[]curr.ac;
			delete[]curr.bd;
			delete[]curr.f1;
			delete[]curr.f2;
			delete[]curr.f1sumf2sum;
			returnfromrecursion = 1;
		}
	} while (!s.isEmpty());
	if (Resreturn != nullptr) {
		for (int i = 0; i < size * 2; i++)
			res[i] = Resreturn[i];
		delete[] Resreturn;
	}
	
}

