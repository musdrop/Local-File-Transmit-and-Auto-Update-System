#pragma once
#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <string>
#include<stdio.h>
#include <conio.h>
#include <iostream>
#include <typeinfo>
#include <vector>
namespace jeff
{
using namespace std;
using onebyte = char;
#define BYTELEN 8//字节位长
#define CHAR2INT 48
//变量名称宏
//int类型名称
#define INT4NAME typeid(int).name()
//short类型名称
#define INT2NAME typeid(short int).name()
//byte类型名称
#define INT1NAME typeid(onebyte).name()
//long类型名称
#define INT8NAME typeid(long long).name()
//字符类型名称
#define CHARNAME typeid(char).name()
//浮点类型名称
#define FLOATNAME typeid(float).name()
//双精度浮点类型名称
#define DOUBLENAME typeid(double).name()
//字符串类型名称
#define STRINGNAME typeid(std::string).name()
//布尔类型名称
#define BOOLNAME typeid(bool).name()

//转换类型宏

#define ARLEN (x)  (sizeof(x))
#define DYNAMIC template<class TYPE>
#define ASBOOL *(bool*)
#define ASTYPE *(TYPE*)
#define BOOLP (bool*)
#define TYPEP (TYPE*)
#define ASINT4 *(int*)
#define ASINT1 *(char*)
#define ASINT2 *(short int*)
#define ASINT8 *(long long* )
#define ASCHAR *(char*)
#define ASFLOAT *(float*)
#define ASDOUBLE *(double*)
#define ASSTRING *(string*)
#define ASNODE *(Node*)
#define ASSTUINF *(StuInfor*)
#define ASCHAIN *(Chain*)
#define INDTYPE unsigned int
//int pointer
#define I4P (int*)
//short pointer
#define I2P (short int*)
//byte pointer
#define I1P (char* )
//long pointer
#define I8P (long long*)
//char pointer
#define CP (char*)
//float pointer
#define FP (float*)
//double pointer
#define DP (double*)
//template pointer
#define TP (TYPE* )
//Calculation
//在两个给定的数组间赋值（默认使用者给出真实的长度）
#define ARRAYASSIGN(x,y,size)for(int n = 0;n<size;++n)x[n]=y[n]
//判断值是否为奇数
#define ISODD(x) x%2!=0
//判断值是否为偶数
#define ISEVEN (x) x%2==0

//jeff algorithm 算法类
	static class JA
	{
	public:
		bool isCommonType(const char* typeName)
		{
			return strcmp(typeName, INT4NAME)
				|| strcmp(typeName, INT2NAME)
				|| strcmp(typeName, FLOATNAME)
				|| strcmp(typeName,CHARNAME)
				|| strcmp(typeName, DOUBLENAME)
				|| strcmp(typeName, INT8NAME)
				|| strcmp(typeName, BOOLNAME)
				|| strcmp(typeName, STRINGNAME);
		}
		//清空任意变量、数组，len为该变量、数组的字节长度
		template<class TYPE>
		TYPE* Clear(TYPE* Array,int Len = 1)
		{
			if (Len > 0)
			{
				if (Len == 1 && isCommonType(typeid(TYPE).name()))
				{
					*Array = 0;
					return Array;
				}
				int byteSize = sizeof(TYPE);//获取字节长度
				void* temp = Array;//消除数组的类型
				if (byteSize % 4 == 0)//按字节数分类，如果以4为间隔就使用int指针初始化
				{
					int intLen = byteSize / 4;
					int* clear = I4P temp;
					for (int m = 0; m < Len; m++)//遍历整个数组
						for (int n = 0; n < intLen; ++clear, ++n)//初始化单个元素
							*clear = 0;
				}
				else
				{
					char* clear = CP temp;
					for (int m = 0; m < Len; m++)//遍历整个数组
						for (int n = 0; n != byteSize; ++clear, ++n)//初始化单个元素
							*clear = 0;
				}
				return Array;
			}
			else
				return NULL;
		}
		//比较任意变量、数组，len为该变量、数组的字节长度
		template <class TYPE>
		bool Compare(TYPE* valA, TYPE* valB,int Len = 1)
		{
			if (isCommonType(typeid(TYPE).name())&&Len == 1)
			{
				return valA == valB;
			}
			void* anyA = valA, * anyB = valB;//消除类型
			int size = sizeof(TYPE);//获取字节数
			bool result = true;
			if (size % 4 == 0)//根据字节数进行分类
			{
				int* tempA = I4P anyA, * tempB = I4P anyB;
				for (int m = 0; m != Len; m++)//遍历整个列表
				{
					for (int n = 0; n != size / 4; tempA++, tempB++, n++)
						result = result && (*tempA == *tempB);//比较每个元素
				}
			}
			else
			{
				char* tempA = CP anyA, * tempB = CP anyB;
				for (int m = 0; m != Len; m++)//遍历整个列表
					for (int n = 0; n != size; tempA++, tempB++, n++)//遍历整个列表
						result = result && (*tempA == *tempB);
			}
			return result;
		}
		//赋值任意变量，将B赋值给A
		DYNAMIC
		TYPE Assign(TYPE& A,TYPE& B)
		{
			if(isCommonType(typeid(TYPE).name()))
				return A=B;
			void* valA = &A, * valB = &B;
			if (sizeof(TYPE)%4 == 0)//根据字节数分类
			{
				int* valIA = I4P valA,*valIB = I4P valB;//消除类型
				for(int n = 0;n<sizeof(TYPE)/4;++n)//遍历每个元素（以4为分界单位）
					valIA[n] = valIB[n];
				return A;
			}
			else
			{
				char* valIA = CP valA, * valIB = CP valB;
				for (int n = 0; n < sizeof(TYPE); ++n)//遍历每个元素（以1为分界单位）
					valIA[n] = valIB[n];
				return A;
			}
		}
		//给出int的位数
		int digits(int newData)
		{
			int result = 0;
			for (; newData != 0; result++)
				newData /= 10;
			return result;
		}
		//给出long的位数
		int longDigits(long long newData)
		{
			int result = 0;
			for (; newData != 0; result++)
				newData /= 10;
			return result;
		}
		//计算一个long的二进制位数
		int binaryL2DecimalL(const int byteSize)
		{
			int allByteLen = byteSize * BYTELEN;
			int decimalSize = allByteLen, Round = decimalSize % 10;
			decimalSize /= 10;
			decimalSize *= 3;
			if (Round != 0)
				decimalSize += 1;
			return decimalSize;
		}
		//翻转一个string
		void strReverse(char* existStr)
		{
			int size = strlen(existStr) - 1;
			char Temp;
			for (int n = 0; n != strlen(existStr) / 2; n++)
			{
				Temp = existStr[n];
				existStr[n] = existStr[size - n];
				existStr[size - n] = Temp;
			}
		}
		//判断一个char数组是不是都是数字
		bool isAllNumber(const char* existStr)
		{
			if (existStr == NULL)
				return false;
			int size = strlen(existStr) - 1;
			for (int n = 0; n != size / 2 + 1; n++)
			{
				if (existStr[n] == 45 || ((existStr[n] >= 48) && (existStr[n] <= 57)))
					continue;
				else
					return false;
				if (existStr[size - n] == 45 || ((existStr[size - n] >= 48) && (existStr[size - n] <= 57)))
					continue;
				else
					return false;
			}
			return true;
		}
		DYNAMIC
		int selection(TYPE* Array, int Len,TYPE goal)
		{
			for (int n = 0; n < Len; ++n)
			{
				if(Array[n] == goal)
					return n;
			}
			return -1;
		}
		int maxSelection(int* Array, int Len)
		{
			int Max = 0,Endl = -1;
			for (int n = 0; n < Len; ++n)
			{
				if (Array[n] > Max)
					Max = Array[n],Endl = n;
			}
			return Endl;
		}
		DYNAMIC
		TYPE* merge(TYPE* Array1, int Size1, TYPE* Array2, int Size2)
		{
			const int resultSize = Size1 + Size2;
			TYPE* result = new TYPE[resultSize];
			for (int n = 0; n != resultSize; n++)
			{
				if (n < Size1)
					result[n] = Array1[n];
				else
					result[n] = Array2[n];
			}
			return result;
		}
		//merge 2 into 1
		DYNAMIC
		std::vector<TYPE >merge(std::vector<TYPE>arr1, std::vector<TYPE>arr2,bool forSort = false)
		{
			for (int n = 0;n< arr2.size(); n++)
			{
				arr1.push_back(arr2[n]);
			}
			return arr1;
		}
	};
	static JA UseJA;
	//给予一个空的空间，用以初始化变量
	class EMPTY
	{
		void* Space;
	public:
		//默认初始化
		EMPTY() :Space(NULL)
		{}
		//给定空间大小的初始化
		EMPTY(int newSize)
		{
			Space = new char[newSize];
			UseJA.Clear(CP Space,newSize);
		}
		//导出空间
		const void* const Export()
		{
			return Space;
		}
		//分配一个空的空间,第二个参数为true时表示空间会被回收
		void* Allocate(int size, bool reclaim = true)
		{
			if (reclaim)
			{
				if (Space)
					delete[] Space;
				Space = new char[size];
				UseJA.Clear(CP Space, size);
				return Space;
			}
			else
			{
				void* result = new char[size];
				UseJA.Clear(CP result, size);
				return result;
			}

		}
		//分配一个空间，并返回当前对象的引用
		EMPTY& operator() (int newSize)
		{
			if (Space == NULL)//当Space为空时创建新空间
			{
				Space = new char[newSize];
				UseJA.Clear(CP Space, newSize);
			}
			else if (Space != NULL && newSize > _msize(Space))//当Space不为空但空间要求大于当前空间大小时
			{
				delete[] Space;
			}
			else//当存在空间大于给定大小时
			{
				return *this;
			}
			Space = new char[newSize];
			UseJA.Clear(CP Space, newSize);
			return *this;
		}
		~EMPTY()//析构函数
		{
			delete[] Space;
		}
	};
	static EMPTY ZERO;
	static class JASorting
	{
		template <class TYPE>
		int divideSearch(TYPE* list, TYPE goal, int Len)
		{
			for (int begin = 0, midBack = Len / 2, midNext = Len / 2, end = Len, result = 0
				; !(begin == midBack || begin == midBack - 1) && !(end == midNext || end == midNext + 1)
				; ++begin, --midBack, ++midNext, --end)
			{
				if (list[(result = begin)] == goal || list[(result = midBack)] == goal || list[(result = midNext)] == goal || list[(result = end)] == goal)
					return result;
			}
			return -1;
		}
		template<class SortType>
		void insertSorting(SortType* anyArray, int sizeofArray)
		{
			for (int n = 1; n != sizeofArray; n++)
			{
				SortType TempValue;
				for (int m = n; m != 0; m--)
				{
					if (anyArray[m - 1] > anyArray[m])
					{
						TempValue = anyArray[m - 1];
						anyArray[m - 1] = anyArray[m], anyArray[m] = TempValue;
					}
				}
			}
		}
		DYNAMIC
		static std::vector<TYPE>* mergingSorting(std::vector<TYPE> waitingArray)
		{
			for (int n = 0;n<waitingArray.size(); ++n)
			{
				
			}
		}
	};
	static JASorting UseJASort;
	
}
#endif