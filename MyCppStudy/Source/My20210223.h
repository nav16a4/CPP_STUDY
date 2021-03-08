#pragma once
#include <functional>
#include <any>
#include <vector>
#include <iostream>
namespace My20210223
{
	void main();

	template <class R, class... Args>
	std::function<R(Args...)> makefuncptr0(R(*func)(Args...))
	{
		std::function<R(Args...)> temp = func;
		return temp;
	}
	template <class T0, class T1, class T2>
	auto makefuncptr(std::function<void(T0, T1, T2)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			func(v0, v1, v2);
		};
	}
	template <class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
	auto makefuncptr(std::function<void(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			T7 v7 = std::any_cast<T7>(args[7]);
			T8 v8 = std::any_cast<T8>(args[8]);
			T9 v9 = std::any_cast<T9>(args[9]);
			T2 v10 = std::any_cast<T10>(args[10]);
			T11 v11 = std::any_cast<T11>(args[11]);
			T12 v12 = std::any_cast<T12>(args[12]);
			T13 v13 = std::any_cast<T13>(args[13]);
			T14 v14 = std::any_cast<T14>(args[14]);
			T15 v15 = std::any_cast<T15>(args[15]);
			func(v0, v1, v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15);
		};
	}
};

