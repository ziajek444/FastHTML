#include <gtest/gtest.h>
#include <string>
#include "../include/FastHTML.h"
#define DO_TEST_ComplexTag_ComplexTag_1 0
#define DO_TEST_ComplexTag_ComplexTag_2 0
#define DO_TEST_ComplexTag_ComplexTag_3 0
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_01 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_02 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_03 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_04 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_05 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_06 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_07 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_08 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_09 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_10 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_11 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_12 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_13 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_14 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_15 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_16 1
#define DO_TEST_FastHTML_ClearOtherTags_ClearOtherTags_17 1

#define GTEST_COUT std::cerr << " ### "


TEST(ComplexTag, ComplexTag_1) {
#if DO_TEST_ComplexTag_ComplexTag_1 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second;
	HResponse lastResponse{ &resp, filter };
	EXPECT_EQ(lastResponse.GetData(), "General Kenobi");

	std::string rura;	
}

TEST(ComplexTag, ComplexTag_2) {
#if DO_TEST_ComplexTag_ComplexTag_2 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["class"] = "Dog";
	HResponse lastResponse{ &resp, filter };
	EXPECT_EQ(lastResponse.GetData(), "Hello There");
}

TEST(ComplexTag, ComplexTag_3) {
#if DO_TEST_ComplexTag_ComplexTag_3 == 0
	GTEST_SKIP();
#endif
	std::string resp = "<body><div><p>General Kenobi</p></div><span>4.4</span><div><p>Hello There</p><p class = \"Dog\">Hello There</p></div><p class=\"Cat\">Han Solo</p><div><p>Grives</p></div></body>";
	std::pair<std::string, std::map<std::string, std::string>> filter;
	filter.first = "p";
	filter.second["class"] = "Cat";
	HResponse lastResponse{ &resp, filter };
	EXPECT_EQ(lastResponse.GetData(), "Han Solo");
}


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
