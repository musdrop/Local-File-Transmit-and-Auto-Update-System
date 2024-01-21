#pragma once
#ifndef J_STRUCTURE
#define J_STRUCTURE

#define COMMONTYPE UseJA.isCommonType(typeid(TYPE).name())
#define STD std::
#include "JeffAlgorithm.h"
namespace jeff
{	
	template <class TYPE>
	class Node
	{
	protected:
		TYPE data;
	public:
		Node()
		{
			data = ASTYPE ZERO(sizeof(TYPE)).Export();
		}
		Node(TYPE newData) : data(newData)
		{}
		bool same_data(TYPE existData)
		{
			return data == existData;
		}
		void set_Data(TYPE newData)
		{
			this->data = newData;
		}
		TYPE& get_Data()
		{
			return data;
		}
		TYPE NOTFOUND()
		{
			return ASTYPE ZERO(sizeof(TYPE)).Export();
		}
		TYPE operator= (TYPE newData)
		{
			this->data = newData;
			return this->data;
		}
		bool operator==(TYPE newData)
		{
			if(COMMONTYPE)
				return data == newData;
			else
				UseJA.Compare(&data,&newData);
		}
		bool operator==(Node& Obj)
		{
			if (COMMONTYPE)
				return data == Obj.data;
			else
				UseJA.Compare(&data, &Obj.data);
		}
		TYPE operator+ (TYPE newData)
		{
			this->data = this->data + newData;
			return this->data;
		}
		Node(Node& Obj)
		{
			*this = Obj.data;
		}
	};
	template <class TYPE>
	class BasicNode:public Node<TYPE>
	{
	protected:
		BasicNode* Next;
	public:
		BasicNode() :Next(NULL)
		{}
		//with Default Number
		explicit BasicNode(TYPE newData) : Next(NULL), Node<TYPE>(newData)
		{}
		//with Father Node
		explicit BasicNode(BasicNode* Father) : Next(NULL), Node<TYPE>()
		{
			if (Father != NULL)
				Father->Next = this;
		}
		explicit BasicNode(BasicNode* Father, TYPE newData) :Next(NULL)
		{
			if (Father != NULL)
				Father->Next = this;
			this->data = newData;
		}
		explicit BasicNode(BasicNode* Father, BasicNode* Son,TYPE newData):Next(Son),Node<TYPE>(newData)
		{
			if(Father != NULL)
				Father->Next = this;
		}
		//Assign Function
		BasicNode(BasicNode& existNode):Node<TYPE>(existNode.data), Next(existNode.Next)
		{}
		virtual BasicNode* link_Node(BasicNode* const newNext)
		{
			Next = newNext;
			return this;
		}
		virtual BasicNode* next_Node()
		{
			return Next;
		}
		bool nextExist_node()
		{
			if (Next == NULL)
				return false;
			else
				return true;
		}
		int left_Node()
		{
			int result = 0;
			BasicNode* temp = Next;
			while (Next != NULL)
				temp = temp->Next,++result;
			return result;
		}
		BasicNode& NOTFOUND()
		{
			return *(BasicNode*)ZERO(sizeof(BasicNode)).Export();
		}
		BasicNode operator+=(const BasicNode& Next)
		{
			this->data = Next.data;
			this->Next = Next.Next;
		}
		virtual TYPE operator= (TYPE newData)
		{
			this->data=newData;
			return this->data;
		}
		virtual BasicNode operator= (BasicNode newData)
		{
			this->data = newData.data;
			this->Next = newData.Next;
			return *this;
		}
		BasicNode operator() (BasicNode* Father, BasicNode* Son)
		{
			Father->Next = this;
			Next = Son;
		}
		virtual BasicNode* operator++()
		{
			return Next;
		}
	};

