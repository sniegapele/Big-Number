#include "my_number.h"

using namespace std;

my_number::my_number() {
	number = "0.0";
	negative = false;
	dot_position = 1;
	digits_after_dot = 1;
}

my_number::my_number(int input) {
	if (input < 0) {
		negative = true;
		input *= -1;
	}
	else
		negative = false;
	number = to_string(input);
	number.append(".0");
	dot_position = number.find('.');
	digits_after_dot = 1;
}

my_number::my_number(double input) {
	if (input < 0) {
		negative = true;
		input *= -1;
	}
	else
		negative = false;
	number = to_string(input);
	delete_zeroes();
}

my_number::my_number(string input) {
	if (input[0] == '-') {
		negative = true;
		input.erase(0, 1);
	}
	else
		negative = false;
	number = input;
	delete_zeroes();
}

my_number::my_number(std::string num, bool neg) {
	number = num;
	negative = neg;
	delete_zeroes();
}


my_number::my_number(const my_number& input) {
	number = input.number;
	negative = input.negative;
	dot_position = input.dot_position;
	digits_after_dot = input.digits_after_dot;
}

bool my_number::operator == (const my_number& other) {
	if (negative != other.negative)
		return false;

	if (dot_position != other.dot_position)
		return false;

	if (digits_after_dot != other.digits_after_dot)
		return false;

	if (number.length() != other.number.length())
		return false;

	for (int i = 0; i < number.length(); ++i)
		if (number[i] != other.number[i])
			return false;

	return true;
}

bool my_number::operator != (const my_number& other) {
	if (dot_position != other.dot_position)
		return true;

	if (number.length() != other.number.length())
		return true;

	for (int i = 0; i < number.length(); ++i)
		if (number[i] != other.number[i])
			return true;

	if (negative != other.negative)
		return true;

	return false;
}

bool my_number::operator > (const my_number& other) {
	if (!negative && other.negative) //first positive, second negative
		return true;

	if (negative && !other.negative) //first negative, second positive
		return false;

	if (!negative && !other.negative) { //both positive
		if (dot_position > other.dot_position)
			return true;
		if (dot_position < other.dot_position)
			return false;

		int n = min(number.length(), other.number.length());
		for (int i = 0; i < n; ++i) {
			if (number[i] > other.number[i])
				return true;
			else if (number[i] < other.number[i])
				return false;
		}

		if (number.length() > other.number.length())
			return true;
		if (number.length() <= other.number.length())
			return false;
	}

	if (negative && other.negative) { //both negative
		if (dot_position > other.dot_position)
			return false;
		if (dot_position < other.dot_position)
			return true;

		int n = min(number.length(), other.number.length());
		for (int i = 0; i < n; ++i) {
			if (number[i] < other.number[i])
				return true;
			if (number[i] > other.number[i])
				return false;
		}

		if (number.length() >= other.number.length())
			return false;
		if (number.length() < other.number.length())
			return true;
	}
}

bool my_number::operator >= (const my_number& other) {
	if (*this > other)
		return true;

	if (*this == other)
		return true;

	return false;
}

bool my_number::operator < (const my_number& other) {
	if (*this >= other)
		return false;
	return true;
}

bool my_number::operator <= (const my_number& other) {
	if (*this > other)
		return false;
	return true;
}

void my_number::operator = (const my_number& other) {
	number = other.number;
	negative = other.negative;
	dot_position = other.dot_position;
	digits_after_dot = other.digits_after_dot;
}

bool my_number::daugiau_reiksme(const string& other) {
	int n1 = number.find('.');
	int n2 = other.find('.');

	if (n1 > n2)
		return true;
	else if (n2 > n1)
		return false;

	//first longer
	if (number.length() > other.length()) {
		for (int i = 0; i < other.length(); ++i) {
			if (number[i] > other[i])
				return true;
			if (number[i] < other[i])
				return false;
		}
		return true;
	}

	//second longer
	if (number.length() < other.length()) {
		for (int i = 0; i < number.length(); ++i) {
			if (number[i] > other[i])
				return true;
			if (number[i] < other[i])
				return false;
		}
		return false;
	}

	//equal size
	for (int i = 0; i < number.length(); ++i) {
		if (number[i] > other[i])
			return true;
		if (number[i] < other[i])
			return false;
	}
	return false;
}

