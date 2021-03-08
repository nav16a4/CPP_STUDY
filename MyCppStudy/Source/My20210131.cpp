#include "My20210131.h"
#include <ostream>
#include <iostream>
#include <string>
#include <array>
#include <functional>
#include "fmt/core.h"
#include "fmt/format.h"
#pragma comment(lib,"fmtd")
#include <ostream>
#include <fstream>
#include <thread>

int test1(int n , int a)
{
	
	throw std::runtime_error(" 테스트 ");
	return n + a;
}
void test2(int n, int a)
{

	throw std::runtime_error(" 테스트2 ");
	return;
}

static std::string My20210131::GetCurrTimeString()

{
	const static char date[7][4] = {
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
void My20210131::main()
{
	/*std::string str = fmt::format("hell world {} \n", 345);
	std::cout << str;
	//
	//fmt::print(str);*/
	My20210131::LogStream logstream(&std::cout);
	//int a = 1;
	//float b = 0.5;
	//char c = 'c';
	//char chararraya[] = "간장공장공장장은   ";
	//char chararrayb[] = " 장공장장\n1234경찰청창살은 쇠창살";
	//std::array<char, 256> arraya;
	//arraya.fill(0);
	//std::copy(std::begin(chararraya), std::end(chararraya), arraya.begin());
	//int size = strlen(chararraya);
	//
	//std::cout << arraya.data() << std::endl << size<<std::endl;
	//std::copy(std::begin(chararrayb), std::end(chararrayb), arraya.begin()+size);
	//

	//std::cout << arraya.data() << std::endl << size;
	//
	//std::cout << Type(arraya);
	//std::cout << __MYFUNC__ ;
	//
	std::function<void(int, int)> bbb = test2;
		std::function<int(int, int)> aaa = test1;
		auto t = My20210131::makelog(logstream, aaa);
		auto t2 = My20210131::makelog(logstream, test2);
		t << std::string(__MYFUNC__);
		t2 << std::string(MYFUNC(test2));
		//std::cout << t(3, 5)<<std::endl;
		t2(3, 2);
		t(10, 509);
		//std::this_thread::sleep_for(std::chrono::duration<int>(1));
	
}

void My20210131::Type(std::stringstream& ss, char ch)

{
	ss << "char";
}

void My20210131::Type(std::stringstream& ss, int n)
{
	ss << "int";
}


void My20210131::LogStream::LogToConsole(std::string& s)
{
	*m_os << s;
}

void My20210131::LogStream::LogToFile(std::string& s)
{
	*m_ofs << s;
}

void My20210131::LogStream::LogToConsoleAndFile(std::string& s)
{
	*m_os << s;
	*m_ofs << s;
}

void My20210131::LogStream::LogNothing(std::string& s)
{
}

My20210131::LogStream::LogStream() : m_os(nullptr), m_ofs(nullptr)
{
	func = std::bind(&LogStream::LogNothing, this, std::placeholders::_1);
}

My20210131::LogStream::LogStream(std::ostream* os) : m_os(os), m_ofs(nullptr)
{
	func = std::bind(&LogStream::LogToConsole, this, std::placeholders::_1);
}

My20210131::LogStream::LogStream(std::ofstream* ofs)
	: m_os(nullptr), m_ofs(ofs)
{
	func = std::bind(&LogStream::LogToFile, this, std::placeholders::_1);
}

My20210131::LogStream::LogStream(std::ofstream* ofs, std::ostream* os)
{
	LogStream(os, ofs);
}

My20210131::LogStream::LogStream(std::ostream* os, std::ofstream* ofs) : m_os(os), m_ofs(ofs)
{
	func = std::bind(&LogStream::LogToConsoleAndFile, this, std::placeholders::_1);
}

void My20210131::LogStream::Write(std::string& s)
{
	func(s);
}
void My20210131::LogStream::Write(std::string&& s)
{
	func(s);
}
My20210131::LogStream& My20210131::operator<<(LogStream& ls, std::string& s)

{
	ls.Write(s);
	return ls;
}
My20210131::LogStream& My20210131::operator<<(LogStream& ls, std::string&& s)
{
	ls.Write(s);
	return ls;
}
My20210131::LogStream& My20210131::operator<<(LogStream& ls, const char* c)
{
	std::string s = std::string(c);
	ls.Write(s);
	return ls;
}
