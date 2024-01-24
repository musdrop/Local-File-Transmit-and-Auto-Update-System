#pragma once
#include "Utools\\Net.h"
#include "Utools\\fileSnd.h"
#include "Utools\\fileRcv.h"
#include <vector>
#include <queue>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <conio.h>
using namespace Net;
using namespace jeff;
using namespace std;
class Test
{
public:
	void Print(int a, int b)
	{
		while (true)
		{
			cout << a + b;
		}
	}
	void start()
	{
		thread s(&Test::Print, this, 3, 5);
		s.join();
	}
};
int main()
{
	Test r;
	r.start();
}