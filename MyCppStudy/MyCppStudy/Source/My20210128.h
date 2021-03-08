#pragma once
namespace My20210128
{


	struct TestClass
	{
		int& intA;
		TestClass(int& a) : intA(a) {}
		int& Get(int) { return intA; }
		int& Get() { return intA; }
		int& Geta(int& aa) { aa = intA; return aa; };
	};
	
	void main0();
	void main1();
};

