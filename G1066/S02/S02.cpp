#include <iostream>
using namespace std;

void dublareAparitiiMax(int*& v, int& n) {
	//p1.determinare noua dimensiune
	int max = v[0];
	int nrApMax = 1;
	for (int i = 1; i < n; i++) {
		if (v[i] > max) {
			max = v[i];
			nrApMax = 1;
		}
		else if (v[i] == max) {
			nrApMax++;
		}
	}
	int dimNoua = n + nrApMax;
	//p2.se aloca xm pt un nou vector din dim din p1
	int* aux = new int[dimNoua];
	//p3.se copiaza in noul vector aux tot ce trebuie
	int k = 0;//pozitia curenta in care adaug
	for (int i = 0; i < n; i++) {
		aux[k++] = v[i];
		if (v[i] == max)
			aux[k++] = v[i];
	}
	//p4.se dezaloca zm pentru fostul vector/pointer
	delete[] v;//dezaloca ce s-a alocat in main
	//p5.vector vechi pointeaza spre vector nou
	v = aux;
	n = dimNoua;
}
int main() {
	int* v = nullptr;
	int n;
	cin >> n;
	v = new int[n];
	for (int i = 0; i < n; i++)
		cin >> v[i];
	dublareAparitiiMax(v, n);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";

	//...
	delete[] v;//adica ce a fost alocat in fct prin aux
	v = nullptr;
	if (v != nullptr) {
		cout << endl << "Incerc sa iau pe v[0]= " << v[0];
	}
	return 0;
}
/*
tema: stocati un vector de nume de contact
o functie care sa returneze cate persoane sunt sarbatorite dandu se numele de sfant
*/
