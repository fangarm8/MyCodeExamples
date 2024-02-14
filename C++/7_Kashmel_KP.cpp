#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<map>
#include<algorithm>
using namespace std;

map<string, int> month{
	pair <string, int> {" ", 0},
	pair <string, int> {"January", 1},
	pair <string, int> {"February", 2},
	pair <string, int> {"March", 3},
	pair <string, int> {"April", 4},
	pair <string, int> {"May", 5},
	pair <string, int> {"June", 6},
	pair <string, int> {"July", 7},
	pair <string, int> {"August", 8},
	pair <string, int> {"September", 9},
	pair <string, int> {"October", 10},
	pair <string, int> {"November", 11},
	pair <string, int> {"December", 12},
};

int step(int a, unsigned int b) {
	if (b == 0) return 1;
	int c = 1;
	while (b != 0) {
		if (b % 2 == 1) {
			c = c * a;
			b--;
		}
		a = a * a;
		b = b / 2;
	}
	return c;
}

unsigned int CountDegits(unsigned int a) {
	unsigned int count = 0;

	while (a > 0) {
		a = a / 10;
		count++;
	}
	return count;
}

unsigned int SumDegits(unsigned int num) {
	unsigned int ans = 0;
	while (num > 0) {
		ans += num % 10;
		num /= 10;
	}
	return ans;
}

struct Date {
	unsigned int Day;
	string MonthSTR;
	unsigned int Year;
	unsigned int MonthINT = month[MonthSTR];

	Date& operator=(const Date& date) {
		this->Day = date.Day;
		this->MonthSTR = date.MonthSTR;
		this->Year = date.Year;
		this->MonthINT = month[MonthSTR];
		return *this;
	}

	Date() {
		Day = 0;
		MonthSTR = " ";
		Year = 0;
		MonthINT = month[MonthSTR];
	}

	Date(unsigned int day, string monthSTR, unsigned int year) {
		Day = day;
		MonthSTR = monthSTR;
		Year = year;
		MonthINT = month[monthSTR];
	}
};

struct Person {
	string Name;
	Date Birth;
	unsigned int Day;
	unsigned int age;
	unsigned int sumDay;
	unsigned int CRS;

	Person() {
		Name = " ";
		Birth = Date();
		Day = 0;
		age = 0;
		sumDay = 0;
		CRS = 0;
	}

	Person(string name, Date birth) {
		Name = name;
		Birth = birth;
		Day = 0;
		age = 0;
		sumDay = 0;
		CRS = 0;
	}

	Person& operator=(const Person& pers) {
		Name = pers.Name;
		Birth = pers.Birth;
		Day = pers.Day;
		age = pers.age;
		sumDay = pers.Day;
		CRS = pers.CRS;
		return *this;
	}

	friend ostream& operator<<(ostream& out, Person pers) {
		out << pers.Name << " " << pers.Birth.Day << "." << pers.Birth.MonthINT << "." << pers.Birth.Year << " " << pers.age << " " << pers.CRS;
		return out;
	}
};

class TPerson {
	int WorkersCount;
	vector<Person> Workers;
public:
	TPerson() {
		WorkersCount = 0;
	}
	~TPerson() {}

	unsigned int getWorkersCount() {
		return WorkersCount;
	}

	void AddWorker(Person noob) {
		Workers.push_back(noob);
		WorkersCount++;
	}

	void date(Person& pers) {
		pers.Day = pers.Birth.Year + pers.Birth.MonthINT * step(10, 4) + pers.Birth.Day * step(10, 6);
		pers.age = 2024 - pers.Birth.Year;
		pers.sumDay = SumDegits(pers.Day);
	}

	void Curious(Person &pers) {
		date(pers);
		unsigned int sumsumDay = SumDegits(pers.sumDay);
		int B = pers.sumDay - (pers.Day / step(10, 8) * 2);
		unsigned int sumB = SumDegits(B);
		pers.CRS = sumB + B * step(10, CountDegits(sumB)) + sumsumDay * step(10, CountDegits(sumB) + CountDegits(B)) + pers.sumDay * step(10, CountDegits(sumB) + CountDegits(B) + CountDegits(sumsumDay));
	}

	friend ifstream& operator>>(ifstream& in, TPerson& person) {
		string input, input_copy;
		while (!in.eof()) {
			getline(in, input);
			input_copy = input;

			for (int i = 0; i < 3; i++)
				input.erase(input.rfind(" "), input.size() - input.rfind(" "));

			input_copy.erase(0, input.size() + 1);
			string nametmp = input;
			unsigned int day = stoi(input_copy.substr(0, input_copy.find(' ')));
			unsigned int year = stoi(input_copy.substr(input_copy.rfind(' '), input_copy.size() - input_copy.rfind(' ')));
			string monthSTR = input_copy.substr(input_copy.find(' ') + 1, input_copy.rfind(' ') - input_copy.find(' ') - 1);
			Date birth =  Date(day, monthSTR, year);
			Person noob = Person(nametmp, birth);
			Person *noobptr = &noob;
			person.Curious(*noobptr);
			person.AddWorker(noob);
		}
		return in;
	}

	friend ostream& operator<<(ostream& out, TPerson& person) {
		for (int i = 0; i < person.getWorkersCount(); i++) {
			out << person.Workers[i] << endl;
		}
		return out;
	}
	

};

int main()
{
	ifstream in("EnName.txt");
	ofstream out("Task.txt");
	TPerson solution;
	in >> solution;
	out << solution;
}


