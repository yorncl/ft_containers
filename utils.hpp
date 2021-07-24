#if !defined(UTILS_HPP)
#define UTILS_HPP

#include <iostream>
#include <iterator>
#include <cstring>
#include <unistd.h>

namespace ft
{
	template<bool B, class T = void>
	struct enable_oof {};

	template<class T>
	struct enable_oof<true, T> { typedef T type; };

	#define REQUIRE_ITER(T) typename ft::enable_oof<!std::numeric_limits<T>::is_integer, T>::type * = NULL

	template<typename T>
	bool isEqual(T& a, T&b) {return a == b;};
	template<typename T>
	bool isSup(T& a, T&b) {return a <= b;};
}

#endif // UTILS_HPP
