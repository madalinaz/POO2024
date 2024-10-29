#include<iostream>
using namespace std;


class Student {
	
	string nume;
	string facultate;
	int* note;
	int nrNote;
	//int pctCredit[100];//alocare statica, nu este membru static
	static float taxaRestanta;//nu incarca sizeof(Student)
	//alte ex atribute statice: ptr validari/restrictii
	//alte ex atribute statice: variabila tip contor la nivelul clasei care contorizeaza nr de obj construite

public:
	const int codMatricol; //declarare care se poate face si in zona public pentru ca e protejat ca este constant si nu poate fi modificat 

	Student():codMatricol(0) {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		//this->codMatricol = 0; too late
		this->nume = "Anonim";
		this->facultate = "ASE";
		this->note = nullptr;
		this->nrNote = 0;
	}

	Student(int _codMatricol, string _nume, string _facultate, int* _note, int _nrNote):codMatricol(_codMatricol) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		this->nume = _nume;
		this->facultate = _facultate;
		//this->note = _note;//copiere superficiala (shallow copy)
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

	Student(const Student& s):codMatricol(s.codMatricol) {
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

	//la op= nu se gestioneaza atributul constant pentru ca this deja exista, deci deja am init atributul const
	//returnam obj prin referinta pentru a optimiza apelul (nu se mai construieste si apoi distruge obj returnat)
	Student& operator=(const Student& s) {
		//este o "combinatie" intre destructor si constructor de copiere
		//obj this deja exista, atunci face dezalocare inainte de modificare in functie de s
		//if-ul nu este pentru a optimiza si evita copierea "degeaba"
		//if-ul este pentru a nu dezaloca right value atunci cand dezaloc left value
		if (this != &s) {
			if (this->note != nullptr) {
				delete[] this->note;
				this->note = nullptr;
			}
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
		return *this;//intoarce obj actualizat (care se gaseste la dereferentierea lui this)
	}

	//meth obligatoriu inline
	void afisare() {
		cout << "\n^^^^^^^^^^^^^^^^^^^^^";
		cout << "\nCod matricol: " << this->codMatricol;
		cout << "\nNume: " << this->nume;
		cout << "\nFacultate: " << this->facultate;
		cout << "\nNr note: " << this->nrNote;
		cout << "\nNote: ";
		for (int i = 0; i < this->nrNote; i++)
			cout << this->note[i] << " ";
		cout << "\n^^^^^^^^^^^^^^^^^^^^^";
	}

	void afisare2();//antetul metodei care nu este metoda inline
	void afisare3();//meth a devenit inline folosind cuvantul cheie inline

	float getCostTotalRestante() {
		//cat il consta pe student ca sa isi plateasca toate restantele
		int nr = 0;
		for (int i = 0; i < this->nrNote; i++)
			if (this->note[i] < 5)
				nr++;
		return nr * Student::taxaRestanta;
	}

	//metode accesor pentru atribut static taxaRestanta
	static float getTaxaRestanta() {
		return Student::taxaRestanta;//recomandare: atributele statice le accesati folosind op de rezolutie :: plecand de la numele clasei(Student)
	}

	static void setTaxaRestanta(float _taxaRestanta) {
		if (_taxaRestanta > 0) {
			//o metoda statica nu are this, pentru ca nu este a unui obiect
			Student::taxaRestanta = _taxaRestanta;
		}
	}

	~Student() {
		cout << "\nAPEL DESTRUCTOR";
		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}
	}
};

float Student::taxaRestanta = 100;//obligatorie ca sa nu primit eroare de linkeditare

void Student::afisare2() {
	cout << "\n^^^^^^^^^^^^^^^^^^^^^";
	cout << "\nNume: " << this->nume;
	cout << "\nFacultate: " << this->facultate;
	cout << "\nNr note: " << this->nrNote;
	cout << "\n^^^^^^^^^^^^^^^^^^^^^";
}

inline void Student::afisare3() {
	cout << "\n^^^^^^^^^^^^^^^^^^^^^";
	cout << "\nNume: " << this->nume;
	cout << "\nFacultate: " << this->facultate;
	cout << "\n^^^^^^^^^^^^^^^^^^^^^";
}


int main() {
	Student s;
	int note[] = { 10,5,3,7 };
	Student s2(123, "Gigel", "CSIE", note, 4);
	s2.afisare();
	Student s3(s2);
	s3.afisare();
	s3.afisare2();

	cout << "\n\nATRIBUT CONSTANT";
	cout << endl << s3.codMatricol;//folosit pentru consultare (right value)
	//s3.codMatricol = 109; dar nu poate fi folosit ca lvalue (left value), adica nu poate fi modificat

	cout << "\n\nATRIBUTE + METODE STATICE";
	cout << endl<<s3.getTaxaRestanta();//POT, dar nu recomand
	cout << endl << Student::getTaxaRestanta();//ca sa evidentiem faptul ca avem o metoda statica, metoda a clasei, si nu a unui obj anume/particular
	Student::setTaxaRestanta(120);
	cout << endl << Student::getTaxaRestanta();

	Student s4(s3);//apel constructor de copiere (construiesc obj nou pe baza unui obj existent)

	s = s4;//nu este constructor de copiere
	s.operator=(s4); //forma explicita de apel a operatorului =
	s.afisare();

	int x, y, z;
	x = y = z = 2;//apel in cascada a operatorului =(atribuire)
	x = x;//auto-atribuire
	cout << endl << x;

	s2 = s3 = s4;//daca vrem op= sa se apeleze in cascada sau in compunere cu alti op, atunci NU trebuie sa intoarca void
	s2 = s2;
	s2.afisare();


	return 0;
}