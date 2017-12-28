// Adapter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Adapter.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	ClassTextShape c;
	c.IsEmpty();

	TextView tv;
	ObjectTextShape o(&tv);
	o.IsEmpty();

	return 0;
}

