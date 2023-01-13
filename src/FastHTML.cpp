// FastHTML.cpp : Defines the entry point for the application.
// v0.0.1a

#include "../include/FastHTML.h"
#include <algorithm>
#include <vector>

static std::string RemoveSpaces(std::string str);

HResponse::HResponse(const std::string *body, std::pair<std::string, std::map<std::string, std::string>> filter)
{
	const size_t additionalSpace = 1024;
	std::string tag = '<' + RemoveSpaces(filter.first);
	size_t open = body->find(tag);  // index { |<tag }
	size_t close = body->find('>', open + tag.size());  // index { <tag...|> }

	
	while (open != std::string::npos)
	{
		// check if need to find attrs
		if (filter.second.size() > 0)
		{
			//check if there is any attribute
			std::string statement = body->substr(open, close - open + 1);  // <tag ... ... >
			statement = RemoveSpaces(statement);  // <tag...>
			if (statement.size() > tag.size() + 2)  // must be tag + at least '>' but could be '/'. Dosent matter for attr wich req at least "a=0>" which is 4 characters
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
				}
				//check if vals are valid
				std::vector<size_t> pos;
				std::string attrStatement = statement.substr(tag.size(), statement.size()- tag.size() - 1);  // <tag|attr1="asd"attr2="qwe"attr3="123"|>
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
					}
					else
					{
						finalOk = false;
						break;
					}
				}
				if (finalOk)
				{
					// add data from this statement to object
				}
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
		open = std::string::npos; // For debug purpose, REMOVE IT !! 
	} // WHILE
}

HResponse::~HResponse()
{
}

std::string HResponse::GetData()
{
	return "Hello There";
}

static std::string RemoveSpaces(std::string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}



