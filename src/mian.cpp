#include "../include/FastHTML.h"

//#include "../include/hugeString.h"
#include<fstream>
#include<sstream>
#include<string>
#include <vector>
#include <chrono>


using namespace std;

int main()
{
	

	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	std::pair<std::string, std::map<std::string, std::string>> filter;
	ifstream f("..\\..\\..\\testsdata\\response.html");  // 50.4 MB
	std::string str;
	if (f) {
		std::cout << "read file \n";
		ostringstream ss;
		ss << f.rdbuf(); // reading data
		std::cout << "saving data \n";
		str = ss.str();
	}
	else {
		std::cout << "file error ! \n";
		return -1;
	}
	std::cout << "done \n";
	
	auto t1 = high_resolution_clock::now();
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> ms_double = t2 - t1;

	



	// !! 
	std::cout << "\n\n";
	std::cout << "response size: " << str.size() << "\n";
	// !!



	// HResponse hr2(&str, filter, true) #1
	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		HResponse hr2(&str, filter, true);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "HResponse #1: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -



	// JfillVect_time #1
	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		std::vector<size_t> tagOpenClosePairs;
		JfillVect_time(str, "<tag", &tagOpenClosePairs);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "JfillVect_time #1: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -



	// !! 
	std::cout << "\n\n";
	str.resize(str.size() / 2);
	std::cout << "response size: " << str.size() << "\n";
	// !!



	// HResponse hr2(&str, filter, true) #2
	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		HResponse hr2(&str, filter, true);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "HResponse #2: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -



	// JfillVect_time #2
	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		std::vector<size_t> tagOpenClosePairs;
		JfillVect_time(str, "<tag", &tagOpenClosePairs);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "JfillVect_time #2: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -



	// !! 
	std::cout << "\n\n";
	str.resize(str.size() / 2);
	std::cout << "response size: " << str.size() << "\n";
	// !!



	// HResponse hr2(&str, filter, true) #3
	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		HResponse hr2(&str, filter, true);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "HResponse #3: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -



	// JfillVect_time #3
	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		std::vector<size_t> tagOpenClosePairs;
		JfillVect_time(str, "<tag", &tagOpenClosePairs);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "JfillVect_time #3: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -



	// !! 
	std::cout << "\n\n";
	str.resize(str.size() / 2);
	std::cout << "response size: " << str.size() << "\n";
	// !!



	// HResponse hr2(&str, filter, true) #4
	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		HResponse hr2(&str, filter, true);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "HResponse #4: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -



	// JfillVect_time #4
	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		std::vector<size_t> tagOpenClosePairs;
		JfillVect_time(str, "<tag", &tagOpenClosePairs);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "JfillVect_time #4: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -



	// !! 
	std::cout << "\n\n";
	str.resize(str.size() / 2);
	std::cout << "response size: " << str.size() << "\n";
	// !!



	// HResponse hr2(&str, filter, true) #5
	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		HResponse hr2(&str, filter, true);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "HResponse #5: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -



	// JfillVect_time #5
	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		std::vector<size_t> tagOpenClosePairs;
		JfillVect_time(str, "<tag", &tagOpenClosePairs);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "JfillVect_time #5: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -




	std::cout << "\n\n";





	return 0;
}

/*
* 12 Threads
* response size: 52650959
HResponse #1: 5963.43ms
JfillVect_time #1: 15548.7ms


response size: 26325479
HResponse #2: 3462.83ms
JfillVect_time #2: 7788.57ms


response size: 13162739
HResponse #3: 2449.72ms
JfillVect_time #3: 3965.06ms


response size: 6581369
HResponse #4: 1734.47ms
JfillVect_time #4: 2112.21ms


response size: 3290684
HResponse #5: 1611.13ms
JfillVect_time #5: 1095.63ms




6 threads
response size: 52650959
HResponse #1: 5963.88ms
JfillVect_time #1: 16178.3ms


response size: 26325479
HResponse #2: 3419.2ms
JfillVect_time #2: 8092.77ms


response size: 13162739
HResponse #3: 1984.87ms
JfillVect_time #3: 4159.01ms


response size: 6581369
HResponse #4: 1347.24ms
JfillVect_time #4: 2172.22ms


response size: 3290684
HResponse #5: 1069.51ms
JfillVect_time #5: 1123.56ms




4 threads
response size: 52650959
HResponse #1: 6151.33ms
JfillVect_time #1: 15434.3ms


response size: 26325479
HResponse #2: 3441.24ms
JfillVect_time #2: 7756.01ms


response size: 13162739
HResponse #3: 1822.24ms
JfillVect_time #3: 3933.94ms


response size: 6581369
HResponse #4: 1094.12ms
JfillVect_time #4: 2076.87ms


response size: 3290684
HResponse #5: 889.509ms
JfillVect_time #5: 1099.72ms




2 threads
response size: 52650959
HResponse #1: 9385.75ms
JfillVect_time #1: 15637.4ms


response size: 26325479
HResponse #2: 4769.99ms
JfillVect_time #2: 7850.14ms


response size: 13162739
HResponse #3: 2710.38ms
JfillVect_time #3: 3990.29ms


response size: 6581369
HResponse #4: 1496.62ms
JfillVect_time #4: 2123.12ms


response size: 3290684
HResponse #5: 953.931ms
JfillVect_time #5: 1112.71ms




1 thread
*/
