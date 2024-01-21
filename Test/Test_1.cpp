#include <iostream>
#include <fstream>
#include "Test_1.h"
using namespace std;
class TransmitSignal
{
public:
	char signal = 0;
	char fileName[63] = { '\0' };
	unsigned int fileByteSize = 0;
	unsigned int segmentSize = 0;
	void SetContent(int pos, int width, char* data);//字节层面向结构体内写入内容
	void GetContent(int pos, int width, char* data);//字节层面向结构体内提取内容
};
int main()
{
	cout << sizeof(TransmitSignal);
	//ifstream fil("test.txt");
	//char a[10]{ 'A','A','A','A','A','A','A','A','A','A' };
	//fil.read(a, 10);
	//cout << fil.gcount() << '\n';
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << a[i] << ' ';
	//}
}