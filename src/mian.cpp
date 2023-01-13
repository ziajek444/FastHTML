#include "../include/FastHTML.h"

using namespace std;

int main()
{
	string s = "";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "a";
	filter.second["id"] = "3";
	HResponse hr(&s, filter);
	cout << "Hello CMake. " << hr.GetData() << endl;
	return 0;
}
