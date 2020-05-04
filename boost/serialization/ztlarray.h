#pragma once

// Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <boost/array.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/boost_array.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>

#include "ztl/array.h"

namespace boost {
namespace serialization {

// ArrayInterface serializer
template<typename Archiver, template<typename, size_t, size_t, typename...> class Class,
	typename T, size_t N, typename ... Args>
void serialize(Archiver& ar, ZTL::ArrayInterface<Class<T, N, 0, Args...>, N>& s,
	unsigned int const)
{
	using namespace boost::serialization;
	ar & make_nvp("data", reinterpret_cast<boost::array<T, N>&>(s));
}

template<typename Archiver, template<typename, size_t, size_t, typename...> class Class,
	typename T, typename ... Args>
void serialize(Archiver&, ZTL::ArrayInterface<Class<T, 0, 0, Args...>, 0>&,
	unsigned int const)
{
}

} // namespace serialization
} // namespace boost
