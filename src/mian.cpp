#include "../include/FastHTML.h"

using namespace std;

int main()
{
	string s = "<tag><p id=\"3\">Cukireczek dla Penny<p></p></p></tag>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["id"] = "3";
	HResponse hr(&s, filter);
	cout << "Hello CMake. " << hr.GetData() << endl;
	cout << ClearOtherTags("Ala <h1 >ma</h1> kota <h2></h2>") << endl;
	return 0;
}
