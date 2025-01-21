#include<iostream>
#include<fstream>
using namespace std;

class Student {
	string nume = "Anonim";//char*
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

	//serializare
	void writeToFile(fstream& f) {
		//scriere string in fisier binar
		//1. scriere lungime sir
		int lg = this->nume.length() + 1;
		f.write((char*) & lg, sizeof(int));
		//2. scriere sir de caractere (continutul string-ului)
		f.write(this->nume.data(), lg);//meth data este echivalent cu un getter pe char*

		//scriere int in fisier binar
		//nr note ale unui student
		f.write((char*) & this->nrNote, sizeof(int));

		//scriere vector de int-uri
		//vectorul de note ale studentului
		for (int i = 0; i < this->nrNote; i++) {
			f.write((char*) & this->note[i], sizeof(int));
		}
	}

	//deserializare
	void readFromFile(fstream& f) {
		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}

		//citire string din fisier binar
		//1.citire lungime
		int lg;
		f.read((char*) & lg, sizeof(int));
		//2.citire sir de caractere
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->nume = buffer;
		
		//citire int(nr note)
		f.read((char*) & this->nrNote, sizeof(int));
		/*if (this->nrNote < 0) {
			this->nrNote = 0;
			this->note = nullptr;
		}*/
		
		//citire vector de note
		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++) {
			f.read((char*) & this->note[i], sizeof(int));
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

	friend ofstream& operator<<(ofstream& out, const Student& s) {
		out << s.nume;
		out << endl<<s.nrNote;
		out << endl;
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

	friend ifstream& operator>>(ifstream& in, Student& s) {
		in >> s.nume;
		if (s.note != nullptr) {
			delete[] s.note;
			s.note = nullptr;
		}
		in >> s.nrNote;
		if (s.nrNote < 0) {
			s.nrNote = 0;
			s.note = nullptr;
		}
		else {
			s.note = new int[s.nrNote];
			for (int i = 0; i < s.nrNote; i++)
				in >> s.note[i];
		}
		return in;
	}
};

int main() {
	Student s;
	cout << s;
	//cin >> s;
	cout << s;

	int note[] = { 10,9,8,5,4,10 };
	Student s1("Gigel", 6, note);
	cout << s1;

	cout << "\n------------------FISIERE TEXT------------";
	//fisier pentru scriere
	ofstream g("studenti.txt");
	g << s1;//ofstream is a ostream // s-a apelat la un upcast
	g.close();
	ifstream f("studenti.txt");
	f >> s; //ifstream is a istream //upcast
	cout << s;

	//rapoarte text
	//1. sa se afiseze intr-un fisier toti studentii integralisti (filtrari)
	//2. sa se afiseze media notelor tuturor studentilor de la specializarea....(agregare)
	
	
	cout << "\n------------------FISIERE BINARE------------";
	//conceptul de serializare si deserializare
	//avem un obj de tip Student =>serie de octeti =>fisierul binar

	/*fstream fileOut("colectie.bin", ios::out | ios::binary);
	s1.writeToFile(fileOut);
	fileOut.close();*/

	fstream fileIn("colectie.bin", ios::in | ios::binary);
	Student sNou;
	sNou.readFromFile(fileIn);
	fileIn.close();
	cout << sNou;
	return 0;
}