/*
 * tests.cpp
 *
 *  Created on: Oct 21, 2012
 *      Author: iso
 */

#include <gtest/gtest.h>
#include "MyString.h"
#include <iostream>

TEST(MyStringTests, Constructors) {
	String s0;
	String s1("");
	String s2("abc");
	String s00(s0);
	String s11(s1);
	String s22(s2);
}

TEST(MyStringTests, length) {
	ASSERT_EQ(String().length(), 0);
	ASSERT_EQ(String("").length(), 0);
	ASSERT_EQ(String("abc").length(), 3);
}

TEST(MyStringTests, charAt) {
	String foobar("foobar");
	ASSERT_EQ('f', foobar.charAt(0));
	ASSERT_EQ('o', foobar.charAt(1));
	ASSERT_EQ('o', foobar.charAt(2));
	ASSERT_EQ('b', foobar.charAt(3));
	ASSERT_EQ('a', foobar.charAt(4));
	ASSERT_EQ('r', foobar.charAt(5));
	ASSERT_ANY_THROW(foobar.charAt(6));
	ASSERT_ANY_THROW(foobar.charAt(-1));
}

TEST(MyStringTests, compareTo) {
	ASSERT_LT(String("a").compareTo(String("b")), 0);
	ASSERT_LT(String("").compareTo(String("a")), 0);
	ASSERT_LT(String("aa").compareTo(String("aaa")), 0);
}

TEST(MyStringTests, concatString) {
	ASSERT_EQ(String("foobar"), String("foo").concat(String("bar")));
}

TEST(MyStringTests, concatStringEmpty) {
	ASSERT_EQ(String("foobar"), String("foobar").concat(String("")));
	ASSERT_EQ(String("foobar"), String("").concat(String("foobar")));
}

TEST(MyStringTests, concatChar) {
	ASSERT_EQ(String("foobar"), String("fooba").concat('r'));
}

TEST(MyStringTests, concatEmptyChar) {
	ASSERT_EQ(String("foo"), String("").concat('f').concat('o').concat('o'));
}

TEST(MyStringTests, subString) {
	String foobar("foobar");

	EXPECT_EQ(String("foo"), foobar.subString(0, 3));
	EXPECT_EQ(String("oo"), foobar.subString(1, 3));
	EXPECT_EQ(String("o"), foobar.subString(2, 3));
	EXPECT_EQ(String("bar"), foobar.subString(3, 6));
	EXPECT_EQ(String("ar"), foobar.subString(4, 6));
	EXPECT_EQ(String("r"), foobar.subString(5, 6));

	EXPECT_EQ(String(""), foobar.subString(0, 0));
	EXPECT_EQ(String(""), foobar.subString(2, 1));
	EXPECT_EQ(String(""), foobar.subString(5, 5));
}

TEST(MyStringTests, toCString) {
	EXPECT_STREQ("foo", String("foo").toCString().get());
	EXPECT_STREQ("", String("").toCString().get());
}

TEST(MyStringTests, valueOf) {
	ASSERT_EQ(String("17"), String::valueOf(17));
	ASSERT_EQ(String("917"), String::valueOf(917));
	ASSERT_EQ(String("0"), String::valueOf(0));
	ASSERT_EQ(String("97628"), String::valueOf(97628));
}


/* following tests were given by Stamm/Nicola */
TEST(GivenStringTests, Construction) {
		String s0;
		String s1("");
		String s2("abc");
		String s00(s0);
		String s11(s1);
		String s22(s2);
}
TEST(GivenStringTests, Length) {
	EXPECT_TRUE(String().length() == 0);
	EXPECT_TRUE(String("").length() == 0);
	EXPECT_TRUE(String("abc").length() == 3);
}
TEST(GivenStringTests, ToCString) {
	// EXPECT_EQ fails here
	EXPECT_STREQ(String().toCString().get(), "");
	EXPECT_STREQ(String("abc").toCString().get(), "abc");
}
TEST(GivenStringTests, Equals) {
	String s("abc");
	EXPECT_TRUE(String() == String(""));
	EXPECT_TRUE(String("") == String());
	EXPECT_TRUE(s ==  s);
	EXPECT_FALSE(s == String("ab"));
}
TEST(GivenStringTests, Compare) {
	String s("abc");
	EXPECT_EQ(String().compareTo(""), 0);
	EXPECT_TRUE(s.compareTo("bcd") < 0);
	EXPECT_TRUE(s.compareTo("abde") < 0);
	EXPECT_TRUE(s.compareTo("abcd") < 0);
	EXPECT_TRUE(s.compareTo("abbb") > 0);
	EXPECT_TRUE(s.compareTo("ABC") > 0);
	EXPECT_TRUE(s.compareTo("") > 0);
	EXPECT_TRUE(String().compareTo(s) < 0);
}
TEST(GivenStringTests, CharAt) {
	String s("abc");
	EXPECT_EQ(s.charAt(0), 'a');
	EXPECT_EQ(s.charAt(1), 'b');
	EXPECT_EQ(s.charAt(2), 'c');

	/*
	bool catched = false;
	try {
		s.charAt(-1);
	} catch(exception&) {
		catched = true;
	}
	EXPECT_TRUE(catched);

	catched = false;
	try {
		String("abc").charAt(3);
	} catch(exception&) {
		catched = true;
	}
	EXPECT_TRUE(catched);

	 */

	// this can be done so easy...
	EXPECT_THROW(s.charAt(-1), std::exception);
	EXPECT_THROW(String("abc").charAt(3), std::exception);

}
TEST(GivenStringTests, Concat) {
	String s;
	EXPECT_TRUE(s.concat("") == "");
	EXPECT_TRUE(s.concat('a') == "a");
	EXPECT_TRUE(String("a").concat("") == "a");
	EXPECT_TRUE(String("ab").concat('c') == "abc");
	EXPECT_TRUE(String("ab").concat("cde") == "abcde");
	EXPECT_TRUE(s.concat("abc").concat(s).concat("") == "abc");
}
TEST(GivenStringTests, Substring) {
	String s("abcd");
	EXPECT_TRUE(s.subString(0, 2) == "ab");
	EXPECT_TRUE(s.subString(1, 3) == "bc");
	EXPECT_TRUE(s.subString(2, 4) == "cd");
	EXPECT_TRUE(s.subString(3, 5) == "d");
	EXPECT_TRUE(s.subString(0, -1) == s);

	EXPECT_TRUE(s.subString(2, 2) == "");
	EXPECT_TRUE(s.subString(4, 5) == "");
	EXPECT_TRUE(s.subString(3, 0) == "");
	EXPECT_TRUE(String().subString(0, 1) == "");

	String s2 = s.subString(2, 4);
	EXPECT_TRUE(s2.charAt(0) == 'c');
}
TEST(GivenStringTests, valueOf) {
	EXPECT_TRUE(String::valueOf(0) == "0");
	EXPECT_TRUE(String::valueOf(10) == "10");
	EXPECT_TRUE(String::valueOf(999) == "999");
	EXPECT_TRUE(String::valueOf(-0) == "0");
	EXPECT_TRUE(String::valueOf(-10) == "-10");
	EXPECT_TRUE(String::valueOf(-999) == "-999");
}
/* end of given tests */

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

	//String s = String("ab").concat("cd").concat("ef");
	//std::cout << s << std::endl;

	//String s = String("foo").subString(1,2);
	//std::cout << s << std::endl;
}
