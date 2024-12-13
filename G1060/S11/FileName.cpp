#include <iostream>
using namespace std;

// design pattern composite
class Cutie {
	string material = "carton";
	float greutate = 0;

public:
	Cutie() {}

	Cutie(string _material, float _greutate) : material(_material), greutate(_greutate) {

	}

	Cutie(const Cutie& c) {
		this->material = c.material;
		this->greutate = c.greutate;
	}

	float getGreutate() {
		return this->greutate;
	}

	void setGreutate(float _greutate) {
		this->greutate = _greutate;
	}

	Cutie& operator=(const Cutie& c) {
		if (this == &c)
			return *this;
		this->material = c.material;
		this->greutate = c.greutate;
		return *this;
	}

	friend ostream& operator<<(ostream& out, Cutie c) {
		out << c.material << " " << c.greutate;
		return out;
	}
};

// Container is a Cutie
// Container has a list of Cutie
class Container : public Cutie {
	string adresaLivrare;
	int nrCutii;
	Cutie* listaCutii[100];
	float greutateMaximaAdmisa;
public:
	// constructor fara param
	Container() : Cutie() {
		this->adresaLivrare = "null";
		this->nrCutii = 0;
		this->greutateMaximaAdmisa = 0;
	}
	// constructor cu param, fara vect si sim
	Container(string _material, float _greutate, string _adresaLivrare, float _greutateMaximaAdmisa) : Cutie(_material, _greutate) {
		this->adresaLivrare = _adresaLivrare;
		this->nrCutii = 0;
		this->greutateMaximaAdmisa = _greutateMaximaAdmisa;
	}
	// constructor copiere
	Container(const Container& c) : Cutie(c) {
		this->adresaLivrare = c.adresaLivrare;
		this->greutateMaximaAdmisa = c.greutateMaximaAdmisa;
		if (c.nrCutii <= 0)
			this->nrCutii = 0;
		else {
			this->nrCutii = c.nrCutii;
			for (int i = 0; i < this->nrCutii; i++)
				this->listaCutii[i] = new Cutie(*c.listaCutii[i]);
		}


	}

	// destructor
	~Container() {
		if (this->nrCutii > 0) {
			for (int i = 0; i < this->nrCutii; i++) {
				delete this->listaCutii[i];
				this->listaCutii[i] = nullptr;
			}
		}
	}
	// op=
	Container& operator=(Container c) {
		if (this == &c)
			return *this;

		Cutie::operator=(c);
		if (this->nrCutii > 0) {
			for (int i = 0; i < this->nrCutii; i++) {
				delete this->listaCutii[i];
				this->listaCutii[i] = nullptr;
			}
		}
		this->adresaLivrare = c.adresaLivrare;
		this->greutateMaximaAdmisa = c.greutateMaximaAdmisa;
		if (c.nrCutii <= 0)
			this->nrCutii = 0;
		else {
			this->nrCutii = c.nrCutii;
			for (int i = 0; i < this->nrCutii; i++)
				this->listaCutii[i] = new Cutie(*c.listaCutii[i]);
		}
	}
	// ostream
	friend ostream& operator<<(ostream& out, const Container& c) {
		out << " " << c.adresaLivrare << " " << c.greutateMaximaAdmisa << " " << c.nrCutii << " ";
		for (int i = 0; i < c.nrCutii; i++)
			out << *c.listaCutii[i];
		return out;
	}

	// getter greutate suprascris
	float getGreutate() {
		float sum = 0;
		for (int i = 0; i < this->nrCutii; i++)
			sum += this->listaCutii[i]->getGreutate();
		return sum;
	}

	// op+= - adauga o noua cutie si verifica pentru greutate maxima admisa, arunca exceptie
	void operator+=(Cutie c) {
		if (this->nrCutii >= 99)
			throw new exception("deja full - nr cutii");

		if (this->getGreutate() + c.getGreutate() > this->greutateMaximaAdmisa)
			throw new exception("deja full - greutate");

		this->listaCutii[this->nrCutii] = new Cutie(c);
		this->nrCutii++;

	}
};



int main() {
	Cutie c1("carton", 2);
	Cutie c2("plastic", 10);
	Container container("metal", 20, "China", 200);
	container += c1;
	container += c2;
	cout << container;
	return 0;
}