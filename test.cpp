#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string.h>
#include "my_number.h"


// other includes and definitions

/* YOUR CODE HERE */

using namespace std;

// define your datatype here
typedef my_number myType;

// convert from string to myType
myType convert(string s) {
	myType num(s);
	return num;
}
// convert from myType to string
string toStr(myType m) {
	return m.get_number();
}

// compute a factorial
myType myFactorial(int n);

// finds the next prime, bigger than n					
myType myPrime(myType n);

// finds d to the power of (positive) p					
myType myPow(double d, int p);

// finds (natural) logarithm of d				
myType myLog(double d);

// finds sinus of d						
myType mySin(double d);

// finds square root of d						
myType mySqrt(double d);

// finds a value of PI with n digits of precision (zeroes afterwards)						
myType myPi(int n);

// computes an average of n valus in an array 					
myType myAvg(myType* data, int n);

// search for a value in an array of n numbers and return an index		
int myFind(myType* data, int n, myType value);

// sorts data in an array of n numbers by (optimized) bubble sort algorithm
void mySort(myType* data, int n);

myType myFactorial(int n) {
	try {
		if (n < 0)
			throw "only positive numbers allowed";
		if (n == 0)
			return myType(1);
		myType temp(1), answer(1), one(1);
		for (int i = 0; i < n; ++i) {
			answer = answer * temp;
			temp = temp + one;
		}
		return answer;
	} catch (const char* message) {
		cerr << message << endl;
	}
}

myType myPrime(myType n) {
	if (n < myType(2)) {
		return myType(2);
	}
	myType one(1);
	myType zero(0);
	myType liek = n % one;
	myType answer = n - liek;
	while (true) {
		answer = answer + one;
		myType temp(2);
		while (temp < answer) {
			if (answer % temp == zero)
				break;
			temp = temp + one;
		}
		if (answer == temp)
			break;
	}
	return answer;
}

myType myPow(double d, int p) {
	try {
		if (p < 0)
			throw "only positive numbers allowed";

		if (p == 0)
			return myType(1);

		if (d == 1.0)
			return myType(1);

		myType answer(d);
		myType number(d);
		for (int i = 0; i < p - 1; ++i)
			answer = (answer * number);
		answer.round_by();
		return answer;
	}catch (const char* message) {
		cerr << message << endl;
	}
}

myType myLog(double d) {
	try {
		if (d <= 0)
			throw "only positive numbers allowed";

		if (d == 1)
			return myType(0);

		myType ln10(LN10);
		myType ln05(LN05);
		myType two(2);
		myType one(1);
		myType half(0.5);
		myType number(d);
		myType ten(10);
		int tenln = 0;
		int halfln = 0;

		if (d == 10) {
			ln10.round_by();
			return ln10;
		}

		while (number > two) {
			number = number / ten;
			tenln++;
		}

		while (number < half) {
			number = number / half;
			halfln++;
		}

		myType answer(0);
		myType up_tr = number - one;
		myType down_tr = number + one;
		myType tr = up_tr / down_tr;
		myType current_power = tr;

		for (int i = 1; i < 210; i += 2) {
			myType temp(i);
			myType first = one / temp;
			myType multiplication = current_power * first;
			multiplication.cut();
			answer = multiplication + answer;
			current_power = current_power * tr;
			current_power.cut();
			current_power = current_power * tr;
			current_power.cut();
		}
		answer = answer * two;

		while (tenln > 0) {
			answer = answer + ln10;
			tenln--;
		}

		while (halfln > 0) {
			answer = answer + ln05;
			halfln--;
		}

		answer.round_by();
		return answer;
	} catch (const char* message) {
		cerr << message << endl;
	}
}

