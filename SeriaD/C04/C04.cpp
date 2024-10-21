#include<iostream>
using namespace std;

class Student {
	string nume;
	string facultate;
	int nrNote;
	int* note;//vector numeric alocat dinamic

public:
	Student() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		nume = "Anonim";
		facultate = "ASE";
		nrNote = 0;
		note = nullptr;
	}

	/*Student(string _nume) {
		cout << "\nAPEL CONSTRUCTOR CU CATIVA PARAM";
		nume = _nume;
		facultate = "ASE";
		nrNote = 0;
		note = nullptr;
	}*/

	//lista de initializatori
	/*Student(string _nume):Student() {
		cout << "\nAPEL CONSTRUCTOR CU 1 PARAM";
		nume = _nume;
	}*/

	//Student(string _nume, string _facultate, int _nrNote, int* _note) {
	//	cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
	//	nume = _nume;
	//	facultate = _facultate;
	//	if (_nrNote > 0 && _note != nullptr) {
	//		nrNote = _nrNote;
	//		//shallow copy
	//		//note = _note;//pointez spre adresa unde sunt notele
	//		//deep copy
	//		note = new int[nrNote];
	//		for (int i = 0; i < nrNote; i++)
	//			note[i] = _note[i];
	//	}
	//	else {
	//		nrNote = 0;
	//		note = nullptr;
	//	}
	//}

	Student(string _nume, string _facultate = "ASE", int _nrNote = 0, int* _note = nullptr) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		nume = _nume;
		facultate = _facultate;
		if (_nrNote > 0 && _note != nullptr) {
			nrNote = _nrNote;
			//shallow copy
			//note = _note;//pointez spre adresa unde sunt notele
			//deep copy
			note = new int[nrNote];
			for (int i = 0; i < nrNote; i++)
				note[i] = _note[i];
		}
		else {
			nrNote = 0;
			note = nullptr;
		}
	}

	Student(const Student& s) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		nume = s.nume;
		facultate = s.facultate;
		if (s.nrNote > 0 && s.note != nullptr) {
			nrNote = s.nrNote;
			//shallow copy
			//note = _note;//pointez spre adresa unde sunt notele
			//deep copy
			note = new int[nrNote];
			for (int i = 0; i < nrNote; i++)
				note[i] = s.note[i];
		}
		else {
			nrNote = 0;
			note = nullptr;
		}
	}

	void afisare() {
		cout << "\n-----------------";
		cout << "\nNume: " << nume;
		cout << "\nFacultate: " << facultate;
		cout << "\nNr note: " << nrNote;
		cout << "\nNote: ";
		for (int i = 0; i < nrNote; i++)
			cout << note[i] << " ";
		cout << "\n-----------------";
	}

	void modificareNota(int nota, int index) {
		if (index >= 0 && index < nrNote) {
			if (nota >= 1 && nota <= 10)
				note[index] = nota;
		}
	}

	~Student() {
		cout << "\nAPEL DESTRUCTOR";
		if (note != nullptr) {
			delete[] note;
			note = nullptr;
		}
	}
};

int main() {
	Student s;
	s.afisare();

	Student* ps = new Student();

	//Student s2("Gigel", "CSIE", 3, new int[3] {10, 6, 3});
	int* note = new int[3] {10, 6, 3};
	Student s2("Gigel", "CSIE", 3, note);
	//delete[] note;
	s2.afisare();

	cout << "\n-----LISTA INITIALIZATORI-----";
	Student s3("Costel");
	string nume = "Marcel";
	Student s31 = nume;//caz particular constr cu 1 param
	
	int x = 10;
	int y;
	int z(20);

	cout << "\n-----CONSTRUCTOR COMBINAT-----";
	Student s4("Gigel", "CSIE", 3, note);
	Student s5("Gigel", "CSIE");
	Student s6("Gigel");
	//Student s7;

	Student vs[10];
	vs[0].afisare();

	cout << "\n-----CONSTRUCTOR COPIERE-----";
	int xx = 2;
	int yy = xx;
	Student s9 = s4;//apel constructor de copiere
	Student s10(s4);
	s9.afisare();
	s4.afisare();
	s4.modificareNota(2, 0);
	s9.afisare();
	s4.afisare();

	//copy elision

	Student* ps2 = new Student();
	delete ps2;

	{
		Student s11;
	}

	return 0;
}