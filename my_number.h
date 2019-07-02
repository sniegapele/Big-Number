#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>

const std::string PI = "3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798";
const std::string LN10 = "2.30258509299404568401799145468436420760110148862877297603332790096757260967735248023599720508959829834";
const std::string LN05 = "-0.693147180559945309417232121458176568075500134360255254120680009493393621969694715605863326996418687542";
const int FRACT = 105;

class my_number {
	std::string number;
	bool negative;
	int dot_position;
	int digits_after_dot;

	void insert_zeroes(int n);
	void delete_zeroes();
public:
	my_number();
	my_number(int input);
	my_number(double input);
	my_number(std::string input);
	my_number(const my_number& input);
	my_number(std::string num, bool neg);

	bool operator == (const my_number& other);
	bool operator != (const my_number& other);
	bool operator > (const my_number& other);
	bool operator >= (const my_number& other);
	bool operator < (const my_number& other);
	bool operator <= (const my_number& other);
	void operator = (const my_number& other);
	bool daugiau_reiksme(const std::string& other);
	bool maziau_reiksme(const std::string& other);

	my_number operator + (my_number& other);
	my_number operator - (my_number& other);
	my_number operator % (my_number& other);
	my_number operator * (my_number& other);
	my_number operator / (my_number& other);
	
	
	void round_by(int digits = 99);
	void cut();

	void print();

	std::string get_number() const;
};

