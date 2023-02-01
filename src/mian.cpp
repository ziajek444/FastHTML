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
	filter.first = "div";
	// whitespaceless
	filter.second["class"] = "flexjustify-betweenborder-bpy-2desktop:py-0.5"; //class="flex justify-between border-b py-2 desktop:py-0.5"

	//ifstream f("..\\..\\..\\testsdata\\investing.tesla.html");  // 1.4348 MB
	ifstream f("..\\..\\..\\testsdata\\investing.tesla.huge.html");  // 26.9141 MB
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

	
	// TODO
	// BodyBuilder -> extract only content between <body>...</body>
	// Also erase all comments: <!-- comment -->


	// !! 
	std::cout << "\n\n";
	std::cout << "response size: " << str.size() << "\n";
	// !!



	t1 = high_resolution_clock::now();
	HResponse hr2(&str, filter);
	for (int idx = 0; idx < 0xff; ++idx) {
		HResponse hr3(&str, filter);
	}
	t2 = high_resolution_clock::now();

	ms_double = t2 - t1;
	std::cout << "HResponse #1: " << ms_double.count() << "ms\n";
	//  -  -  -  -  -



	// !! 
	//std::cout << "\n\n";
	//std::cout << hr2.GetListedData().size() << std::endl;
	//for (auto e : hr2.GetListedData()) {
	//	std::cout << e << std::endl;
	//}
	// !!


	return 0;
}



