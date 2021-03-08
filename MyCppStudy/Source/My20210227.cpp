#include "My20210227.h"


#include <any>
#include <iostream>

void My20210227::main()
{
	std::function<int(int)> func0 = [](int n)
	{
		return n * 2;
	};
	std::function<void(int)> func1 = [](int n)
	{
		std::cout << 2 * n<<std::endl;
	};

	std::cout << example(func0, 3) << std::endl;
	example(func1, 4);

	auto result0 = example1(func0, 5);

	std::cout << std::any_cast<int>(result0);
	//auto result1 = example1(func1, 6);

	
}

void My20210227::main1()
{
	char* n = nullptr;
	std::any a = nullptr;
	std::cout << typeid(a).name();
	auto aa = std::any_cast<void*>(a);
	std::cout << typeid(aa).name();

}

void My20210227::main2()
{
	Test<int> t(1);
	Test<void> tt(void);

	t.test(3,4);
	//tt.test(3);


	Test1<int> tttt(1);
	tttt.Test(3,3);

	Test<void> ttttt();
	tttt.Test(3.5f,4);
}
