/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////���������㹦�ܺ���ʵ��

#include"Bigint.h"

/////////////////////////////////////////////
////����
BigInt::BigInt(u_long val)
{
	if (val == 0)
		push_back(0);
	while (val)
	{
		push_back(val % 10);
		val /= 10;
	}
}

/////////////////////////////////////////////
////��������
void BigInt:: LoadDdata(int bit_size)
{
	srand(time(0));
	for (int i = 0; i < bit_size; ++i)
		_big.push_back(rand()%10);
}

/////////////////////////////////////////////
////����
void BigInt::push_back(u_char x)
{  _big.push_back(x);  }

/////////////////////////////////////////////
////����
size_t BigInt::size()const
{  return _big.size();  }

/////////////////////////////////////////////
////���
void BigInt::clear()
{
	_big.clear();
}

/////////////////////////////////////////////
////��ĳһ��
u_char BigInt::Add_Item(u_char a, u_char b, u_char& c)
{
	u_char sum = a + b + c;
	if (sum > 9)
	{
		sum -= 10;
		c = 1;
	}
	else
		c = 0;
	return sum;
}

/////////////////////////////////////////////
////�ӷ�
void BigInt::Add(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	u_char c = 0;
	u_char sum;
	size_t i=1,j=1;
	while (i <= bt1.size() && j <= bt2.size())
	{
		sum = Add_Item(bt1[i], bt2[j], c);
		bt.push_back(sum);
		j++;
		i++;
	}
	
	while (i <= bt1.size())
	{
		sum = Add_Item(bt1[i],0, c);
		bt.push_back(sum);
		++i;
	}
	while (j <= bt2.size())
	{
		sum = Add_Item(0, bt2[j], c);
		bt.push_back(sum);
		++j;
	}
	if (c > 0)
		bt.push_back(c);
		
}

/////////////////////////////////////////////
////��ĳһ��
u_char BigInt::Sub_Item(u_char a, u_char b, u_char& c)
{
	u_char sub;
	if (a >= b + c)
	{
		sub = a - b - c;
		c = 0;
	}
	else
	{
		sub = (a + 10) - b - c;
		c = 1;
	}
	return sub;
}

/////////////////////////////////////////////
////����
void BigInt::Sub(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	if (bt1 < bt2)
		return;
	else if (bt1 == bt2)
		bt = 0;
	else
	{
		bt.clear();
		u_long i, j;
		i = j = 1;
		u_char sub, c = 0;
		while (i <= bt1.size() && j <= bt2.size())
		{
			sub = Sub_Item(bt1[i], bt2[j], c);
			bt.push_back(sub);
			i++;
			j++;
		}
		while (i <= bt1.size())
		{
			sub = Sub_Item(bt1[i], 0, c);
			bt.push_back(sub);
			i++;
		}
	}
}

/////////////////////////////////////////////
////��ĳһ��
void BigInt::Mul_Item(BigInt &bt, const BigInt &bt1, u_char x)
{
	u_long i = 1;
	u_char res,c = 0;
	while (i <= bt1.size())
	{
		res = x * bt1[i] + c;
		c = res / 10;
		res %= 10;
		bt.push_back(res);
		i++;
	}
	if (c > 0)
		bt.push_back(c);
}

/////////////////////////////////////////////
////��λ��ӣ����ڳ˷���
void BigInt::MoveAdd(BigInt &bt, const BigInt &bt1, u_long offset)
{
	u_long i = offset;
	u_long j = 1;
	u_char c = 0;
	while (i <= bt.size() && j <= bt1.size())
	{
		bt[i] = Add_Item(bt[i],bt1[j],c);
		i++;
		j++;
	}
	while (c > 0 && i <= bt.size())
	{
		bt[i] = Add_Item(bt[i], 0, c);
		i++;
	}
	while (j <= bt1.size())
	{
		u_char sum = Add_Item(0, bt1[j], c);
		bt.push_back(sum);
		j++;
	}
	if (c>0)
	{
		bt.push_back(c);
	}
}

