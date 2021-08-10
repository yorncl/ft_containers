#ifndef FT_MAP_HPP
#define FT_MAP_HPP
#include <memory>
#include "utils.hpp"
#include <map>
std::map<string, int> stdmap;

namespace ft
{


	template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
           > class map
	{
		private:
		//Member types
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type>;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		/* typedef value_type const_pointer; */
		typedef T iterator;
		typedef T const_iterator;
		typedef T reverse_iterator;
		typedef T const_reverse_iterator;
		typedef ft::iterator_traits<iterator>::difference_type difference_type;
		typedef difference_type size_type;
		public:

		// constructor
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			(void) comp;
			(void) alloc;
		}
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			(void) first;
			(void) last;
			(void) comp;
			(void) alloc;
		}
		map (const map& x)
		{
			(void) x;
		}

		// ~map
		~map()
		{
		}

		// operator=
		map& operator= (const map& x)
		{
			(void) x;
		}

		// begin
		iterator begin()
		{
		}
		const_iterator begin() const
		{
		}

		// end
		iterator end()
		{
		}
		const_iterator end() const
		{
		}

		// rbegin
		reverse_iterator rbegin()
		{
		}
		const_reverse_iterator rbegin() const
		{
		}

		// rend
		reverse_iterator rend()
		{
		}
		const_reverse_iterator rend() const
		{
		}

		// empty
		bool empty() const
		{
		}

		// size
		size_type size() const
		{
		}

		// max_size
		size_type max_size() const
		{
		}

		// operator[]
		mapped_type& operator[] (const key_type& k)
		{
			(void) k;
		}

		// insert
		pair<iterator,bool> insert (const value_type& val)
		{
			(void) val;
		}
		iterator insert (iterator position, const value_type& val)
		{
			(void) position;
			(void) val;
		}
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			(void) first;
			(void) last;
		}

		// erase
		void erase (iterator position)
		{
			(void) position;
		}
		size_type erase (const key_type& k)
		{
			(void) k;
		}
		void erase (iterator first, iterator last)
		{
			(void) first;
			(void) last;
		}

		// swap
		void swap (map& x)
		{
			(void) x;
		}

		// clear
		void clear()
		{
		}

		// key_comp
		key_compare key_comp() const
		{
		}

		// value_comp
		value_compare value_comp() const
		{
		}

		// find
		iterator find (const key_type& k)
		{
			(void) k;
		}
		const_iterator find (const key_type& k) const
		{
			(void) k;
		}

		// count
		size_type count (const key_type& k) const
		{
			(void) k;
		}

		// lower_bound
		iterator lower_bound (const key_type& k)
		{
			(void) k;
		}
		const_iterator lower_bound (const key_type& k) const
		{
			(void) k;
		}

		// upper_bound
		iterator upper_bound (const key_type& k)
		{
			(void) k;
		}
		const_iterator upper_bound (const key_type& k) const
		{
			(void) k;
		}

		// equal_range
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			(void) k;
		}
		pair<iterator,iterator>             equal_range (const key_type& k)
		{
			(void) k;
		}
	};


  // Comparison member
  template <class Key, class T, class Compare, class Alloc>
  class map<Key,T,Compare,Alloc>::value_compare
  {
    friend class map;
  protected:
    Compare comp;
    value_compare (Compare c) : comp(c) {}
  public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator() (const value_type& x, const value_type& y) const
    {
      return comp(x.first, y.first);
    }
  }
};

#endif //MAP_HPP
