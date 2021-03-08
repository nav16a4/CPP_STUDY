#include "My20210225.h"
#include <typeinfo>

void My20210225::testfunc123(int a, float b, char c)
{
	std::cout << "a : " << a << " b: " << b << " c: " << c << std::endl;

}

void My20210225::makeanyvector(std::vector<std::any>& v)
{
}




void My20210225::main()
{
	
	auto func = myfunction(stdfunction(testfunc123));
	auto tt = anyvector(4, 0.123f, 'c');
	
	auto t =func(tt);
	std::cout << typeid(t).name();
}

