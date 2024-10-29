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
			this->note = new int[this->nrNote];//alocare zm
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = _note[i];
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
};

int main() {
	Student s;
	return 0;
}