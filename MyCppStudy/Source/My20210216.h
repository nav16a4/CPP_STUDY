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
		//���� ������ ���������� ���ÿ� ����� ���̹Ƿ� �׳� ���� �ɸ� ���
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
			std::cout << a.some << "�� " << b << "�� ��" << std::endl;
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
