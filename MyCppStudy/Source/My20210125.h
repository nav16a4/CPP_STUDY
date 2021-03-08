#pragma once
#include <iostream>
#include <array>
#include <optional>
#include <mutex>
#include <random>
#include <chrono>
#include <cassert>
namespace My20210125
{
	template <class T, int A>
	class RingBuffer2
	{
	private:
		
		std::array<T, A> m_buffer; //실제 데이터
		std::array<T*, A> m_ptrBuffer; //
		void Initialize()
		{
			for (int iter = 0; iter < A; ++iter)
			{
				m_ptrBuffer[iter] = *(m_buffer[iter]);
			}
		}
	public:
		T* Acquire()
		{

		}
		void Release(T* ptr)
		{

		}
		//T operator[](int n) { return m_buffer[n]; }
	};

	//이 링버퍼는 정적 배열을 사용한 링버퍼로 자료가 있는 포인터를 직접 줘서 다루게 한다.
	template <class T, int MAX>
	class RingBuffer
	{
		const static int arraySize = MAX;
		std::array<T, arraySize> m_buffer;
		int m_readPos =0;
		int m_WritePos = 0;
		std::mutex m_mutex;
		//처음 리드포지션과 라이트포지션에 대한 처리를 전체에 추가하는것은 비효율적인것 같으니 갯수 별도 관리
		int m_count = 0;
	public:
		RingBuffer() { Initialize(); }
		~RingBuffer() = default;
	protected:
	private:
		void Initialize()
		{
			for(int i=0;i<arraySize;++i)
			{
				m_buffer[i] = T();
			}
		}
	/*	inline bool IsMeetingifMove(int move ,const int lock)
		{
			
			bool flag1 = (move < lock);
			bool flag2 = (lock <= (move + 1) % MAX);

			return (flag1 && flag2);
			
		}
		inline bool Readable(int& readposition, int& writeposition)
		{
			if (writeposition == (readposition+1)%MAX)
			{
				return false;
			}
			return true;
		}
		inline bool Writeable(int& readposition, int& writeposition)
		{
			if ((writeposition + 1) % MAX == readposition)
			{
				return false;
			}
			return true;
		}*/
	/*	void Read(int& readposition, int& writeposition)
		{
			if (readposition + 1 == writeposition)
			{

			}
		}
		void Write(T&)
		{

		}*/
	public:
		std::optional<T> Pull()
		{

			//std::cout << "read : " << m_readPos << " write : " << m_WritePos << " count "<<m_count << "_";
			T returnvalue=T();
			{
				std::lock_guard<std::mutex> lockguard(m_mutex);

				//result = IsMeetingifMove(m_readPos, m_WritePos);
				if (0 < m_count)
				{
					--m_count;
					returnvalue = m_buffer[m_readPos];
					m_buffer[m_readPos] = T();
					m_readPos = (m_readPos + 1) % arraySize;
				}
				else
				{
					return std::nullopt;
				}
			}
			return returnvalue;
		}
		bool Push(T object)
		{
			//std::cout << "read : " << m_readPos << " write : " << m_WritePos << " count " << m_count << "_";
			{
				std::lock_guard<std::mutex> lockguard(m_mutex);
				if (m_count < (MAX))
				{
					//std::cout << T() << std::endl;
					assert(m_buffer[m_WritePos] == T());
					++m_count;
					m_buffer[m_WritePos] = object;
					m_WritePos = (m_WritePos + 1) % arraySize;
					return true;
				}
				else
				{
					return false;
				}
			}
			
		}
	protected:
	private:
	};

	class Object
	{
		int a;
		int b;
		int c;
	};
	constexpr int maxObject(void) { return 100; }

	class ObjectManager
	{
		const static int MAXOBJECT = 100;
		std::array<Object, MAXOBJECT> objects;



	};



	void main();
};

