#include<iostream>
using namespace std;

void adaugaZeroIntrePare(int*& v, int& n) {
	//p1.se calc noua dimensiune
	int ct = 0;
	for (int i = 0; i < n - 1; i++) {
		if (v[i] % 2 == 0 && v[i + 1] % 2 == 0)
			ct++;
	}
	int dimensiuneNoua = n + ct;
	//p2.se aloca zm pentru un nou vector
	int* aux = new int[dimensiuneNoua];
	//p3.se copiaza in vector nou tot ce trebuie
	int k = 0;//poz curenta in care bagam in noul vector
	aux[k++] = v[0];
	for (int i = 1; i < n; i++) {
		if (v[i - 1] % 2 == 0 && v[i] % 2 == 0)
			aux[k++] = 0;
		aux[k++] = v[i];
	}
	//p4.dezalocam zm a vectorului vechi
	delete[] v;//dezaloc ce a fost alocat in main
	//p5.vechiul pointer/vector pointeaza spre cel nou
	v = aux;
	n = dimensiuneNoua;

}

int main() {
	int n;
	int* v = nullptr;
	cin >> n;
	v = new int[n];
	for (int i = 0; i < n; i++)
		cin >> v[i];
	adaugaZeroIntrePare(v, n);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	delete[] v;
	v = nullptr;

	if (v != nullptr) {
		cout << "\nIncerc sa extrag v[0]: " << v[0];
	}
	return 0;
}