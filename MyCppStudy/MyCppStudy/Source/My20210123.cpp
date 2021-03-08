#include "My20210123.h"



void MyStudy20210123::main()
{
	//성능을 고려해 동일한 스트링은 별도로 처리하게 만들려다가
	//어자피 내 코드에 성능 따질 상황이 아니고
	//디자인패턴 자체가 성능을 갉아먹는 요소도 있어서 포기
	
	/*std::string str = "아아아1";
	auto strfunc = []() {return std::string("아아아2"); };
	MyStrFunc* testfunc = new StrFunc1(strfunc);
	
	testfunc->Write();*/
	std::ofstream file1("1.txt");
	std::ofstream file2("2.txt");
	std::mutex mutex1;
	std::mutex mutex2;
	
	LogStream lf1(&std::cout);
	LogStream lf2(&file1);
	LogStream lf3(&std::cout, &file2);

	std::string str1 = "가나다라마바사";
	std::string str2 = "아자차카타파하";
	std::string str3 = "궭뉅뒑뤩뭵뷁쉙";

	lf1.Write(str1);
	lf2.Write(str2);
	lf3.Write(str3);
}

void MyStudy20210123::main1()
{

	/*std::ofstream file1("111.txt");
	LogStream lf2(&file1);

	LogStream lf1(&std::cout);
	std::func00 t = [](int a, int b) {std::cout << "input int a = " << a << " int b = " << b << std::endl; return 1; };
	auto tmep1 = []() {return std::string("HELL!1"); };
	auto tmep2 = []() {return std::string("HELL!2"); };
	auto tmep3 = []() {return std::string("HELL!3"); };
	auto tmep4 = []() {return std::string("HELL!4"); };
	auto temp5 = []() {return MyGetTime(); };
	auto temp6 = __FUNCTION__;
	auto logger = makelog(lf1, t, temp5, tmep2,temp6);
	logger.SetBlank(" ");
	for (int i = 0; i < 10; ++i)
	{
		logger(i, 2*i);
		std::this_thread::sleep_for(std::chrono::duration<int>(1));
	}*/
	
	
}
