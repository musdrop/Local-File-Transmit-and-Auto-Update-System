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
#define BYTELEN 8//�ֽ�λ��
#define CHAR2INT 48
	//�������ƺ�
	//int��������
#define INT4NAME typeid(int).name()
//short��������
#define INT2NAME typeid(short int).name()
//byte��������
#define INT1NAME typeid(onebyte).name()
//long��������
#define INT8NAME typeid(long long).name()
//�ַ���������
#define CHARNAME typeid(char).name()
//������������
#define FLOATNAME typeid(float).name()
//˫���ȸ�����������
#define DOUBLENAME typeid(double).name()
//�ַ�����������
#define STRINGNAME typeid(std::string).name()
//������������
#define BOOLNAME typeid(bool).name()

//ת�����ͺ�

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
//����������������丳ֵ��Ĭ��ʹ���߸�����ʵ�ĳ��ȣ�
#define ARRAYASSIGN(x,y,size)for(int n = 0;n<size;++n)x[n]=y[n]
//�ж�ֵ�Ƿ�Ϊ����
#define ISODD(x) x%2!=0
//�ж�ֵ�Ƿ�Ϊż��
#define ISEVEN (x) x%2==0

//jeff algorithm �㷨��
	static class JA
	{
	public:
		bool isCommonType(const char* typeName)
		{
			return strcmp(typeName, INT4NAME)
				|| strcmp(typeName, INT2NAME)
				|| strcmp(typeName, FLOATNAME)
				|| strcmp(typeName, CHARNAME)
				|| strcmp(typeName, DOUBLENAME)
				|| strcmp(typeName, INT8NAME)
				|| strcmp(typeName, BOOLNAME)
				|| strcmp(typeName, STRINGNAME);
		}
		//���������������飬lenΪ�ñ�����������ֽڳ���
		template<class TYPE>
		TYPE* Clear(TYPE* Array, int Len = 1)
		{
			if (Len > 0)
			{
				if (Len == 1 && isCommonType(typeid(TYPE).name()))
				{
					*Array = 0;
					return Array;
				}
				int byteSize = sizeof(TYPE);//��ȡ�ֽڳ���
				void* temp = Array;//�������������
				if (byteSize % 4 == 0)//���ֽ������࣬�����4Ϊ����ʹ��intָ���ʼ��
				{
					int intLen = byteSize / 4;
					int* clear = I4P temp;
					for (int m = 0; m < Len; m++)//������������
						for (int n = 0; n < intLen; ++clear, ++n)//��ʼ������Ԫ��
							*clear = 0;
				}
				else
				{
					char* clear = CP temp;
					for (int m = 0; m < Len; m++)//������������
						for (int n = 0; n != byteSize; ++clear, ++n)//��ʼ������Ԫ��
							*clear = 0;
				}
				return Array;
			}
			else
				return NULL;
		}
		//�Ƚ�������������飬lenΪ�ñ�����������ֽڳ���
		template <class TYPE>
		bool Compare(TYPE* valA, TYPE* valB, int Len = 1)
		{
			if (isCommonType(typeid(TYPE).name()) && Len == 1)
			{
				return valA == valB;
			}
			void* anyA = valA, * anyB = valB;//��������
			int size = sizeof(TYPE);//��ȡ�ֽ���
			bool result = true;
			if (size % 4 == 0)//�����ֽ������з���
			{
				int* tempA = I4P anyA, * tempB = I4P anyB;
				for (int m = 0; m != Len; m++)//���������б�
				{
					for (int n = 0; n != size / 4; tempA++, tempB++, n++)
						result = result && (*tempA == *tempB);//�Ƚ�ÿ��Ԫ��
				}
			}
			else
			{
				char* tempA = CP anyA, * tempB = CP anyB;
				for (int m = 0; m != Len; m++)//���������б�
					for (int n = 0; n != size; tempA++, tempB++, n++)//���������б�
						result = result && (*tempA == *tempB);
			}
			return result;
		}
		//��ֵ�����������B��ֵ��A
		DYNAMIC
			TYPE Assign(TYPE& A, TYPE& B)
		{
			if (isCommonType(typeid(TYPE).name()))
				return A = B;
			void* valA = &A, * valB = &B;
			if (sizeof(TYPE) % 4 == 0)//�����ֽ�������
			{
				int* valIA = I4P valA, * valIB = I4P valB;//��������
				for (int n = 0; n < sizeof(TYPE) / 4; ++n)//����ÿ��Ԫ�أ���4Ϊ�ֽ絥λ��
					valIA[n] = valIB[n];
				return A;
			}
			else
			{
				char* valIA = CP valA, * valIB = CP valB;
				for (int n = 0; n < sizeof(TYPE); ++n)//����ÿ��Ԫ�أ���1Ϊ�ֽ絥λ��
					valIA[n] = valIB[n];
				return A;
			}
		}
		//����int��λ��
		int digits(int newData)
		{
			int result = 0;
			for (; newData != 0; result++)
				newData /= 10;
			return result;
		}
		//����long��λ��
		int longDigits(long long newData)
		{
			int result = 0;
			for (; newData != 0; result++)
				newData /= 10;
			return result;
		}
		//����һ��long�Ķ�����λ��
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
		//��תһ��string
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
		//�ж�һ��char�����ǲ��Ƕ�������
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
			int selection(TYPE* Array, int Len, TYPE goal)
		{
			for (int n = 0; n < Len; ++n)
			{
				if (Array[n] == goal)
					return n;
			}
			return -1;
		}
		int maxSelection(int* Array, int Len)
		{
			int Max = 0, Endl = -1;
			for (int n = 0; n < Len; ++n)
			{
				if (Array[n] > Max)
					Max = Array[n], Endl = n;
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
			std::vector<TYPE >merge(std::vector<TYPE>arr1, std::vector<TYPE>arr2, bool forSort = false)
		{
			for (int n = 0; n < arr2.size(); n++)
			{
				arr1.push_back(arr2[n]);
			}
			return arr1;
		}
	};
	static JA UseJA;
	//����һ���յĿռ䣬���Գ�ʼ������
	class EMPTY
	{
		void* Space;
	public:
		//Ĭ�ϳ�ʼ��
		EMPTY() :Space(NULL)
		{}
		//�����ռ��С�ĳ�ʼ��
		EMPTY(int newSize)
		{
			Space = new char[newSize];
			UseJA.Clear(CP Space, newSize);
		}
		//�����ռ�
		const void* const Export()
		{
			return Space;
		}
		//����һ���յĿռ�,�ڶ�������Ϊtrueʱ��ʾ�ռ�ᱻ����
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
		//����һ���ռ䣬�����ص�ǰ���������
		EMPTY& operator() (int newSize)
		{
			if (Space == NULL)//��SpaceΪ��ʱ�����¿ռ�
			{
				Space = new char[newSize];
				UseJA.Clear(CP Space, newSize);
			}
			else if (Space != NULL && newSize > _msize(Space))//��Space��Ϊ�յ��ռ�Ҫ����ڵ�ǰ�ռ��Сʱ
			{
				delete[] Space;
			}
			else//�����ڿռ���ڸ�����Сʱ
			{
				return *this;
			}
			Space = new char[newSize];
			UseJA.Clear(CP Space, newSize);
			return *this;
		}
		~EMPTY()//��������
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
			for (int n = 0; n < waitingArray.size(); ++n)
			{

			}
		}
	};
	static JASorting UseJASort;

}
#endif