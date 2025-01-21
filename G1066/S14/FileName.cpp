#include<iostream>
using namespace std;

class Student {
	string nume = "Anonim";
	int nrNote = 0;
	int* note = nullptr;

public:
	Student() {
	}

	Student(string _nume, int _nrNote, int* _note) {
		this->nume = _nume;
		if (_nrNote > 0 && _note != nullptr) {
			this->nrNote = _nrNote;
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = _note[i];
		}
	}

	Student(const Student& s) {
		this->nume = s.nume;
		if (s.nrNote > 0 && s.note != nullptr) {
			this->nrNote = s.nrNote;
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = s.note[i];
		}
	}

	Student& operator=(const Student& s) {
		if (this != &s) {
			if (this->note != nullptr) {
				delete[] this->note;
				this->note = nullptr;
			}
			this->nume = s.nume;
			if (s.nrNote > 0 && s.note != nullptr) {
				this->nrNote = s.nrNote;
				this->note = new int[this->nrNote];
				for (int i = 0; i < this->nrNote; i++)
					this->note[i] = s.note[i];
			}
			else {
				this->nrNote = 0;
				this->note = nullptr;
			}
		}
		return *this;
	}

	~Student() {
		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const Student& s) {
		out << "\nNume: " << s.nume;
		out << "\nNr note: " << s.nrNote;
		out << "\nNote: ";
		for (int i = 0; i < s.nrNote; i++)
			out << s.note[i] << " ";
		return out;
	}

	friend istream& operator>>(istream& in, Student& s) {
		cout << "\nIntroduceti nume: ";
		in >> s.nume;
		if (s.note != nullptr) {
			delete[] s.note;
			s.note = nullptr;
		}
		cout << "Introduceti nr note: ";
		in >> s.nrNote;
		if (s.nrNote < 0) {
			s.nrNote = 0;
			s.note = nullptr;
		}
		else {
			s.note = new int[s.nrNote];
			cout << "Introduceti note:\n";
			for (int i = 0; i < s.nrNote; i++)
				in >> s.note[i];
		}
		return in;
	}
};

int main() {
	Student s;
	cout << s;
	cin >> s;
	cout << s;

	int note[] = { 10,9,8,5,4,10 };
	Student s1("Gigel", 6, note);
	cout << s1;
	return 0;
}