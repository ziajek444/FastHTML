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

	std::string GetLastData();
	std::string GetFirstData();
	std::list<std::string> GetListedData();

private:
	std::list<std::string> occurrence;
};

#ifdef CUSTOM_GOOGLE_TEST_DEF
std::string GtestWrapper_FastHTML_RemoveSpaces(std::string);
std::string GtestWrapper_FastHTML_StickPrefixWithTag(std::string);
size_t GtestWrapper_FastHTML_FindWhitespace(std::string, size_t);
#endif
