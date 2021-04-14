#include <iostream>
#include <cassert>

#include "rctext.h"
#include "cref.h"
#include "rcstring.h"

using namespace std;

rcstring::rcstring()
{
	data = new rctext(0, "");
}

rcstring::rcstring(const rcstring& x)
{
	x.data->n++;
	data = x.data;
}
rcstring::~rcstring()
{
	if (--data->n == 0)
		delete data;
}

rcstring& rcstring::operator=(const rcstring & x)
{
	x.data->n++;
	if (--data->n == 0)
		delete data;
	data = x.data;
	return *this;
}

rcstring::rcstring(const char* s)
{
	data = new rctext(strlen(s), s);
}

std::ostream& operator << (std::ostream& o, const rcstring& s)
{
	return o << s.data->s;
}

rcstring& rcstring::operator+=(const rcstring & s)
{
	unsigned int newsize = data->size + s.data->size;
	rctext *newdata = new rctext(newsize, data->s);
	strcat(newdata->s, s.data->s);
	if (--data->n == 0)
		delete data;
	data = newdata;
	return *this;
}

rcstring rcstring::operator+(const rcstring & s) const
{
	return rcstring(*this) += s;
}

void rcstring::check(unsigned int i) const
{
	if (data->size <= i)
		throw Range();
}
char rcstring::read(unsigned int i) const
{
	return data->s[i];
}
void rcstring::write(unsigned int i, char c)
{
	data = data->detach();
	data->s[i] = c;
}

char rcstring::operator[](unsigned int i) const
{
	//cout << "char rcstring::operator[](unsigned int i) const"<<endl;
	check(i);
	return data->s[i];
}

rcstring::Cref rcstring::operator[](unsigned int i)
{
	//cout << "Cref rcstring::operator[](unsigned int i)"<<endl;
	check(i);
	return Cref(*this, i);
}

int rcstring::atoi()
{
	int result = 0;
	for (int i = 0; data->s[i] != '\0'; i++)
	{
		result = result * 10 + data->s[i] - '0';
	}
	return result;
}

rcstring& rcstring::toLower()
{
	for (int i = 0; data->s[i] != '\0'; i++)
	{
		if (data->s[i] >= 'A' && data->s[i] <= 'Z')
		{
			for (int j = 'A'; j <= 'Z'; j++)
			{
				if (data->s[i] == j)
				{
					data->s[i] = 'a' + j - 'A';
					break;
				}
			}
		}
	}
	return *this;
}

//rcstring rcstring::Left(int n)
//{
//
//
//}