bool my_number::maziau_reiksme(const string& other) {
	int n1 = number.find('.');
	int n2 = other.find('.');

	if (n1 < n2)
		return true;
	else if (n1 > n2)
		return false;

	//first longer
	if (number.length() > other.length()) {
		for (int i = 0; i < other.length(); ++i) {
			if (number[i] < other[i])
				return true;
			if (number[i] > other[i])
				return false;
		}
		return false;
	}

	//second longer
	if (number.length() < other.length()) {
		for (int i = 0; i < number.length(); ++i) {
			if (number[i] < other[i])
				return true;
			if (number[i] > other[i])
				return false;
		}
		return true;
	}

	//equal size
	for (int i = 0; i < number.length(); ++i) {
		if (number[i] < other[i])
			return true;
		if (number[i] > other[i])
			return false;
	}
	return false;
}

my_number my_number::operator + (my_number& other) {
	if (dot_position != other.dot_position) { //insert zeroes in the beginning
		if (dot_position > other.dot_position) { //second is smaller
			reverse(other.number.begin(), other.number.end());
			other.insert_zeroes(dot_position - other.dot_position);
			reverse(other.number.begin(), other.number.end());
		}
		if (dot_position < other.dot_position) { //first is smaller
			reverse(number.begin(), number.end());
			insert_zeroes(other.dot_position - dot_position);
			reverse(number.begin(), number.end());
		}
	}

	if (digits_after_dot != other.digits_after_dot) { //insert zeros in the end
		if (digits_after_dot > other.digits_after_dot)
			other.insert_zeroes(digits_after_dot - other.digits_after_dot);
		if (digits_after_dot < other.digits_after_dot)
			insert_zeroes(other.digits_after_dot - digits_after_dot);
	}

	if (negative && !other.negative) {//first negative, second positive
		if (daugiau_reiksme(other.number)) { //negative, first-second
			string answer;
			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());

			for (int i = 0; i < number.length(); ++i) {
				if (number[i] != '.')
					answer.push_back(number[i] - other.number[i]);
				else
					answer.push_back('.');
			}

			for (int i = 0; i < answer.length(); ++i) {
				if (answer[i]<0 && answer[i] != '.') {
					if (answer[i + 1] != '.') {
						answer[i] += 10;
						answer[i + 1]--;
					}
					else {
						answer[i] += 10;
						answer[i + 2]--;
					}
				}
			}
			
			for (int i = 0; i < answer.length(); ++i)
				if (answer[i] != '.')
					answer[i] += 48;

			reverse(answer.begin(), answer.end());

			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());
			delete_zeroes();
			other.delete_zeroes();
			return my_number(answer, true);
		}
		if (maziau_reiksme(other.number)) { //positive,second-first
			string answer;
			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());

			for (int i = 0; i < number.length(); ++i) {
				if (number[i] != '.')
					answer.push_back(other.number[i] - number[i]);
				else
					answer.push_back('.');
			}

			for (int i = 0; i < answer.length(); ++i) {
				if (answer[i] < 0 && answer[i] != '.') {
					if (answer[i + 1] != '.') {
						answer[i] += 10;
						answer[i + 1]--;
					}
					else {
						answer[i] += 10;
						answer[i + 2]--;
					}
				}
			}

			for (int i = 0; i < answer.length(); ++i)
				if (answer[i] != '.')
					answer[i] += 48;

			reverse(answer.begin(), answer.end());

			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());
			delete_zeroes();
			other.delete_zeroes();
			return my_number(answer, false);
		}
	}

	if (!negative && other.negative) { //first positive, second negative
		if (daugiau_reiksme(other.number)) {//first-second
			string answer;
			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());

			for (int i = 0; i < number.length(); ++i) {
				if (number[i] != '.')
					answer.push_back(number[i] - other.number[i]);
				else
					answer.push_back('.');
			}

			for (int i = 0; i < answer.length(); ++i) {
				if (answer[i] < 0 && answer[i] != '.') {
					if (answer[i + 1] != '.') {
						answer[i] += 10;
						answer[i + 1]--;
					}
					else {
						answer[i] += 10;
						answer[i + 2]--;
					}
				}
			}

			for (int i = 0; i < answer.length(); ++i)
				if (answer[i] != '.')
					answer[i] += 48;

			reverse(answer.begin(), answer.end());

			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());
			delete_zeroes();
			other.delete_zeroes();
			return my_number(answer, false);
		}
		if (maziau_reiksme(other.number)) { //second-first
			string answer;
			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());

			for (int i = 0; i < number.length(); ++i) {
				if (number[i] != '.')
					answer.push_back(other.number[i] - number[i]);
				else
					answer.push_back('.');
			}

			for (int i = 0; i < answer.length(); ++i) {
				if (answer[i] < 0 && answer[i] != '.') {
					if (answer[i + 1] != '.') {
						answer[i] += 10;
						answer[i + 1]--;
					}
					else {
						answer[i] += 10;
						answer[i + 2]--;
					}
				}
			}

			for (int i = 0; i < answer.length(); ++i)
				if (answer[i] != '.')
					answer[i] += 48;

			reverse(answer.begin(), answer.end());

			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());
			delete_zeroes();
			other.delete_zeroes();
			return my_number(answer, true);
		}
	}
	
	//if both of variables are either positive or negative 
	{
		string answer;
		for (int i = 0; i < number.length(); ++i) {
			if (number[i] != '.')
				answer.push_back(number[i] + other.number[i] - 2 * 48);
			else
				answer.push_back('.');
		}

		reverse(answer.begin(), answer.end());
		for (int i = 0; i < answer.length() - 1; ++i) {
			if (answer[i] >= 10 && answer[i] != '.') {
				if (answer[i + 1] != '.') {
					answer[i] -= 10;
					answer[i + 1]++;
				}
				else {
					answer[i] -= 10;
					answer[i + 2]++;
				}
			}
		}

		if (answer[answer.length() - 1] >= 10) {
			answer[answer.length() - 1] -= 10;
			answer.push_back(1);
		}

		for (int i = 0; i < answer.length(); ++i)
			if (answer[i] != '.')
				answer[i] += 48;

		reverse(answer.begin(), answer.end());

		delete_zeroes();
		other.delete_zeroes();

		//if both are negative
		if (negative)
			return my_number(answer, true);

		//if both are positive
		else
			return my_number(answer, false);
	}
}

