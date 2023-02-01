// FastHTML.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <list>

#include <vector>
#include <mutex>
#include <deque>

std::string ClearOtherTags(const std::string dataWithTags);

// TODO: Reference additional headers your program requires here.
class HResponse
{
public:
	HResponse(const std::string* body, const std::pair<std::string, std::map<std::string, std::string>> filter);
	//HResponse(const std::string* body, const std::pair<std::string, std::map<std::string, std::string>> filter, bool alterAlg);
	HResponse(const std::string* body, const std::string tag);
	virtual ~HResponse();


	std::string GetLastData();
	std::string GetFirstData();
	std::list<std::string> GetListedData();

private:
	std::list<std::string> occurrence;
	const std::pair<std::string, std::map<std::string, std::string>> filter;
	const std::string* body;
	const bool reqAnyAttr;
	std::mutex mtxFillup;
	std::mutex mtx1;
	std::mutex mtx2;
	std::condition_variable cvFillup;
	std::condition_variable cv1;
	std::condition_variable cv2;
	unsigned int currentThreadID = 0;
	unsigned int threadsToRun = 0;
	void fillupOccurrences_consumer(const std::string tag, const std::list<size_t>* refOpenOccurr);
	void fillupOccurrences_consumer_th(const std::string tag, std::deque<size_t>* refOpenOccurr, const size_t startIndex, const size_t stopIndex);
};

// TODO remove
// execute time test
void GetAllTagOpenIndexes(std::string partBody, const std::pair<std::string, std::map<std::string, std::string>> filter, std::vector<size_t>* refOpenOccurr);

#ifdef CUSTOM_GOOGLE_TEST_DEF
std::string GtestWrapper_FastHTML_RemoveSpaces(std::string);
std::string GtestWrapper_FastHTML_StickPrefixWithTag(std::string);
size_t GtestWrapper_FastHTML_FindWhitespace(std::string, size_t);
bool GtestWrapper_FastHTML_HasAnyAttr(const std::string, const std::string);
bool GtestWrapper_FastHTML_RequireAnyAttr(const std::map<std::string, std::string>);
std::tuple<size_t, size_t> GtestWrapper_FastHTML_GetOpenTagIndexes(const std::string*, const std::string);
size_t GtestWrapper_FastHTML_GetNextOpenTagOpenIndex(const std::string*, const std::string, const size_t);
size_t GtestWrapper_FastHTML_GetNextOpenTagCloseIndex(const std::string*, const size_t);
std::string GtestWrapper_FastHTML_ExtractStatement(const std::string*, const size_t, const size_t);
bool GtestWrapper_FastHTML_CheckReqAttrExists(const std::string, const std::map<std::string, std::string>);
bool GtestWrapper_FastHTML_CheckAttrsAreValid(const std::string, const std::string, const std::map<std::string, std::string>);
std::string GtestWrapper_FastHTML_ExtractData(const std::string*, const size_t, size_t, const std::string, const std::string);
#endif
