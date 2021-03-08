#include "My20210205.h"
#include <iostream>

namespace My20210205 {
	struct B
	{
		
		int b;
		B(int n) : b(n) {}
		B() : b(10) {}
	};
}
void My20210205::main()
{
	B bb(10);
	A a(bb);
	std::cout << a.a.b;
}


My20210205::A::A(B& b) : a(b)
{

}
