#pragma once
#include <functional>
#include <string>
#include <sstream>
#include <ostream>
#include <fstream>
#include <algorithm>
#include <chrono>
namespace My20210131
{


	static std::string GetCurrTimeString();


	void main();
	;



#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define __MYFUNC__ fmt::format("File:{} Func:{} Line:{}",__FILENAME__,__FUNCTION__,__LINE__)
#define MYFUNC(name) fmt::format("File:{} Func:{} Line:{} call: {}",__FILENAME__,__FUNCTION__,__LINE__,#name)

	void Type(std::stringstream& ss, char ch);
	void Type(std::stringstream& ss, int n);
	template <class T, int N>
	void Type(std::stringstream& ss, const std::array<T, N>& array)
	{

		ss << " array " << N << " \n";
		int i = 0;
		for (auto iter = array.cbegin(); iter < array.cend(); ++iter)
		{
			if (0 == (i) % 16) { ss << i << "\t||"; }
			ss << i % 16 << "[" << (int)*iter << "]";
			if (0 == (++i) % 16) { ss << "\n\n"; }
		}
		//for(const auto& iter: array)
		//{
		//	//ss << const_cast<int>(iter);
		//	ss <<"[" << (int)iter<<"]";
		//}
		return;
	}



	class MyStringFunc
	{
	private:
		const std::function<std::string(void)> func;
		const std::string str;
	public:
		MyStringFunc(std::function<std::string(void)> str_func) : func(str_func), str(std::string("")) {}
		MyStringFunc(std::string const_str) : func(nullptr), str(const_str) {}
		MyStringFunc(const char* ch) : func(nullptr), str(std::string(ch)) {}

		std::string operator()(void)
		{
			return func != nullptr ? func() : str;
		}
	};


	class LogStream
	{
		std::ostream* m_os;
		std::ofstream* m_ofs;
		std::function<void(std::string&)> func = nullptr;

		void LogToConsole(std::string& s);
		void LogToFile(std::string& s);
		void LogToConsoleAndFile(std::string& s);
		void LogNothing(std::string& s);
	public:
		LogStream();
		LogStream(std::ostream* os);
		LogStream(std::ofstream* ofs);
		LogStream(std::ofstream* ofs, std::ostream* os);
		LogStream(std::ostream* os, std::ofstream* ofs);
		void Write(std::string& s);
		void Write(std::string&& s);
	};
	LogStream& operator<<(LogStream& ls, std::string& s);
	LogStream& operator<<(LogStream& ls, std::string&& s);
	LogStream& operator<<(LogStream& ls, const char* c);

	

	template <typename ReturnType, typename... Args>
	class Logger
	{
	public:
		LogStream& m_logstream;
		//std::vector<MyStringFunc> makeString;
		std::function<std::string(void)> m_timestring = GetCurrTimeString;
		std::vector<std::string> makeString;
		std::function<ReturnType(Args ...)> func;

	public:
	private:
		void PushBackStrFunc(void)
		{
			return;
		}
		template <class T>
		void PushBackStrFunc(T& str)
		{
			makeString.push_back(MyStringFunc(str));

		}


	public:

		Logger(LogStream& logstream, std::function<ReturnType(Args...)> func) : func{ func }, m_logstream(logstream)
		{

		}

		//template <class... StrFunc>
		//Logger(LogStream& logstream, std::func00<ReturnType(Args...)> func, StrFunc... strfunc) : func{ func }, m_logstream(logstream)
		//{
		//	PushBackStrFunc(strfunc...);
		//}

		Logger(LogStream& logstream, std::function<ReturnType(Args...)> func, std::function<std::string(void)> timestring) : func{ func }, m_logstream(logstream), m_timestring(timestring)
		{

		}

		template <class T>
		Logger& operator<<(T t)
		{
			//PushBackStrFunc(t);
			makeString.push_back(std::string(t));
			return *this;
		}

		void value(std::stringstream& ss)
		{
			return;
		}
		template <class T>
		void value(std::stringstream& ss, T&& t)
		{
			ss << "[";
			Type(ss, t);
			ss << ":" << (int)t << "]";
			return;
		}
		template <class T, class... Ts>
		void value(std::stringstream& ss, T&& t, Ts&&... ts)
		{
			value(ss, t);
			value(ss, ts...);
			return;
		}
		ReturnType operator() (Args... args)
		{
			ReturnType result;
			memset(&result, 0, sizeof(result));
			std::stringstream ss;
			ss.str("");
			ss << m_timestring();

			std::stringstream temp;
			for (auto& iter : makeString)
			{
				temp << iter;
				temp << " ";
			}
			value(temp, args...);

			ss << temp.str();
			ss << " Begin\n";
			m_logstream.Write(ss.str());
			try
			{
				result = func(args...);

				ss.str("");
				ss << m_timestring();
				ss << temp.str();
				ss << " End\n";
				m_logstream.Write(ss.str());
				ss.str("");
				temp.str("");
			}
			catch (std::exception& ex)
			{
				ss.str("");
				ss << m_timestring() << temp.str() << ex.what() << " Fail\n";
				m_logstream.Write(ss.str());
			}
			return result;
		};

