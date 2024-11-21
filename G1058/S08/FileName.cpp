#include<iostream>
using namespace std;

class Prajitura {
	string denumire;
	int nrCalorii;
	int nrIngrediente;
	float* gramajIngrediente;
	bool esteVegana;
	float rating;//1-5
	static float pretAmbalaj;//in caz de servicii transport
	//static float gramajMinim;

public:
	Prajitura() {
		this->denumire = "-";
		this->nrCalorii = 0;
		this->nrIngrediente = 0;
		this->gramajIngrediente = nullptr;
		this->esteVegana = false;
		this->rating = 1;
	}

	//nu am primit si rating ca am zis sa exersam si constr care NU are toti param
	Prajitura(string _denumire, int _nrCalorii, int _nrIngrediente, float* _gramajIngrediente, bool _esteVegana) {
		this->denumire = _denumire;
		this->nrCalorii = _nrCalorii;
		if (_nrIngrediente > 0 && _gramajIngrediente != nullptr) {
			this->nrIngrediente = _nrIngrediente;
			this->gramajIngrediente = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->gramajIngrediente[i] = _gramajIngrediente[i];
		}
		else {
			this->nrIngrediente = 0;
			this->gramajIngrediente = nullptr;
		}
		this->esteVegana = _esteVegana;
		//nu am primit ca param si rating-ul
		this->rating = 1;
	}

	Prajitura(const Prajitura& p) {
		this->denumire = p.denumire;
		this->nrCalorii = p.nrCalorii;
		if (p.nrIngrediente > 0 && p.gramajIngrediente != nullptr) {
			this->nrIngrediente = p.nrIngrediente;
			this->gramajIngrediente = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->gramajIngrediente[i] = p.gramajIngrediente[i];
		}
		else {
			this->nrIngrediente = 0;
			this->gramajIngrediente = nullptr;
		}
		this->esteVegana = p.esteVegana;

		this->rating = p.rating;
	}

	Prajitura& operator=(const Prajitura& p) {
		if (this != &p) {
			if (this->gramajIngrediente != nullptr) {
				delete[] this->gramajIngrediente;
				this->gramajIngrediente = nullptr;
			}
			this->denumire = p.denumire;
			this->nrCalorii = p.nrCalorii;
			if (p.nrIngrediente > 0 && p.gramajIngrediente != nullptr) {
				this->nrIngrediente = p.nrIngrediente;
				this->gramajIngrediente = new float[this->nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++)
					this->gramajIngrediente[i] = p.gramajIngrediente[i];
			}
			else {
				this->nrIngrediente = 0;
				this->gramajIngrediente = nullptr;
			}
			this->esteVegana = p.esteVegana;

			this->rating = p.rating;
		}
		return *this;
	}

	Prajitura& operator*=(int x) {
		if (x > 0) {
			for (int i = 0; i < this->nrIngrediente; i++)
				this->gramajIngrediente[i] *= x;
		}
		return *this;
	}

	float getRating() {
		return this->rating;
	}

	void setRating(float _rating) {
		if (_rating >= 1 && _rating <= 5) {
			this->rating = _rating;
		}
	}

	static float getPretAmbalaj() {
		return Prajitura::pretAmbalaj;
	}

	static void setPretAmbalaj(float _pretAmbalaj) {
		if (_pretAmbalaj > 0) {
			Prajitura::pretAmbalaj = _pretAmbalaj;
		}
	}

	float getGramajTotal() {
		float rez = 0;
		for (int i = 0; i < this->nrIngrediente; i++) {
			rez += this->gramajIngrediente[i];
		}
		return rez;
	}

	~Prajitura() {
		if (this->gramajIngrediente != nullptr) {
			delete[] this->gramajIngrediente;
			this->gramajIngrediente = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const Prajitura& p) {
		out << "\nDenumire: " << p.denumire << ", nr calorii: " << p.nrCalorii;
		out << ", nr ingrediente: " << p.nrIngrediente << ", ingrediente: ";
		for (int i = 0; i < p.nrIngrediente; i++)
			out << p.gramajIngrediente[i] << " ";
		out << ", este vegana?: " << p.esteVegana << ", rating: " << p.rating;
		return out;
	}

	friend Prajitura operator+(float x, const Prajitura& p) {
		//op + NU modifica operanzii
		Prajitura rez = p;
		if (rez.gramajIngrediente != nullptr) {
			delete[] rez.gramajIngrediente;
			rez.gramajIngrediente = nullptr;
		}
		rez.gramajIngrediente = new float[rez.nrIngrediente + 1];
		for (int i = 0; i < p.nrIngrediente; i++)
			rez.gramajIngrediente[i] = p.gramajIngrediente[i];
		rez.gramajIngrediente[rez.nrIngrediente] = x;
		rez.nrIngrediente++;
		return rez;
	}
};

float Prajitura::pretAmbalaj = 5;

int main() {
	cout << "\nZona constructor fara param si get si set";
	Prajitura p1;
	cout << p1;
	p1.setRating(3);
	cout << endl << p1.getRating();
	Prajitura::setPretAmbalaj(6);
	cout << endl << Prajitura::getPretAmbalaj();
	cout << "\nZona constructor cu toti param si destructor";
	float gramaje[] = {50, 20, 40, 30};
	Prajitura p2("Amandina", 400, 4, gramaje, false);
	cout << p2;
	cout << "\nZona meth prelucrare";
	cout << endl << p2.getGramajTotal();
	cout << "\nZona constructor copiere";
	Prajitura p3(p2);
	cout << p3;
	cout << "\nZona operator atribuire";
	Prajitura p4;
	p4 = p2;
	cout << p4;
	cout << "\nZona operator *=";
	p4 *= 2;
	cout << p4;
	cout << "\nZona operator +";
	Prajitura p5;
	p5 = 123 + p4;
	cout << p5;
	Prajitura p6 = 123 + p4;//copy elision
	return 0;
}