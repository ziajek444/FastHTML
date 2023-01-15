// FastHTML.cpp : Defines the entry point for the application.
// v0.0.1a

#include "../include/FastHTML.h"
#include <algorithm>
#include <vector>
#include <ctype.h>

static std::string RemoveSpaces(std::string str);
static std::string StickPrefixWithTag(std::string str);
static size_t FindWhitespace(std::string str, size_t offset=0);

HResponse::HResponse(const std::string *body, std::pair<std::string, std::map<std::string, std::string>> filter)
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
					continue;
				}
				//check if vals are valid
				std::vector<size_t> pos;
				std::string attrStatement = statement.substr(openTagName.size(), statement.size()- openTagName.size() - 1);  // <tag|attr1="asd"attr2="qwe"attr3="123"|>
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
					size_t nextRedundantOpenTagIndex = body->substr(openTagCloseIndex + 1, closingTagIndex).find(openTagName) + openTagCloseIndex + 1;
					bool tmp = false;
					if (nextRedundantOpenTagIndex != std::string::npos)
					{ // found redundant openTagName on nextRedundantOpenTagIndex
						// nextRedundantOpenTagIndex keeps first redundant open address
						size_t redundantOpens = 1;
						while (redundantOpens)
						{
							// ups open
							while (true) {
								nextRedundantOpenTagIndex = body->substr(nextRedundantOpenTagIndex + openTagName.size(), closingTagIndex).find(openTagName);
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
		openTagOpenIndex = body->find(openTagName, openTagOpenIndex+openTagName.size());
		// set all again
	} // WHILE
}

HResponse::~HResponse()
{
}

std::string HResponse::GetData()
{
	if (occurrence.size() > 0) return occurrence.back();
	
	return "UPS";
}

static std::string RemoveSpaces(std::string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

std::string ClearOtherTags(std::string dataWithTags)
{
	size_t openTagOpenCharacterIndex = 0;
	size_t openTagCloseCharacterIndex = 0;
	size_t firstCloseCharacterIndex = 0;
	size_t lastCloseCharacterIndex = 0;
	size_t spaceAfterOpenTag = 0;
	std::string tagName = "";
	std::string openTagName = "";
	std::string closeTagName = "";
	const std::string closePrefixStr = "</";
	const std::string openPrefixStr = "<";
	
	// stick prefixes '<' and '< /' with tag name
	// " <  tag ... > " ->  " <tag ... > ",
	//  " <  /  tag ... > " -> " </  tag ... > ",
	// " </  tag ... > " ->  " </tag ... > "
	std::string statement = StickPrefixWithTag(dataWithTags);

	// STAYS |          REMOVE          | STAYS
	//	 ... {<tag ... > ... </tag ... >} ...
	while (true)
	{
		openTagOpenCharacterIndex = statement.find('<', lastCloseCharacterIndex);  // |<tag ...  >
		if (openTagOpenCharacterIndex == std::string::npos) break;  // there is no any open prefixes
		spaceAfterOpenTag = FindWhitespace(statement, openTagOpenCharacterIndex + 1);  // <tag| ...  >
		
		// get tagName, openTagName, closeTagName
		// find closest openTagName and set index fight before |<tag ... >
		// find latest closeTagName and set index to last character </tag ... |>
		// erase data between them (|<tag ... > ... ... ... </tag ... |>)
		// fin, go testing
	}
	
	return statement;
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

		while (isspace(statement[openTagCloseCharacterIndex + 1 + whitespaceCount++])) {}
		if (whitespaceCount) whitespaceCount--;
		statement.erase(openTagCloseCharacterIndex + 1, whitespaceCount);
		openTagCloseCharacterIndex = statement.find(closePrefixStr, openTagCloseCharacterIndex + 1);
	}

	return statement;
}

static size_t FindWhitespace(std::string str, size_t offset = 0)
{
	size_t whiteSpaceIndex = 0;
	size_t strSize = str.size();

	while (!isspace(str[offset + whiteSpaceIndex])) {
		whiteSpaceIndex++;
		if(whiteSpaceIndex + offset >= strSize) return std::string::npos;
	}

	return whiteSpaceIndex;
}
