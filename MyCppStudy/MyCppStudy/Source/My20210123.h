#pragma once
#include <functional>
#include <vector>
#include <cassert>
#include <mutex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
namespace MyStudy20210123
{
	class MyString
	{
	private:
		MyString() = default;
		MyString(MyString&&) = delete;
		MyString(const MyString&) = delete;
		MyString& operator=(const MyString&) = delete;
		MyString& operator=(MyString&&) = delete;

		size_t Size(void) { return 0; }
		size_t Size(const char* c) { return ::strlen(c); }
		size_t Size(std::string& str) { return str.size(); }
		template <class Type>
		size_t Size(Type data) { return sizeof(data); }
		size_t Size(bool) { return 6; }
		template <class Type, class... Types>
		size_t Size(Type first, Types... others)
		{
			return Size(first) + Size(others...);
		}

		//Logger클래스에서 필요하여 추가
		template <class Type, class... Types>
		size_t SizeWith(char* ch,Type first, Types... others)
		{
			//strlen(ch)은 마지막 띄어쓰기에 추가적으로 들어가는 길이
			return strlen(ch) + Size(ch,first) + Size(ch,others...);
		}
		
		std::string MakeString(void) { return std::string(); }
		std::string MakeString(int integer) { return std::to_string(integer); }
		std::string MakeString(long integer) { return std::to_string(integer); }
		std::string MakeString(unsigned long integer) { return std::to_string(integer); }
		std::string MakeString(long long integer) { return std::to_string(integer); }
		std::string MakeString(unsigned long long integer) { return std::to_string(integer); }

		std::string MakeString(float decimal) { return std::to_string(decimal); }
		std::string MakeString(double decimal) { return std::to_string(decimal); }
		std::string MakeString(long double decimal) { return std::to_string(decimal); }


		std::string MakeString(const char* ch) { return std::string(ch); }
		std::string MakeString(char* ch) { return std::string(ch); }
		std::string MakeString(std::string str) { return str; }
		std::string MakeString(std::string& str) { return std::string(str); }
		std::string MakeString(bool trueorfalse) { return std::string((trueorfalse ? "true" : "false")); }
		
		template <class T>
		std::string MakeStringWithBlank(T t) { return MakeString(t)+" "; }

		void Append(std::string& dest)
		{
			return;
		}
		template <class Type, class... Types>
		void Append(std::string& dest, Type source)
		{
			dest.append(MakeString(source));
			return;
		}
		
		template <class Type, class... Types>
		void Append(std::string& dest, Type source, Types... next)
		{
			dest.append(MakeString(source));
			Append(dest, next...);
			return;
		}
		template <class Type>
		void AppendWith(std::string& dest, char* ch, Type source)
		{
			dest.append(MakeString(source));
			dest.append(ch);
			//마지막 띄어쓰기 넣기
			Append(dest, ch, source,ch);
			return;
		}
		template <class Type, class... Types>
		void AppendWith(std::string& dest,char* ch, Type source, Types... next)
		{
			dest.append(MakeString(source));
			dest.append(ch);
			AppendWith(dest,ch, next...);
			
			return;
		}
		template <class Type>
		std::string String(Type first)
		{
			return [&]()->std::string {return MakeString(first); };
		}
	//	template <class Type>
	//	std::string String2(Type first)
	//	{
	//		return [&]()->std::string {return MakeString2(first); };
	//	}

		template <class Type, class... Types>
		std::string String(Type first, Types... others)
		{
			int size = Size(first, others...);
			std::string str = "";
			str.reserve(size);
			Append(str, first, others...);
			return str;
		}
		template <class Type, class... Types>
		std::string StringWith( char* ch,Type first, Types... others)
		{
			std::string str = "";
			//str.reserve(64);
			int size = SizeWith(ch,first, others...);
			str.reserve(size);
			AppendWith(str,ch, first, others...);
			return str;
		}
	public:
		template <class Type, class... Types>
		static friend std::string MyMakeString(Type first, Types... others);
		template <class Type, class... Types>
		static friend std::string MyMakeStringWith(char* ch,Type first, Types... others);

	};
	template <class Type, class... Types>
	static std::string MyMakeString(Type first, Types... others)
	{
		static MyString* mystring = new MyString;
		return mystring->String(first, others...);
	}
	template <class Type, class... Types>
	static std::string MyMakeStringWith(char* ch,Type first, Types... others)
	{
		static MyString* mystring = new MyString;
		return mystring->StringWith(ch,first, others...);
	}

	class LogStream
	{
		std::ostream* m_os;
		std::ofstream* m_ofs;
		std::function<void(std::string&)> func = nullptr;
		void LogToConsole(std::string& s)
		{
			*m_os << s;
		}
		void LogToFile(std::string& s)
		{
			*m_ofs << s;
		}
		void LogToConsoleAndFile(std::string& s)
		{
			*m_os << s;
			*m_ofs << s;
		}
		void LogNothing(std::string& s) {}
	public:
		LogStream(const char* ch ="\0") : m_os(nullptr), m_ofs(nullptr) 
		{
			func = std::bind(&LogStream::LogNothing, this, std::placeholders::_1);
		}
		LogStream(std::ostream* os) : m_os(os), m_ofs(nullptr)
		{
			func = std::bind(&LogStream::LogToConsole, this, std::placeholders::_1);
		}
		LogStream(std::ofstream* ofs) : m_os(nullptr), m_ofs(ofs)
		{
			func = std::bind(&LogStream::LogToFile, this, std::placeholders::_1);
		}
		LogStream(std::ostream* os, std::ofstream* ofs) : m_os(os), m_ofs(ofs)
		{
			func = std::bind(&LogStream::LogToConsoleAndFile, this, std::placeholders::_1);
		}
		void Write(std::string& s) { func(s); }
	};

