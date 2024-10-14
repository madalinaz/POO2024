#include <stdio.h>
#include <malloc.h>

/*
 tranfer facut prin valoare
 Schimbă a și b prin valoare, dar nu afectează variabilele originale , modificarile sunt doar in cadrul functiei
 avantaje: protejam obiectul, dezavantaje : consum de memorie + timp (din cauza copiei)
*/
void f1(int a, int b)
{
	int aux = a;
	a = b;
	b = aux;
}

/*
 nu este implementare corecta , schimbă local adresele pointerilor, dar nu afectează valorile efective ale lui x și y.
*/
void f2(int* a, int* b)
{
	int* aux = a;
	a = b;
	b = aux;
}
/*
schimbă valorile prin referință, afectând variabilele originale (specific pentru C++).
*/
void f3(int& a, int& b)
{
	int aux = a;
	a = b;
	b = aux;
}

/*
varianta pentru C
schimbă valorile la care pointează a și b, modificările fiind vizibile în variabilele originale.
folosim cand vrem sa modificam obiectul , nu facem copie , dar nu este protejat
*/
void f4(int* a, int* b)
{
	//deferentiere
	int aux = *a;
	*a = *b;
	*b = aux;
}

int main()
{
	int x, y;
	x = 10; y = 20;
	printf("\n-----------Meth1----------");
	printf("\nx = %d , y = %d", x, y); // x = 10 , y = 20
	f1(x, y);
	printf("\nx = %d , y = %d", x, y); // x = 10 , y = 20

	x = 10; y = 20;
	printf("\n-----------Meth2----------");
	printf("\nx = %d , y = %d", x, y); // x = 10 ,  y = 20
	f2(&x, &y);
	printf("\nx = %d , y = %d", x, y); // x = 10 , y = 20

	x = 10; y = 20;
	printf("\n-----------Meth3----------");
	printf("\nx = %d , y = %d", x, y); // x = 10 , y = 20
	f3(x, y);
	printf("\nx = %d , y = %d", x, y); // x = 20 , y = 10

	x = 10; y = 20;
	printf("\n-----------Meth4----------");
	printf("\nx = %d , y = %d", x, y); // x = 10 , y = 20
	f4(&x, &y);
	printf("\nx = %d , y = %d", x, y); // x = 20 , y = 10
	\

	int* v;
	int n = 10;
	// vector alocat dinamic pentru un tablou de 10 elemente , ocupa 10*4 = 40 octeti
	v = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		v[i] = 2 * i;
	}

	/*
	memorie eliberata cu ajutorul lui free !!!!
	*/
	free(v);
}