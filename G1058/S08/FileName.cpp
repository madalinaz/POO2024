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
	Prajitura(string _denumire, int _nrCalorii, int _nrIngrediente, float* _gramajIngrediente, bool _esteVegan) {
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
		this->esteVegana = _esteVegan;
		//nu am primit ca param si rating-ul
		this->rating = 1;
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


};

float Prajitura::pretAmbalaj = 5;

int main() {
	cout << "\nZona constructor fara param si get si set";
	Prajitura p1;
	p1.setRating(3);
	cout << endl << p1.getRating();
	Prajitura::setPretAmbalaj(6);
	cout << endl << Prajitura::getPretAmbalaj();
	cout << "\nConstructor cu toti param si destructor";
	return 0;
}