#pragma once
#include <shared_mutex>
#include <tuple>
#include <any>
#include <vector>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <utility>
namespace My20210217
{
	void main();
	
	
	void write();
	void read();

	void main1();
	void test(int& a, int& b, int& c, int& d);


	template <class... Args >
	std::tuple<Args...> test1 (Args... args)
	{
		return std::make_tuple(args...);
	}
	void test2();

	void main2();


	void SetData(typename std::vector<std::any>::iterator iter);
	template <class T>
	void SetData(typename std::vector<std::any>::iterator iter, T& t)
	{
		t = std::any_cast<T>(*iter);
		return;
	}
	template <class T, class... Ts>
	void SetData(typename std::vector<std::any>::iterator iter, T& t, Ts&... ts)
	{
		SetData(iter, t);
		SetData(++iter, ts...);
		return;
	}
	template < class... Ts>
	void SetData(std::vector<std::any>& value, Ts&... ts)
	{
		typename std::vector<std::any>::iterator iter = value.begin();
		SetData(iter, ts...);
	}

	template <class R,class T1>
	void AAAA1(std::function<R(T1)> func, T1 t1)
	{
		func(t1);
	}
	
	
	template <class R, class...Args>
	void AA44(std::function<R(Args...)> func, std::vector<std::any>& value, Args&... args)
	{
		auto t = std::make_tuple(args);

		func( );
		
		return;
	}


	template<class R>
	R func00(std::function<R()> func, std::vector<std::any>& value)
	{
		return func();
	}
	template<class R, class T0>
	R func00(std::function<R(T0)> func, std::vector<std::any>& value)
	{
		T0 v0 = std::any_cast<T0>(value[0]);
		return func(v0);
	}
	template<class R, class T0, class T1>
	R func00(std::function<R(T0, T1)> func, std::vector<std::any>& value)
	{
		T0 v0 = std::any_cast<T0>(value[0]);
		T1 v1 = std::any_cast<T1>(value[1]);
		return func(v0, v1);
	}
	template<class R, class T0, class T1, class T2>
	R func00(std::function<R(T0, T1, T2)> func, std::vector<std::any>& value)
	{
		T0 v0 = std::any_cast<T0>(value[0]);
		T1 v1 = std::any_cast<T1>(value[1]);
		T2 v2 = std::any_cast<T2>(value[2]);
		return func(v0, v1, v2);
	}
	template<class R, class T0, class T1, class T2, class T3>
	R func00(std::function<R(T0, T1, T2, T3)> func, std::vector<std::any>& value)
	{
		T0 v0 = std::any_cast<T0>(value[0]);
		T1 v1 = std::any_cast<T1>(value[1]);
		T2 v2 = std::any_cast<T2>(value[2]);
		T3 v3 = std::any_cast<T3>(value[3]);
		
		
		return func(v0, v1, v2, v3);
	}
	template<class R, class T0, class T1, class T2, class T3, class T4>
	R func00(std::function<R(T0, T1, T2, T3, T4)> func, std::vector<std::any>& value)
	{
		T0 v0 = std::any_cast<T0>(value[0]);
		T1 v1 = std::any_cast<T1>(value[1]);
		T2 v2 = std::any_cast<T2>(value[2]);
		T3 v3 = std::any_cast<T3>(value[3]);
		T4 v4 = std::any_cast<T4>(value[4]);
		return func(v0, v1, v2, v3, v4);
	}
	template<class R, class T0, class T1, class T2, class T3, class T4, class T5>
	R func00(std::function<R(T0, T1, T2, T3, T4, T5)> func, std::vector<std::any>& value)
	{
		T0 v0 = std::any_cast<T0>(value[0]);
		T1 v1 = std::any_cast<T1>(value[1]);
		T2 v2 = std::any_cast<T2>(value[2]);
		T3 v3 = std::any_cast<T3>(value[3]);
		T4 v4 = std::any_cast<T4>(value[4]);
		T5 v5 = std::any_cast<T5>(value[5]);
		return func(v0, v1, v2, v3, v4, v5);
	}
	template<class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6>
	R func00(std::function<R(T0, T1, T2, T3, T4, T5, T6)> func, std::vector<std::any>& value)
	{
		T0 v0 = std::any_cast<T0>(value[0]);
		T1 v1 = std::any_cast<T1>(value[1]);
		T2 v2 = std::any_cast<T2>(value[2]);
		T3 v3 = std::any_cast<T3>(value[3]);
		T4 v4 = std::any_cast<T4>(value[4]);
		T5 v5 = std::any_cast<T5>(value[5]);
		T6 v6 = std::any_cast<T6>(value[6]);
		return func(v0, v1, v2, v3, v4, v5, v6);
	}
	template<class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
	R func00(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7)> func, std::vector<std::any>& value)
	{
		T0 v0 = std::any_cast<T0>(value[0]);
		T1 v1 = std::any_cast<T1>(value[1]);
		T2 v2 = std::any_cast<T2>(value[2]);
		T3 v3 = std::any_cast<T3>(value[3]);
		T4 v4 = std::any_cast<T4>(value[4]);
		T5 v5 = std::any_cast<T5>(value[5]);
		T6 v6 = std::any_cast<T6>(value[6]);
		T7 v7 = std::any_cast<T7>(value[7]);
		return func(v0, v1, v2, v3, v4, v5, v6, v7);
	}
	template<class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
	R func00(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7, T8)> func, std::vector<std::any>& value)
	{
		T0 v0 = std::any_cast<T0>(value[0]);
		T1 v1 = std::any_cast<T1>(value[1]);
		T2 v2 = std::any_cast<T2>(value[2]);
		T3 v3 = std::any_cast<T3>(value[3]);
		T4 v4 = std::any_cast<T4>(value[4]);
		T5 v5 = std::any_cast<T5>(value[5]);
		T6 v6 = std::any_cast<T6>(value[6]);
		T7 v7 = std::any_cast<T7>(value[7]);
		T8 v8 = std::any_cast<T8>(value[8]);
		return func(v0, v1, v2, v3, v4, v5, v6, v7, v8);
	}
	template<class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
	R func00(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)> func, std::vector<std::any>& value)
	{
		T0 v0 = std::any_cast<T0>(value[0]);
		T1 v1 = std::any_cast<T1>(value[1]);
		T2 v2 = std::any_cast<T2>(value[2]);
		T3 v3 = std::any_cast<T3>(value[3]);
		T4 v4 = std::any_cast<T4>(value[4]);
		T5 v5 = std::any_cast<T5>(value[5]);
		T6 v6 = std::any_cast<T6>(value[6]);
		T7 v7 = std::any_cast<T7>(value[7]);
		T8 v8 = std::any_cast<T8>(value[8]);
		T9 v9 = std::any_cast<T9>(value[9]);
		return func(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
	}
	template < class...Args>
	void testfunc000(std::function<void(Args...)> func, std::vector<std::any>& value)
	{
		func00(func, value);
		return;
	}
	template <class R, class...Args>
	auto testfunc000(std::function<R(Args...)> func, std::vector<std::any>& value)
	{
		return func00(func, value);
	}
	
}



