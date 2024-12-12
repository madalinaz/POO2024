#include<iostream>
using namespace std;

//design pattern-ul composite

class Cutie {
	string material="Carton";
	float greutate=0;

public:
	Cutie() {
	}

	Cutie(string _material, float _greutate) {
		this->material = _material;
		this->greutate = _greutate;
	}

	Cutie(const Cutie& c) {
		this->material = c.material;
		this->greutate = c.greutate;
	}

	Cutie& operator=(const Cutie& c) {
		if (this != &c) {
			this->material = c.material;
			this->greutate = c.greutate;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Cutie& c) {
		out << "\nMaterial: " << c.material;
		out << "\nGreutate: " << c.greutate;
		return out;
	}
};

//Container is a Cutie
//Container has a lista de cutii

class Container: public Cutie {
	string adresaLivrare;
	int nrCutii;
	Cutie* listaCutii[100];
	float greutateMaximaAdmisa;

public:
	//constructor fara param
	//contructor cu param mai putin vector + dim
	// contructor copiere
	// op=
	// destructor
	// ostream
	//op += care adauga o noua Cutie + verif pentru greutate + aruncare de exception
	//constructor cu toti param
	//set si get 
	//get pe vector 
	//get pe un elem din vector get(index)
	//get pe dim vector
	//set vector + dim
};

int main() {
	return 0;
}