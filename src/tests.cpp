#include <gtest/gtest.h>
#include <string>
#include "../include/FastHTML.h"

#define RUN 1
#define SKIP 0

#define DO_TEST_ComplexTag_ComplexTag_01 RUN
#define DO_TEST_ComplexTag_ComplexTag_02 RUN
#define DO_TEST_ComplexTag_ComplexTag_03 RUN
#define DO_TEST_ComplexTag_ComplexTag_04 RUN
#define DO_TEST_ComplexTag_ComplexTag_05 RUN
#define DO_TEST_ComplexTag_ComplexTag_06 RUN
#define DO_TEST_ComplexTag_ComplexTag_07 RUN
#define DO_TEST_ComplexTag_ComplexTag_08 RUN
#define DO_TEST_ComplexTag_ComplexTag_09 RUN
#define DO_TEST_ComplexTag_ComplexTag_10 RUN
#define DO_TEST_ComplexTag_ComplexTag_11 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_01 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_02 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_03 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_04 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_05 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_06 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_07 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_08 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_09 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_10 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_11 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_12 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_13 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_14 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_15 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_16 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_17 RUN
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_18 RUN  // related to DO_TEST_ComplexTag_ComplexTag_4
#define DO_TEST_STATIC_FastHTML_FindWhitespace_01 RUN
#define DO_TEST_STATIC_FastHTML_FindWhitespace_02 RUN
#define DO_TEST_STATIC_FastHTML_FindWhitespace_03 RUN
#define DO_TEST_STATIC_FastHTML_FindWhitespace_04 RUN
#define DO_TEST_STATIC_FastHTML_FindWhitespace_05 RUN
#define DO_TEST_STATIC_FastHTML_FindWhitespace_06 RUN
#define DO_TEST_STATIC_FastHTML_FindWhitespace_07 RUN
#define DO_TEST_STATIC_FastHTML_FindWhitespace_08 RUN
#define DO_TEST_STATIC_FastHTML_FindWhitespace_09 RUN
#define DO_TEST_STATIC_FastHTML_FindWhitespace_10 RUN
#define DO_TEST_STATIC_FastHTML_StickPrefixWithTag_01 RUN
#define DO_TEST_STATIC_FastHTML_StickPrefixWithTag_02 RUN
#define DO_TEST_STATIC_FastHTML_StickPrefixWithTag_03 RUN
#define DO_TEST_STATIC_FastHTML_StickPrefixWithTag_04 RUN
#define DO_TEST_STATIC_FastHTML_StickPrefixWithTag_05 RUN
#define DO_TEST_STATIC_FastHTML_StickPrefixWithTag_06 RUN
#define DO_TEST_STATIC_FastHTML_StickPrefixWithTag_07 RUN
#define DO_TEST_STATIC_FastHTML_StickPrefixWithTag_08 RUN
#define DO_TEST_STATIC_FastHTML_RemoveSpaces_01 RUN
#define DO_TEST_STATIC_FastHTML_RemoveSpaces_02 RUN
#define DO_TEST_STATIC_FastHTML_RemoveSpaces_03 RUN
#define DO_TEST_STATIC_FastHTML_RemoveSpaces_04 RUN
#define DO_TEST_STATIC_FastHTML_RemoveSpaces_05 RUN
#define DO_TEST_STATIC_FastHTML_RemoveSpaces_06 RUN

#define GTEST_COUT std::cerr << " ! ! ! \n"


// -  -  -  -  -  -  -  -  -  -  -  - 
// obj init

TEST(ComplexTag, ComplexTag_1) {
#if DO_TEST_ComplexTag_ComplexTag_01 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second;
	HResponse lastResponse{ &resp, filter };
	EXPECT_EQ(lastResponse.GetFirstData(), "General Kenobi");
	EXPECT_EQ(lastResponse.GetLastData(), "Grives");
}

TEST(ComplexTag, ComplexTag_2) {
#if DO_TEST_ComplexTag_ComplexTag_02 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["class"] = "Dog";
	HResponse lastResponse{ &resp, filter };
	std::string ret = lastResponse.GetLastData();
	EXPECT_EQ(ret, "Hello There");
}

TEST(ComplexTag, ComplexTag_3) {
#if DO_TEST_ComplexTag_ComplexTag_03 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["class"] = "Cat";
	HResponse lastResponse{ &resp, filter };
	std::string ret = lastResponse.GetLastData();
	EXPECT_EQ(ret, "Han Solo");
}

