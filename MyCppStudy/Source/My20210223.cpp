#include "My20210223.h"


void testfunc123(int a, float b, char c)
{
	std::cout << "a : " << a << " b: " << b << " c: " << c << std::endl;

}

void My20210223::main()
{
	std::vector<std::any> v;
	v.push_back(1);
	v.push_back(0.5f);
	v.push_back('c');
	
	auto f = makefuncptr(makefuncptr0(testfunc123));

	f(v);
	
}
