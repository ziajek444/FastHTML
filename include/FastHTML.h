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
	HResponse(const std::string* body, const std::pair<std::string, std::map<std::string, std::string>> filter);
	HResponse(const std::string* body, const std::pair<std::string, std::map<std::string, std::string>> filter, bool alterAlg);
	HResponse(const std::string* body, const std::string tag);
	HResponse(const std::string* body, const std::pair<std::string, std::map<std::string, std::string>> filter[], size_t n);
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
bool GtestWrapper_FastHTML_HasAnyAttr(const std::string, const std::string);
bool GtestWrapper_FastHTML_RequireAnyAttr(const std::map<std::string, std::string>);
std::tuple<size_t, size_t> GtestWrapper_FastHTML_GetOpenTagIndexes(const std::string*, const std::string);
size_t GtestWrapper_FastHTML_GetNextOpenTagOpenIndex(const std::string*, const std::string, const size_t);
size_t GtestWrapper_FastHTML_GetNextOpenTagCloseIndex(const std::string*, const std::string, const size_t);
std::string GtestWrapper_FastHTML_ExtractStatement(const std::string*, const size_t, const size_t);
bool GtestWrapper_FastHTML_CheckReqAttrExists(const std::string, const std::map<std::string, std::string>);
bool GtestWrapper_FastHTML_CheckAttrsAreValid(const std::string, const std::string, const std::map<std::string, std::string>);
std::string GtestWrapper_FastHTML_ExtractData(const std::string*, const size_t, size_t, const std::string, const std::string);
#endif
