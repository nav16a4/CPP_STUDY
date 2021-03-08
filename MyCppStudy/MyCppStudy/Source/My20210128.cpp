#include "My20210128.h"
#include <array>
#include <iostream>
#include <WinSock2.h>
void My20210128::main0()
{
	int aa = 35;
	TestClass testa(aa);

//	int& b = testa.Geta(b);

	//std::cout << b;

	
	
}

void My20210128::main1()
{
	std::array<char, 128> strarray;
	const char* name = "abcde";
	strarray.fill(0);
	auto a= strarray.data();
	memcpy_s(a, strarray.max_size(), name, 6);
	std::cout << strarray.data()<<strarray.max_size()<<" , "<<strarray.size();
}
