#include "My20210215.h"



#include <bitset>
#include <iomanip>
#include <ios>
#include <iostream>

void My20210215::main()
{



	

	char test[] = "abcdefg가나다라마바사";
	for (auto i : test)
	{
		std::cout << std::setfill('0') << std::setw(2) << std::hex << (0xff & (unsigned int)i) << " ";
	}
	std::cout << std::endl;
	wchar_t test2[] = L"abcdefg가나다라마바사";
	for (auto i : test2)
	{
		std::wcout << std::setfill(L'0') << std::setw(4) << std::hex << (0xffff & (int)i) << " ";
	}
	for (auto i : test2)
	{
		std::wcout << std::setfill(L'0') << std::setw(4) << std::hex << (0xffff & (int)i) << " ";
	}
	/*for (auto i : test)
	{
		std::cout << std::hex<<std::dec <<i;
	}*/
}

void My20210215::main1()
{
	std::cout << __FUNCTION__ << std::endl;
	for (int i = 1; i <= 4; ++i)
	{
		std::cout << std::bitset<32>(allbit1(i)) << "\t" << allbit1(i) << std::endl;
	}

	for (int i = 1; i <= 4; ++i)
	{
		std::cout << std::hex << allbit1(i) << std::endl;
	}
}

constexpr int My20210215::allbit1(const int size)
{
	int num = 0x0;
	for (int i = 0; i < size; ++i)
	{
		num = num << 8;
		num = num | 0xff;
	}
	return num;
}
