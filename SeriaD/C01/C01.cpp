#include<stdio.h>
#include<string.h>

int main() {
	int x, y;
	x = 2; y = 5;
	x = y + 2;
	printf("\nx=%d, y=%d", x, y);
	float z;
	int v[5];
	for (int i = 0; i < 5; i++)
		v[i] = i;
	char s[20];
	strcpy_s(s, "Ana are mere");

	bool ok;
	ok = 5;
	//s[3] = '\0';
	s[3] = NULL;
	printf("\n%s", s);
	return 0;
}