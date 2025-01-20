#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<map>

using namespace std;

namespace TEST {
	int variabilaTEST = 10;
}

namespace TEST2 {
	int variabilaTEST = 20;
}

using namespace TEST2;
//using namespace TEST;

class Student {
public:
	string nume=" ";
	float medie=0;

	Student() {

	}

	Student(string _nume, float _medie) {
		this->nume = _nume;
		this->medie = _medie;
	}

	friend ostream& operator<<(ostream& out, const Student& s) {
		out << "\nNume: " << s.nume << ", Medie: " << s.medie;
		return out;
	}

	bool operator<(const Student& s) const {
		return this->nume < s.nume;
	}
};

int main() {
	std::cout << TEST::variabilaTEST << std::endl;
	cout << TEST2::variabilaTEST << endl;
	cout << variabilaTEST << endl;

	//STL
	//faciliteaza lucrul cu structuri de date
	//vector
	vector<int> vInt;
	vInt.push_back(10);
	vInt.push_back(12);
	vInt.push_back(15);
	vInt[0] = 123;
	for (int i = 0; i < vInt.size(); i++) {
		cout << vInt[i]<<" ";
	}
	cout << "\nAfisare vector: ";
	vector<int>::iterator itInt;
	for (itInt = vInt.begin(); itInt != vInt.end(); itInt++) {
		cout << *itInt << " ";
	}

	//list
	list<float> listFloat;
	listFloat.push_back(10);
	listFloat.push_front(20);
	listFloat.push_front(30);

	//iterator
	cout << "\nAfisare lista: ";
	list<float>::iterator it;
	for (it = listFloat.begin(); it != listFloat.end(); it++) {
		cout << *it << " ";
	}

	//set
	set<string> setString;
	setString.insert("Zaharia Ionut");
	setString.insert("Ionescu Marcela");
	setString.insert("Popescu Monica");
	setString.insert("Ionescu Marcela");

	cout << "\nAfisare set: ";
	set<string>::iterator itSet;
	for (itSet = setString.begin(); itSet != setString.end(); itSet++) {
		cout << *itSet << endl;
	}

	cout << "\nAfisare set (reverse): ";
	set<string>::reverse_iterator rItSet;
	for (rItSet = setString.rbegin(); rItSet != setString.rend(); 
		rItSet++) {
		cout << *rItSet << endl;
	}

	itSet = setString.find("Ionescu Marcela");
	if (itSet != setString.end()) {
		cout << endl << "S-a gasit!!!";
		cout << endl << *itSet;
	}
	else {
		cout << "\nNu s-a gasit";
	}

	Student s1("Gigel", 9.8);
	Student s2("Costel", 9.7);
	Student s3("Maria", 9.7);
	Student s4("Gigel", 9.5);

	set<Student> setStud;
	setStud.insert(s1);
	setStud.insert(s2);
	setStud.insert(s3);
	setStud.insert(s4);


	cout << "\n\n\nAfisare set (Student): ";
	set<Student>::iterator itSet2;
	for (itSet2 = setStud.begin(); itSet2 != setStud.end(); itSet2++) {
		cout << *itSet2;
	}

	//map
	map<int, Student> mapStud;
	mapStud[0] = s1;
	mapStud[134] = s2;
	mapStud[134] = s1;
	mapStud.insert(pair<int,Student>(5, s3));

	cout << "\n\nParcurgere map:";
	map<int, Student>::iterator itMap;
	for (itMap = mapStud.begin(); itMap != mapStud.end(); itMap++) {
		cout << "\ncheie: " << (*itMap).first;
		cout << "\nvaloare: " << itMap->second;
	}

	//introduceti stl-ul set intr-o clasa tip container care permite unicitate
	//implementare de clasa care sa permita stocarea de persoane in context de unicitate si pentru fiecare persoana masinile detinute in caracter de unicitate
	map<Student, set<Student>> test;
	return 0;
}