myType mySin(double d) {
	myType answer(0);
	myType number(d);
	myType pi(PI);
	myType half(2);
	int periods = 0;

	while (number > pi) {
		number = number - pi;
		++periods;
	}

	while (number < answer) {
		number = number + pi;
		++periods;
	}

	if (number == answer)
		return answer;

	if (number >= (pi / half))
		number = pi - number;
	
	for (int i = 0; i < 40; ++i) {
		myType down = myFactorial(2 * i + 1);
		myType up = number;
		for (int j = 0; j < i * 2; ++j) {
			up = up * number;
			up.cut();
		}
		myType tr = up / down;
		if (i % 2 == 0)
			answer = answer + tr;
		else
			answer = answer - tr;
	}

	answer.round_by();
	if (periods % 2) {
		myType minusone(-1);
		answer = answer * minusone;
	}

	return answer;
}

myType mySqrt(double d) {
	try {
		if (d < 0)
			throw "only positive numbers allowed";
		if (d == 0)
			return myType(0);

		myType number(d);
		myType answer(sqrt(d));
		myType half(0.5);

		for (int i = 0; i < 10; ++i) {
			myType division = number / answer;
			myType sum = answer + division;
			answer = sum * half;
		}
		answer.round_by();
		return answer;
	} catch (const char* message) {
		cerr << message << endl;
	}
}

myType myPi(int n) {
	try {
		if (n < 0)
			throw "only positive numbers allowed";

		if (n == 0) {
			myType num("3.0");
			return num;
		}

		myType m(PI);
		m.round_by(n);
		return m;
	} catch (const string &error) {
		cerr << error << endl;
	}
}

myType myAvg(myType* data, int n) {
	myType answer;
	myType quantity(n);

	if (n == 1) {
		answer = data[0];
		return answer;
	}
	
	for (int i = 0; i < n; ++i)
		answer = (answer + data[i]);
	answer = answer / quantity;
	answer.round_by();
	return answer;
}

int myFind(myType* data, int n, myType value) {
	for (int i = 0; i < n; ++i)
		if (data[i] == value)
			return i;
	return -1;
}

void mySort(myType* data, int n) {
	for (int i = 0; i < n - 1; ++i) {
		bool changed = false;
		for (int j = 0; j < n - i - 1; ++j) {
			if (data[j] > data[j + 1]) {
				myType temp(data[j]);
				data[j] = data[j + 1];
				data[j + 1] = temp;
				changed = true;
			}
		}
		if (!changed)
			break;
	}
}

/* DO NOT MODIFY CODE BELOW */

int main() {
	while (1) {
		int x = -1;
		cin >> x;
		if (x == 0)
			break;
		string s;
		double d;
		int n;
		myType* data = NULL;
		string output;
		switch (x) {
		case 1:
			cin >> n;
			cout << (output = toStr(myFactorial(n))) << endl;
			break;
		case 2:
			cin >> s;
			cout << (output = toStr(myPrime(convert(s)))) << endl;
			break;
		case 3:
			int p;
			cin >> d >> p;
			cout << (output = toStr(myPow(d, p))) << endl;
			break;
		case 4:
			cin >> d;
			cout << (output = toStr(myLog(d))) << endl;
			break;
		case 5:
			cin >> d;
			cout << (output = toStr(mySin(d))) << endl;
			break;
		case 6:
			cin >> d;
			cout << (output = toStr(mySqrt(d))) << endl;
			break;
		case 7:
			cin >> n;
			cout << (output = toStr(myPi(n))) << endl;
			break;
		case 8:
			cin >> n;
			data = new myType[n];
			for (int i = 0; i < n; ++i) {
				string s;
				cin >> s;
				data[i] = convert(s);
			}
			cout << (output = toStr(myAvg(data, n))) << endl;
			delete[] data;
			break;
		case 9:
			cin >> n;
			data = new myType[n];
			for (int i = 0; i < n; ++i) {
				string s;
				cin >> s;
				data[i] = convert(s);
			}
			cin >> s;
			int f;
			cout << (f = myFind(data, n, convert(s))) << endl;
			delete[] data;
			break;
		case 10:
			cin >> n;
			data = new myType[n];
			for (int i = 0; i < n; ++i) {
				string s;
				cin >> s;
				data[i] = convert(s);
			}
			mySort(data, n);
			for (int i = 0; i < n; ++i) {
				cout << (output = toStr(data[i])) << endl;
			}
			delete[] data;
			break;
		}
	}
	return 0;
}