TEST(ComplexTag, ComplexTag_4) {
#if DO_TEST_ComplexTag_ComplexTag_04 == 0
	GTEST_SKIP();
#endif
	// <p></p> inside
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han <p>nothing</p>Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["class"] = "Cat";
	HResponse lastResponse{ &resp, filter };
	std::string ret = lastResponse.GetLastData();
	EXPECT_EQ(ret, "Han <p>nothing</p>Solo");
}

TEST(ComplexTag, ComplexTag_5) {
#if DO_TEST_ComplexTag_ComplexTag_05 == 0
	GTEST_SKIP();
#endif
	// </p> inside, no open exists
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han </p>Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["class"] = "Cat";
	HResponse lastResponse{ &resp, filter };
	std::string ret = lastResponse.GetLastData();
	EXPECT_EQ(ret, "Han ");
}

TEST(ComplexTag, ComplexTag_6) {
#if DO_TEST_ComplexTag_ComplexTag_06 == 0
	GTEST_SKIP();
#endif
	// <p> inside, no close exists
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han <p>Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["class"] = "Cat";
	HResponse lastResponse{ &resp, filter };
	std::string ret = lastResponse.GetLastData();
	EXPECT_EQ(ret, "Han <p>Solo</p><div><p>Grives");
}

TEST(ComplexTag, ComplexTag_7) {
#if DO_TEST_ComplexTag_ComplexTag_07 == 0
	GTEST_SKIP();
#endif
	// looking for tag does not exists
	std::string resp = "<body><div></div><span>4.4</span><div></div><div></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second;
	HResponse lastResponse{ &resp, filter };
	std::string ret = lastResponse.GetLastData();
	EXPECT_EQ(ret, "UPS");
}

TEST(ComplexTag, ComplexTag_8) {
#if DO_TEST_ComplexTag_ComplexTag_08 == 0
	GTEST_SKIP();
#endif
	// cover CheckAttrsAreValid for reqAttr + hasAttr + notValidAttrValues #1
	std::string resp = "<body><div><p id=12 class=\"XWING\">Hello There</p><p >General Kenobi</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["id"] = "11";
	filter.second["class"] = "XWING";
	HResponse lastResponse{ &resp, filter };
	std::string ret = lastResponse.GetLastData();
	EXPECT_EQ(ret, "UPS");
}

TEST(ComplexTag, ComplexTag_9) {
#if DO_TEST_ComplexTag_ComplexTag_09 == 0
	GTEST_SKIP();
#endif
	// cover CheckAttrsAreValid for reqAttr + hasAttr + notValidAttrValues #2
	std::string resp = "<body><div><p id=11 class=\"Lawbringer\">Hello There</p><p >General Kenobi</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["id"] = "11";
	filter.second["class"] = "XWING";
	HResponse lastResponse{ &resp, filter };
	std::string ret = lastResponse.GetLastData();
	EXPECT_EQ(ret, "UPS");
}

TEST(ComplexTag, ComplexTag_10) {
#if DO_TEST_ComplexTag_ComplexTag_10 == 0
	GTEST_SKIP();
#endif
	// cover CRC for tests 8 and 9
	std::string resp = "<body><div><p id=11 class=\"XWING\">Hello There</p><p >General Kenobi</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["id"] = "11";
	filter.second["class"] = "XWING";
	HResponse lastResponse{ &resp, filter };
	std::string ret = lastResponse.GetLastData();
	EXPECT_EQ(ret, "Hello There");
}

TEST(ComplexTag, ComplexTag_11) {
#if DO_TEST_ComplexTag_ComplexTag_11 == 0
	GTEST_SKIP();
#endif
	// cover CheckAttrsAreValid for reqAttr + hasAttr + notValidAttrNames
	std::string resp = "<body><div><p id=12>Hello There</p><p class=\"XWING\">General Kenobi</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["id"] = "11";
	filter.second["class"] = "XWING";
	HResponse lastResponse{ &resp, filter };
	std::string ret = lastResponse.GetLastData();
	EXPECT_EQ(ret, "UPS");
}


// -  -  -  -  -  -  -  -  -  -  -  - 
// ClearOtherTags

