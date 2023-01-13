#include <gtest/gtest.h>
#include <string>
#include "../include/FastHTML.h"



TEST(ComplexTag, ComplexTag_1) {
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second;

	HResponse lastResponse{ &resp, filter };
	EXPECT_EQ(lastResponse.GetData(), "General Kenobi");
}

TEST(ComplexTag, ComplexTag_2) {
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["class"] = "Dog";
	HResponse lastResponse{ &resp, filter };
	EXPECT_EQ(lastResponse.GetData(), "Hello There");
}

TEST(ComplexTag, ComplexTag_3) {
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["class"] = "Cat";
	HResponse lastResponse{ &resp, filter };
	EXPECT_EQ(lastResponse.GetData(), "Han Solo");
}
