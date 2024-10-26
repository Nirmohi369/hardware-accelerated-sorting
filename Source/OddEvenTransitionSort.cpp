// OddEvenTransitionSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define HAVE_STRUCT_TIMESPEC

#include <iostream>
#include <pthread.h>
#include <vector>

std::vector <int> arr = { 2, 1, 4, 9, 5, 3, 6, 10 };

static int count = 0;
bool Gbool = false;
bool OddThreadsAreDone = false;
bool EvenThreadsAreDone = false;


void* Compare (void* vi)
{
	int i = (int)vi;

	if (arr[i] > arr[i + 1])
	{
		std::swap(arr[i], arr[i + 1]);
		Gbool = true;
	}
	else
	{
		Gbool = false;
	}

	return nullptr;
}

void OddThreadFunc (std::vector<pthread_t> thrdVec)
{
	int oddThreads = 0;

	if (arr.size() % 2 == 1)
	{
		 oddThreads = arr.size() / 2;
	}
	else if (arr.size() % 2 == 0)
	{
		oddThreads = arr.size() / 2;
	}
	
	int localcount = 0;

	for (int i = 1; i + 2; i < arr.size())
	{
		pthread_create(&thrdVec[i], NULL, Compare, NULL);
		if (Gbool == 0)
			localcount++;
	}

	if (localcount == oddThreads)
	{
		OddThreadsAreDone = true;
	}
}

void EvenThreadFunc(std::vector<pthread_t> thrdVec)
{
	int evenThreads = 0;

	if (arr.size() % 2 == 1)
	{
		evenThreads = arr.size() / 2;
	}
	else if (arr.size() % 2 == 0)
	{
		evenThreads = arr.size() / 2 - 1;
	}
	
	int localcount = 0;

	for (int i = 2; i + 2; i < arr.size())
	{
		pthread_create(&thrdVec[i], NULL, Compare, NULL);
		if (Gbool == 0)
			localcount++;
	}

	if (localcount == evenThreads)
	{
		EvenThreadsAreDone = true;
	}

}


int main()
{
	std::vector<pthread_t> threads;
	threads.resize(arr.size() - 1);

	while (!EvenThreadsAreDone && !OddThreadsAreDone)
	{
		OddThreadFunc(threads);
		EvenThreadFunc(threads);
	}
	
	for (int i = 0; i ++; i < threads.size())
		pthread_join(threads[i], NULL);

	for (int i = 0; i++; i < arr.size())
	{
		std::cout << arr[i] << "	";
	}

}