TEST(FastHTML_ClearOtherTags, ClearOtherTags_1) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_01 == 0
	GTEST_SKIP();
#endif
	std::string resp = "Wanted data<tag1>Unwanted data</tag1>";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_2) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_02 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<tag1>Unwanted data</tag1>Wanted data<tag1>Unwanted data</tag1>";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_3) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_03 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<tag1>Unwanted data</tag1>Wanted data";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_4) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_04 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 >Unwanted data< / tag1 >Wanted data< tag1 >Unwanted data< / tag1 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_5) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_05 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 >Unwanted data< / tag1 >Wanted data<tag2>< tag1 >Unwanted data< / tag1 ></tag2>";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_6) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_06 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 >Unwanted data< / tag1 >Wanted data< tag2 ><tag1>Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_7) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_07 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class=\"custom_class1\">Unwanted data< / tag1 >Wanted data< tag2 id=4.4><tag1>Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_8) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_08 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class=\"custom_class1\" id=\"100\">Unwanted data< / tag1 >Wanted data< tag2 id=4.4 class=\"custom_class2\"><tag1>Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_9) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_09 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class = \"custom_class1\" id=\"100\">Unwanted data< / tag1 >Wanted data< tag2 id = 4.4 class = \"custom_class2\" ><tag1>Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_10) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_10 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class = \"custom_class1\" id=\"100\">Unwanted data< / tag1 >Wanted data< tag2 id = 4.4 class = \"custom_class2\" ><tag1><tr>Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_11) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_11 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class = \"custom_class1\" id=\"100\"><tr>Unwanted data< / tag1 >Wanted data< tag2 id = 4.4 class = \"custom_class2\" ><tag1><tr>Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_12) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_12 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class = \"custom_class1\" id=\"100\"><tr/>Unwanted data< / tag1 >Wanted data< tag2 id = 4.4 class = \"custom_class2\" ><tag1><tr>Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_13) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_13 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class = \"custom_class1\" id=\"100\"><tr/>Unwanted data< / tag1 >Wanted data< tag2 id = 4.4 class = \"custom_class2\" ><tag1><tr/>Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_14) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_14 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class = \"custom_class1\" id=\"100\">< tr />Unwanted data< / tag1 >Wanted data< tag2 id = 4.4 class = \"custom_class2\" ><tag1>< tr />Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_15) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_15 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class = \"custom_class1\" id=\"100\">< tr />Unwanted data< / tag1 ><tr>Wanted data< tag2 id = 4.4 class = \"custom_class2\" ><tag1>< tr />Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_16) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_16 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class = \"custom_class1\" id=\"100\">< tr />Unwanted data< / tag1 >< tr >Wanted data< tag2 id = 4.4 class = \"custom_class2\" ><tag1>< tr />Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_17) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_17 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag1 class = \"custom_class1\" id=\"100\">< tr />Unwanted data< / tag1 >< tr />Wanted data< tag2 id = 4.4 class = \"custom_class2\" ><tag1>< tr />Unwanted data</tag1>< / tag2 >";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Wanted data");
}

TEST(FastHTML_ClearOtherTags, ClearOtherTags_18) {
#if DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_18 == 0
	GTEST_SKIP();
#endif
	std::string resp = "Han <p>nothing< / p>Solo";
	std::string ret = ClearOtherTags(resp);
	EXPECT_EQ(ret, "Han Solo");
}




// -  -  -  -  -  -  -  -  -  -  -  - 
// GtestWrapper_FastHTML_FindWhitespace

TEST(STATIC_FastHTML, FindWhitespace_01) {
#if DO_TEST_STATIC_FastHTML_FindWhitespace_01 == 0
	GTEST_SKIP();
#endif
	std::string resp = " 0 index space";
	size_t ret = GtestWrapper_FastHTML_FindWhitespace(resp, 0);
	EXPECT_EQ(ret, 0);
}

TEST(STATIC_FastHTML, FindWhitespace_02) {
#if DO_TEST_STATIC_FastHTML_FindWhitespace_02 == 0
	GTEST_SKIP();
#endif
	std::string resp = " 2 index space";
	size_t ret = GtestWrapper_FastHTML_FindWhitespace(resp, 1);
	EXPECT_EQ(ret, 2);
}

