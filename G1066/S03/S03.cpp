#include<iostream>
using namespace std;

class Student {
private:
	//atribute
	string nume;
	char* facultate;
	char serie;
	int anStudiu;
	int nrNote;
	int* note;//vector alocat dinamic

public:
	//metode
	// metode tip constructor
	Student(string nume, const char* facultate, char serie, int anStudiu, int nrNote, int* note) {
		//pointerul this
		//this este adresa obj apelator
		this->nume = nume;
		if (facultate != nullptr) {
			this->facultate = new char[strlen(facultate) + 1];
			strcpy_s(this->facultate, strlen(facultate) + 1, facultate);
		}
		else {
			this->facultate = nullptr;
		}
		this->serie = serie;
		this->anStudiu = anStudiu;
		if (note != nullptr && nrNote > 0) {
			this->nrNote = nrNote;
			//this->note = note; shallow copy
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = note[i];
		}
		else {
			this->note = nullptr;
		}

	}
	//metode tip accesor (get si set)
	int getAnStudiu() {
		return anStudiu;
	}

	void setAnStudiu(int anStudiuNou) {
		if (anStudiuNou >= 1 && anStudiuNou <= 5) {
			anStudiu = anStudiuNou;
		}
		else {
			cout << "\nAn Studiu nu este conform";
		}
	}

	void setFacultate(const char* facultateNoua) {
		if (facultateNoua != nullptr && strlen(facultateNoua) >= 3) {
			if (facultate != nullptr) {
				delete[] facultate;
				facultate = nullptr;
			}
			facultate = new char[strlen(facultateNoua) + 1];
			strcpy_s(facultate, strlen(facultateNoua) + 1, facultateNoua);
		}
	}

	const char* getFacultate1() {
		return facultate;
	}

	char* getFacultate2() {
		char* copieFacultate = nullptr;
		if (facultate != nullptr) {
			copieFacultate = new char[strlen(facultate) + 1];
			strcpy_s(copieFacultate, strlen(facultate) + 1, facultate);
		}
		return copieFacultate;
	}
};

int main() {
	int note[] = { 10,7,4 };
	Student s("Gigel", "CSIE", 'A', 2, 3, note);
	cout << s.getAnStudiu();//s este obj apelator 
	s.setAnStudiu(3);
	cout << endl << s.getAnStudiu();
	s.setFacultate("CSIE");
	char facultate[] = "FABIZ";
	s.setFacultate(facultate);
	cout << endl << s.getFacultate1();
	//s.getFacultate1()[0] = 'M';
	cout << endl << s.getFacultate1();

	cout << endl << s.getFacultate2();//memory leaks
	char* facultateCopie = s.getFacultate2();
	delete[] facultateCopie;
	facultateCopie = nullptr;

	return 0;
}