	template<class TYPE>
	class Chain
	{
	protected:
		using BasicNode = BasicNode<TYPE>;
		BasicNode* Head;
		BasicNode* End;
		int size = 0;
	public:
		int size_Chain() const
		{
			return this->size;
		}
		bool isEmpty() const
		{
			return Head == NULL || End == NULL;
		}
	protected:
		virtual bool index_OutRange(int Index)
		{
			return Index > size - 1;
		}
		BasicNode* appendNull_Node(int newSize = 1)
		{
			if (newSize > 0)
			{
				size += newSize;
				for (int n = 0; n < newSize; ++n)
				{
					if (this->isEmpty())
						End = Head = new BasicNode;
					else
						End = new BasicNode(End);
				}
				return End;
			}
			else
				return NULL;
		}
	public:
		Chain():Head(NULL), End(NULL), size(0)
		{}
		bool exist_Node(TYPE Data)const
		{
			BasicNode* temp = Head;
			while (temp != NULL)
			{
				if(temp->same_data(Data))
					return true;
				temp=temp->next_Node();
			}
			return false;
		}
		BasicNode* locate_Node(unsigned int Index)
		{
			BasicNode* Temp = NULL;
			if (!(index_OutRange(Index) && isEmpty()))
			{
				Temp = Head;
				for (int n = 0; n < Index; n++)
					Temp = Temp->next_Node();
				return Temp;
			}
			else
				return NULL;
		}
		BasicNode* append_Node(TYPE Data)
		{
			size++;
			if (this->isEmpty())
				End = Head = new BasicNode(Data);
			else
				End = new BasicNode(End, Data);
			return End;
		}
		BasicNode* append_Node(BasicNode& newNode)
		{
			this->append_Node(newNode.get_Data());
			return this->End;
		}
		BasicNode* append_Chain(Chain& other)
		{
			for (int n = 0; n < other.size; ++n)
				this->append_Node(other[n]);
			return End;
		}
		BasicNode* append_Chain(const TYPE* newArray,int size)
		{	
			if (size > 0)
			{
				for (int n = 0; n < size; ++n)
					this->append_Node(newArray[n]);
			}
			else
				return NULL;
		}
		BasicNode& operator[](unsigned int Index)
		{
			static int lastIndex =-1;
			static BasicNode* lastNode = NULL;
			if (lastIndex != -1 && lastNode != NULL && Index == lastIndex)
			{
				return *lastNode;
			}
			if (index_OutRange(Index))
			{
				if (Index == this->size)
				{
					lastNode = appendNull_Node();
					lastIndex= Index;
					return *this->End;
				}
				else
					return lastNode->NOTFOUND();
			}
			else
			{
				if (Index == this->size-1)
					return *(lastNode = End);
				else
					return *(lastNode = locate_Node(lastIndex = Index));
			}
		}
		Chain(TYPE* Array,int size)
		{
			this->append_Chain(Array,size);
		}
		Chain(Chain& Obj)
		{
			this->appendNull_Node(Obj.size);
			for (int n = 0; n < this->size; n++)
			{
				(*this)[n] = Obj[n].get_Data();
			}
		}
		//insert data at position
		virtual BasicNode* insert_Node(unsigned int Index,TYPE newData)
		{
			if (index_OutRange(Index))
				return NULL;
			BasicNode* Temp = Head;
			if (Index == 0)
				Head= Temp = new BasicNode(NULL,Temp,newData);
			else if (Index == size - 1)
				return this->append_Node(newData);
			else
			{
				if (Index <= size - 1)
				{
					Temp = locate_Node(Index - 1);
					Temp = new BasicNode(Temp, Temp->next_Node(), newData);
				}
			}
			++size;
			return Temp;
		}
		virtual int find_Node(TYPE existData)
		{
			BasicNode* Temp = this->Head;
			for (int n = 0; n != this->size; n++)
			{
				if (Temp->same_data(existData))
					return n;
				Temp = Temp->next_Node();
			}
			return -1;
		}
		virtual std::vector<int> search_Node(TYPE existData)
		{
			std::vector<int> result;
			BasicNode* temp = Head;
			for (int n = 0;temp != NULL;++n)
			{
				if(temp->same_data(existData))
					result.push_back(n);
				temp=temp->next_Node();
			}	
			return result;
		}
		virtual void delete_node(unsigned int Index)
		{
			BasicNode* temp;
			if (Index == 0)
			{
				temp = this->Head;
				this->Head = temp->next_Node();
				delete temp;
				if (this->Head == NULL)
					this->End = this->Head;
			}
			else
			{
				temp = locate_Node(Index - 1);
				BasicNode* delNode = temp->next_Node();
				temp->link_Node(delNode->next_Node());
				delete delNode;
			}
			this->size--;
		}
		void delete_node(BasicNode* existEle)
		{
			delete existEle;
		}
		virtual TYPE locate_Data(unsigned int Index)
		{
			if (!(index_OutRange(Index) && isEmpty()))
				return locate_Node(Index)->get_Data();
			else
				return ASTYPE ZERO(sizeof(TYPE)).Export();

		}
		virtual void cut_Chain(unsigned int position)
		{
			if (position < size)
			{
				BasicNode* start = &(*this)[position], * prevTemp = NULL;
				this->End = start;
				start = start->next_Node();
				while (start != NULL)
				{
					prevTemp = start;
					start = start->next_Node();
					delete prevTemp;
				}
				this->End->link_Node(NULL);
				this->size = position + 1;
			}

		}
		void clear_Chain()
		{
			if (this->Head != NULL)
			{
				BasicNode* Temp = this->Head;
				for (int n = 0; n != this->size&&Temp != NULL; n++)
				{
					Temp = this->Head;
					this->Head = this->Head->next_Node();
					delete Temp;
				}
			}
			size = 0;
			this->Head = this->End = NULL;
		}
		BasicNode& operator +(TYPE newData)
		{
			return *this->append_Node(newData);
		}
		Chain& operator+(Chain& Obj)
		{
			for (int n = 0; n < Obj.size; n++)
			{
				this->append_Node(Obj[n]);
			}
		}
		BasicNode& operator +(BasicNode& newData)
		{
			return *this->append_Node(newData);
		}
		virtual const Chain& operator=(Chain& existChain)
		{
			int n = 0;
			for (;n<existChain.size; ++n)
				(*this)[n] = existChain[n].get_Data();
			if (this->size > existChain.size)
			{
				cut_Chain(n);
			}
			return *this;
		}
		const Chain& operator+=(Chain& existChain)
		{
			for (int n = 0; n < existChain.size; ++n)
				this->append_Node(existChain[n].get_Data());
			return *this;
		}
		~Chain()
		{
			this->clear_Chain();
		}
	};
	///
	/// Chain
	///
	template<class TYPE>
	class Stack
	{
		using BasicNode = BasicNode<TYPE>;
		BasicNode* Top;
		BasicNode* Bottom;
	public:
		Stack();
		void data_Push(TYPE newData);
		Stack(TYPE* Array, int size);
		TYPE data_Pop();
		void stack_Destroy();
		bool stack_End();
		bool stack_Empty();
		~Stack();
	};
	///
	///Stack
	///

