#include "My20210127.h"

int My20210127::main()
{
	Init init;

	auto test = TestClass::TestClassBuilder(init);
	test.SetA(1);
	test.SetC(34);
	auto testclass = test.build();

	testclass.Show();
	
    return 0;
}
My20210127::TestClass::TestClassBuilder::TestClassBuilder(Init& a)
	: a1(a.test1()) , b1(a.test2()) , c1(a.test3())
{

	

	
}