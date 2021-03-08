#include "My20210217.h"
#include <thread>
#include <chrono>
#include <iostream>
int n;
std::shared_mutex mutex;

void My20210217::main()
{
	std::thread a[9];
	a[0] = std::thread(write);

	for(int i=1;i<9;++i)
	{
		a[i] = std::thread(read);
	}

	for (int i = 0; i < 9; ++i)
	{
		a[i].join();
	}

	
}

void My20210217::write()
{
	while (true)
	{
		{
			std::cout << "쓰기 락 걸기 직전\n";
			std::lock_guard<std::shared_mutex> lockguard(mutex);
			
			std::cout << "쓰기 락 걸었음\n";
			std::this_thread::sleep_for(std::chrono::duration<float>(3.0f));
			++n;
			std::cout << "쓰기 락 곧 풀림3\n";
		}
		std::this_thread::sleep_for(std::chrono::duration<float>(0.5f));
		std::cout << "조금 있다 쓰기락 걸 예정\n";
	}
}

void My20210217::read()
{
	while (true)
	{
		{
			{
				std::shared_lock<std::shared_mutex> lockquard(mutex);
			
				std::cout << n;
			}
			std::this_thread::sleep_for(std::chrono::duration<float>(0.01f));
		}
	}
	
}
void temp2(int& a) {  a++; }
void temp1(int* a) { int& aa(*a);   return temp2(aa); }

void My20210217::main1()
{
	auto a=	test1(1, 5, 3.4);

	int abcint = 123;
	temp1(nullptr);
	std::cout << abcint;
	
}

void My20210217::test(int& a , int& b, int& c, int& d)
{
	std::cout << 1;
}

void My20210217::test2()
{
	int a = 1;
	std::type_index t = typeid(int);
	
	
}

void testfunc1( int a , float b, char c)
{
	std::cout << "a : " << a << " b: " << b << " c: " << c << std::endl;
	
}

void My20210217::main2()
{
	int a = 29;
	float b = 20.5f;
	char c = 'a';
	std::vector<std::any> vt;
	vt.push_back(std::any(a));
	vt.push_back(std::any(b));
	vt.push_back(std::any(c));

	int aa=0;
	float bb=0;
	char cc=0;
	SetData(vt, aa,bb,cc);
	//SetData(vt,aa,bb,cc);
	std::function<void(int, float, char)> ft = testfunc1;
	testfunc000(ft ,vt);
}

void My20210217::SetData(typename std::vector<std::any>::iterator iter)
{
}
