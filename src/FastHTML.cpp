// FastHTML.cpp : Defines the entry point for the application.
// v0.9.99B
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <sysinfoapi.h>
#endif

#ifdef CUSTOM_GOOGLE_TEST_DEF
//#include "../include/tests.hpp"
#endif

#include "../include/FastHTML.h"
#include <algorithm>
#include <vector>
#include <ctype.h>
#include <stdexcept>
#include <tuple>

#include <thread>
#include <mutex>
#include <condition_variable>



// STATIC PROTOTYPES

static std::string RemoveSpaces(std::string);
static std::string StickPrefixWithTag(std::string statement);
static size_t FindWhitespace(const std::string, const size_t);
static bool HasAnyAttr(const std::string statement, const std::string openTagName);
static bool RequireAnyAttr(const std::map<std::string, std::string>);
static std::tuple<size_t, size_t> GetOpenTagIndexes(const std::string* body, const std::string openTagName);
static size_t GetNextOpenTagOpenIndex(const std::string*, const std::string, const size_t);
static size_t GetNextOpenTagCloseIndex(const std::string*, const size_t);
static std::string ExtractStatement(const std::string*, const size_t, const size_t);
static bool CheckReqAttrExists(const std::string statement, const std::map<std::string, std::string> dict);
static bool CheckAttrsAreValid(const std::string statement, const std::string openTagName, const std::map<std::string, std::string> dict);
static std::string ExtractData(const std::string* body, const size_t openTagCloseIndex, size_t closeTagOpenIndex, const std::string openTagName, const std::string closeTagName);

// CTOR/DTOR
void GetAllTagOpenIndexes(std::string partBody, const std::pair<std::string, std::map<std::string, std::string>> filter, std::vector<size_t>* refOpenOccurr)
{
	const std::string tag = RemoveSpaces(filter.first);
	const std::string openTagName = '<' + tag;
	size_t found = 0;
	size_t id = 1;
	std::vector<size_t> tmpVector;
	while (true) {
		found = partBody.find(openTagName, found);
		if (found != std::string::npos) {
			refOpenOccurr->push_back(found);
			found++;
		}
		else { break; }
	}
}


void GetAllTagOpenIndexes_th(std::string partBody, size_t offset, const std::pair<std::string, std::map<std::string, std::string>> filter, std::vector<size_t> *refOpenOccurr, std::mutex *mtx)
{
	const std::string tag = RemoveSpaces(filter.first);
	const std::string openTagName = '<' + tag;
	size_t openTagOpenIndex = -1;
	//size_t openTagCloseIndex;
	size_t id = 1;
	std::vector<size_t> tmpVector;
	while (true) {
		openTagOpenIndex = partBody.find(openTagName, openTagOpenIndex + 1); // openTagOpenIndex + 1 = 0 first time
		if (openTagOpenIndex != std::string::npos) {
			//openTagCloseIndex = GetNextOpenTagCloseIndex(&partBody, openTagOpenIndex);
			tmpVector.push_back(openTagOpenIndex + offset);
		}
		else { break; }
	}

	std::vector<size_t> copyVector;
	mtx->lock();
	std::merge(tmpVector.begin(), tmpVector.end(), refOpenOccurr->begin(), refOpenOccurr->end(), std::back_inserter(copyVector));
	*refOpenOccurr = copyVector;
	mtx->unlock();
}


void HResponse::fillupOccurrences_consumer(const std::string tag, std::vector<size_t>* refOpenOccurr)
{
	const std::string openTagName = '<' + tag;
	const std::string closeTagName = "</" + tag;
	size_t openTagOpenIndex;
	while (true) {
		// pop index
		if (!refOpenOccurr->empty()) {
			openTagOpenIndex = refOpenOccurr->back();
			refOpenOccurr->pop_back();
		}
		else {
			break; // main exit
		}

		// extract statement
		size_t openTagCloseIndex = GetNextOpenTagCloseIndex(body, openTagOpenIndex);
		if (openTagCloseIndex == std::string::npos) break; // missing close means corrupted body
		std::string statement = body->substr(openTagOpenIndex, openTagCloseIndex - openTagOpenIndex + 1);  // <tag ... ... >
		statement = RemoveSpaces(statement);  // <tag...>

		// valid attrs
		bool hasAnyAttr = HasAnyAttr(statement, openTagName);
		if (reqAnyAttr && hasAnyAttr) {
			if (!CheckReqAttrExists(statement, filter.second) || !CheckAttrsAreValid(statement, openTagName, filter.second)) {
				continue; // invalid tag
			}
		}

		// extract data
		if (reqAnyAttr == hasAnyAttr) {
			size_t closeTagOpenIndex = body->find(closeTagName, openTagCloseIndex + 1);
			if (closeTagOpenIndex == std::string::npos) throw std::length_error("Missing close tag in html statement");

			if (openTagCloseIndex + 1 == closeTagOpenIndex) { //there is no data
				occurrence.push_back("");
			}
			else {
				std::string extractedDataBeforeMutex = ExtractData(body, openTagCloseIndex, closeTagOpenIndex, openTagName, closeTagName);
				occurrence.push_back(extractedDataBeforeMutex);
			}
		}
	}
}