my_number my_number::operator - (my_number& other) {
	if (*this == other) {
		return my_number(0);
	}
	if (dot_position != other.dot_position) { //insert zeroes in the beginning
		if (dot_position > other.dot_position) { //second is smaller
			reverse(other.number.begin(), other.number.end());
			other.insert_zeroes(dot_position - other.dot_position);
			reverse(other.number.begin(), other.number.end());
		}
		if (dot_position < other.dot_position) { //first is smaller
			reverse(number.begin(), number.end());
			insert_zeroes(other.dot_position - dot_position);
			reverse(number.begin(), number.end());
		}
	}

	if (digits_after_dot != other.digits_after_dot) { //insert zeros in the end
		if (digits_after_dot > other.digits_after_dot)
			other.insert_zeroes(digits_after_dot - other.digits_after_dot);
		if (digits_after_dot < other.digits_after_dot)
			insert_zeroes(other.digits_after_dot - digits_after_dot);
	}

	if (!negative && !other.negative) { //both are positive
		if (daugiau_reiksme(other.number)) { //first-second +
			string answer;
			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());

			for (int i = 0; i < number.length(); ++i) {
				if (number[i] != '.')
					answer.push_back(number[i] - other.number[i]);
				else
					answer.push_back('.');
			}

			for (int i = 0; i < answer.length(); ++i) {
				if (answer[i] < 0 && answer[i] != '.') {
					if (answer[i + 1] != '.') {
						answer[i] += 10;
						answer[i + 1]--;
					}
					else {
						answer[i] += 10;
						answer[i + 2]--;
					}
				}
			}

			for (int i = 0; i < answer.length(); ++i)
				if (answer[i] != '.')
					answer[i] += 48;

			reverse(answer.begin(), answer.end());

			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());
			delete_zeroes();
			other.delete_zeroes();
			return my_number(answer, false);
		}
		if (maziau_reiksme(other.number)) { //second-first -
			string answer;
			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());

			for (int i = 0; i < number.length(); ++i) {
				if (number[i] != '.')
					answer.push_back(other.number[i] - number[i]);
				else
					answer.push_back('.');
			}

			for (int i = 0; i < answer.length(); ++i) {
				if (answer[i] < 0 && answer[i] != '.') {
					if (answer[i + 1] != '.') {
						answer[i] += 10;
						answer[i + 1]--;
					}
					else {
						answer[i] += 10;
						answer[i + 2]--;
					}
				}
			}

			for (int i = 0; i < answer.length(); ++i)
				if (answer[i] != '.')
					answer[i] += 48;

			reverse(answer.begin(), answer.end());

			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());
			delete_zeroes();
			other.delete_zeroes();
			return my_number(answer, true);
		}
	}

	if (negative && other.negative) { //both negative
		if (daugiau_reiksme(other.number)) { //first-second -
			string answer;
			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());

			for (int i = 0; i < number.length(); ++i) {
				if (number[i] != '.')
					answer.push_back(number[i] - other.number[i]);
				else
					answer.push_back('.');
			}

			for (int i = 0; i < answer.length(); ++i) {
				if (answer[i] < 0 && answer[i] != '.') {
					if (answer[i + 1] != '.') {
						answer[i] += 10;
						answer[i + 1]--;
					}
					else {
						answer[i] += 10;
						answer[i + 2]--;
					}
				}
			}

			for (int i = 0; i < answer.length(); ++i)
				if (answer[i] != '.')
					answer[i] += 48;

			reverse(answer.begin(), answer.end());

			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());
			delete_zeroes();
			other.delete_zeroes();
			return my_number(answer, true);
		}
		if (maziau_reiksme(other.number)) { //second-first +
			string answer;
			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());

			for (int i = 0; i < number.length(); ++i) {
				if (number[i] != '.')
					answer.push_back(other.number[i] - number[i]);
				else
					answer.push_back('.');
			}

			for (int i = 0; i < answer.length(); ++i) {
				if (answer[i] < 0 && answer[i] != '.') {
					if (answer[i + 1] != '.') {
						answer[i] += 10;
						answer[i + 1]--;
					}
					else {
						answer[i] += 10;
						answer[i + 2]--;
					}
				}
			}

			for (int i = 0; i < answer.length(); ++i)
				if (answer[i] != '.')
					answer[i] += 48;

			reverse(answer.begin(), answer.end());

			reverse(number.begin(), number.end());
			reverse(other.number.begin(), other.number.end());
			delete_zeroes();
			other.delete_zeroes();
			return my_number(answer, false);
		}
	}

	{
		string answer;
		for (int i = 0; i < number.length(); ++i) {
			if (number[i] != '.')
				answer.push_back(number[i] + other.number[i] - 2 * 48);
			else
				answer.push_back('.');
		}

		reverse(answer.begin(), answer.end());
		for (int i = 0; i < answer.length() - 1; ++i) {
			if (answer[i] >= 10 && answer[i] != '.') {
				if (answer[i + 1] != '.') {
					answer[i] -= 10;
					answer[i + 1]++;
				}
				else {
					answer[i] -= 10;
					answer[i + 2]++;
				}
			}
		}

		if (answer[answer.length() - 1] >= 10) {
			answer[answer.length() - 1] -= 10;
			answer.push_back(1);
		}

		for (int i = 0; i < answer.length(); ++i)
			if (answer[i] != '.')
				answer[i] += 48;

		reverse(answer.begin(), answer.end());

		delete_zeroes();
		other.delete_zeroes();

		if (!negative && other.negative) { //first positive, second negative, first+second +
			return my_number(answer, false);
		}

		if (negative && !other.negative) { //first negative, second positive firs+second -
			return my_number(answer, true);
		}
	}
}

