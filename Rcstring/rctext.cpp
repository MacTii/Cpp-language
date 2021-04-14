#include "rctext.h"

rcstring::rctext::rctext(unsigned int nsize, const char* p)
{
	n = 1;
	size = nsize;
	s = new char[size + 1];
	strncpy(s, p, size);
	s[size] = '\0';
}

rcstring::rctext::~rctext()
{
	delete[] s;
}

rcstring::rctext* rcstring::rctext::detach()
{
	if (n == 1)
		return this;
	rctext* t = new rctext(size, s);
	n--;
	return t;
}