void HResponse::fillupOccurrences_consumer_th(const std::string tag, std::vector<size_t>* refOpenOccurr, const unsigned int threadID)
{
	const std::string openTagName = '<' + tag;
	const std::string closeTagName = "</" + tag;
	size_t openTagOpenIndex;
	
	while (true) {
		// pop index
		mtxFillup.lock();
		if (!refOpenOccurr->empty()) {
			openTagOpenIndex = refOpenOccurr->back();
			refOpenOccurr->pop_back();
			mtxFillup.unlock();
		}
		else {
			mtxFillup.unlock();
			break; // main exit
		}

		// extract statement
		size_t openTagCloseIndex = GetNextOpenTagCloseIndex(body, openTagOpenIndex);
		if (openTagCloseIndex == std::string::npos) {
			break; // missing close means corrupted body
		}
		std::string statement = body->substr(openTagOpenIndex, openTagCloseIndex - openTagOpenIndex + 1);  // <tag ... ... >
		statement = RemoveSpaces(statement);  // <tag...>

		// valid attrs
		bool hasAnyAttr = HasAnyAttr(statement, openTagName);
		if (reqAnyAttr && hasAnyAttr) {
			if (!CheckReqAttrExists(statement, filter.second) || !CheckAttrsAreValid(statement, openTagName, filter.second)) {
				continue; // invalid tag
			}
		}

		// extract data
		if (reqAnyAttr == hasAnyAttr) {
			size_t closeTagOpenIndex = body->find(closeTagName, openTagCloseIndex + 1);
			if (closeTagOpenIndex == std::string::npos) throw std::length_error("Missing close tag in html statement");

			if (openTagCloseIndex + 1 == closeTagOpenIndex) { //there is no data
				mtxFillup.lock();
				occurrence.push_back("");
				mtxFillup.unlock();
			}
			else {
				std::string extractedDataBeforeMutex = ExtractData(body, openTagCloseIndex, closeTagOpenIndex, openTagName, closeTagName);
				mtxFillup.lock();
				occurrence.push_back(extractedDataBeforeMutex);
				mtxFillup.unlock();
			}
		}

	}
}

HResponse::HResponse(const std::string* _body, const std::pair<std::string, std::map<std::string, std::string>> _filter) : body(_body), filter(_filter), reqAnyAttr(RequireAnyAttr(_filter.second))
{
	// filter attr's values must be whitespaceless
	const std::string tag = RemoveSpaces(filter.first);
	const std::string openTagName = '<' + tag;
	const std::string closeTagName = "</" + tag;
	const size_t minResonableSize = 0xffffff; //~1.5mb
	const size_t bodySize = body->size();
	unsigned int numCPU;

#if defined(_WIN32) || defined(_WIN64)
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	numCPU = sysinfo.dwNumberOfProcessors;
#else*/
	numCPU = std::thread::hardware_concurrency();
#endif

	std::vector<size_t> tagOpenOpenIndexOccurrences;
	
	if (bodySize < minResonableSize) {
		GetAllTagOpenIndexes(*body, filter, &tagOpenOpenIndexOccurrences);
		fillupOccurrences_consumer(tag, &tagOpenOpenIndexOccurrences);
	}
	else {
		numCPU = numCPU >= 2 ? numCPU : 2;
		size_t count = bodySize / numCPU;
		size_t startIndex = 0;
		threadsToRun = numCPU;

		std::vector<std::thread> threadsVector;
		std::mutex mtx;

		
		while (--numCPU)
		{
			threadsVector.push_back(std::thread{ GetAllTagOpenIndexes_th, body->substr(startIndex, count), startIndex, filter, &tagOpenOpenIndexOccurrences, &mtx });
			startIndex += count - (openTagName.size() - 1);
		}
		threadsVector.push_back(std::thread{ GetAllTagOpenIndexes_th, body->substr(startIndex), startIndex, filter, &tagOpenOpenIndexOccurrences, &mtx });

		for (auto& thd : threadsVector) {
			thd.join();
		}
		threadsVector.clear();

		currentThreadID = 0;
		numCPU = threadsToRun;
		int index = 0;
		while (numCPU--)
		{
			threadsVector.push_back(std::thread{ &HResponse::fillupOccurrences_consumer_th, this, tag, &tagOpenOpenIndexOccurrences, index++ });
		}

		for (auto& thd : threadsVector) {
			thd.join();
		}
	}
}

