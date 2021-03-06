#include <gtest/gtest.h>

#include "ztl/pack.h"
#include "ztl/runtime.h"

#include <tuple>
#include <type_traits>

using namespace ZTL;

typedef std::tuple<float, double, int, double> my_tuple;

TEST(PackTest, ArgumentPackAccess) {

	ASSERT_TRUE((std::is_same<float,  typename get<0, my_tuple>::type>::value));
	ASSERT_TRUE((std::is_same<double, typename get<1, my_tuple>::type>::value));
	ASSERT_TRUE((std::is_same<int,    typename get<2, my_tuple>::type>::value));
	ASSERT_TRUE((std::is_same<double, typename get<3, my_tuple>::type>::value));

	ASSERT_EQ(4, arg<0>(4,5.3));
	ASSERT_EQ(5.3, arg<1>(4,5.3));

	ASSERT_EQ(4u, (size<my_tuple>::value));
}

TEST(PackTest, Copying) {

	ASSERT_TRUE((std::is_same<typename copy<my_tuple, std::tuple>::type, my_tuple>::value));

	ASSERT_TRUE((std::is_same<typename copy_n<std::tuple<float, double, int, double, char>, std::tuple, 4>::type, my_tuple>::value));
}

TEST(PackTest, ArgumentPackManipulation) {

	// pop_front
	ASSERT_TRUE((std::is_same<
					 my_tuple,
					 typename pop_front<std::tuple<char, float, double, int, double>>::type
				 >::value));

	ASSERT_TRUE((std::is_same<
					 std::tuple<>,
					 typename pop_front<std::tuple<char, float, double, int, double>, 5>::type
				 >::value));

	ASSERT_TRUE((std::is_same<my_tuple, typename pop_front<my_tuple, 0>::type>::value));

	// pop_back
	ASSERT_TRUE((std::is_same<
					 my_tuple,
					 typename pop_back<std::tuple<float, double, int, double, char>>::type
				 >::value));

	ASSERT_TRUE((std::is_same<
					 std::tuple<>,
					 typename pop_back<std::tuple<char, float, double, int, double>, 5>::type
				 >::value));

	// push_front
	ASSERT_TRUE((std::is_same<
					 my_tuple,
					 typename push_front<std::tuple<double, int, double>, float>::type
				 >::value));

	ASSERT_TRUE((std::is_same<
					 my_tuple,
					 typename push_front<std::tuple<float, double, int, double>>::type
				 >::value));

	ASSERT_TRUE((std::is_same<
					 my_tuple,
					 typename push_front<std::tuple<>, float, double, int, double>::type
				 >::value));

	// push_back
	ASSERT_TRUE((std::is_same<
					 my_tuple,
					 typename push_back<std::tuple<float, double>, int, double>::type
				 >::value));

	ASSERT_TRUE((std::is_same<
					 my_tuple,
					 typename push_back<std::tuple<float, double, int, double>>::type
				 >::value));

	ASSERT_TRUE((std::is_same<
					 my_tuple,
					 typename push_back<std::tuple<>, float, double, int, double>::type
				 >::value));
}

TEST(PackTest, Merge) {
	ASSERT_TRUE((std::is_same<
					 typename merge< std::tuple<float, double>,
						 std::tuple<int, double> >::type,
					 my_tuple
				 >::value));
}

TEST(PackTest, Shifting) {
	ASSERT_TRUE((std::is_same<
					 typename shift_left<my_tuple>::type,
					 std::tuple<double, int, double, float>
				 >::value));

	ASSERT_TRUE((std::is_same<
					 typename shift_left<my_tuple, 3>::type,
					 std::tuple<double, float, double, int>
				 >::value));

	ASSERT_TRUE((std::is_same<typename shift_left<my_tuple, 4>::type, my_tuple>::value));

	ASSERT_TRUE((std::is_same<typename shift_left<my_tuple, 0>::type, my_tuple>::value));

	ASSERT_TRUE((std::is_same<
					 typename shift_right<my_tuple, 2>::type,
					 std::tuple<int, double, float, double>
				 >::value));

	ASSERT_TRUE((std::is_same<typename shift_right<my_tuple, 4>::type, my_tuple>::value));

	ASSERT_TRUE((std::is_same<typename shift_right<my_tuple, 0>::type, my_tuple>::value));
}

TEST(PackTest, Find) {

	ASSERT_EQ( 2, ((find<int, my_tuple>::value)));
	ASSERT_EQ(-1, ((find<char, my_tuple>::value)));
}


template<typename Anytype>
struct apply_t
{
	typedef bool type;
};

TEST(PackTest, Apply) {
	ASSERT_TRUE((std::is_same<std::tuple<bool,bool,bool,bool>, typename Apply<apply_t, my_tuple>::type>::value));
}

TEST(PackTest, ForEach) {

	int const N = 5;
	int ar[N];
	std::function<int (float, int*&)> f =
		[](float x, int*& pos) -> float { *pos = x+2; ++pos; return x+2; };
	std::function<int (float)> f0 = std::bind(f, std::placeholders::_1, ar);

	for_each(f0, 0, 1, 2, 3, 4);
	for (int ii = 0; ii< N; ++ii) {
		ASSERT_EQ(f0(ii), ar[ii]);
	}
}

TEST(PackTest, Range) {
	typedef range<0> range0_t;
	typedef range<1> range1_t;
	ASSERT_EQ(0u, (size<typename range0_t::type>::value));
	ASSERT_EQ(1u, (size<typename range1_t::type>::value));
	ASSERT_EQ(0,  (get<0, typename range1_t::type>::type::value));

	typedef range<20, 0, 2> range_t;
	ASSERT_EQ( 0, (get<0, typename range_t::type>::type::value));
	ASSERT_EQ( 2, (get<1, typename range_t::type>::type::value));
	ASSERT_EQ(18, (get<9, typename range_t::type>::type::value));
	ASSERT_EQ(10u, (size<typename range_t::type>::value));


	//typedef range_c<20, 0, 2> rangec_t;
	//ASSERT_EQ( 0, (get_c<0, typename rangec_t::type>::value));
	//ASSERT_EQ(18, (get_c<9, typename rangec_t::type>::value));
}
