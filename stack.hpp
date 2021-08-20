#ifndef FT_STACK_HPP
#define FT_STACK_HPP
#include <memory>
#include "vector.hpp"
namespace ft
{
	template <class T, class Container = ft::vector<T> > class stack
	{
		private:
		//Member types
		typedef Container container_type;
		typedef typename container_type::value_type value_type;
		typedef size_t size_type;
		public:

    container_type _ctnr;

		// constructor
		stack (const container_type& ctnr = container_type())
		{
      _ctnr = ctnr;
		}

		// empty
		bool empty() const
		{
      return _ctnr.empty();
		}

		// size
		size_type size() const
		{
      return _ctnr.size();
		}

		// top
		value_type& top()
		{
      return _ctnr.back();
		}
		const value_type& top() const
		{
      return _ctnr.back();
		}

		// push
		void push (const value_type& val)
		{
      _ctnr.push_back(val);
		}

		// pop
		void pop()
		{
      _ctnr.pop_back();
		}

	};
  // operators
  template <class T, class Container>
  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs._ctnr == rhs._ctnr;
  }
  template <class T, class Container>
  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs._ctnr != rhs._ctnr;
  }
  template <class T, class Container>
  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs._ctnr < rhs._ctnr;
  }
  template <class T, class Container>
  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs._ctnr <= rhs._ctnr;
  }
  template <class T, class Container>
  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs._ctnr > rhs._ctnr;
  }
  template <class T, class Container>
  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  {
    return lhs._ctnr >= rhs._ctnr;
  }
} // namespace ft

#endif //STACK_HPP