my_number my_number::operator % (my_number& other) {
	int temp = 0;
	my_number copy = *this;
	while(copy>=other) {
		copy = (copy - other);
		++temp;
	}
	return copy;
}

my_number my_number::operator * (my_number& other) {
	string copy1 = number;
	string copy2 = other.number;
	reverse(copy1.begin(), copy1.end());
	reverse(copy2.begin(), copy2.end());
	int dot = copy1.find('.') + copy2.find('.');
	copy1.erase(copy1.find('.'), 1);
	copy2.erase(copy2.find('.'), 1);

	string answer;
	vector <int> ans;

	for (int i = 0; i < copy2.length() - 1; ++i)
		ans.push_back(0);

	for (int i = 0; i < copy1.length(); ++i) {
		int t = i;
		for (int j = 0; j < copy2.length(); ++j) {
			if (j + 1 == copy2.length()) ans.push_back((copy1[i] - 48) * (copy2[j] - 48));
			else ans[t] = ans[t] + (copy1[i] - 48) * (copy2[j] - 48);
			++t;
		}
	}

	for (int i = 0; i < ans.size() - 1; ++i) {
		if (ans[i] > 9) {
			ans[i + 1] = ans[i + 1] + ans[i] / 10;
			ans[i] = ans[i] % 10;
		}
	}

	int nr = ans.size() - 1;
	while (ans[nr] > 9) {
		ans.push_back(ans[nr] / 10);
		ans[nr] = ans[nr] % 10;
		++nr;
	}

	for (int i = 0; i < dot; ++i) {
		answer.push_back(ans[i] + 48);
	}
	answer.push_back('.');
	for (int i = dot; i < ans.size(); ++i) 
		answer.push_back(ans[i] + 48);
		
	reverse(answer.begin(),answer.end());
	if ((negative && !other.negative) || (!negative && other.negative))
		return my_number(answer, true);
	else
		return my_number(answer, false);
	
}

