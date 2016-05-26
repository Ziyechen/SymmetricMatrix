#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include <stdlib.h>
#include "Matrix.h"

void test1()
{
	int a[6][5] =
	{
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 2, 0, 4, 0, 6 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
	};

	SparseMatrix<int> sm1((int*)a, 6, 5, 0);
	sm1.Display();

	SparseMatrix<int> sm2 = sm1.Transport();
	sm2.Display();

	SparseMatrix<int> sm3 = sm1.FastTransport();
	sm3.Display();
}

int main()
{
	test1();

	system("pause");
	return 0;
}
