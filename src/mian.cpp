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
	filter.first = "<span";

	ifstream f("..\\..\\..\\testsdata\\investing.html");  // 1 MB
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
	std::vector<size_t> tagOpenClosePairs;
	for (int i = 0; i < 100; i++) {
		tagOpenClosePairs.clear();
		JfillVect_time(str, "<span", &tagOpenClosePairs);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "JfillVect_time #1: " << ms_double.count() << "ms\n";
	std::cout << str.substr(250187, 16);
	//  -  -  -  -  -



	return 0;
}
