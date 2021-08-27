#ifndef FT_STACK_HPP
#define FT_STACK_HPP
#include <memory>
#include "vector.hpp"
namespace ft
{
	template <class T, class Container = ft::vector<T> > class stack
	{
    public:
		//Member types
		typedef Container container_type;
		typedef typename container_type::value_type value_type;
		typedef size_t size_type;

    container_type c;

		// constructor
		stack (const container_type& ctnr = container_type())
		{
      c = ctnr;
		}

		// empty
		bool empty() const
		{
      return c.empty();
		}

		// size
		size_type size() const
		{
      return c.size();
		}

		// top
		value_type& top()
		{
      return c.back();
		}
		const value_type& top() const
		{
      return c.back();
		}

		// push
		void push (const value_type& val)
		{
      c.push_back(val);
		}

		// pop
		void pop()
		{
      c.pop_back();
		}

	};
  // operators
  template <class T, class Container>
  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs.c == rhs.c;
  }
  template <class T, class Container>
  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs.c != rhs.c;
  }
  template <class T, class Container>
  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs.c < rhs.c;
  }
  template <class T, class Container>
  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs.c <= rhs.c;
  }
  template <class T, class Container>
  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs.c > rhs.c;
  }
  template <class T, class Container>
  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs.c >= rhs.c;
  }
} // namespace ft

#endif //STACK_HPP
