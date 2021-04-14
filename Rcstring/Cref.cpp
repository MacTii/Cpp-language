#include "cref.h"

using namespace std;

rcstring::Cref::operator char() const
{
	//cout << "operator char() const"<<endl;
	return s.read(i);
}

rcstring::Cref& rcstring::Cref::operator = (char c)
{
	//cout << "void operator = (char c)"<<endl;
	s.write(i, c);
	return *this;
}

rcstring::Cref& rcstring::Cref::operator = (const Cref& ref)
{
	return operator= ((char)ref);
}