my_number my_number::operator / (my_number& other) {
	string c1 = number;
	string c2 = other.number;
	my_number copy1(c1);
	my_number copy2(c2);
	int n = max(digits_after_dot, other.digits_after_dot);
	my_number ten(10);
	my_number zero(0);
	for (int i = 0; i < n; ++i) {
		copy1 = (copy1 * ten);
		copy2 = copy2 * ten;
	}
	int times = 0;
	while (copy1 >= copy2) {
		copy1 = (copy1 - copy2);
		++times;
	}
	string answer = to_string(times);

	if (copy1 == zero) {
		answer.append(".0");
		return my_number(answer);
	}

	answer.append(".");
	int t = 0;
	while (copy1 != zero && t < FRACT) {
		
		if (copy1 < copy2)
			copy1 = copy1 * ten;
		int counting = 0;
		while (copy1 >= copy2) {
			copy1 = copy1 - copy2;
			++counting;
		}
		++t;
		answer.push_back(counting + 48);
	}
	
	if ((negative && !other.negative) || (!negative && other.negative))
		return my_number(answer, true);
	else
		return my_number(answer, false);
}


void my_number::insert_zeroes(int n) {
	for (int i = 0; i < n; ++i)
		number.push_back('0');
}

void my_number::delete_zeroes() {
	//delete in the beginning
	while (number[0] == '0')
		number.erase(0, 1);
	if (number[0] == '.') {
		reverse(number.begin(), number.end());
		number.append("0");
		reverse(number.begin(), number.end());
	}

	//delete in the end
	reverse(number.begin(), number.end());
	while (number[0] == '0')
		number.erase(0, 1);
	if (number[0] == '.') {
		reverse(number.begin(), number.end());
		number.append("0");
	}
	else
		reverse(number.begin(), number.end());

	digits_after_dot = number.length() - (number.find('.') + 1);
	dot_position = number.find('.');
}

void my_number::print() {
	cout << number << endl;
}

string my_number::get_number() const {
	string copy = number;
	if (negative) {
		reverse(copy.begin(), copy.end());
		copy.append("-");
		reverse(copy.begin(), copy.end());
	}
	return copy;
}

//digits=how many should be left
void my_number::round_by(int digits) {
	if (digits_after_dot <= digits)
		return;

	number.erase(number.begin() + number.find('.') + 2 + digits, number.end());
	
	reverse(number.begin(), number.end());
	if (number[0] >= '0' && number[0] <= '4') {
		number.erase(0, 1);
		reverse(number.begin(), number.end());
		return;
	}

	for (int i = 0; i < number.length(); ++i)
		if (number[i] != '.')
			number[i] -= 48;
	//suapvalinti
	number[1]++;
	number.erase(0, 1);
	for (int i = 0; i < number.length() - 1; ++i) {
		if (number[i] >= 10 && number[i] != '.') {
			if (number[i + 1] != '.') {
				number[i + 1]++;
				number[i] -= 10;
			}
			else if (number[i + 1] == '.') {
				number[i + 2]++;
				number[i] -= 10;
			}
		}
	}
	if (number[number.length() - 1] >= 10) {
		number[number.length() - 1] -= 10;
		number.append("1");
	}

	for (int i = 0; i < number.length(); ++i)
		if (number[i] != '.')
			number[i] += 48;
	reverse(number.begin(), number.end());
	delete_zeroes();
}

void my_number::cut() {
	if (digits_after_dot >= 110)
		number.erase(number.begin() + dot_position + 110, number.end());
}