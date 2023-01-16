// FastHTML.cpp : Defines the entry point for the application.
// v0.1.0

#ifdef CUSTOM_GOOGLE_TEST_DEF
//#include "../include/tests.hpp"
#endif

#include "../include/FastHTML.h"
#include <algorithm>
#include <vector>
#include <ctype.h>
#include <stdexcept>
#include <tuple>


// STATIC PROTOTYPES

static std::string RemoveSpaces(std::string);
static std::string StickPrefixWithTag(std::string);
static size_t FindWhitespace(const std::string, const size_t);
static bool HasAnyAttr(const std::string statement, const std::string openTagName);
static bool RequireAnyAttr(const std::map<std::string, std::string>);
static std::tuple<size_t, size_t> GetOpenTagIndexes(const std::string* body, const std::string openTagName);
static size_t GetNextOpenTagOpenIndex(const std::string*, const std::string, const size_t);
static size_t GetNextOpenTagCloseIndex(const std::string*, const std::string, const size_t);
static std::string ExtractStatement(const std::string*, const size_t, const size_t);
static bool CheckReqAttrExists(const std::string statement, const std::map<std::string, std::string> dict);
static bool CheckAttrsAreValid(const std::string statement, const std::string openTagName, const std::map<std::string, std::string> dict);
static std::string ExtractDataTagWithAttr(const std::string* body, const size_t openTagCloseIndex, size_t closeTagOpenIndex, const std::string openTagName, const std::string closeTagName);


// CTOR/DTOR

/*HResponse::HResponse(const std::string* body, std::pair<std::string, std::map<std::string, std::string>> filter)
{
	if (filter.first.size() < 1) return;

	const std::string tag = RemoveSpaces(filter.first);
	const std::string openTagName = '<' + tag;
	const std::string closeTagName = "</" + tag;
	auto [openTagOpenIndex, openTagCloseIndex] = GetOpenTagIndexes(body, openTagName);

	while (openTagOpenIndex != std::string::npos) {
		std::string statement = ExtractStatement(body, openTagOpenIndex, openTagCloseIndex);  // |<tag ... ... >|
		statement = RemoveSpaces(statement);  // <tag...>

		bool reqAnyAttr = RequireAnyAttr(filter.second);
		bool hasAnyAttr = HasAnyAttr(statement, openTagName);

		if (reqAnyAttr && hasAnyAttr) { // ATTRS	
			if (!CheckReqAttrExists(statement, filter.second)) {
				break;
			}

			if (!CheckAttrsAreValid(statement, openTagName, filter.second)) {
				break;
			}

			size_t closeTagOpenIndex;
			closeTagOpenIndex = body->find(closeTagName, openTagCloseIndex + 1);
			if (closeTagOpenIndex == std::string::npos || openTagCloseIndex + 1 == closeTagOpenIndex) break;

			std::string data = ExtractDataTagWithAttr(body, openTagCloseIndex, closeTagOpenIndex, openTagName, closeTagName);
			occurrence.push_back(data);
		}
		else if (!reqAnyAttr && !hasAnyAttr) { // NO ATTRS
			size_t closeTagOpenIndex;
			closeTagOpenIndex = body->find(closeTagName, openTagCloseIndex + 1);
			if (closeTagOpenIndex == std::string::npos || openTagCloseIndex + 1 == closeTagOpenIndex) break;

			std::string data = ExtractDataTagWithAttr(body, openTagCloseIndex, closeTagOpenIndex, openTagName, closeTagName);
			occurrence.push_back(data);
		}
		else { }  // wrong statement

		openTagOpenIndex = GetNextOpenTagOpenIndex(body, openTagName, openTagOpenIndex);
		openTagCloseIndex = GetNextOpenTagCloseIndex(body, openTagName, openTagOpenIndex);
	} // WHILE
}*/