/////////////////////////////////////////////
////�˷�
void BigInt::Mul(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	if (bt1 == 0 || bt2 == 0)
		bt = 0;
	else
	{
		BigInt tmp;
		tmp.clear();
		for (u_long i = 1; i <= bt2.size(); ++i)
		{
			Mul_Item(tmp, bt1, bt2[i]);
			MoveAdd(bt,tmp,i);
			tmp.clear();
		}
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////����

/////////////////////////////////////////////
////����[]
u_char BigInt::operator[](int pos)const
{
	return _big[pos];
}
u_char& BigInt::operator[](int pos)
{
	return _big[pos];
}

/////////////////////////////////////////////
////���� <<
ostream& operator<<(ostream& out, const BigInt &bt)
{
	for (u_long i = bt.size(); i>0; --i)
		cout << (int)bt[i];
	return out;
}

/////////////////////////////////////////////
////���� ==
bool BigInt:: operator==(const BigInt &bt)const
{
	if (size() != bt.size())
		return false;
	for (u_long i = bt.size(); i > 0; --i)
	{
		if (_big[i] != bt[i])
			return false;
	}
	return true;
}

/////////////////////////////////////////////
////���� !=
bool BigInt:: operator!=(const BigInt &bt)const
{
	return !(*this==bt);
}

/////////////////////////////////////////////
////���� <
bool BigInt:: operator<(const BigInt &bt)const
{
	if (size() < bt.size())
		return true;
	else if (size() > bt.size())
		return false;
	else
	{
		for (u_long i = bt.size(); i > 0; --i)
		{
			if ((*this)[i] > bt[i])
				return false;
			else if ((*this)[i] < bt[i])
				return true;
		}
		return false;
	}
}

/////////////////////////////////////////////
////���� >=
bool BigInt:: operator>=(const BigInt &bt)const
{
	return !(*this < bt);
}


/////////////////////////////////////////////
////���� ++
BigInt& BigInt::operator++()//ǰ++
{
	BigInt tmp;
	Add(tmp, *this, 1);
	*this = tmp;
	return *this;
}
BigInt BigInt::operator++(int)//��++
{
	BigInt tmp = *this;
    ++*this;
	return tmp;
}

/////////////////////////////////////////////
////���� --
BigInt& BigInt::operator--()//ǰ--
{
	BigInt tmp;
	Sub(tmp, *this, 1);
	*this = tmp;
	return *this;
}
BigInt BigInt::operator--(int)//��--
{
	BigInt tmp = *this;
	--*this;
	return tmp;
}

/////////////////////////////////////////////
////���� +=
BigInt& BigInt::operator+=(const BigInt &bt)
{
	BigInt tmp;
	Add(tmp, *this, bt);
	*this = tmp;
	return *this;
}

/////////////////////////////////////////////
////���� -=
BigInt& BigInt::operator-=(const BigInt &bt)
{
	BigInt tmp;
	Sub(tmp, *this, bt);
	*this = tmp;
	return *this;
}

/////////////////////////////////////////////
////���� *=
BigInt& BigInt::operator*=(const BigInt &bt)
{
	BigInt tmp;
	Mul(tmp, *this, bt);
	*this = tmp;
	return *this;
}


/////////////////////////////////////////////
////���� +
BigInt BigInt::operator+(const BigInt &bt)
{
	BigInt tmp;
	Add(tmp, *this, bt);
	return tmp;
}

/////////////////////////////////////////////
////���� -
BigInt  BigInt::operator-(const BigInt &bt)
{
	BigInt tmp;
	Sub(tmp, *this, bt);
	return tmp;
}

/////////////////////////////////////////////
////���� *
BigInt BigInt::operator*(const BigInt &bt)
{
	BigInt tmp;
	Mul(tmp, *this, bt);
	return tmp;
}