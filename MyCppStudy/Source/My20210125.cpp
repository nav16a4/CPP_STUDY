#include "My20210125.h"

void My20210125::main()
{
	auto current = std::chrono::system_clock::now();
	auto duration = current.time_since_epoch();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	std::mt19937_64 genMT(time);
	std::uniform_int_distribution<__int64> uniformDist(0, 99);

	RingBuffer<int, 10> ringbuffer;

	while(false)
	{
		std::cout << uniformDist(genMT)<<std::endl;
		std::this_thread::sleep_for(std::chrono::duration<float>(0.1f));
	}

	for(int i=0;i<20;++i)
	{
		if (true == ringbuffer.Push(i))
			{
				std::cout << i << " 번째 반복 : " << i << " 데이터 넣는 것에 성공하였습니다.\n";
			}
			else
			{
				std::cout << i << " 번째 반복 : " << i << " 데이터 넣는 것에 실패하였습니다.\n";
			}
		

	}
	
	int test = 10;
	for (int i = 0;;++i)
	{
		
		if (!(0 == uniformDist(genMT) % 2))
		{
			if(true==ringbuffer.Push(test))
			{
				std::cout << i << " 번째 반복 : " << test << " 데이터 넣는 것에 성공하였습니다.\n";
				++test;
			}
			else
			{
				std::cout << i << " 번째 반복 : " << test << " 데이터 넣는 것에 실패하였습니다.\n";
			}

		}
		else
		{
			auto data = ringbuffer.Pull();
			if(true==data.has_value())
			{
				std::cout << i << " 번째 반복 : " <<  data.value() << " 데이터 꺼내는 것에 성공하였습니다.\n";
			}
			else
			{
				std::cout << i << " 번째 반복 : 데이터 꺼내는 것에 실패하였습니다.\n";
			}
		}
		//std::this_thread::sleep_for(std::chrono::duration<float>(0.1f));
	}


	
}