HResponse::HResponse(const std::string* _body, const std::string tag) : body(_body), filter({ tag, {} }), reqAnyAttr(false)
{
	const std::string openTagName = '<' + tag;
	const std::string closeTagName = "</" + tag;
	auto [openTagOpenIndex, openTagCloseIndex] = GetOpenTagIndexes(body, openTagName);

	while (openTagOpenIndex != std::string::npos) {
		std::string statement = body->substr(openTagOpenIndex, openTagCloseIndex - openTagOpenIndex + 1);  // <tag ... ... >
		statement = RemoveSpaces(statement);  // <tag...>

		bool hasAnyAttr = HasAnyAttr(statement, openTagName);

		if (!hasAnyAttr) {
			size_t closeTagOpenIndex = body->find(closeTagName, openTagCloseIndex + 1);
			if (closeTagOpenIndex == std::string::npos) throw std::length_error("Missing close tag in html statement");

			if (openTagCloseIndex + 1 == closeTagOpenIndex) { //there is no data
				openTagOpenIndex = GetNextOpenTagOpenIndex(body, openTagName, openTagOpenIndex);
				openTagCloseIndex = GetNextOpenTagCloseIndex(body, openTagOpenIndex);
				occurrence.push_back("");
				continue;
			}

			occurrence.push_back(ExtractData(body, openTagCloseIndex, closeTagOpenIndex, openTagName, closeTagName));
		}

		openTagOpenIndex = body->find(openTagName, openTagOpenIndex + openTagName.size());
		openTagCloseIndex = body->find('>', openTagOpenIndex + openTagName.size());  // index { <tag...|> }
	} // WHILE

	//Reverse ? occurrence ?
}


HResponse::~HResponse()
{
}


// METHODS

std::string HResponse::GetLastData()
{
	if (occurrence.size() > 0) return occurrence.back();
	
	return "UPS";
}

std::string HResponse::GetFirstData()
{
	if (occurrence.size() > 0) return occurrence.front();

	return "UPS";
}

std::list<std::string> HResponse::GetListedData()
{
	return occurrence;
}


// FUNCTIONS

std::string ClearOtherTags(std::string _statement)
{
	size_t openTagOpenCharacterIndex = 0;
	size_t openTagCloseCharacterIndex = 0;
	size_t lastCloseCharacterIndex = 0;
	size_t spaceAfterOpenTag = 0;
	std::string tagName = "";
	std::string openTagName = "";
	std::string closeTagName = "";
	const std::string closePrefixStr = "</";
	const std::string openPrefixStr = "<";
	
	std::string statement = StickPrefixWithTag(_statement);

	while (true)
	{
		openTagOpenCharacterIndex = statement.find('<');  // |<tag ...  >
		if (openTagOpenCharacterIndex == std::string::npos) break;  // there is no any open prefixes

		openTagCloseCharacterIndex = statement.find('>', openTagOpenCharacterIndex);  // <tag|>
		// TODO Handle ret value
		spaceAfterOpenTag = FindWhitespace(statement, openTagOpenCharacterIndex);  // <tag| ...  > or NPOS
		if (spaceAfterOpenTag == std::string::npos || spaceAfterOpenTag > openTagCloseCharacterIndex)
		{  // <tag>
			tagName = statement.substr(openTagOpenCharacterIndex + 1, openTagCloseCharacterIndex - openTagOpenCharacterIndex - 1);
		}
		else {  // <tag ...>
			tagName = statement.substr(openTagOpenCharacterIndex + 1, spaceAfterOpenTag - openTagOpenCharacterIndex);
		}

		tagName = RemoveSpaces(tagName);
		openTagName = openPrefixStr + tagName;  // <tag
		closeTagName = closePrefixStr + tagName;  // </tag

		size_t closestOpenTagName = openTagOpenCharacterIndex;
		size_t latestCloseTagName = statement.find(closeTagName);
		// TODO check return code
		latestCloseTagName = statement.find('>', latestCloseTagName + closeTagName.size());
		// TODO check return code
		
		auto it = statement.begin();
		statement.erase(it + closestOpenTagName, it + latestCloseTagName + 1);
	}
	
	return statement;
}


