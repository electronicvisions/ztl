#include <gtest/gtest.h>

#include <boost/archive/text_oarchive.hpp>
#include <sstream>
#include <array>

#include "../include/array.h"

using namespace ZTL;


struct Dummy
{
	constexpr Dummy(int i) : value(i) {}
	int value;
};

struct DummyWithDefault
{
	constexpr DummyWithDefault(int i) : value(i) {}
	constexpr DummyWithDefault() : DummyWithDefault(-1) {}
	int value;
};

struct DummyTwoArgs
{
	int i, j;
	constexpr DummyTwoArgs(int i, int j) : i(i), j(j) {}
};

// Testing the StandardArray
TEST(StandardArrayTest, BasicCheck) {
	typedef Array<Dummy, 11> array_type_a;

	// non-const array check
	array_type_a a(42);
	for (int ii=0; ii<10; ++ii) {
		a[ii].value = ii;
		ASSERT_EQ(ii, a[ii].value);
	}
	ASSERT_EQ(42, a[10].value);

	//const array check
	typedef Array<Dummy const, 11> array_type_b;
	constexpr array_type_b b(42);
	for (int ii=0; ii<11; ++ii) {
		ASSERT_EQ(42, b[ii].value);
	}

	Array<char, 10> q;
	Array<char const, 10> r;
	Array<char, 10> const s;
	Array<char const, 10> const t;
}


TEST(StandardArrayTest, Constructors) {
	// default constructor
	Array<int, 100> a;
	for (int ii=0; ii<100; ++ii) {
		ASSERT_EQ(a[ii], 0);
	}

	// copy constructor
	Array<Dummy, 100> b(0);

	for (int ii=0; ii<100; ++ii) {
		b[ii].value = ii;
		ASSERT_EQ(ii, b[ii].value);
	}

	Array<Dummy, 100> c(b);
	for (int ii=0; ii<100; ++ii) {
		ASSERT_EQ(b[ii].value, c[ii].value);
	}
}


TEST(StandardArrayTest, Comparisons) {
	Array<int, 10> m(1);
	Array<int, 10> n(1);
	Array<int, 10> o(2);

	ASSERT_TRUE(m==n);
	ASSERT_TRUE(m<=n);
	ASSERT_TRUE(m>=n);
	ASSERT_TRUE(m!=o);
	ASSERT_TRUE(m<=o);
	ASSERT_TRUE(m<o);
	ASSERT_TRUE(o>m);
}


TEST(StandardArrayTest, Padding) {
	ASSERT_EQ(1+1, sizeof(Array<char, 1>));
	ASSERT_EQ(1, sizeof(Array<char, 0>));
}


TEST(StandardArrayTest, ZeroSizeArray) {
	Array<char, 0> zero_size;
}


TEST(StandardArrayTest, Serialization) {
	Array<int, 42> to_serialize;
	std::stringstream ss;
	boost::archive::text_oarchive oa(ss);
	oa << to_serialize;

	ASSERT_TRUE(ss.str().size());
}


TEST(StandardArrayTest, InitializerList) {
	int const N = 5;
	Array<int, N>      il1 = {0, 1, 2, 3, 4};
	for (int ii=0; ii<N; ++ii) {
	  ASSERT_EQ(ii, il1[ii]);
	}
}


TEST(StandardArrayTest, Conversion) {
	int const N = 5;
	std::array<int, N> in0 = {{0, 1, 2, 3, 4}};
	Array<int, N>      in1(in0);

	Array<Dummy, N> conv0(in0);
	Array<Dummy, N> conv1(in1);

	for (int ii=0; ii<N; ++ii) {
	  ASSERT_EQ(ii, conv0[ii].value);
	  ASSERT_EQ(ii, conv1[ii].value);
	}
}



// Testing the RecursiveArray
TEST(RecursiveArrayTest, BasicCheck) {

	// non-const array check
	ArrayA<int, 11> a(ArrayA<int, 0>(), 42);
	ASSERT_EQ(42, a[0]);

	ArrayA<int, 1> b = {1};
	ASSERT_EQ(1, b[0]);
	ArrayA<int, 5> c(b, 1,1,1,1);
	for (int ii=0; ii<5; ++ii) {
		ASSERT_EQ(1, c[ii]);
	}

	//const array check
	ArrayA<int const, 10> d = {0,1,2,3,4,5,6,7,8,9};
	for (int ii=0; ii<10; ++ii) {
		ASSERT_EQ(ii, d[ii]);
	}

	ArrayA<char, 10> q;
	ArrayA<char const, 10> r;
	ArrayA<char, 10> const s;
	ArrayA<char const, 10> const t;
}


TEST(RecursiveArrayTest, InitializerList) {
	int const N = 5;
	ArrayA<int, N> il1 = {0, 1, 2, 3, 4};
	for (int ii=0; ii<N; ++ii) {
		ASSERT_EQ(ii, il1[ii]);
	}
}


TEST(RecursiveArrayTest, Constructors) {
	// default
	ArrayA<DummyWithDefault, 100> dc;
	for (int ii=0; ii<100; ++ii) {
		ASSERT_EQ(-1, dc[ii].value);
	}

	// copy
	ArrayA<double, 10> ccs = {0,1,2,3,4,5,6,7,8,9};
	ArrayA<double, 10> cct(ccs);
	for (int ii=0; ii<10; ++ii) {
		ASSERT_EQ(ii, cct[ii]);
	}
}


TEST(RecursiveArrayTest, Serialization) {
	ArrayA<int, 42> to_serialize;
	std::stringstream ss;
	boost::archive::text_oarchive oa(ss);
	oa << to_serialize;
	ASSERT_TRUE(ss.str().size());
}



// Testing the EnumArray
TEST(EnumArrayTest, BasicCheck) {
	ArrayE<int, 10> a;
	for (int ii=0; ii<10; ++ii) {
		ASSERT_EQ(ii, a[ii]);
		ASSERT_EQ(ii, a[ii]);
	}

	ArrayE<DummyTwoArgs, 10> q(42);
	ArrayE<DummyTwoArgs const, 10> r(42);
	ArrayE<DummyTwoArgs, 10> const s(42);
	ArrayE<DummyTwoArgs const, 10> const t(42);
}

TEST(EnumArrayTest, Serialization) {
	ArrayE<int, 42> to_serialize;
	std::stringstream ss;
	boost::archive::text_oarchive oa(ss);
	oa << to_serialize;
	ASSERT_TRUE(ss.str().size());
}