	DYNAMIC
		Stack<TYPE>::Stack() :Top(NULL), Bottom(NULL)
	{}
	DYNAMIC
	Stack<TYPE>::Stack(TYPE* Data, int Size)
	{
		for(int n  = 0;n<Size ;++n)
			this->data_Push(Data[n]);
	}
	DYNAMIC
		void Stack<TYPE>::data_Push(TYPE newData)
	{
		static BasicNode* Last = NULL;
		if (Bottom == NULL)
			Last = Top = Bottom = new BasicNode(newData);
		else
			Top = new BasicNode(newData), Last = Top->link_Node(Last);

	}
	DYNAMIC
		TYPE Stack<TYPE>::data_Pop()
	{
		if (Top != NULL)
		{
			BasicNode* Temp = Top;
			TYPE result = Temp->get_Data();
			if (Top != Bottom)
				Top = Top->next_Node();
			else
				Top = Bottom = NULL;
			delete Temp;
			return result;
		}
		else
		{
			ZERO[sizeof(TYPE)];
			return *(TYPE*)ZERO.Export();
		}
	}
	DYNAMIC
	void Stack<TYPE>::stack_Destroy()
	{
		if (Top != NULL && Bottom != NULL )
		{
			BasicNode* Temp = Top;
			for (int n = 0; Temp != Bottom; n++, Temp = Top)
				Top = Top->next_Node(), delete Temp;
			delete Bottom;
			Top = Bottom = NULL;
		}
	}
	DYNAMIC
	bool Stack<TYPE>::stack_End()
	{
		return Top == Bottom;
	}
	DYNAMIC
	bool Stack<TYPE>::stack_Empty()
	{
		return Top == NULL && Bottom == NULL;
	}
	DYNAMIC
		Stack<TYPE>::~Stack()
	{
		stack_Destroy();
	}

}
#endif