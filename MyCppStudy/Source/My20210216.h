#pragma once
#include <vector>
#include <functional>
#include <iostream>

namespace My20210216
{

	template <class Type ,class... Args>
	struct Observer
	{
	
		virtual ~Observer() {}
		virtual  void Update(Type& , Args... ) = 0;
	};
	template <class Type, class... Args>
	struct Observable
	{
		void Notify(Type& source, Args... args )
		{
			for (auto iter : observers)
			{
				iter->Update( source, args...);
			}
		}
		void Subscribe(Observer<Type,Args...>* f)
		{
			observers.push_back(f);
		}
		void Unsubscribe(Observer<Type,Args...>* f) {  }
	private:
		std::vector<Observer<Type,Args...>*> observers;
		//std::mutex mutex;
		//여러 스레드 병렬적으로 동시에 사용할 것이므로 그냥 락을 걸면 곤란
	};
	struct Some
	{
		int some = 0;
	};

	class A : public Observer<Some,int>
	{
	public:
		

		void Update(Some& a, int b) override
		{
			std::cout << a.some << "과 " << b << "가 옴" << std::endl;
		}
	};

	class B : public Observable<Some,int>
	{
	public:
		void Test(int a, int b)
		{
			Some aa;
			aa.some = a;

			Notify(aa, b);
		}

		
	};
	
	void main();

	
	
};