TEST(STATIC_FastHTML, FindWhitespace_03) {
#if DO_TEST_STATIC_FastHTML_FindWhitespace_03 == 0
	GTEST_SKIP();
#endif
	std::string resp = " 8 index space";
	size_t ret = GtestWrapper_FastHTML_FindWhitespace(resp, 5);
	EXPECT_EQ(ret, 8);
}

TEST(STATIC_FastHTML, FindWhitespace_04) {
#if DO_TEST_STATIC_FastHTML_FindWhitespace_04 == 0
	GTEST_SKIP();
#endif
	std::string resp = " NPOS index space";
	size_t ret = GtestWrapper_FastHTML_FindWhitespace(resp, 12);
	EXPECT_EQ(ret, std::string::npos);
}

TEST(STATIC_FastHTML, FindWhitespace_05) {
#if DO_TEST_STATIC_FastHTML_FindWhitespace_05 == 0
	GTEST_SKIP();
#endif
	std::string resp = "NPOS";
	size_t ret = GtestWrapper_FastHTML_FindWhitespace(resp, 12);
	EXPECT_EQ(ret, std::string::npos);
}

TEST(STATIC_FastHTML, FindWhitespace_06) {
#if DO_TEST_STATIC_FastHTML_FindWhitespace_06 == 0
	GTEST_SKIP();
#endif
	std::string resp = "";
	size_t ret = GtestWrapper_FastHTML_FindWhitespace(resp, 0);
	EXPECT_EQ(ret, std::string::npos);
}

TEST(STATIC_FastHTML, FindWhitespace_07) {
#if DO_TEST_STATIC_FastHTML_FindWhitespace_07 == 0
	GTEST_SKIP();
#endif
	std::string resp = " ";
	size_t ret = GtestWrapper_FastHTML_FindWhitespace(resp, 0);
	EXPECT_EQ(ret, 0);
}

TEST(STATIC_FastHTML, FindWhitespace_08) {
#if DO_TEST_STATIC_FastHTML_FindWhitespace_08 == 0
	GTEST_SKIP();
#endif
	std::string resp = " Lot of spaces but npos cos started too far ";
	size_t ret = GtestWrapper_FastHTML_FindWhitespace(resp, 1000);
	EXPECT_EQ(ret, std::string::npos);
}

TEST(STATIC_FastHTML, FindWhitespace_09) {
#if DO_TEST_STATIC_FastHTML_FindWhitespace_09 == 0
	GTEST_SKIP();
#endif
	std::string resp = "";
	size_t ret = GtestWrapper_FastHTML_FindWhitespace(resp, 1000);
	EXPECT_EQ(ret, std::string::npos);
}

TEST(STATIC_FastHTML, FindWhitespace_10) {
#if DO_TEST_STATIC_FastHTML_FindWhitespace_10 == 0
	GTEST_SKIP();
#endif
	std::string resp = " Lot of spaces but npos cos started too far ";
	size_t ret = GtestWrapper_FastHTML_FindWhitespace(resp, -1); // size_t will never be smaller than 0
	EXPECT_EQ(ret, std::string::npos);
}


// -  -  -  -  -  -  -  -  -  -  -  - 
// GtestWrapper_FastHTML_StickPrefixWithTag

TEST(STATIC_FastHTML, StickPrefixWithTag_01) {
#if DO_TEST_STATIC_FastHTML_StickPrefixWithTag_01 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<tag>Some Data</tag>";
	std::string ret = GtestWrapper_FastHTML_StickPrefixWithTag(resp);
	EXPECT_EQ(ret, "<tag>Some Data</tag>");
}

TEST(STATIC_FastHTML, StickPrefixWithTag_02) {
#if DO_TEST_STATIC_FastHTML_StickPrefixWithTag_02 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag>Some Data</tag>";
	std::string ret = GtestWrapper_FastHTML_StickPrefixWithTag(resp);
	EXPECT_EQ(ret, "<tag>Some Data</tag>");
}

TEST(STATIC_FastHTML, StickPrefixWithTag_03) {
#if DO_TEST_STATIC_FastHTML_StickPrefixWithTag_03 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<tag >Some Data</tag>";
	std::string ret = GtestWrapper_FastHTML_StickPrefixWithTag(resp);
	EXPECT_EQ(ret, "<tag >Some Data</tag>");
}

