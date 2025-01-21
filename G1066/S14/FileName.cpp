#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<set>
#include<map>
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

	//ne trebuie aceasta forma pentru op de comparatie la set
	bool operator<(const Student& s) const{//de fapt declar ca si this este const
		return this->nume < s.nume;
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

	cout << "\n------------------STL------------";
	cout << "\n------------------VECTOR------------";
	vector<int> vInt;
	vInt.push_back(10);
	vInt.push_back(20);
	vInt.push_back(30);
	vInt.push_back(40);

	//si aici se poate cu iterator, precum la list,set,map
	cout << "\nAfisare vector de int: ";
	for (int i = 0; i < vInt.size(); i++)//folosesc index pentru ca este zona de memorie contigua
		cout << vInt[i] << " ";
	cout << "\n------------------LIST------------";
	list<float> lFloat;
	lFloat.push_back(20);
	lFloat.push_front(10);
	lFloat.push_front(30);
	lFloat.push_back(40);

	cout << "\nAfisare lista de float: ";
	list<float>::iterator itList;
	for (itList = lFloat.begin(); itList != lFloat.end(); itList++) {
		cout << *itList << " ";
	}
	cout << "\n------------------SET------------";
	set<string> sString;
	sString.insert("Popescu Maria");
	sString.insert("Ionescu Marcel");
	sString.insert("Ivanca Dorina");
	sString.insert("Popescu Maria");

	cout << "\nAfisare set de string: ";
	set<string>::iterator itSet;
	for (itSet = sString.begin(); itSet != sString.end(); itSet++) {
		cout << *itSet << "* ";
	}

	cout << "\nAfisare set de string (invers): ";
	set<string>::reverse_iterator itSet2;
	for (itSet2 = sString.rbegin(); itSet2 != sString.rend(); itSet2++) {
		cout << *itSet2 << "* ";
	}

	cout << "\nProcedura cautare: ";
	itSet = sString.find("Ivanca Dorina");
	if (itSet != sString.end()) {
		cout << "\nS-a gasit ceea ce cautam!";
		cout << *itSet;
	}
	else {
		cout << "\nNu s-a gasit informatia cautata";
	}
	cout << "\n------------------SET STUDENT------------";
	//folosesc acelasi vector de note dar preiau doar 3/2/4/5 elem din el
	Student s12("Gigel", 3, note);
	Student s13("Costel", 2, note);
	Student s14("Marcel", 4, note);
	Student s15("Maria", 5, note);
	set<Student> sStud;
	sStud.insert(s12);//fct insert apeleaza op< pentru a compara obj intre ele
	sStud.insert(s13);
	sStud.insert(s14);
	cout << "\n------------------MAP------------";
	map<int, Student> mStud; //stochez Studenti iar cautarea lor se face pe baza unei chei de tip int
	mStud[0] = s12;
	mStud[134] = s14;//134 este cheia
	mStud[13] = s12;
	mStud.insert(pair<int, Student>(13, s15));//sau asa putem face inserarea in map

	map<int, Student>::iterator itMap;
	cout << "\nAfisare map de Student: ";
	for (itMap = mStud.begin(); itMap != mStud.end(); itMap++) {
		cout << itMap->first << "//" << itMap->second << endl;
	}

	//extinderi pentru examen
	//clasa Student, Materie/Disciplina
	//modelez relatia dintre studenti si disciplinele la care sunt restanti/pe care le-au ales ca optionale
	//astfel incat sa am unicitate pe studenti la nivelul unui an universitar
	//sa am lista disciplinelor alese de Student iar in lista sa am unicitate
	//map<Student, set<Disciplina>> structuraAn; (hint de implementare)
	return 0;
}