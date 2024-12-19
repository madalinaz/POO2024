#include<iostream>
using namespace std;

enum TipCombustibil {
	BENZINA95, BENZINA98, MOTORINA
};

class Rezervor {
	TipCombustibil tipCombustibil;
	float capacitateMaxima;
	float capacitateCurenta; //nivelCurent

public:
	Rezervor(){
		this->tipCombustibil = BENZINA95;
		this->capacitateCurenta = 0;
		this->capacitateMaxima = 0;
	}

	Rezervor(TipCombustibil _tipCombustibil, float _capacitateMaxima, float _capacitateCurenta) {
		this->tipCombustibil = _tipCombustibil;
		this->capacitateMaxima = _capacitateMaxima;
		this->capacitateCurenta = _capacitateCurenta;
	}

	friend ostream& operator<<(ostream& out, const Rezervor& r) {
		out << "\nRezervor tip " << r.tipCombustibil << ", capacitate curenta: " << r.capacitateCurenta;
		out << ", capacitate maxima: " << r.capacitateMaxima;
		return out;
	}
	//op +=
	Rezervor& operator+=(float _cantitate) {
		if (_cantitate > 0 && _cantitate + this->capacitateCurenta <= this->capacitateMaxima) {
			this->capacitateCurenta += _cantitate;
		}
		else {
			throw exception("alimentarea depaseste capacitatea maxima a rezervorului");
		}
		return *this;
	}

	//op -=
	Rezervor& operator-=(float _cantitate) {
		if (_cantitate > 0) {
			if (_cantitate <= this->capacitateCurenta) {
				this->capacitateCurenta -= _cantitate;
			}
		}
		return *this;
	}
};

//clasa optionala
class Pompa {
	//vector cu tipurile de combustibil
	//legatura cu rezervoarele cu care comunica
	//dispobilitate
	//valoare curenta
};

class Benzinarie {
	const string denumire;
	int nrRezervoare;
	Rezervor* listaRezervoare;
	int nrPompe;//toate pompele sunt conectate la toate rezervoarele din benzinarie
	float listaPreturi[3];//3 este cardinalitatea enumeratiei
	static float alimentareMaxima;//restrictie de la guvern prin OU

public:
	void suplimentareRezervor(float cantitate, TipCombustibil tipCombustibil) {
		//apelati op += pentru actualizare in rezervor
	}

	void alimentareDinPompa(float cantitate, int nrPompa, TipCombustibil tipCombustibil) {
		//apelati op -= pentru actualizare in rezervor
	}
};

int main() {
	
	return 0;
}