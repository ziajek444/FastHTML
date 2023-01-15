// FastHTML.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <list>

std::string ClearOtherTags(const std::string dataWithTags);

// TODO: Reference additional headers your program requires here.
class HResponse
{
public:
	HResponse(const std::string* body, std::pair<std::string, std::map<std::string, std::string>> filter);
	virtual ~HResponse();

	std::string GetData();

private:
	std::list<std::string> occurrence;
};