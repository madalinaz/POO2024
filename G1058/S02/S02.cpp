#include <iostream>
using namespace std;
//TEMA SIRURI DE CARACTERE: AVEM O AGENDA TELEFONICA IN CARE SE RETINE DOAR NUMELE PRIETENILOR. SE CERE
//SA SE AFISEZE CATI PRIETENI SUNT SARBATORITI DANDU-SE NUMELE SFANTULUI(ION,MIHAI,ANDREI,ELENA, ETC)


//dandu-se un vector cu valori distincte si dimensiunea sa sa se elimine cele mai mari 2 valori.
void eliminareMax2Elem(int*& v, int& n)
{
	int nouadim, max1, max2;
	nouadim = n - 2; max1 = v[0]; max2 = v[0];
	for (int i = 0; i < n; i++)
	{
		if (v[i] > max2)
		{
			max1 = max2;
			max2 = v[i];
		}
		else
		{
			if (v[i] > max1)
				max1 = v[i];
		}
	}
	int* aux = new int[nouadim];
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (v[i] != max1 && v[i] != max2)
		{
			aux[k] = v[i];
			k++;
		}
	}
	delete[] v;
	v = aux;
	n = nouadim;


}
//ADAUGA DUPA FIECARE ELEM PAR VALOAREA 0;
void adauga_dupa_par_val_0(int*& v, int& n)
{
	//pas1 se determina noua dimensiune
	int nrpare = 0;
	for (int i = 0; i < n; i++)
	{
		if (v[i] % 2 == 0)
			nrpare++;
	}
	int nouadim = n + nrpare;
	//pas 2 se aloca noua dim pentru noul vector;
	int* aux = new int[nouadim];
	//pas 3 se copiaza in noul vector tot ce e nevoie
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		aux[k++] = v[i];
		if (v[i] % 2 == 0) {
			aux[k++] = 0;
		}

	}
	//pas 4 eliberam zona de memorie pentru fostul vector(care a fost alocat in main)
	delete[] v;
	//pas 5 noul vector/pointer pointeaza spre cel nou
	v = aux;
	n = nouadim;
}

int main() {

	int* v = nullptr;
	int n = 5;
	v = new int[n];
	cout << "introdu valorile vectorului: ";
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	eliminareMax2Elem(v, n);
	cout << "Noul vector este:";
	for (int i = 0; i < n; i++)
	{
		cout << v[i] << " ";
	}
	delete[] v;//dezaloc ce am alocat in fct pentru aux
	v = nullptr;

	return 0;
}