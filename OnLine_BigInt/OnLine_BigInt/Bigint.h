#ifndef _BIGINT_H_
#define _BIGINT_H_
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////������������

#include"SeqList.h"

class BigInt;
ostream& operator<<(ostream& out, const BigInt &bt);

class BigInt
{

public:
	BigInt(u_long val);
	BigInt()
	{}

	~BigInt()
	{}

public:
	void LoadDdata(int bit_size);//��������
	void push_back(u_char x);//����
	void clear();//���
	size_t size()const;//�󳤶�
public:
	static u_char  Add_Item(u_char a, u_char b, u_char& c);//��ĳһ��
	static void    MoveAdd(BigInt &bt, const BigInt &bt1, u_long offset);//��λ��ӣ����ڳ˷���
	static u_char  Sub_Item(u_char a, u_char b, u_char& c);//��ĳһ��
	static void    Mul_Item(BigInt &bt, const BigInt &bt1, u_char x);//��ĳһ��
	static void    Add(BigInt &bt, const BigInt &bt1, const BigInt &bt2);//�ӷ�
	static void    Sub(BigInt &bt, const BigInt &bt1, const BigInt &bt2);//����
	static void    Mul(BigInt &bt, const BigInt &bt1, const BigInt &bt2);//�˷�
	static void    Div(BigInt &bt, const BigInt &bt1, const BigInt &bt2);
	static void    Mod(BigInt &bt, const BigInt &bt1, const BigInt &bt2);
	static void    Square(BigInt &bt, const BigInt &bt1);//bt = bt1^2;
	static void    Power(BigInt &bt, const BigInt &bt1, u_long n);// bt =bt1^n;
	static void    Power(BigInt &bt, const BigInt &bt1, const BigInt &bt2);//bt = bt1^bt2
public:
	u_char operator[](int pos)const;
	u_char& operator[](int pos);
	friend ostream& operator<<(ostream& out, const BigInt &bt);
	BigInt operator+(const BigInt &bt);
	BigInt operator-(const BigInt &bt);
	BigInt operator*(const BigInt &bt);
	BigInt operator/(const BigInt &bt);
	BigInt operator%(const BigInt &bt);
public:
	BigInt& operator++();
	BigInt operator++(int);
	BigInt& operator--();
	BigInt operator--(int);
public:
	BigInt& operator+=(const BigInt &bt);
	BigInt& operator-=(const BigInt &bt);
	BigInt& operator*=(const BigInt &bt);
	BigInt& operator/=(const BigInt &bt);
	BigInt& operator%=(const BigInt &bt);

public:
	bool operator<(const BigInt &bt)const;
	bool operator>(const BigInt &bt)const;
	bool operator>=(const BigInt &bt)const;
	bool operator<=(const BigInt &bt)const;
	bool operator==(const BigInt &bt)const;
	bool operator!=(const BigInt &bt)const;
private:
	SeqList<u_char> _big;
};


#endif /*_BIGINT_H_*/