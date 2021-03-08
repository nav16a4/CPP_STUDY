#pragma once
#include <any>
#include <functional>

namespace My20210227
{
	void main();
	void main1();
	void main2();

	template <class T>
	class Test
	{
	public:
		Test(T t) {}
		void test(T t, int n) {}

	};
	template <class R, class... Args>
	R example(std::function<R(Args...)>func, Args... args)
	{
		return func(args...);
	}

	template <class R, class... Args>
	std::any example1(std::function<R(Args...)>func, Args... args)
	{
		std::any any = func(args...);
		return any;
	}

	template <class... Types>
	class Test1
	{
	public:
		Test1(Types... args){}
		void Test(Types... args,int n)
		{
			
			
		}
		void print();
	};
	
	/*template<class ...Types>
	inline void My20210227::Test1<Types... >::print()
	{
	}
	template<class Type>
	inline void My20210227::Test1<Type>::print()
	{
	}*/

};

