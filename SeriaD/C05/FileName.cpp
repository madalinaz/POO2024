#include<iostream>
using namespace std;

class Student {
	string nume;
	string facultate;
	int* note;
	int nrNote;

public:
	Student() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		this->nume = "Anonim";
		this->facultate = "ASE";
		this->note = nullptr;
		this->nrNote = 0;
	}

	Student(string _nume, string _facultate, int* _note, int _nrNote) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		this->nume = _nume;
		this->facultate = _facultate;
		if (_note != nullptr && _nrNote > 0) {
			this->nrNote = _nrNote;
			this->note = new int[this->nrNote];//alocare zm pe heap
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = _note[i];
		}
		else {
			this->nrNote = 0;
			this->note = nullptr;
		}
	}

	Student(const Student& s) {
		cout << "\nAPEL CONSTRUCTOR COPIERE";
		this->nume = s.nume;
		this->facultate = s.facultate;
		if (s.note != nullptr && s.nrNote > 0) {
			this->nrNote = s.nrNote;
			this->note = new int[this->nrNote];//alocare zm pe heap
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = s.note[i];
		}
		else {
			this->nrNote = 0;
			this->note = nullptr;
		}
	}

	void afisare() {
		cout << "\n^^^^^^^^^^^^^^^^^^^^^";
		cout << "\nNume: " << this->nume;
		cout << "\nFacultate: " << this->facultate;
		cout << "\nNr note: " << this->nrNote;
		cout << "\nNote: ";
		for (int i = 0; i < this->nrNote; i++)
			cout << this->note[i] << " ";
		cout << "\n^^^^^^^^^^^^^^^^^^^^^";
	}

	void afisare2();//antetul metodei care nu este metoda inline
	void afisare3();

	~Student() {
		cout << "\nAPEL DESTRUCTOR";
		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}
	}
};

void Student::afisare2() {
	cout << "\n^^^^^^^^^^^^^^^^^^^^^";
	cout << "\nNume: " << this->nume;
	cout << "\nFacultate: " << this->facultate;
	cout << "\nNr note: " << this->nrNote;
	cout << "\n^^^^^^^^^^^^^^^^^^^^^";
}

void Student::afisare3() {
	cout << "\n^^^^^^^^^^^^^^^^^^^^^";
	cout << "\nNume: " << this->nume;
	cout << "\nFacultate: " << this->facultate;
	cout << "\n^^^^^^^^^^^^^^^^^^^^^";
}

int main() {
	Student s;
	int note[] = { 10,5,3,7 };
	Student s2("Gigel", "CSIE", note, 4);
	s2.afisare();
	Student s3(s2);
	s3.afisare();
	s3.afisare2();
	return 0;
}