		/*template< class...Args>
		void operator() (Args... args)
		{
			
			std::stringstream ss;
			ss.str("");
			ss << m_timestring();

			std::stringstream temp;
			for (auto& iter : makeString)
			{
				temp << iter;
				temp << " ";
			}
			value(temp, args...);

			ss << temp.str();
			ss << " Begin\n";
			m_logstream.Write(ss.str());
			try
			{
				func(args...);

				ss.str("");
				ss << m_timestring();
				ss << temp.str();
				ss << " End\n";
				m_logstream.Write(ss.str());
				ss.str("");
				temp.str("");
			}
			catch (std::exception& ex)
			{
				ss.str("");
				ss << m_timestring() << temp.str() << ex.what() << " Fail\n";
				m_logstream.Write(ss.str());
			}
			return;
		};*/
	};
	template <class R, class... Args>
	auto makelog(LogStream& logstream, std::function<R(Args...)> func)
	{
		return Logger<R, Args...>(logstream, std::function<R(Args...)>(func));
	};
	template <class R, class... Args>
	auto makelog(LogStream& logstream, R(*func)(Args...))
	{
		std::function<R(Args...)> function = func;
		return Logger<R, Args...>(logstream, function);
	};
	template <class R, class... Args, class... T>
	auto makelog(LogStream& logstream, std::function<R(Args...)> func, T... strfuncs)
	{
		return Logger<R, Args...>(logstream, std::function<R(Args...)>(func), strfuncs...);
	};
	template <class R, class... Args, class... T>
	auto makelog(LogStream& logstream, R(*func)(Args...), T... strfuncs)
	{
		std::function<R(Args...)> function = func;
		return Logger<R, Args...>(logstream, function, strfuncs...);
	};

	template <typename... Args>
	class Logger<void, Args...>
	{
	public:
		LogStream& m_logstream;
		std::function<std::string(void)> m_timestring = GetCurrTimeString;
		std::vector<std::string> makeString;
		std::function<void(Args ...)> func;
	public:

		Logger(LogStream& logstream, std::function<void(Args...)> func) : func{ func }, m_logstream(logstream){	}
		Logger(LogStream& logstream, std::function<void(Args...)> func, std::function<std::string(void)> timestring) : func{ func }, m_logstream(logstream), m_timestring(timestring)	{	}
		template <class T>
		Logger& operator<<(T t)
		{
			makeString.push_back(std::string(t));
			return *this;
		}

		void value(std::stringstream& ss)
		{
			return;
		}
		template <class T>
		void value(std::stringstream& ss, T&& t)
		{
			ss << "[";
			Type(ss, t);
			ss << ":" << (int)t << "]";
			return;
		}
		template <class T, class... Ts>
		void value(std::stringstream& ss, T&& t, Ts&&... ts)
		{
			value(ss, t);
			value(ss, ts...);
			return;
		}
		void operator() (Args... args)
		{
			std::stringstream ss;
			ss.str("");
			ss << m_timestring();

			std::stringstream temp;
			for (auto& iter : makeString)
			{
				temp << iter;
				temp << " ";
			}
			value(temp, args...);

			ss << temp.str();
			ss << " Begin\n";
			m_logstream.Write(ss.str());
			try
			{
				func(args...);

				ss.str("");
				ss << m_timestring();
				ss << temp.str();
				ss << " End\n";
				m_logstream.Write(ss.str());
				ss.str("");
				temp.str("");
			}
			catch (std::exception& ex)
			{
				ss.str("");
				ss << m_timestring() << temp.str() << ex.what() << " Fail\n";
				m_logstream.Write(ss.str());
			}
			return;
		};
	};
	template <class... Args>
	auto makelog(LogStream& logstream, std::function<void(Args...)> func)
	{
		return Logger<void, Args...>(logstream, std::function<void(Args...)>(func));
	};
	template <class... Args>
	auto makelog(LogStream& logstream, void(*func)(Args...))
	{
		std::function<void(Args...)> function = func;
		return Logger< void, Args...>(logstream, function);
	};
	template < class... Args, class... T>
	auto makelog(LogStream& logstream, std::function<void(Args...)> func, T... strfuncs)
	{
		return Logger< void, Args...>(logstream, std::function<void(Args...)>(func), strfuncs...);
	};
	template < class... Args, class... T>
	auto makelog(LogStream& logstream, void(*func)(Args...), T... strfuncs)
	{
		std::function<void(Args...)> function = func;
		return Logger< void, Args...>(logstream, function, strfuncs...);
	};
	
}