HResponse::HResponse(const std::string* body, std::pair<std::string, std::map<std::string, std::string>> filter)
{
	// if html code would have whitespaces between open character '<' and tag name i.e. < div ... >
	// using body->find(openTagOpenIndex) and body->find(openTagCloseIndex) wont work !!
	// Removing whitespaces (i.e. by RemoveSpaces function) could be too expensive.
	// Need to figure it out.
	const std::string tag = RemoveSpaces(filter.first);
	const std::string openTagName = '<' + tag;
	const std::string closeTagName = "</" + tag;
	size_t openTagOpenIndex = body->find(openTagName);  // index { |<tag }
	size_t openTagCloseIndex = body->find('>', openTagOpenIndex + openTagName.size());  // index { <tag...|> }
	while (openTagOpenIndex != std::string::npos)
	{
		// check if need to find attrs
		if (filter.second.size() > 0)
		{
			//check if there is any attribute
			std::string statement = body->substr(openTagOpenIndex, openTagCloseIndex - openTagOpenIndex + 1);  // <tag ... ... >
			statement = RemoveSpaces(statement);  // <tag...>
			if (statement.size() > openTagName.size() + 2)  // must be tag + at least '>' but could be '/'. Dosent matter for attr wich req at least "a=0>" which is 4 characters
			{
				// attribute exist
				// check if exists all req attrs
				bool ok = true;
				for (const auto& kv : filter.second)
				{
					if (statement.find(kv.first) != std::string::npos) { continue; }
					else { ok = false; break; }
				}
				if (!ok)
				{
					// not this statement I am fooking for, continue
					openTagOpenIndex = body->find(openTagName, openTagOpenIndex + openTagName.size());
					openTagCloseIndex = body->find('>', openTagOpenIndex + openTagName.size());  // index { <tag...|> }
					continue;
				}
				//check if vals are valid
				std::vector<size_t> pos;
				std::string attrStatement = statement.substr(openTagName.size(), statement.size() - openTagName.size() - 1);  // <tag|attr1="asd"attr2="qwe"attr3="123"|>
				if (attrStatement.back() == '/')
				{ // TODO remove this if statement and handle '/' character
					attrStatement.erase(attrStatement.end() - 1, attrStatement.end());
				}

				bool finalOk = true;
				for (const auto& kv : filter.second)
				{
					size_t attrBegin = attrStatement.find(kv.first);
					size_t valBegin = attrBegin + kv.first.size() + 1; // =
					size_t valEnd = valBegin + kv.second.size() + 2;  // "" 
					if (attrStatement.substr(valBegin, valEnd).find(kv.second) != std::string::npos)
					{
						// ok
						continue;
					}
					else
					{
						finalOk = false;
						break;
					}
				}
				if (finalOk)
				{
					//step 1
					size_t closingTagIndex;
					closingTagIndex = body->find(closeTagName, openTagCloseIndex + 1);

					//TODO missing exception for npos
					if (closingTagIndex == std::string::npos)
					{
						// exception, there must me closing tag "</tag>"
					}
					// C
					if (openTagCloseIndex + 1 == closingTagIndex)
					{
						//there is no data
						occurrence.push_back("#NO DATA");
						continue;
					}
					// B
					// closingTagIndex has an index
					// check if redundant openTagName appear between <tag> and </tag>
					size_t nextRedundantOpenTagIndex = body->substr(openTagCloseIndex + 1, closingTagIndex - (openTagCloseIndex + 1)).find(openTagName);
					bool tmp = false;
					if (nextRedundantOpenTagIndex != std::string::npos)
					{ // found redundant openTagName on nextRedundantOpenTagIndex
						// nextRedundantOpenTagIndex keeps first redundant open address
						size_t redundantOpens = 1;
						while (redundantOpens)
						{
							// ups open
							while (true) {
								nextRedundantOpenTagIndex = body->substr(openTagCloseIndex + 1 + nextRedundantOpenTagIndex + openTagName.size(), closingTagIndex - (nextRedundantOpenTagIndex + openTagName.size() + openTagCloseIndex + 1)).find(openTagName);
								if (nextRedundantOpenTagIndex != std::string::npos)
								{
									redundantOpens++;
									tmp = true;
								}
								else
								{
									break;
								}
							}

							// shifting closing index to the next maching close tag
							nextRedundantOpenTagIndex = closingTagIndex + closeTagName.size();
							closingTagIndex = body->find(closeTagName, closingTagIndex + closeTagName.size());
							redundantOpens--;
						}
					}
					// data are stored between {openTagCloseIndex + 1} and {closingTagIndex}
					std::string data = body->substr(openTagCloseIndex + 1, closingTagIndex - (openTagCloseIndex + 1));
					occurrence.push_back(data);
				}
				openTagOpenIndex = body->find(openTagName, openTagOpenIndex + openTagName.size());
				openTagCloseIndex = body->find('>', openTagOpenIndex + openTagName.size());  // index { <tag...|> }
				continue;
			}
			else
			{
				// not this statement I am fooking for, continue
			}
		} // ATTRS
		else
		{
			/*
			* if have attrs > continue
			* else finalOk, add data from this statement to object
			*
			*/
		} // NO ATTRS
		openTagOpenIndex = body->find(openTagName, openTagOpenIndex + openTagName.size());
		openTagCloseIndex = body->find('>', openTagOpenIndex + openTagName.size());  // index { <tag...|> }
		// set all again
	} // WHILE
}

HResponse::~HResponse()
{
}


// METHODS

std::string HResponse::GetData()
{
	if (occurrence.size() > 0) return occurrence.back();
	
	return "UPS";
}


// FUNCTIONS

std::string ClearOtherTags(std::string dataWithTags)
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
	
	std::string statement = StickPrefixWithTag(dataWithTags);

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
	size_t openTagCloseIndex = body->find('>', openTagOpenIndex + openTagName.size());  // index { <tag...|> }

	return std::make_tuple(openTagOpenIndex, openTagCloseIndex);
}

static size_t GetNextOpenTagOpenIndex(const std::string* body, const std::string openTagName, const size_t openTagOpenIndex)
{
	return body->find(openTagName, openTagOpenIndex + openTagName.size());
}

static size_t GetNextOpenTagCloseIndex(const std::string* body, const std::string openTagName, const size_t openTagOpenIndex)
{
	return body->find('>', openTagOpenIndex + openTagName.size());
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

static std::string ExtractDataTagWithAttr(const std::string* body, const size_t openTagCloseIndex, size_t closeTagOpenIndex, const std::string openTagName, const std::string closeTagName)
{
	size_t nextRedundantOpenTagIndex = body->substr(openTagCloseIndex + 1, closeTagOpenIndex - (openTagCloseIndex + 1)).find(openTagName);
	if (nextRedundantOpenTagIndex != std::string::npos)
	{
		size_t redundantOpens = 1;
		while (redundantOpens)
		{
			while (true) {
				nextRedundantOpenTagIndex = body->substr(nextRedundantOpenTagIndex + openTagName.size(), closeTagOpenIndex - (nextRedundantOpenTagIndex + openTagName.size())).find(openTagName);
				if (nextRedundantOpenTagIndex != std::string::npos)
				{
					redundantOpens++;
				}
				else
				{
					break;
				}
			}

			nextRedundantOpenTagIndex = closeTagOpenIndex + closeTagName.size();
			closeTagOpenIndex = body->find(closeTagName, closeTagOpenIndex + closeTagName.size());
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
#endif