// STATIC DEFINITIONS

static std::string RemoveSpaces(std::string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());

	return str;
}

static std::string StickPrefixWithTag(std::string statement)
{
	size_t openTagOpenCharacterIndex = 0;
	size_t openTagCloseCharacterIndex = 0;
	const std::string closePrefixStr = "</";

	// remove every whitespace between open prefix '<' and tag name
	openTagOpenCharacterIndex = statement.find('<', openTagOpenCharacterIndex);
	while (openTagOpenCharacterIndex != std::string::npos) {
		unsigned int whitespaceCount = 0;

		while (isspace(statement[openTagOpenCharacterIndex + 1 + whitespaceCount++])) {}
		if (whitespaceCount) whitespaceCount--;
		statement.erase(openTagOpenCharacterIndex + 1, whitespaceCount);
		openTagOpenCharacterIndex = statement.find('<', openTagOpenCharacterIndex + 1);
	}

	// remove every whitespace between close prefix "</" and tag name
	openTagCloseCharacterIndex = statement.find(closePrefixStr, openTagCloseCharacterIndex);
	while (openTagCloseCharacterIndex != std::string::npos) {
		unsigned int whitespaceCount = 0;

		while (isspace(statement[openTagCloseCharacterIndex + 2 + whitespaceCount++])) {}
		if (whitespaceCount) whitespaceCount--;
		statement.erase(openTagCloseCharacterIndex + 2, whitespaceCount);
		openTagCloseCharacterIndex = statement.find(closePrefixStr, openTagCloseCharacterIndex + 1);
	}

	return statement;
}

static size_t FindWhitespace(const std::string str, const size_t offset = 0)
{
	size_t whiteSpaceIndex = 0;
	size_t strSize = str.size();

	if(offset >= strSize) return std::string::npos;

	while (!isspace(str[offset + whiteSpaceIndex])) {
		whiteSpaceIndex++;
		if(whiteSpaceIndex + offset >= strSize) return std::string::npos;
	}

	return whiteSpaceIndex + offset;
}

static bool HasAnyAttr(const std::string statement, const std::string openTagName)
{
	return statement.size() > openTagName.size() + 2;  // "<tag...>" > "<tag" + 2  

}

static bool RequireAnyAttr(const std::map<std::string, std::string> dict)
{
	return dict.size() > 0;
}

// !!!
// I need to find a way to reuse structured bindings, otherwise it is useless feature !!!
// !!!
static std::tuple<size_t, size_t> GetOpenTagIndexes(const std::string* body, const std::string openTagName)
{
	size_t openTagOpenIndex = body->find(openTagName);  // index { |<tag }
	size_t openTagCloseIndex = openTagOpenIndex == std::string::npos ? openTagOpenIndex : body->find('>', openTagOpenIndex + openTagName.size());  // index { <tag...|> }

	return std::make_tuple(openTagOpenIndex, openTagCloseIndex);
}

static size_t GetNextOpenTagOpenIndex(const std::string* body, const std::string openTagName, const size_t openTagOpenIndex)
{
	if (openTagOpenIndex == std::string::npos) return std::string::npos;
	if (openTagName.size() >= 0 && openTagOpenIndex + openTagName.size() < openTagOpenIndex) return std::string::npos;
	return body->find(openTagName, openTagOpenIndex + openTagName.size());
}

static size_t GetNextOpenTagCloseIndex(const std::string* body, const size_t openTagOpenIndex)
{
	return body->find('>', openTagOpenIndex);
}

static std::string ExtractStatement(const std::string* body, const size_t openTagOpenIndex, const size_t openTagCloseIndex)
{
	return body->substr(openTagOpenIndex, openTagCloseIndex - openTagOpenIndex + 1);
}

static bool CheckReqAttrExists(const std::string statement, const std::map<std::string, std::string> dict)
{
	bool ret = true;
	for (const auto& kv : dict)
	{
		if (statement.find(kv.first) != std::string::npos) { continue; }
		else { ret = false; break; }
	}

	return ret;
}

