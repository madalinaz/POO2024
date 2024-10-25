#include<iostream>
using namespace std;

/* -----------SPECIFICATII-------------
 - orasSursa si orasDestinatie - sir de caractere de lungime maxima 15
 care contin doar litere si caracterul - cu restrictie suplimentara orasSursa diferit de orasDestinatie
 - data - sir de caractere de lungime fixa avand formatul zz/ll/aaaa; restrictii suplimentare: data trebuie sa fie mai mare ca daca curenta a sistemului
 - NrLocuri - valoare intreaga ce reprezinta lungimea vectorului disponibilitateLocuri
 si pretBilete cu o valoare maxima de 400
 - disponibilitateLocuri - vector alocat dinamic ce stocheaza valori booleene si refera disponibilitatea locurilor
 din cadrul zborului curent
 - pretBilete - vector alocat dinamic ce stocheaza valori reale pozitive si refera
 pretul aferent fiecarui loc disponibil in cadrul zborului curent
 */

/* -----------CERINTE IMPLEMENTARE-------------
 Sa se implementeze urmatoarele cerinte in cadrul clasei Zbor:
 1. Constructor fara parametri care va initializa obiectul pe 0 sau nullptr in functie de tipul atributelor.
 2. Constructor cu toti parametri care va initiaza obiectul curent daca sunt validate
 restrictiile enuntate in specificatii. Daca se primeste un parametru eronat, atunci se initializeaza precum in constructorul default.
 3. Constructor cu mai putini parametri in care nu se primeste si vectorul de disponibilitate, acesta o sa se incarca automat cu true pentru fiecare loc disponibil.
 4. Metoda de afisare care afiseaza fiecare atribut pe cate o linie separata.
 5. Metoda de afisare compactata care afiseaza fiecare atribut pe linie iar pentru disponibilitateLocuri afiseaza doar numarul de locuri ramase disponibile
 iar pentru pretBilete afiseaza pretul mediu pentru biletele libere ramase pentru respectivul zbor
 6. Metoda de afisare compactata care afiseaza informatiile prezentate la cerinta nr 5 doar ca pe o singura linie, separate prin virgula(,)
 7. Constructor de copiere
 8. Destructor
 9. Metode accesor pentru vectorii disponibilitateLocuri si pretBilete cu urmatoarele restrictii:
	- get pentru nrLocuri, disponibilitateLocuri, disponibilitateLocuri pentru un anume index primit ca parametru
	- get pentru pretBilete, pretBilete pentru un anume index primit ca parametru
	- set pentru disponibilitateLocuri pentru o anume pozitie
	- set pentru pretBilete pentru o anume pozitie (pretul se poate schimba doar daca locul aferent este disponibil, daca deja a fost vandut respectivul loc, atunci nu se schimba pretul)
10. Metoda care verifica daca exista cel putin k bilete libere alaturate pentru zborul curent (k este primit ca parametru in metoda)
11. Metoda care simuleaza vanzarea unui anume loc primit ca parametru
12. Metoda care simuleaza vanzarea unui numar de k locuri alaturate, unde k este primit ca parametru. Metoda returneaza totalul de plata.
13. Metoda care returneaza totalul incasarilor pentru zborul curent
14. Metoda care returneaza pretul mediu al biletelor vandute
15. Metoda care calculeaza cea mai ieftina combinatie de k locuri disponibile alaturate in configuratia curenta a disponibilitatii locurilor din zbor.
16. Metoda care verifica cate zile mai sunt pana la data zborului fata de data curenta a sistemului sau fata de o data primita ca parametru.
17. Metoda care actualizeaza preturilor biletelor nevandute in functie de numarul de zile ramase pana la zbor. Propuneti voi o regula in acest sens.
18. Sa se propuna/implementeze o modalitate de calculare a distantelor dintre orasul sursa si orasul destinatie pentru fiecare zbor. Se poate avea in vedere o matrice a drumurilor stocata intr-un fisier sau alte solutii propuse de voi.

Toate metodele implementate sunt testate in main si se folosesc separatori prin cout<<"\n------Cerinta x-----"; pentru o intelegere usoara a celor implementate
Implementarea trebuie sa nu aiba memory leaks.
Daca sunt necesare metode suplimentare de tip get si set, se pot implementa.
Succes si spor la lucru!
*/

class Zbor {
	string orasSursa;
	string orasDestinatie;
	char data[11];
	int nrLocuri;
	bool* disponibilitateLocuri;
	float* pretBilete;
};

int main() {
	return 0;
}