	class StringFunc
	{
	private:
		const std::function<std::string(void)> func;
		const std::string str;
	public:
		StringFunc(std::function<std::string(void)> str_func) : func(str_func), str(std::string("")) {}
		StringFunc(std::string const_str) : func(nullptr), str(const_str) {}
		StringFunc(const char* ch) : func(nullptr), str(std::string(ch)) {}

		std::string GetString(void)
		{
			return func != nullptr ? func() : str;
		}
	};

	template <typename ReturnType, typename... Args>
	class Logger
	{

	public:
		LogStream& m_logstream;
		std::vector<StringFunc> makeString;
		std::function<ReturnType(Args ...)> func;
	public:
	private:
		void PushStringFunction(void)
		{
			return;
		}
		template <class T>
		void PushStringFunction(T& str)
		{
			makeString.push_back(StringFunc(str));
		}
		template <class T, class ...Ts>
		void PushStringFunction(T& str, Ts& ...strs)
		{
			makeString.push_back(StringFunc(str));
			PushStringFunction(strs...);
		}
	public:
		Logger(LogStream& logstream ,std::function<ReturnType(Args...)> func) : func{ func } , m_logstream(logstream) 
		{
		}

		template <class... StrFunc>
		Logger(LogStream& logstream, std::function<ReturnType(Args...)> func, StrFunc... strfunc) : func{ func } , m_logstream(logstream)
		{
			PushStringFunction(strfunc...);
		}
		ReturnType operator() (Args... args)
		{
			std::string str = "";
			for (auto &iter : makeString)
			{
				std::string temp = iter.GetString().append(m_ch);
				str.append(temp);
			}
			if ('\0' == *m_ch) {str.append(MyMakeString(args...));}
			else {str.append(MyMakeStringWith(m_ch,args...));}
			
			m_logstream.Write(str.append("시작\n"));
			ReturnType result = func(args...);
			str.erase(str.end() - 1); //끝 '\n' 제거
			m_logstream.Write(str.append(" - 완료\n"));

			return result;
		};
		
	};
	template < typename... Args>
	class Logger//<ReturnType(Args...)>
	{

	public:
		LogStream& m_logstream;
		std::vector<StringFunc> makeString;
		std::function<void(Args ...)> func;
	public:
	private:
		void PushStringFunction(void)
		{
			return;
		}
		template <class T>
		void PushStringFunction(T& str)
		{
			makeString.push_back(StringFunc(str));
		}
		template <class T, class ...Ts>
		void PushStringFunction(T& str, Ts& ...strs)
		{
			makeString.push_back(StringFunc(str));
			PushStringFunction(strs...);
		}
	public:
		Logger(LogStream& logstream, std::function<ReturnType(Args...)> func) : func{ func }, m_logstream(logstream)
		{
		}

		template <class... StrFunc>
		Logger(LogStream& logstream, std::function<ReturnType(Args...)> func, StrFunc... strfunc) : func{ func }, m_logstream(logstream)
		{
			PushStringFunction(strfunc...);
		}
		void operator() (Args... args)
		{
			std::string str = "";
			for (auto& iter : makeString)
			{
				std::string temp = iter.GetString().append(m_ch);
				str.append(temp);
			}
			if ('\0' == *m_ch) { str.append(MyMakeString(args...)); }
			else { str.append(MyMakeStringWith(m_ch, args...)); }

			m_logstream.Write(str.append("시작\n"));
			func(args...);
			str.erase(str.end() - 1); //끝 '\n' 제거
			m_logstream.Write(str.append(" - 완료\n"));

			return ;
		};
	};



	/*template <class R, class... Args, class... T>
	auto makelog(LogStream& logstream, R(*func)(Args...), T... strfuncs)
	{
		return Logger<R, Args...>(logstream,std::func00<R(Args...)>(func), strfuncs...);
	};*/
	template <class R, class... Args, class... T>
	auto makelog(LogStream& logstream, std::function<R(Args...)>& func, T... strfuncs)
	{
		return Logger<R, Args...>(logstream, std::function<R(Args...)>(func), strfuncs...);
	};


	
	//template <class R, class... Args, class... T>
	//auto makelog(R(*func)(Args...), T... strfuncs)
	//{
	//	return Logger<R, Args...>(std::func00<R(Args...)>(func), strfuncs...);
	//};
	static std::string MyGetTime()
	{
		char date[7][4] = {
		"SUN","MON","TUE","WED","THU","FRI","SAT"
		};

		std::string returnString;
		const int UTC = +9;

		std::stringstream ss;
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		std::tm today;
		__time64_t t = std::chrono::system_clock::to_time_t(now);
		_localtime64_s(&today, &t);

		ss << "[" << (today.tm_year + 1900) << '-'
			<< (today.tm_mon + 1) << '-'
			<< today.tm_mday << " "
			<< date[(today.tm_wday)] << " ";


		auto duration = now.time_since_epoch();

		typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<UTC>	>::type> Days;
		Days days = std::chrono::duration_cast<Days>(duration);
		duration -= days;
		auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
		duration -= hours;
		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
		duration -= minutes;
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
		duration -= seconds;
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
		duration -= milliseconds;
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
		//duration -= microseconds;
		//auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

		ss << today.tm_hour << "H"
			<< minutes.count() << "M"
			<< seconds.count() << "."
			<< milliseconds.count() << microseconds.count()/* << nanoseconds.count()*/ << "S]";

		returnString = ss.str();

		return returnString;
	}
	
	void main();
	void main1();
}
