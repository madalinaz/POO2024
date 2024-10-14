#include<iostream>
using namespace std;

int main() {
	//c: scanf si printf
	//c++: cin si cout + >> si <<
	int n;
	//scanf("%d", &n);
	//std::cin >> n;
	//std::cout << std::endl;
	cout << "n=";
	cin >> n;
	//printf("n=%d", n);
	cout << "n=" << n;

	int* px;//px=0xcccccc
	//px = NULL;
	px = nullptr;//nullptr =>pointer null
	int nr = NULL;
	px = &nr;

	px = nullptr;
	//px += 1;
	px++;
	cout << endl << px;
	px -= 1;

	//alocare dinamica + dezalocare
	//px = (int*)malloc(n * sizeof(int));
	px = new int[10];//alocare 10 elem de tip int
	//free(px);
	for (int i = 0; i < 10; i++)
		px[i] = i;
	cout << endl << px;
	cout << endl << *px;
	delete[] px;

	int* px2 = nullptr;
	px2 = new int(10);//un pointer la un int + initializare acel unic int cu 10
	cout << endl << &px2;
	cout << endl << px2;
	cout << endl << *px2;//dereferentiere
	delete px2;

	int* px3 = new int[1];
	px3[0] = 10;
	delete[] px3;



	return 0;
}