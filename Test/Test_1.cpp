#include <iostream>
#include <fstream>
#include "Test_1.h"
using namespace std;
int main()
{
	ifstream fil("test.txt");
	char a[10]{ 'A','A','A','A','A','A','A','A','A','A' };
	fil.read(a, 10);
	cout << fil.gcount() << '\n';
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << ' ';
	}
}