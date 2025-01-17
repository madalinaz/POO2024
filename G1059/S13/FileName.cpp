#include<iostream>
using namespace std;

//clasa tip interfata
//care are doar meth virtuale pure
//interfata = contract
//interfata caz particular din clasa abstracta
class ICheltuiala {
public:
	virtual void getInfo() = 0;//meth virtuala pura
	virtual float getCostLunar() = 0;//meth virtuala pura
};

//clasa abstracta
//clasa care are cel putin o meth virtuala pura
class ACheltuiala : public ICheltuiala {
protected:
	string denumire;
	string dataContract;

public:
	ACheltuiala(string _denumire, string _dataContract) {
		this->denumire = _denumire;
		this->dataContract = _dataContract;
	}
};

//clasa concreta - care nu este abstracta
class ChFurnizor :public ACheltuiala {
	float costLunar;

public:
	ChFurnizor(string _denumire, string _dataContract, float _costLunar) :ACheltuiala(_denumire, _dataContract) {
		this->costLunar = _costLunar;
	}

	void getInfo() override {
		cout << "\nCh: " << this->denumire << ", cost lunar: " << this->costLunar;
	}

	float getCostLunar() override {
		return this->costLunar;
	}
};

class ChEchipament :public ACheltuiala {
	float pretAchizitie;
	int nrLuniAmortizare;

public:
	ChEchipament(string _denumire, string _dataContract, float _pretAchizitie, int _nrLuniAmortizare) :ACheltuiala(_denumire, _dataContract) {
		this->pretAchizitie = _pretAchizitie;
		this->nrLuniAmortizare = _nrLuniAmortizare;
	}

	void getInfo() override {
		cout << "\nCh: " << this->denumire << ", pret achizitie: " << this->pretAchizitie;
	}

	float getCostLunar() override {
		return this->pretAchizitie / this->nrLuniAmortizare;
	}
};

int main() {
	//interfata
	//ICheltuiala obj;
	ICheltuiala* pObj = nullptr;//container unde gasesc adresa de obj
	//pObj->getInfo();

	//clasa abstracta
	//ACheltuiala objCh;
	//ACheltuiala* pObjCh = new ACheltuiala("apa", "12/12/2023");

	//clasa concreta
	ChEchipament ch1("laptop", "12/12/2020", 4800, 24);
	ACheltuiala* pChEchipament = new ChEchipament("laptop", "12/12/2020", 4800, 24);
	return 0;
}