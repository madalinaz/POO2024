#include<iostream>
#include<set>
#include<list>
using namespace std;

class Animal {
public:
	int nrPicioare;
	virtual void getInfo() {
		cout << "\nSunt animal";
	}

	bool operator<(const Animal& a) const {
		return this->nrPicioare < a.nrPicioare;
	}

	//sau un cast la int
	//functie globala
	//functie globala vs functie statica

	friend class Zoo;
};

void functieGlobala() {
	cout << "\nSunt globala";
}

class Pisica : public Animal {
public:
	int nrVieti;
	void getInfo() override {
		cout << "\nSunt pisica";
	}
};

class Zoo {
	set<Animal> colectieAnimale;
	//list<Animal> listaAnimale;

public:
	Zoo() {
		//nu am ce initializa pentru set
	}

	Zoo& operator+=(Animal a) {
		this->colectieAnimale.insert(a);
		//listaAnimale.push_back(a);
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Zoo& z) {
		out << "\nZoo";
		set<Animal>::iterator it;
		for (it = z.colectieAnimale.begin(); it != z.colectieAnimale.end(); it++) {
			out << endl << it->nrPicioare;
		}
		return out;
	}
};

int main() {
	Animal a;
	Pisica p;
	a = p;//upcast
	a.getInfo();

	Animal* pa = new Animal();
	pa = &p;
	pa->getInfo();

	Zoo zoo;
	zoo += a;
	zoo += a;
	cout << zoo;
	return 0;
}