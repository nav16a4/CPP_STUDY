#pragma once
#include <iostream>

namespace My20210127
{
	struct Init
	{
		static constexpr int test1() { return 123; };
		static constexpr int test2() { return 456; };
		static constexpr int test3() { return 789; };
	};


	
	
	struct TestClass
	{
		TestClass(int *a, int b, int aa) : a1(*a),b1(b),c1(aa) {}
		const int a1;
		const int b1;
		const int c1;
		
		class TestClassBuilder
		{
			
			int a1;
			int b1;
			int c1;
		public:
			void SetA(int a) { a1 = a; }
			void SetB(int b) { b1 = b; }
			void SetC(int c) { c1 = c; }
		public:
			TestClassBuilder(Init& a);
			TestClass build() { return TestClass(&a1, b1, c1); }
		};
		void Show() { std::cout << "a1 : " << a1 << " b1 : " << b1<< " c1: " << c1 << std::endl; }
	};




	
	int main();
};

