#include "../include/FastHTML.h"

using namespace std;

int main()
{
	string s = "<tag><p id=\"3\">Cukireczek dla Penny<p></p></p></tag>";
	std::pair<std::string, std::map<std::string, std::string>> filter[3];
	filter[0].first = "p";
	filter[0].second["id"] = "3";
	filter[1].first = "p";
	filter[1].second["id"] = "3";
	filter[2].first = "p";
	filter[2].second["id"] = "3";
	
	HResponse hr(&s, filter, 3);
	
	return 0;
}
