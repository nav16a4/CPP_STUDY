#pragma once
#include <iostream>
#include <optional>
#include <vector>
namespace MyStudy20210124
{
	template <class Type>
	struct Observer
	{
		virtual ~Observer(){}
		virtual  void Changed(Type& source , int t) =0 ;
	};
	template <class Type>
	struct Observable
	{
		void Notify(Type& source , int num )
		{
			for( auto iter : observers)
			{
				iter->Changed(source, num);
			}
		}
		void Subscribe(Observer<Type>* f)
		{
			observers.push_back(f);
		}
		void Unsubscribe(Observer<Type>* f) {  }
	private:
		std::vector<Observer<Type>*> observers;
		
	};

	struct Player : Observable<Player>
	{
		const int number;
		Player(int n) : number(n) {}
		void move(const int n)
		{
			Notify(*this, n);
		}
	};
	struct PlayerObserver : public Observer<Player>
	{
		virtual void Changed(Player& p, int n) override
		{
			std::cout << p.number << "플레이어가 " << n << "움직임 감지\n";
		}
	};
	void main();
};

