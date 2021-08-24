#if !defined(UTILS_HPP)
#define UTILS_HPP

#include <iostream>
#include <iterator>
#include <cstring>
#include <unistd.h>

namespace ft
{
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };
  

  template<class T, T v>
  struct integral_constant {
      static const T value = v;
      typedef T value_type;
      typedef integral_constant type;
      /* const operator value_type() const noexcept { return value; } */
      /* const value_type operator()() const noexcept { return value; } //since c++14 */
  };

  typedef ft::integral_constant<bool, true> true_type;
  typedef ft::integral_constant<bool, false> false_type;

  template<class T, class U> struct is_same : ft::false_type {};
  template<class T> struct is_same<T, T> : ft::true_type {};

  template<class T> struct is_integral_base : ft::false_type {}; 
  template<> struct is_integral_base<bool> : ft::true_type {}; 
  template<> struct is_integral_base<int> : ft::true_type {}; 
  template<> struct is_integral_base<long> : ft::true_type {}; 
  template<> struct is_integral_base<short> : ft::true_type {}; 
  template<> struct is_integral_base<long long> : ft::true_type {}; 
  template<> struct is_integral_base<char> : ft::true_type {}; 
  /* template<> struct is_integral_base<char16_t> : ft::true_type {};  */
  /* template<> struct is_integral_base<char32_t> : ft::true_type {};  */
  template<> struct is_integral_base<wchar_t> : ft::true_type {}; 

  template<class T> struct is_integral : ft::is_integral_base<T> {};

  
  //Iterator traits

  /* struct input_iterator {}; */
  /* struct output_iterator_tag {}; */
  /* struct forward_iterator_tag {}; */
  /* struct bidirectional_iterator_tag {}; */
  /* struct random_access_iterator_tag {}; */

  // Base struct
  template <class Iterator>
  struct iterator_traits
  {
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
  };

  //Specialization for T* (array-like)
  template <class T>
  struct iterator_traits<T*>
  {
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;
  };

  //Specialization for const T*
  template <class T>
  struct iterator_traits<const T*>
  {
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef std::random_access_iterator_tag iterator_category;
  };

	#define REQUIRE_ITER(T) typename ft::enable_if< !ft::is_integral<T>::value, T>::type * = NULL
  //Pairs

  template<class T1, class T2>
  struct pair
  {
    pair()
    {
      first = T1();
      second = T2();
    }
    pair(T1 f, T2 s) : first(f), second(s)
    {
    }
    template <class U, class V>
    pair(const pair<U, V>& p) : first(p.first), second(p.second)
    {

    }
    struct pair<T1, T2>& operator=(struct pair<T1, T2> p)
    {
      first = p.first;
      second = p.second;
      return *this;
    }
    T1 first;
    T2 second;
    typedef T1 first_type;
    typedef T2 second_type;
  };
  template <class T1, class T2>
  struct pair<T1, T2> make_pair(T1 first, T2 second)
  {
    struct pair<T1, T2> pair(first, second);
    return pair;
  }

  template <class T1, class T2>
  bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
  { return lhs.first==rhs.first && lhs.second==rhs.second; }

  template <class T1, class T2>
  bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
  { return !(lhs==rhs); }

  template <class T1, class T2>
  bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
  { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

  template <class T1, class T2>
  bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
  { return !(rhs<lhs); }

  template <class T1, class T2>
  bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
  { return rhs<lhs; }

  template <class T1, class T2>
  bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
  { return !(lhs<rhs); }


  template <class InputIterator1, class InputIterator2>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
{
  while (first1!=last1)
  {
    if (first2==last2 || *first2<*first1) return false;
    else if (*first1<*first2) return true;
    ++first1; ++first2;
  }
  return (first2!=last2);
}

  template < class InputIterator >
  size_t itlen(InputIterator first, InputIterator last, REQUIRE_ITER(InputIterator))
  {
    size_t n = 0;
    while (first != last)
    {
      first++;
      n++;
    }
    return n;
  }

	template<typename T>
	bool isEqual(T& a, T&b) {return a == b;};
	template<typename T>
	bool isSup(T& a, T&b) {return a <= b;};
} // namespace ft

#endif // UTILS_HPP