static bool CheckAttrsAreValid(const std::string statement, const std::string openTagName, const std::map<std::string, std::string> dict)
{
	bool attrsAreValid = true;

	std::string attrStatement = statement.substr(openTagName.size(), statement.size() - openTagName.size() - 1);  // <tag|attr1="asd"attr2="qwe"attr3="123"|>
	if (attrStatement.back() == '/')
	{ // TODO remove this if statement and handle '/' character
		attrStatement.erase(attrStatement.end() - 1, attrStatement.end());
	}

	if (dict.size() < 1) return false;

	for (const auto& kv : dict)
	{
		size_t attrBegin = attrStatement.find(kv.first);
		size_t valBegin = attrBegin + kv.first.size() + 1; // =
		size_t valEnd = valBegin + kv.second.size() + 2;  // "" 
		if (attrStatement.substr(valBegin, valEnd).find(kv.second) == std::string::npos)
		{
			attrsAreValid = false;
			break;
		}
	}

	return attrsAreValid;
}


static std::string ExtractData(const std::string* body, const size_t openTagCloseIndex, size_t closeTagOpenIndex, const std::string openTagName, const std::string closeTagName)
{
	std::string debugstring = body->substr(openTagCloseIndex + 1, closeTagOpenIndex - (openTagCloseIndex + 1));
	size_t nextRedundantOpenTagIndex = debugstring.find(openTagName);

	if (nextRedundantOpenTagIndex != std::string::npos)
	{
		size_t redundantOpens = 1;
		while (redundantOpens)
		{
			while (true) {
				nextRedundantOpenTagIndex = debugstring.find(openTagName, nextRedundantOpenTagIndex + (openTagName.size() - 1));
				if (nextRedundantOpenTagIndex != std::string::npos)
				{
					redundantOpens++;
				}
				else
				{
					break;
				}
			}

			nextRedundantOpenTagIndex = closeTagOpenIndex;
			closeTagOpenIndex = body->find(closeTagName, closeTagOpenIndex+1);
			debugstring = body->substr(nextRedundantOpenTagIndex, closeTagOpenIndex - nextRedundantOpenTagIndex);
			redundantOpens--;
		}
	}

	return body->substr(openTagCloseIndex + 1, closeTagOpenIndex - (openTagCloseIndex + 1));
}


// GTEST Defines

#ifdef CUSTOM_GOOGLE_TEST_DEF
std::string GtestWrapper_FastHTML_RemoveSpaces(std::string str)
{
	return RemoveSpaces(str);
}
std::string GtestWrapper_FastHTML_StickPrefixWithTag(std::string str)
{
	return StickPrefixWithTag(str);
}
size_t GtestWrapper_FastHTML_FindWhitespace(std::string str, size_t offset = 0)
{
	return FindWhitespace(str, offset);
}
bool GtestWrapper_FastHTML_HasAnyAttr(const std::string statement, const std::string openTagName)
{
	return HasAnyAttr(statement, openTagName);
}
bool GtestWrapper_FastHTML_RequireAnyAttr(const std::map<std::string, std::string> dict)
{
	return RequireAnyAttr(dict);
}
std::tuple<size_t, size_t> GtestWrapper_FastHTML_GetOpenTagIndexes(const std::string* body, const std::string openTagName)
{
	return GetOpenTagIndexes(body, openTagName);
}
size_t GtestWrapper_FastHTML_GetNextOpenTagOpenIndex(const std::string* body, const std::string openTagName, const size_t openTagOpenIndex)
{
	return GetNextOpenTagOpenIndex(body, openTagName, openTagOpenIndex);
}
size_t GtestWrapper_FastHTML_GetNextOpenTagCloseIndex(const std::string* body, const size_t openTagOpenIndex)
{
	return GetNextOpenTagCloseIndex(body, openTagOpenIndex);
}
std::string GtestWrapper_FastHTML_ExtractStatement(const std::string* body, const size_t openTagOpenIndex, const size_t openTagCloseIndex)
{
	return ExtractStatement(body, openTagOpenIndex, openTagCloseIndex);
}
bool GtestWrapper_FastHTML_CheckReqAttrExists(const std::string statement, const std::map<std::string, std::string> dict)
{
	return CheckReqAttrExists(statement, dict);
}
bool GtestWrapper_FastHTML_CheckAttrsAreValid(const std::string statement, const std::string openTagName, const std::map<std::string, std::string> dict)
{
	return CheckAttrsAreValid(statement, openTagName, dict);
}
std::string GtestWrapper_FastHTML_ExtractData(const std::string* body, const size_t openTagCloseIndex, size_t closeTagOpenIndex, const std::string openTagName, const std::string closeTagName)
{
	return ExtractData(body, openTagCloseIndex, closeTagOpenIndex, openTagName, closeTagName);
}
#endif
