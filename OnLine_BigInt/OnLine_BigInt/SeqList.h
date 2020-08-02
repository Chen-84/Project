#ifndef _SEQLIST_H_
#define _SEQLIST_H_
//////////////////////////////////////////
////�ײ����ݴ洢�ṹ����˳���
////�ص㣺(1) 0�±겻�洢���ݣ���Ϊ����λ  (2) ���ݷ��Ŵ洢�����ڴ����λ��

#include"Public.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
////˳�����
template <typename Type>
class SeqList
{
public:
	SeqList(int sz = SEQLIST_DEFAULT_SIZE);
	SeqList<Type>& operator=(const SeqList<Type> &st);
	SeqList(const SeqList<Type> &st);
	~SeqList();

public:
	typedef Type& reference;
	typedef const Type& const_reference;

public:
	bool full()const;
	bool empty()const;
	void push_back(const Type &x); //β������
	void push_front(const Type &x);//ͷ������
	void pop_back();//β��ɾ��
	void pop_front();//ͷ��ɾ��
	reference front();//ȡ����Ԫ��
	const_reference front()const;
	reference back();//ȡ�����һ��Ԫ��
	const_reference back()const;
	size_t size()const;//�󳤶�
	void reverse();//��ת
	void clear();//���
	void sort();//����
	int find(const Type &key); //����
	void erase(const Type &key);//ɾ��
protected:
	bool Expansion();//����
public:
	reference operator[](int pos);
	const_reference operator[](int pos)const;

private:
	Type *base;
	size_t capacity;
	size_t _size;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
////˳����ࡪ������ʵ��

/////////////////////////////////////////////
////����
template <typename Type>
SeqList<Type>::SeqList(int sz)
{
	capacity = sz > SEQLIST_DEFAULT_SIZE ? sz : SEQLIST_DEFAULT_SIZE;
	base = new Type[capacity+1];//��һ���ռ䲻�洢����
	memset(base, 0, sizeof(Type)*(capacity + 1));
	_size = 0;
}
template <typename Type>
SeqList<Type>:: SeqList(const SeqList<Type> &st)
{
	capacity = st.capacity;
	base = new Type[sizeof(Type)*(capacity+1)];
	memset(base, 0, sizeof(Type)*(capacity + 1));
	memcpy(base, st.base, sizeof(Type)*(st._size + 1));
	_size = st._size;
}
/////////////////////////////////////////////
////����
template <typename Type>
SeqList<Type>::~SeqList()
{
	delete[]base;
	base = nullptr;
	capacity = _size = 0;
}

/////////////////////////////////////////////
////�Ƿ����
template <typename Type>
bool SeqList<Type>:: full()const
{
	return _size >= capacity;
}

/////////////////////////////////////////////
////�Ƿ�Ϊ��
template <typename Type>
bool SeqList<Type>::empty()const
{
	return _size == 0;
}

/////////////////////////////////////////////
////�󳤶�
template <typename Type>
size_t SeqList<Type>::size()const
{return _size;}

/////////////////////////////////////////////
////����
template <typename Type>
bool SeqList<Type>::Expansion()
{
	
	Type* new_base;
	try
	{
		new_base = new Type[2 * capacity + 1];//��һ���ռ䲻�洢����
	}
	catch (bad_alloc &e)
	{
		cout << "Out Of Memory" << endl;
		return false;
	}

	memset(new_base, 0, sizeof(Type)*(capacity*2 + 1));
	for (int i = 1; i <= _size; ++i)
	{
		new_base[i] = base[i];
	}
	delete[]base;
	capacity *= 2;
	base = new_base;
	return true;
}

/////////////////////////////////////////////
////β������
template <typename Type>
void SeqList<Type>::push_back(const Type &x)
{
	if (full())//��ʾ��������Ҫ����
	{
		Expansion();
	}
	base[++_size] = x;
}

/////////////////////////////////////////////
////ͷ������
template <typename Type>
void SeqList<Type>::push_front(const Type &x)
{
	if (full())//��ʾ��������Ҫ����
	{
		Expansion();
	}
	for (size_t i = _size; i > 0; --i)
		base[i + 1] = base[i];
	base[1] = x;
	_size++;
}

/////////////////////////////////////////////
////β��ɾ��
template <typename Type>
void SeqList<Type>::pop_back()
{
	if (empty())
		return;
	_size--;
}

/////////////////////////////////////////////
////ͷ��ɾ��
template <typename Type>
void SeqList<Type>::pop_front()
{
	if (empty())
		return;
	for (size_t i = 1; i <_size; ++i)
		base[i] = base[i + 1];
	_size--;
}

/////////////////////////////////////////////
////ȡ����Ԫ��
template <typename Type>
typename SeqList<Type>::reference SeqList<Type>::front()
{
	if (empty())
		ERR_EXIT("front");
	return base[1];
}
template <typename Type>
typename SeqList<Type>::const_reference SeqList<Type>::front()const
{
	if (empty())
		ERR_EXIT("front");
	return base[1];
}

/////////////////////////////////////////////
////ȡ�����һ��Ԫ��
template <typename Type>
typename SeqList<Type>::reference SeqList<Type>::back()
{
	if (empty())
		ERR_EXIT("back");
	return base[_size];
}
template <typename Type>
typename SeqList<Type>::const_reference SeqList<Type>::back()const
{
	if (empty())
		ERR_EXIT("back");
	return base[_size];
}

/////////////////////////////////////////////
////��ת
template <typename Type>
void SeqList<Type>::reverse()
{
	if (_size <= 1)
		return;
	size_t start = 1, end = _size;
	while (start < end)
	{
		Type tmp = base[start];
		base[start] = base[end];
		base[end] = tmp;
		start++;
		end--;
	}
}

/////////////////////////////////////////////
////���
template <typename Type>
void SeqList<Type>::clear()
{_size = 0;}

/////////////////////////////////////////////
////����
template <typename Type>
void SeqList<Type>::sort()
{
	if (_size <= 1)
		return;
	for (size_t i = 0; i < _size; ++i)
	{
		for (size_t j = 1; j <= _size - i - 1; ++j)
		{
			if (base[j]>base[j+1])
			{
				Type tmp = base[j];
				base[j] = base[j+1];
				base[j+1] = tmp;
			}
		}
	}
}

/////////////////////////////////////////////
////����
template <typename Type>
int SeqList<Type>::find(const Type &key)
{
	for (size_t i = 1; i <= _size; ++i)
	{
		if (base[i] == key)
			return i;
	}
	return -1;
}

/////////////////////////////////////////////
////ɾ��
template <typename Type>
void SeqList<Type>::erase(const Type &key)
{
	size_t pos = find(key);
	if (pos == -1)
		return;
	for (size_t i = pos; i < _size; ++i)
		base[i] = base[i + 1];
	_size--;
}

/////////////////////////////////////////////
////���� =
template<class Type>
SeqList<Type>& SeqList<Type>::operator=(const SeqList<Type> &st)
{
	if (this != &st)
	{
		if (capacity < st._size)
		{
			Type* new_base = new Type[st.capacity + 1];
			delete[] base;
			base = new_base;
			capacity = st.capacity;
		}
		memcpy(base,st.base,sizeof(Type)*(st._size+1));
		_size = st._size;
	}
	return *this;
}

/////////////////////////////////////////////
////����[]
template <typename Type>
typename SeqList<Type>::reference SeqList<Type>::operator[](int pos)
{
	return base[pos];
}

template <typename Type>
typename SeqList<Type>:: const_reference SeqList<Type>:: operator[](int pos)const
{
	return base[pos];
}

#endif /*_SEQLIST_H_*/