TEST(STATIC_FastHTML, StickPrefixWithTag_04) {
#if DO_TEST_STATIC_FastHTML_StickPrefixWithTag_04 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<tag>Some Data< /tag>";
	std::string ret = GtestWrapper_FastHTML_StickPrefixWithTag(resp);
	EXPECT_EQ(ret, "<tag>Some Data</tag>");
}

TEST(STATIC_FastHTML, StickPrefixWithTag_05) {
#if DO_TEST_STATIC_FastHTML_StickPrefixWithTag_05 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<tag>Some Data</ tag>";
	std::string ret = GtestWrapper_FastHTML_StickPrefixWithTag(resp);
	EXPECT_EQ(ret, "<tag>Some Data</tag>");
}

TEST(STATIC_FastHTML, StickPrefixWithTag_06) {
#if DO_TEST_STATIC_FastHTML_StickPrefixWithTag_06 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<tag>Some Data</tag >";
	std::string ret = GtestWrapper_FastHTML_StickPrefixWithTag(resp);
	EXPECT_EQ(ret, "<tag>Some Data</tag >");
}

TEST(STATIC_FastHTML, StickPrefixWithTag_07) {
#if DO_TEST_STATIC_FastHTML_StickPrefixWithTag_07 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< tag >Some Data< / tag >";
	std::string ret = GtestWrapper_FastHTML_StickPrefixWithTag(resp);
	EXPECT_EQ(ret, "<tag >Some Data</tag >");
}

TEST(STATIC_FastHTML, StickPrefixWithTag_08) {
#if DO_TEST_STATIC_FastHTML_StickPrefixWithTag_08 == 0
	GTEST_SKIP();
#endif
	std::string resp = "< / tag> < / tag > < tag> Some Data < / tag > < tag>< tag > < tag>";
	std::string ret = GtestWrapper_FastHTML_StickPrefixWithTag(resp);
	EXPECT_EQ(ret, "</tag> </tag > <tag> Some Data </tag > <tag><tag > <tag>");
}


// -  -  -  -  -  -  -  -  -  -  -  - 
// GtestWrapper_FastHTML_RemoveSpaces

TEST(STATIC_FastHTML, RemoveSpaces_01) {
#if DO_TEST_STATIC_FastHTML_RemoveSpaces_01 == 0
	GTEST_SKIP();
#endif
	std::string resp = "     few spaces at start";
	std::string ret = GtestWrapper_FastHTML_RemoveSpaces(resp);
	EXPECT_EQ(ret, "fewspacesatstart");
}

TEST(STATIC_FastHTML, RemoveSpaces_02) {
#if DO_TEST_STATIC_FastHTML_RemoveSpaces_02 == 0
	GTEST_SKIP();
#endif
	std::string resp = "few spaces at the end     ";
	std::string ret = GtestWrapper_FastHTML_RemoveSpaces(resp);
	EXPECT_EQ(ret, "fewspacesattheend");
}

TEST(STATIC_FastHTML, RemoveSpaces_03) {
#if DO_TEST_STATIC_FastHTML_RemoveSpaces_03 == 0
	GTEST_SKIP();
#endif
	std::string resp = "nospacesatall";
	std::string ret = GtestWrapper_FastHTML_RemoveSpaces(resp);
	EXPECT_EQ(ret, "nospacesatall");
}

TEST(STATIC_FastHTML, RemoveSpaces_04) {
#if DO_TEST_STATIC_FastHTML_RemoveSpaces_04 == 0
	GTEST_SKIP();
#endif
	std::string resp = "";
	std::string ret = GtestWrapper_FastHTML_RemoveSpaces(resp);
	EXPECT_EQ(ret, "");
}

TEST(STATIC_FastHTML, RemoveSpaces_05) {
#if DO_TEST_STATIC_FastHTML_RemoveSpaces_05 == 0
	GTEST_SKIP();
#endif
	std::string resp = "            ";
	std::string ret = GtestWrapper_FastHTML_RemoveSpaces(resp);
	EXPECT_EQ(ret, "");
}

TEST(STATIC_FastHTML, RemoveSpaces_06) {
#if DO_TEST_STATIC_FastHTML_RemoveSpaces_06 == 0
	GTEST_SKIP();
#endif
	std::string resp = " ";
	std::string ret = GtestWrapper_FastHTML_RemoveSpaces(resp);
	EXPECT_EQ(ret, "");
}