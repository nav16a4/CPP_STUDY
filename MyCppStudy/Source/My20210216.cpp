#include "My20210216.h"


#include <bitset>
#include <iostream>

void My20210216::main()
{
	A a;
	B b;
	b.Subscribe(&a);

	b.Test(56, 1024);
}


