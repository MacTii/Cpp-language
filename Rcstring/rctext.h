#ifndef __RCTEXT_H__
#define __RCTEXT_H__

#include "rcstring.h"

struct rcstring::rctext
{
		char* s;
		unsigned int size;
		unsigned int n;

		rctext(unsigned int nsize, const char* p);
		~rctext();
		rctext* detach();
	private:
		rctext(const rctext&);
		rctext& operator=(const rctext&);
};

#endif