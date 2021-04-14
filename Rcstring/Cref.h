#ifndef __CREF_H__
#define __CREF_H__

#include "rcstring.h"

class rcstring::Cref
{
		friend class rcstring;
		rcstring& s;
		int i;
		Cref(rcstring& ss, unsigned int ii) : s(ss), i(ii) {};
	public:
		operator char() const;
		rcstring::Cref& operator = (char c);
		rcstring::Cref& operator = (const Cref& ref);
};

#endif