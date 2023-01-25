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
